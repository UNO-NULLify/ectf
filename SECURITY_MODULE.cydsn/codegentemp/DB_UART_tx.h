/*******************************************************************************
* File Name: DB_UART_tx.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DB_UART_tx_H) /* Pins DB_UART_tx_H */
#define CY_PINS_DB_UART_tx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DB_UART_tx_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} DB_UART_tx_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DB_UART_tx_Read(void);
void    DB_UART_tx_Write(uint8 value);
uint8   DB_UART_tx_ReadDataReg(void);
#if defined(DB_UART_tx__PC) || (CY_PSOC4_4200L) 
    void    DB_UART_tx_SetDriveMode(uint8 mode);
#endif
void    DB_UART_tx_SetInterruptMode(uint16 position, uint16 mode);
uint8   DB_UART_tx_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DB_UART_tx_Sleep(void); 
void DB_UART_tx_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DB_UART_tx__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DB_UART_tx_DRIVE_MODE_BITS        (3)
    #define DB_UART_tx_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DB_UART_tx_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DB_UART_tx_SetDriveMode() function.
         *  @{
         */
        #define DB_UART_tx_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DB_UART_tx_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DB_UART_tx_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DB_UART_tx_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DB_UART_tx_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DB_UART_tx_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DB_UART_tx_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DB_UART_tx_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DB_UART_tx_MASK               DB_UART_tx__MASK
#define DB_UART_tx_SHIFT              DB_UART_tx__SHIFT
#define DB_UART_tx_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DB_UART_tx_SetInterruptMode() function.
     *  @{
     */
        #define DB_UART_tx_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DB_UART_tx_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DB_UART_tx_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DB_UART_tx_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DB_UART_tx__SIO)
    #define DB_UART_tx_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DB_UART_tx__PC) && (CY_PSOC4_4200L)
    #define DB_UART_tx_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DB_UART_tx_USBIO_DISABLE              ((uint32)(~DB_UART_tx_USBIO_ENABLE))
    #define DB_UART_tx_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DB_UART_tx_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DB_UART_tx_USBIO_ENTER_SLEEP          ((uint32)((1u << DB_UART_tx_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DB_UART_tx_USBIO_SUSPEND_DEL_SHIFT)))
    #define DB_UART_tx_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DB_UART_tx_USBIO_SUSPEND_SHIFT)))
    #define DB_UART_tx_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DB_UART_tx_USBIO_SUSPEND_DEL_SHIFT)))
    #define DB_UART_tx_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DB_UART_tx__PC)
    /* Port Configuration */
    #define DB_UART_tx_PC                 (* (reg32 *) DB_UART_tx__PC)
#endif
/* Pin State */
#define DB_UART_tx_PS                     (* (reg32 *) DB_UART_tx__PS)
/* Data Register */
#define DB_UART_tx_DR                     (* (reg32 *) DB_UART_tx__DR)
/* Input Buffer Disable Override */
#define DB_UART_tx_INP_DIS                (* (reg32 *) DB_UART_tx__PC2)

/* Interrupt configuration Registers */
#define DB_UART_tx_INTCFG                 (* (reg32 *) DB_UART_tx__INTCFG)
#define DB_UART_tx_INTSTAT                (* (reg32 *) DB_UART_tx__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DB_UART_tx_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DB_UART_tx__SIO)
    #define DB_UART_tx_SIO_REG            (* (reg32 *) DB_UART_tx__SIO)
#endif /* (DB_UART_tx__SIO_CFG) */

/* USBIO registers */
#if !defined(DB_UART_tx__PC) && (CY_PSOC4_4200L)
    #define DB_UART_tx_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DB_UART_tx_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DB_UART_tx_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DB_UART_tx_DRIVE_MODE_SHIFT       (0x00u)
#define DB_UART_tx_DRIVE_MODE_MASK        (0x07u << DB_UART_tx_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DB_UART_tx_H */


/* [] END OF FILE */
