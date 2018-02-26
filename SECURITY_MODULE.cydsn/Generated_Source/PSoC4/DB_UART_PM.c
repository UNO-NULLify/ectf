/***************************************************************************//**
* \file DB_UART_PM.c
* \version 3.20
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DB_UART.h"
#include "DB_UART_PVT.h"

#if(DB_UART_SCB_MODE_I2C_INC)
    #include "DB_UART_I2C_PVT.h"
#endif /* (DB_UART_SCB_MODE_I2C_INC) */

#if(DB_UART_SCB_MODE_EZI2C_INC)
    #include "DB_UART_EZI2C_PVT.h"
#endif /* (DB_UART_SCB_MODE_EZI2C_INC) */

#if(DB_UART_SCB_MODE_SPI_INC || DB_UART_SCB_MODE_UART_INC)
    #include "DB_UART_SPI_UART_PVT.h"
#endif /* (DB_UART_SCB_MODE_SPI_INC || DB_UART_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(DB_UART_SCB_MODE_UNCONFIG_CONST_CFG || \
   (DB_UART_SCB_MODE_I2C_CONST_CFG   && (!DB_UART_I2C_WAKE_ENABLE_CONST))   || \
   (DB_UART_SCB_MODE_EZI2C_CONST_CFG && (!DB_UART_EZI2C_WAKE_ENABLE_CONST)) || \
   (DB_UART_SCB_MODE_SPI_CONST_CFG   && (!DB_UART_SPI_WAKE_ENABLE_CONST))   || \
   (DB_UART_SCB_MODE_UART_CONST_CFG  && (!DB_UART_UART_WAKE_ENABLE_CONST)))

    DB_UART_BACKUP_STRUCT DB_UART_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: DB_UART_Sleep
****************************************************************************//**
*
*  Prepares the DB_UART component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the DB_UART_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void DB_UART_Sleep(void)
{
#if(DB_UART_SCB_MODE_UNCONFIG_CONST_CFG)

    if(DB_UART_SCB_WAKE_ENABLE_CHECK)
    {
        if(DB_UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            DB_UART_I2CSaveConfig();
        }
        else if(DB_UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            DB_UART_EzI2CSaveConfig();
        }
    #if(!DB_UART_CY_SCBIP_V1)
        else if(DB_UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            DB_UART_SpiSaveConfig();
        }
        else if(DB_UART_SCB_MODE_UART_RUNTM_CFG)
        {
            DB_UART_UartSaveConfig();
        }
    #endif /* (!DB_UART_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        DB_UART_backup.enableState = (uint8) DB_UART_GET_CTRL_ENABLED;

        if(0u != DB_UART_backup.enableState)
        {
            DB_UART_Stop();
        }
    }

#else

    #if (DB_UART_SCB_MODE_I2C_CONST_CFG && DB_UART_I2C_WAKE_ENABLE_CONST)
        DB_UART_I2CSaveConfig();

    #elif (DB_UART_SCB_MODE_EZI2C_CONST_CFG && DB_UART_EZI2C_WAKE_ENABLE_CONST)
        DB_UART_EzI2CSaveConfig();

    #elif (DB_UART_SCB_MODE_SPI_CONST_CFG && DB_UART_SPI_WAKE_ENABLE_CONST)
        DB_UART_SpiSaveConfig();

    #elif (DB_UART_SCB_MODE_UART_CONST_CFG && DB_UART_UART_WAKE_ENABLE_CONST)
        DB_UART_UartSaveConfig();

    #else

        DB_UART_backup.enableState = (uint8) DB_UART_GET_CTRL_ENABLED;

        if(0u != DB_UART_backup.enableState)
        {
            DB_UART_Stop();
        }

    #endif /* defined (DB_UART_SCB_MODE_I2C_CONST_CFG) && (DB_UART_I2C_WAKE_ENABLE_CONST) */

#endif /* (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: DB_UART_Wakeup
****************************************************************************//**
*
*  Prepares the DB_UART component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the DB_UART_Wakeup() function without first calling the 
*   DB_UART_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void DB_UART_Wakeup(void)
{
#if(DB_UART_SCB_MODE_UNCONFIG_CONST_CFG)

    if(DB_UART_SCB_WAKE_ENABLE_CHECK)
    {
        if(DB_UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            DB_UART_I2CRestoreConfig();
        }
        else if(DB_UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            DB_UART_EzI2CRestoreConfig();
        }
    #if(!DB_UART_CY_SCBIP_V1)
        else if(DB_UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            DB_UART_SpiRestoreConfig();
        }
        else if(DB_UART_SCB_MODE_UART_RUNTM_CFG)
        {
            DB_UART_UartRestoreConfig();
        }
    #endif /* (!DB_UART_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != DB_UART_backup.enableState)
        {
            DB_UART_Enable();
        }
    }

#else

    #if (DB_UART_SCB_MODE_I2C_CONST_CFG  && DB_UART_I2C_WAKE_ENABLE_CONST)
        DB_UART_I2CRestoreConfig();

    #elif (DB_UART_SCB_MODE_EZI2C_CONST_CFG && DB_UART_EZI2C_WAKE_ENABLE_CONST)
        DB_UART_EzI2CRestoreConfig();

    #elif (DB_UART_SCB_MODE_SPI_CONST_CFG && DB_UART_SPI_WAKE_ENABLE_CONST)
        DB_UART_SpiRestoreConfig();

    #elif (DB_UART_SCB_MODE_UART_CONST_CFG && DB_UART_UART_WAKE_ENABLE_CONST)
        DB_UART_UartRestoreConfig();

    #else

        if(0u != DB_UART_backup.enableState)
        {
            DB_UART_Enable();
        }

    #endif /* (DB_UART_I2C_WAKE_ENABLE_CONST) */

#endif /* (DB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
