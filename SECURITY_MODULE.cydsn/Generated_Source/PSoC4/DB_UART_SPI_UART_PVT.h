/***************************************************************************//**
* \file DB_UART_SPI_UART_PVT.h
* \version 3.20
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
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

#if !defined(CY_SCB_SPI_UART_PVT_DB_UART_H)
#define CY_SCB_SPI_UART_PVT_DB_UART_H

#include "DB_UART_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (DB_UART_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  DB_UART_rxBufferHead;
    extern volatile uint32  DB_UART_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   DB_UART_rxBufferOverflow;
    /** @} globals */
#endif /* (DB_UART_INTERNAL_RX_SW_BUFFER_CONST) */

#if (DB_UART_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  DB_UART_txBufferHead;
    extern volatile uint32  DB_UART_txBufferTail;
#endif /* (DB_UART_INTERNAL_TX_SW_BUFFER_CONST) */

#if (DB_UART_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 DB_UART_rxBufferInternal[DB_UART_INTERNAL_RX_BUFFER_SIZE];
#endif /* (DB_UART_INTERNAL_RX_SW_BUFFER) */

#if (DB_UART_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 DB_UART_txBufferInternal[DB_UART_TX_BUFFER_SIZE];
#endif /* (DB_UART_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void DB_UART_SpiPostEnable(void);
void DB_UART_SpiStop(void);

#if (DB_UART_SCB_MODE_SPI_CONST_CFG)
    void DB_UART_SpiInit(void);
#endif /* (DB_UART_SCB_MODE_SPI_CONST_CFG) */

#if (DB_UART_SPI_WAKE_ENABLE_CONST)
    void DB_UART_SpiSaveConfig(void);
    void DB_UART_SpiRestoreConfig(void);
#endif /* (DB_UART_SPI_WAKE_ENABLE_CONST) */

void DB_UART_UartPostEnable(void);
void DB_UART_UartStop(void);

#if (DB_UART_SCB_MODE_UART_CONST_CFG)
    void DB_UART_UartInit(void);
#endif /* (DB_UART_SCB_MODE_UART_CONST_CFG) */

#if (DB_UART_UART_WAKE_ENABLE_CONST)
    void DB_UART_UartSaveConfig(void);
    void DB_UART_UartRestoreConfig(void);
#endif /* (DB_UART_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in DB_UART_SetPins() */
#define DB_UART_UART_RX_PIN_ENABLE    (DB_UART_UART_RX)
#define DB_UART_UART_TX_PIN_ENABLE    (DB_UART_UART_TX)

/* UART RTS and CTS position to be used in  DB_UART_SetPins() */
#define DB_UART_UART_RTS_PIN_ENABLE    (0x10u)
#define DB_UART_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define DB_UART_SpiUartEnableIntRx(intSourceMask)  DB_UART_SetRxInterruptMode(intSourceMask)
#define DB_UART_SpiUartEnableIntTx(intSourceMask)  DB_UART_SetTxInterruptMode(intSourceMask)
uint32  DB_UART_SpiUartDisableIntRx(void);
uint32  DB_UART_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_DB_UART_H) */


/* [] END OF FILE */
