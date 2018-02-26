/*******************************************************************************
* File Name: DB_UART_tx.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DB_UART_tx_ALIASES_H) /* Pins DB_UART_tx_ALIASES_H */
#define CY_PINS_DB_UART_tx_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DB_UART_tx_0			(DB_UART_tx__0__PC)
#define DB_UART_tx_0_PS		(DB_UART_tx__0__PS)
#define DB_UART_tx_0_PC		(DB_UART_tx__0__PC)
#define DB_UART_tx_0_DR		(DB_UART_tx__0__DR)
#define DB_UART_tx_0_SHIFT	(DB_UART_tx__0__SHIFT)
#define DB_UART_tx_0_INTR	((uint16)((uint16)0x0003u << (DB_UART_tx__0__SHIFT*2u)))

#define DB_UART_tx_INTR_ALL	 ((uint16)(DB_UART_tx_0_INTR))


#endif /* End Pins DB_UART_tx_ALIASES_H */


/* [] END OF FILE */
