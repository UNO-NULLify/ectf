/***************************************************************************//**
* \file .h
* \version 3.20
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_DB_UART_H)
#define CY_SCB_PVT_DB_UART_H

#include "DB_UART.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define DB_UART_SetI2CExtClkInterruptMode(interruptMask) DB_UART_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define DB_UART_ClearI2CExtClkInterruptSource(interruptMask) DB_UART_CLEAR_INTR_I2C_EC(interruptMask)
#define DB_UART_GetI2CExtClkInterruptSource()                (DB_UART_INTR_I2C_EC_REG)
#define DB_UART_GetI2CExtClkInterruptMode()                  (DB_UART_INTR_I2C_EC_MASK_REG)
#define DB_UART_GetI2CExtClkInterruptSourceMasked()          (DB_UART_INTR_I2C_EC_MASKED_REG)

#if (!DB_UART_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define DB_UART_SetSpiExtClkInterruptMode(interruptMask) \
                                                                DB_UART_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define DB_UART_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                DB_UART_CLEAR_INTR_SPI_EC(interruptMask)
    #define DB_UART_GetExtSpiClkInterruptSource()                 (DB_UART_INTR_SPI_EC_REG)
    #define DB_UART_GetExtSpiClkInterruptMode()                   (DB_UART_INTR_SPI_EC_MASK_REG)
    #define DB_UART_GetExtSpiClkInterruptSourceMasked()           (DB_UART_INTR_SPI_EC_MASKED_REG)
#endif /* (!DB_UART_CY_SCBIP_V1) */

#if(DB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void DB_UART_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (DB_UART_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_DB_UART_CUSTOM_INTR_HANDLER)
    extern cyisraddress DB_UART_customIntrHandler;
#endif /* !defined (CY_REMOVE_DB_UART_CUSTOM_INTR_HANDLER) */
#endif /* (DB_UART_SCB_IRQ_INTERNAL) */

extern DB_UART_BACKUP_STRUCT DB_UART_backup;

#if(DB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 DB_UART_scbMode;
    extern uint8 DB_UART_scbEnableWake;
    extern uint8 DB_UART_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 DB_UART_mode;
    extern uint8 DB_UART_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * DB_UART_rxBuffer;
    extern uint8   DB_UART_rxDataBits;
    extern uint32  DB_UART_rxBufferSize;

    extern volatile uint8 * DB_UART_txBuffer;
    extern uint8   DB_UART_txDataBits;
    extern uint32  DB_UART_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 DB_UART_numberOfAddr;
    extern uint8 DB_UART_subAddrSize;
#endif /* (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (DB_UART_SCB_MODE_I2C_CONST_CFG || \
        DB_UART_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 DB_UART_IntrTxMask;
#endif /* (! (DB_UART_SCB_MODE_I2C_CONST_CFG || \
              DB_UART_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(DB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define DB_UART_SCB_MODE_I2C_RUNTM_CFG     (DB_UART_SCB_MODE_I2C      == DB_UART_scbMode)
    #define DB_UART_SCB_MODE_SPI_RUNTM_CFG     (DB_UART_SCB_MODE_SPI      == DB_UART_scbMode)
    #define DB_UART_SCB_MODE_UART_RUNTM_CFG    (DB_UART_SCB_MODE_UART     == DB_UART_scbMode)
    #define DB_UART_SCB_MODE_EZI2C_RUNTM_CFG   (DB_UART_SCB_MODE_EZI2C    == DB_UART_scbMode)
    #define DB_UART_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (DB_UART_SCB_MODE_UNCONFIG == DB_UART_scbMode)

    /* Defines wakeup enable */
    #define DB_UART_SCB_WAKE_ENABLE_CHECK       (0u != DB_UART_scbEnableWake)
#endif /* (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!DB_UART_CY_SCBIP_V1)
    #define DB_UART_SCB_PINS_NUMBER    (7u)
#else
    #define DB_UART_SCB_PINS_NUMBER    (2u)
#endif /* (!DB_UART_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_DB_UART_H) */


/* [] END OF FILE */
