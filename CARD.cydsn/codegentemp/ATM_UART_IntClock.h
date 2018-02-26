/*******************************************************************************
* File Name: ATM_UART_IntClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_ATM_UART_IntClock_H)
#define CY_CLOCK_ATM_UART_IntClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void ATM_UART_IntClock_StartEx(uint32 alignClkDiv);
#define ATM_UART_IntClock_Start() \
    ATM_UART_IntClock_StartEx(ATM_UART_IntClock__PA_DIV_ID)

#else

void ATM_UART_IntClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void ATM_UART_IntClock_Stop(void);

void ATM_UART_IntClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 ATM_UART_IntClock_GetDividerRegister(void);
uint8  ATM_UART_IntClock_GetFractionalDividerRegister(void);

#define ATM_UART_IntClock_Enable()                         ATM_UART_IntClock_Start()
#define ATM_UART_IntClock_Disable()                        ATM_UART_IntClock_Stop()
#define ATM_UART_IntClock_SetDividerRegister(clkDivider, reset)  \
    ATM_UART_IntClock_SetFractionalDividerRegister((clkDivider), 0u)
#define ATM_UART_IntClock_SetDivider(clkDivider)           ATM_UART_IntClock_SetDividerRegister((clkDivider), 1u)
#define ATM_UART_IntClock_SetDividerValue(clkDivider)      ATM_UART_IntClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define ATM_UART_IntClock_DIV_ID     ATM_UART_IntClock__DIV_ID

#define ATM_UART_IntClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define ATM_UART_IntClock_CTRL_REG   (*(reg32 *)ATM_UART_IntClock__CTRL_REGISTER)
#define ATM_UART_IntClock_DIV_REG    (*(reg32 *)ATM_UART_IntClock__DIV_REGISTER)

#define ATM_UART_IntClock_CMD_DIV_SHIFT          (0u)
#define ATM_UART_IntClock_CMD_PA_DIV_SHIFT       (8u)
#define ATM_UART_IntClock_CMD_DISABLE_SHIFT      (30u)
#define ATM_UART_IntClock_CMD_ENABLE_SHIFT       (31u)

#define ATM_UART_IntClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << ATM_UART_IntClock_CMD_DISABLE_SHIFT))
#define ATM_UART_IntClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << ATM_UART_IntClock_CMD_ENABLE_SHIFT))

#define ATM_UART_IntClock_DIV_FRAC_MASK  (0x000000F8u)
#define ATM_UART_IntClock_DIV_FRAC_SHIFT (3u)
#define ATM_UART_IntClock_DIV_INT_MASK   (0xFFFFFF00u)
#define ATM_UART_IntClock_DIV_INT_SHIFT  (8u)

#else 

#define ATM_UART_IntClock_DIV_REG        (*(reg32 *)ATM_UART_IntClock__REGISTER)
#define ATM_UART_IntClock_ENABLE_REG     ATM_UART_IntClock_DIV_REG
#define ATM_UART_IntClock_DIV_FRAC_MASK  ATM_UART_IntClock__FRAC_MASK
#define ATM_UART_IntClock_DIV_FRAC_SHIFT (16u)
#define ATM_UART_IntClock_DIV_INT_MASK   ATM_UART_IntClock__DIVIDER_MASK
#define ATM_UART_IntClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_ATM_UART_IntClock_H) */

/* [] END OF FILE */
