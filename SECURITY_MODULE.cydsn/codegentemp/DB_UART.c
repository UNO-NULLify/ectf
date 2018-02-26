/***************************************************************************//**
* \file DB_UART.c
* \version 3.20
*
* \brief
*  This file provides the source code to the API for the SCB Component.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DB_UART_PVT.h"

#if (DB_UART_SCB_MODE_I2C_INC)
    #include "DB_UART_I2C_PVT.h"
#endif /* (DB_UART_SCB_MODE_I2C_INC) */

#if (DB_UART_SCB_MODE_EZI2C_INC)
    #include "DB_UART_EZI2C_PVT.h"
#endif /* (DB_UART_SCB_MODE_EZI2C_INC) */

#if (DB_UART_SCB_MODE_SPI_INC || DB_UART_SCB_MODE_UART_INC)
    #include "DB_UART_SPI_UART_PVT.h"
#endif /* (DB_UART_SCB_MODE_SPI_INC || DB_UART_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 DB_UART_scbMode = DB_UART_SCB_MODE_UNCONFIG;
    uint8 DB_UART_scbEnableWake;
    uint8 DB_UART_scbEnableIntr;

    /* I2C configuration variables */
    uint8 DB_UART_mode;
    uint8 DB_UART_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * DB_UART_rxBuffer;
    uint8  DB_UART_rxDataBits;
    uint32 DB_UART_rxBufferSize;

    volatile uint8 * DB_UART_txBuffer;
    uint8  DB_UART_txDataBits;
    uint32 DB_UART_txBufferSize;

    /* EZI2C configuration variables */
    uint8 DB_UART_numberOfAddr;
    uint8 DB_UART_subAddrSize;
#endif /* (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** DB_UART_initVar indicates whether the DB_UART 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the DB_UART_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  DB_UART_Init() function can be called before the 
*  DB_UART_Start() or DB_UART_Enable() function.
*/
uint8 DB_UART_initVar = 0u;


#if (! (DB_UART_SCB_MODE_I2C_CONST_CFG || \
        DB_UART_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * DB_UART_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent DB_UART_Enable() call.
    */
    uint16 DB_UART_IntrTxMask = 0u;
#endif /* (! (DB_UART_SCB_MODE_I2C_CONST_CFG || \
              DB_UART_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (DB_UART_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_DB_UART_CUSTOM_INTR_HANDLER)
    void (*DB_UART_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_DB_UART_CUSTOM_INTR_HANDLER) */
