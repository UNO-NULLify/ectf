/***************************************************************************//**
* \file DB_UART_BOOT.h
* \version 3.20
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_DB_UART_H)
#define CY_SCB_BOOT_DB_UART_H

#include "DB_UART_PVT.h"

#if (DB_UART_SCB_MODE_I2C_INC)
    #include "DB_UART_I2C.h"
#endif /* (DB_UART_SCB_MODE_I2C_INC) */

#if (DB_UART_SCB_MODE_EZI2C_INC)
    #include "DB_UART_EZI2C.h"
#endif /* (DB_UART_SCB_MODE_EZI2C_INC) */

#if (DB_UART_SCB_MODE_SPI_INC || DB_UART_SCB_MODE_UART_INC)
    #include "DB_UART_SPI_UART.h"
#endif /* (DB_UART_SCB_MODE_SPI_INC || DB_UART_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define DB_UART_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DB_UART) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (DB_UART_SCB_MODE_I2C_INC)
    #define DB_UART_I2C_BTLDR_COMM_ENABLED     (DB_UART_BTLDR_COMM_ENABLED && \
                                                            (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             DB_UART_I2C_SLAVE_CONST))
#else
     #define DB_UART_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (DB_UART_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (DB_UART_SCB_MODE_EZI2C_INC)
    #define DB_UART_EZI2C_BTLDR_COMM_ENABLED   (DB_UART_BTLDR_COMM_ENABLED && \
                                                         DB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define DB_UART_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (DB_UART_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (DB_UART_SCB_MODE_SPI_INC)
    #define DB_UART_SPI_BTLDR_COMM_ENABLED     (DB_UART_BTLDR_COMM_ENABLED && \
                                                            (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             DB_UART_SPI_SLAVE_CONST))
#else
        #define DB_UART_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (DB_UART_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (DB_UART_SCB_MODE_UART_INC)
       #define DB_UART_UART_BTLDR_COMM_ENABLED    (DB_UART_BTLDR_COMM_ENABLED && \
                                                            (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (DB_UART_UART_RX_DIRECTION && \
                                                              DB_UART_UART_TX_DIRECTION)))
#else
     #define DB_UART_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (DB_UART_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define DB_UART_BTLDR_COMM_MODE_ENABLED    (DB_UART_I2C_BTLDR_COMM_ENABLED   || \
                                                     DB_UART_SPI_BTLDR_COMM_ENABLED   || \
                                                     DB_UART_EZI2C_BTLDR_COMM_ENABLED || \
                                                     DB_UART_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (DB_UART_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void DB_UART_I2CCyBtldrCommStart(void);
    void DB_UART_I2CCyBtldrCommStop (void);
    void DB_UART_I2CCyBtldrCommReset(void);
    cystatus DB_UART_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus DB_UART_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (DB_UART_SCB_MODE_I2C_CONST_CFG)
        #define DB_UART_CyBtldrCommStart   DB_UART_I2CCyBtldrCommStart
        #define DB_UART_CyBtldrCommStop    DB_UART_I2CCyBtldrCommStop
        #define DB_UART_CyBtldrCommReset   DB_UART_I2CCyBtldrCommReset
        #define DB_UART_CyBtldrCommRead    DB_UART_I2CCyBtldrCommRead
        #define DB_UART_CyBtldrCommWrite   DB_UART_I2CCyBtldrCommWrite
    #endif /* (DB_UART_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (DB_UART_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (DB_UART_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void DB_UART_EzI2CCyBtldrCommStart(void);
    void DB_UART_EzI2CCyBtldrCommStop (void);
    void DB_UART_EzI2CCyBtldrCommReset(void);
    cystatus DB_UART_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus DB_UART_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (DB_UART_SCB_MODE_EZI2C_CONST_CFG)
        #define DB_UART_CyBtldrCommStart   DB_UART_EzI2CCyBtldrCommStart
        #define DB_UART_CyBtldrCommStop    DB_UART_EzI2CCyBtldrCommStop
        #define DB_UART_CyBtldrCommReset   DB_UART_EzI2CCyBtldrCommReset
        #define DB_UART_CyBtldrCommRead    DB_UART_EzI2CCyBtldrCommRead
        #define DB_UART_CyBtldrCommWrite   DB_UART_EzI2CCyBtldrCommWrite
    #endif /* (DB_UART_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (DB_UART_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (DB_UART_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void DB_UART_SpiCyBtldrCommStart(void);
    void DB_UART_SpiCyBtldrCommStop (void);
    void DB_UART_SpiCyBtldrCommReset(void);
    cystatus DB_UART_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus DB_UART_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (DB_UART_SCB_MODE_SPI_CONST_CFG)
        #define DB_UART_CyBtldrCommStart   DB_UART_SpiCyBtldrCommStart
        #define DB_UART_CyBtldrCommStop    DB_UART_SpiCyBtldrCommStop
        #define DB_UART_CyBtldrCommReset   DB_UART_SpiCyBtldrCommReset
        #define DB_UART_CyBtldrCommRead    DB_UART_SpiCyBtldrCommRead
        #define DB_UART_CyBtldrCommWrite   DB_UART_SpiCyBtldrCommWrite
    #endif /* (DB_UART_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (DB_UART_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (DB_UART_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void DB_UART_UartCyBtldrCommStart(void);
    void DB_UART_UartCyBtldrCommStop (void);
    void DB_UART_UartCyBtldrCommReset(void);
    cystatus DB_UART_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus DB_UART_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (DB_UART_SCB_MODE_UART_CONST_CFG)
        #define DB_UART_CyBtldrCommStart   DB_UART_UartCyBtldrCommStart
        #define DB_UART_CyBtldrCommStop    DB_UART_UartCyBtldrCommStop
        #define DB_UART_CyBtldrCommReset   DB_UART_UartCyBtldrCommReset
        #define DB_UART_CyBtldrCommRead    DB_UART_UartCyBtldrCommRead
        #define DB_UART_CyBtldrCommWrite   DB_UART_UartCyBtldrCommWrite
    #endif /* (DB_UART_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (DB_UART_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (DB_UART_BTLDR_COMM_ENABLED)
    #if (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void DB_UART_CyBtldrCommStart(void);
        void DB_UART_CyBtldrCommStop (void);
        void DB_UART_CyBtldrCommReset(void);
        cystatus DB_UART_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus DB_UART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DB_UART)
        #define CyBtldrCommStart    DB_UART_CyBtldrCommStart
        #define CyBtldrCommStop     DB_UART_CyBtldrCommStop
        #define CyBtldrCommReset    DB_UART_CyBtldrCommReset
        #define CyBtldrCommWrite    DB_UART_CyBtldrCommWrite
        #define CyBtldrCommRead     DB_UART_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DB_UART) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (DB_UART_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define DB_UART_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define DB_UART_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define DB_UART_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define DB_UART_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef DB_UART_SPI_BYTE_TO_BYTE
    #define DB_UART_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef DB_UART_UART_BYTE_TO_BYTE
    #define DB_UART_UART_BYTE_TO_BYTE  (177u)
#endif /* DB_UART_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_DB_UART_H) */


/* [] END OF FILE */
