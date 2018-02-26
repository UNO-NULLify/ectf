/*******************************************************************************
* File Name: CARD_UART_IntClock.h
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

#if !defined(CY_CLOCK_CARD_UART_IntClock_H)
#define CY_CLOCK_CARD_UART_IntClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void CARD_UART_IntClock_StartEx(uint32 alignClkDiv);
#define CARD_UART_IntClock_Start() \
    CARD_UART_IntClock_StartEx(CARD_UART_IntClock__PA_DIV_ID)

#else

void CARD_UART_IntClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void CARD_UART_IntClock_Stop(void);

void CARD_UART_IntClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 CARD_UART_IntClock_GetDividerRegister(void);
uint8  CARD_UART_IntClock_GetFractionalDividerRegister(void);

#define CARD_UART_IntClock_Enable()                         CARD_UART_IntClock_Start()
#define CARD_UART_IntClock_Disable()                        CARD_UART_IntClock_Stop()
#define CARD_UART_IntClock_SetDividerRegister(clkDivider, reset)  \
    CARD_UART_IntClock_SetFractionalDividerRegister((clkDivider), 0u)
#define CARD_UART_IntClock_SetDivider(clkDivider)           CARD_UART_IntClock_SetDividerRegister((clkDivider), 1u)
#define CARD_UART_IntClock_SetDividerValue(clkDivider)      CARD_UART_IntClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define CARD_UART_IntClock_DIV_ID     CARD_UART_IntClock__DIV_ID

#define CARD_UART_IntClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define CARD_UART_IntClock_CTRL_REG   (*(reg32 *)CARD_UART_IntClock__CTRL_REGISTER)
#define CARD_UART_IntClock_DIV_REG    (*(reg32 *)CARD_UART_IntClock__DIV_REGISTER)

#define CARD_UART_IntClock_CMD_DIV_SHIFT          (0u)
#define CARD_UART_IntClock_CMD_PA_DIV_SHIFT       (8u)
#define CARD_UART_IntClock_CMD_DISABLE_SHIFT      (30u)
#define CARD_UART_IntClock_CMD_ENABLE_SHIFT       (31u)

#define CARD_UART_IntClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << CARD_UART_IntClock_CMD_DISABLE_SHIFT))
#define CARD_UART_IntClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << CARD_UART_IntClock_CMD_ENABLE_SHIFT))

#define CARD_UART_IntClock_DIV_FRAC_MASK  (0x000000F8u)
#define CARD_UART_IntClock_DIV_FRAC_SHIFT (3u)
#define CARD_UART_IntClock_DIV_INT_MASK   (0xFFFFFF00u)
#define CARD_UART_IntClock_DIV_INT_SHIFT  (8u)

#else 

#define CARD_UART_IntClock_DIV_REG        (*(reg32 *)CARD_UART_IntClock__REGISTER)
#define CARD_UART_IntClock_ENABLE_REG     CARD_UART_IntClock_DIV_REG
#define CARD_UART_IntClock_DIV_FRAC_MASK  CARD_UART_IntClock__FRAC_MASK
#define CARD_UART_IntClock_DIV_FRAC_SHIFT (16u)
#define CARD_UART_IntClock_DIV_INT_MASK   CARD_UART_IntClock__DIVIDER_MASK
#define CARD_UART_IntClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_CARD_UART_IntClock_H) */

/* [] END OF FILE */