#endif /* (DB_UART_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void DB_UART_ScbEnableIntr(void);
static void DB_UART_ScbModeStop(void);
static void DB_UART_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: DB_UART_Init
****************************************************************************//**
*
*  Initializes the DB_UART component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  DB_UART_I2CInit, DB_UART_SpiInit, 
*  DB_UART_UartInit or DB_UART_EzI2CInit.
*
*******************************************************************************/
void DB_UART_Init(void)
{
#if (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    if (DB_UART_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        DB_UART_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (DB_UART_SCB_MODE_I2C_CONST_CFG)
    DB_UART_I2CInit();

#elif (DB_UART_SCB_MODE_SPI_CONST_CFG)
    DB_UART_SpiInit();

#elif (DB_UART_SCB_MODE_UART_CONST_CFG)
    DB_UART_UartInit();

#elif (DB_UART_SCB_MODE_EZI2C_CONST_CFG)
    DB_UART_EzI2CInit();

#endif /* (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: DB_UART_Enable
****************************************************************************//**
*
*  Enables DB_UART component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  DB_UART_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The DB_UART configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured DB_UART”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void DB_UART_Enable(void)
{
#if (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!DB_UART_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        DB_UART_CTRL_REG |= DB_UART_CTRL_ENABLED;

        DB_UART_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        DB_UART_ScbModePostEnable();
    }
#else
    DB_UART_CTRL_REG |= DB_UART_CTRL_ENABLED;

    DB_UART_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    DB_UART_ScbModePostEnable();
#endif /* (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: DB_UART_Start
****************************************************************************//**
*
*  Invokes DB_UART_Init() and DB_UART_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  DB_UART_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void DB_UART_Start(void)
{
    if (0u == DB_UART_initVar)
    {
        DB_UART_Init();
        DB_UART_initVar = 1u; /* Component was initialized */
    }

    DB_UART_Enable();
}


/*******************************************************************************
* Function Name: DB_UART_Stop
****************************************************************************//**
*
*  Disables the DB_UART component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function DB_UART_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void DB_UART_Stop(void)
{
#if (DB_UART_SCB_IRQ_INTERNAL)
    DB_UART_DisableInt();
#endif /* (DB_UART_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    DB_UART_ScbModeStop();

    /* Disable SCB IP */
    DB_UART_CTRL_REG &= (uint32) ~DB_UART_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    DB_UART_SetTxInterruptMode(DB_UART_NO_INTR_SOURCES);

#if (DB_UART_SCB_IRQ_INTERNAL)
    DB_UART_ClearPendingInt();
#endif /* (DB_UART_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: DB_UART_SetRxFifoLevel
****************************************************************************//**
*
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
*  \param level: Level in the RX FIFO to generate RX level interrupt.
*   The range of valid level values is between 0 and RX FIFO depth - 1.
*
*******************************************************************************/
void DB_UART_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = DB_UART_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~DB_UART_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (DB_UART_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    DB_UART_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: DB_UART_SetTxFifoLevel
****************************************************************************//**
*
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has less entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
*  \param level: Level in the TX FIFO to generate TX level interrupt.
*   The range of valid level values is between 0 and TX FIFO depth - 1.
*
*******************************************************************************/
void DB_UART_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = DB_UART_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~DB_UART_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (DB_UART_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    DB_UART_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (DB_UART_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: DB_UART_SetCustomInterruptHandler
    ****************************************************************************//**
    *
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    *  \param func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    *******************************************************************************/
    void DB_UART_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_DB_UART_CUSTOM_INTR_HANDLER)
        DB_UART_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_DB_UART_CUSTOM_INTR_HANDLER) */
    }
#endif /* (DB_UART_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: DB_UART_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void DB_UART_ScbEnableIntr(void)
{
#if (DB_UART_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != DB_UART_scbEnableIntr)
        {
            DB_UART_EnableInt();
        }

    #else
        DB_UART_EnableInt();

    #endif /* (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (DB_UART_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: DB_UART_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void DB_UART_ScbModePostEnable(void)
{
#if (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!DB_UART_CY_SCBIP_V1)
    if (DB_UART_SCB_MODE_SPI_RUNTM_CFG)
    {
        DB_UART_SpiPostEnable();
    }
    else if (DB_UART_SCB_MODE_UART_RUNTM_CFG)
    {
        DB_UART_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!DB_UART_CY_SCBIP_V1) */

#elif (DB_UART_SCB_MODE_SPI_CONST_CFG)
    DB_UART_SpiPostEnable();

#elif (DB_UART_SCB_MODE_UART_CONST_CFG)
    DB_UART_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: DB_UART_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void DB_UART_ScbModeStop(void)
{
#if (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    if (DB_UART_SCB_MODE_I2C_RUNTM_CFG)
    {
        DB_UART_I2CStop();
    }
    else if (DB_UART_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        DB_UART_EzI2CStop();
    }
#if (!DB_UART_CY_SCBIP_V1)
    else if (DB_UART_SCB_MODE_SPI_RUNTM_CFG)
    {
        DB_UART_SpiStop();
    }
    else if (DB_UART_SCB_MODE_UART_RUNTM_CFG)
    {
        DB_UART_UartStop();
    }
#endif /* (!DB_UART_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (DB_UART_SCB_MODE_I2C_CONST_CFG)
    DB_UART_I2CStop();

#elif (DB_UART_SCB_MODE_EZI2C_CONST_CFG)
    DB_UART_EzI2CStop();

#elif (DB_UART_SCB_MODE_SPI_CONST_CFG)
    DB_UART_SpiStop();

#elif (DB_UART_SCB_MODE_UART_CONST_CFG)
    DB_UART_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: DB_UART_SetPins
    ****************************************************************************//**
    *
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    *  \param mode:      Mode of SCB operation.
    *  \param subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  \param uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    *******************************************************************************/
    void DB_UART_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[DB_UART_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!DB_UART_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!DB_UART_CY_SCBIP_V1) */
        
        uint32 hsiomSel[DB_UART_SCB_PINS_NUMBER] = 
        {
            DB_UART_RX_SCL_MOSI_HSIOM_SEL_GPIO,
            DB_UART_TX_SDA_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (DB_UART_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (DB_UART_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < DB_UART_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = DB_UART_PIN_DM_ALG_HIZ;
        }

        if ((DB_UART_SCB_MODE_I2C   == mode) ||
            (DB_UART_SCB_MODE_EZI2C == mode))
        {
        #if (DB_UART_RX_SCL_MOSI_PIN)
            hsiomSel[DB_UART_RX_SCL_MOSI_PIN_INDEX] = DB_UART_RX_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [DB_UART_RX_SCL_MOSI_PIN_INDEX] = DB_UART_PIN_DM_OD_LO;
        #elif (DB_UART_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[DB_UART_RX_WAKE_SCL_MOSI_PIN_INDEX] = DB_UART_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [DB_UART_RX_WAKE_SCL_MOSI_PIN_INDEX] = DB_UART_PIN_DM_OD_LO;
        #else
        #endif /* (DB_UART_RX_SCL_MOSI_PIN) */
        
        #if (DB_UART_TX_SDA_MISO_PIN)
            hsiomSel[DB_UART_TX_SDA_MISO_PIN_INDEX] = DB_UART_TX_SDA_MISO_HSIOM_SEL_I2C;
            pinsDm  [DB_UART_TX_SDA_MISO_PIN_INDEX] = DB_UART_PIN_DM_OD_LO;
        #endif /* (DB_UART_TX_SDA_MISO_PIN) */
        }
    #if (!DB_UART_CY_SCBIP_V1)
        else if (DB_UART_SCB_MODE_SPI == mode)
        {
        #if (DB_UART_RX_SCL_MOSI_PIN)
            hsiomSel[DB_UART_RX_SCL_MOSI_PIN_INDEX] = DB_UART_RX_SCL_MOSI_HSIOM_SEL_SPI;
        #elif (DB_UART_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[DB_UART_RX_WAKE_SCL_MOSI_PIN_INDEX] = DB_UART_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (DB_UART_RX_SCL_MOSI_PIN) */
        
        #if (DB_UART_TX_SDA_MISO_PIN)
            hsiomSel[DB_UART_TX_SDA_MISO_PIN_INDEX] = DB_UART_TX_SDA_MISO_HSIOM_SEL_SPI;
        #endif /* (DB_UART_TX_SDA_MISO_PIN) */
        
        #if (DB_UART_SCLK_PIN)
            hsiomSel[DB_UART_SCLK_PIN_INDEX] = DB_UART_SCLK_HSIOM_SEL_SPI;
        #endif /* (DB_UART_SCLK_PIN) */

            if (DB_UART_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[DB_UART_RX_SCL_MOSI_PIN_INDEX] = DB_UART_PIN_DM_DIG_HIZ;
                pinsDm[DB_UART_TX_SDA_MISO_PIN_INDEX] = DB_UART_PIN_DM_STRONG;
                pinsDm[DB_UART_SCLK_PIN_INDEX] = DB_UART_PIN_DM_DIG_HIZ;

            #if (DB_UART_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[DB_UART_SS0_PIN_INDEX] = DB_UART_SS0_HSIOM_SEL_SPI;
                pinsDm  [DB_UART_SS0_PIN_INDEX] = DB_UART_PIN_DM_DIG_HIZ;
            #endif /* (DB_UART_SS0_PIN) */

            #if (DB_UART_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= DB_UART_TX_SDA_MISO_PIN_MASK;
            #endif /* (DB_UART_TX_SDA_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[DB_UART_RX_SCL_MOSI_PIN_INDEX] = DB_UART_PIN_DM_STRONG;
                pinsDm[DB_UART_TX_SDA_MISO_PIN_INDEX] = DB_UART_PIN_DM_DIG_HIZ;
                pinsDm[DB_UART_SCLK_PIN_INDEX] = DB_UART_PIN_DM_STRONG;

            #if (DB_UART_SS0_PIN)
                hsiomSel [DB_UART_SS0_PIN_INDEX] = DB_UART_SS0_HSIOM_SEL_SPI;
                pinsDm   [DB_UART_SS0_PIN_INDEX] = DB_UART_PIN_DM_STRONG;
                pinsInBuf |= DB_UART_SS0_PIN_MASK;
            #endif /* (DB_UART_SS0_PIN) */

            #if (DB_UART_SS1_PIN)
                hsiomSel [DB_UART_SS1_PIN_INDEX] = DB_UART_SS1_HSIOM_SEL_SPI;
                pinsDm   [DB_UART_SS1_PIN_INDEX] = DB_UART_PIN_DM_STRONG;
                pinsInBuf |= DB_UART_SS1_PIN_MASK;
            #endif /* (DB_UART_SS1_PIN) */

            #if (DB_UART_SS2_PIN)
                hsiomSel [DB_UART_SS2_PIN_INDEX] = DB_UART_SS2_HSIOM_SEL_SPI;
                pinsDm   [DB_UART_SS2_PIN_INDEX] = DB_UART_PIN_DM_STRONG;
                pinsInBuf |= DB_UART_SS2_PIN_MASK;
            #endif /* (DB_UART_SS2_PIN) */

            #if (DB_UART_SS3_PIN)
                hsiomSel [DB_UART_SS3_PIN_INDEX] = DB_UART_SS3_HSIOM_SEL_SPI;
                pinsDm   [DB_UART_SS3_PIN_INDEX] = DB_UART_PIN_DM_STRONG;
                pinsInBuf |= DB_UART_SS3_PIN_MASK;
            #endif /* (DB_UART_SS3_PIN) */

                /* Disable input buffers */
            #if (DB_UART_RX_SCL_MOSI_PIN)
                pinsInBuf |= DB_UART_RX_SCL_MOSI_PIN_MASK;
            #elif (DB_UART_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= DB_UART_RX_WAKE_SCL_MOSI_PIN_MASK;
            #else
            #endif /* (DB_UART_RX_SCL_MOSI_PIN) */

            #if (DB_UART_SCLK_PIN)
                pinsInBuf |= DB_UART_SCLK_PIN_MASK;
            #endif /* (DB_UART_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (DB_UART_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (DB_UART_TX_SDA_MISO_PIN)
                hsiomSel[DB_UART_TX_SDA_MISO_PIN_INDEX] = DB_UART_TX_SDA_MISO_HSIOM_SEL_UART;
                pinsDm  [DB_UART_TX_SDA_MISO_PIN_INDEX] = DB_UART_PIN_DM_OD_LO;
            #endif /* (DB_UART_TX_SDA_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (DB_UART_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (DB_UART_RX_SCL_MOSI_PIN)
                    hsiomSel[DB_UART_RX_SCL_MOSI_PIN_INDEX] = DB_UART_RX_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [DB_UART_RX_SCL_MOSI_PIN_INDEX] = DB_UART_PIN_DM_DIG_HIZ;
                #elif (DB_UART_RX_WAKE_SCL_MOSI_PIN)
                    hsiomSel[DB_UART_RX_WAKE_SCL_MOSI_PIN_INDEX] = DB_UART_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [DB_UART_RX_WAKE_SCL_MOSI_PIN_INDEX] = DB_UART_PIN_DM_DIG_HIZ;
                #else
                #endif /* (DB_UART_RX_SCL_MOSI_PIN) */
                }

                if (0u != (DB_UART_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (DB_UART_TX_SDA_MISO_PIN)
                    hsiomSel[DB_UART_TX_SDA_MISO_PIN_INDEX] = DB_UART_TX_SDA_MISO_HSIOM_SEL_UART;
                    pinsDm  [DB_UART_TX_SDA_MISO_PIN_INDEX] = DB_UART_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= DB_UART_TX_SDA_MISO_PIN_MASK;
                #endif /* (DB_UART_TX_SDA_MISO_PIN) */
                }

            #if !(DB_UART_CY_SCBIP_V0 || DB_UART_CY_SCBIP_V1)
                if (DB_UART_UART_MODE_STD == subMode)
                {
                    if (0u != (DB_UART_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (DB_UART_SCLK_PIN)
                        hsiomSel[DB_UART_SCLK_PIN_INDEX] = DB_UART_SCLK_HSIOM_SEL_UART;
                        pinsDm  [DB_UART_SCLK_PIN_INDEX] = DB_UART_PIN_DM_DIG_HIZ;
                    #endif /* (DB_UART_SCLK_PIN) */
                    }

                    if (0u != (DB_UART_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (DB_UART_SS0_PIN)
                        hsiomSel[DB_UART_SS0_PIN_INDEX] = DB_UART_SS0_HSIOM_SEL_UART;
                        pinsDm  [DB_UART_SS0_PIN_INDEX] = DB_UART_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= DB_UART_SS0_PIN_MASK;
                    #endif /* (DB_UART_SS0_PIN) */
                    }
                }
            #endif /* !(DB_UART_CY_SCBIP_V0 || DB_UART_CY_SCBIP_V1) */
            }
        }
    #endif /* (!DB_UART_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (DB_UART_RX_SCL_MOSI_PIN)
        DB_UART_SET_HSIOM_SEL(DB_UART_RX_SCL_MOSI_HSIOM_REG,
                                       DB_UART_RX_SCL_MOSI_HSIOM_MASK,
                                       DB_UART_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[DB_UART_RX_SCL_MOSI_PIN_INDEX]);

        DB_UART_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[DB_UART_RX_SCL_MOSI_PIN_INDEX]);

        #if (!DB_UART_CY_SCBIP_V1)
            DB_UART_SET_INP_DIS(DB_UART_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                         DB_UART_uart_rx_i2c_scl_spi_mosi_MASK,
                                         (0u != (pinsInBuf & DB_UART_RX_SCL_MOSI_PIN_MASK)));
        #endif /* (!DB_UART_CY_SCBIP_V1) */
    
    #elif (DB_UART_RX_WAKE_SCL_MOSI_PIN)
        DB_UART_SET_HSIOM_SEL(DB_UART_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       DB_UART_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       DB_UART_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[DB_UART_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        DB_UART_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[DB_UART_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        DB_UART_SET_INP_DIS(DB_UART_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     DB_UART_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & DB_UART_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        DB_UART_SET_INCFG_TYPE(DB_UART_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        DB_UART_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        DB_UART_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        DB_UART_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (DB_UART_RX_WAKE_SCL_MOSI_PIN) */

    #if (DB_UART_TX_SDA_MISO_PIN)
        DB_UART_SET_HSIOM_SEL(DB_UART_TX_SDA_MISO_HSIOM_REG,
                                       DB_UART_TX_SDA_MISO_HSIOM_MASK,
                                       DB_UART_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[DB_UART_TX_SDA_MISO_PIN_INDEX]);

        DB_UART_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[DB_UART_TX_SDA_MISO_PIN_INDEX]);

    #if (!DB_UART_CY_SCBIP_V1)
        DB_UART_SET_INP_DIS(DB_UART_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     DB_UART_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & DB_UART_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!DB_UART_CY_SCBIP_V1) */
    #endif /* (DB_UART_RX_SCL_MOSI_PIN) */

    #if (DB_UART_SCLK_PIN)
        DB_UART_SET_HSIOM_SEL(DB_UART_SCLK_HSIOM_REG,
                                       DB_UART_SCLK_HSIOM_MASK,
                                       DB_UART_SCLK_HSIOM_POS,
                                       hsiomSel[DB_UART_SCLK_PIN_INDEX]);

        DB_UART_spi_sclk_SetDriveMode((uint8) pinsDm[DB_UART_SCLK_PIN_INDEX]);

        DB_UART_SET_INP_DIS(DB_UART_spi_sclk_INP_DIS,
                                     DB_UART_spi_sclk_MASK,
                                     (0u != (pinsInBuf & DB_UART_SCLK_PIN_MASK)));
    #endif /* (DB_UART_SCLK_PIN) */

    #if (DB_UART_SS0_PIN)
        DB_UART_SET_HSIOM_SEL(DB_UART_SS0_HSIOM_REG,
                                       DB_UART_SS0_HSIOM_MASK,
                                       DB_UART_SS0_HSIOM_POS,
                                       hsiomSel[DB_UART_SS0_PIN_INDEX]);

        DB_UART_spi_ss0_SetDriveMode((uint8) pinsDm[DB_UART_SS0_PIN_INDEX]);

        DB_UART_SET_INP_DIS(DB_UART_spi_ss0_INP_DIS,
                                     DB_UART_spi_ss0_MASK,
                                     (0u != (pinsInBuf & DB_UART_SS0_PIN_MASK)));
    #endif /* (DB_UART_SS0_PIN) */

    #if (DB_UART_SS1_PIN)
        DB_UART_SET_HSIOM_SEL(DB_UART_SS1_HSIOM_REG,
                                       DB_UART_SS1_HSIOM_MASK,
                                       DB_UART_SS1_HSIOM_POS,
                                       hsiomSel[DB_UART_SS1_PIN_INDEX]);

        DB_UART_spi_ss1_SetDriveMode((uint8) pinsDm[DB_UART_SS1_PIN_INDEX]);

        DB_UART_SET_INP_DIS(DB_UART_spi_ss1_INP_DIS,
                                     DB_UART_spi_ss1_MASK,
                                     (0u != (pinsInBuf & DB_UART_SS1_PIN_MASK)));
    #endif /* (DB_UART_SS1_PIN) */

    #if (DB_UART_SS2_PIN)
        DB_UART_SET_HSIOM_SEL(DB_UART_SS2_HSIOM_REG,
                                       DB_UART_SS2_HSIOM_MASK,
                                       DB_UART_SS2_HSIOM_POS,
                                       hsiomSel[DB_UART_SS2_PIN_INDEX]);

        DB_UART_spi_ss2_SetDriveMode((uint8) pinsDm[DB_UART_SS2_PIN_INDEX]);

        DB_UART_SET_INP_DIS(DB_UART_spi_ss2_INP_DIS,
                                     DB_UART_spi_ss2_MASK,
                                     (0u != (pinsInBuf & DB_UART_SS2_PIN_MASK)));
    #endif /* (DB_UART_SS2_PIN) */

    #if (DB_UART_SS3_PIN)
        DB_UART_SET_HSIOM_SEL(DB_UART_SS3_HSIOM_REG,
                                       DB_UART_SS3_HSIOM_MASK,
                                       DB_UART_SS3_HSIOM_POS,
                                       hsiomSel[DB_UART_SS3_PIN_INDEX]);

        DB_UART_spi_ss3_SetDriveMode((uint8) pinsDm[DB_UART_SS3_PIN_INDEX]);

        DB_UART_SET_INP_DIS(DB_UART_spi_ss3_INP_DIS,
                                     DB_UART_spi_ss3_MASK,
                                     (0u != (pinsInBuf & DB_UART_SS3_PIN_MASK)));
    #endif /* (DB_UART_SS3_PIN) */
    }

#endif /* (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (DB_UART_CY_SCBIP_V0 || DB_UART_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: DB_UART_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void DB_UART_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (DB_UART_CTRL_REG & DB_UART_CTRL_EC_AM_MODE)) &&
            (0u == (DB_UART_I2C_CTRL_REG & DB_UART_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            DB_UART_CTRL_REG &= ~DB_UART_CTRL_EC_AM_MODE;
            DB_UART_CTRL_REG |=  DB_UART_CTRL_EC_AM_MODE;
        }

        DB_UART_I2C_SLAVE_CMD_REG = DB_UART_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (DB_UART_CY_SCBIP_V0 || DB_UART_CY_SCBIP_V1) */


/* [] END OF FILE */
