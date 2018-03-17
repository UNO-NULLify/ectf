;
; File Name: cyfitterrv.inc
; 
; PSoC Creator  4.1 Update 1
;
; Description:
; 
;
;-------------------------------------------------------------------------------
; Copyright (c) 2007-2017 Cypress Semiconductor.  All rights reserved.
; You may use this file only in accordance with the license, terms, conditions, 
; disclaimers, and limitations in the end user license agreement accompanying 
; the software package with which this file was provided.
;-------------------------------------------------------------------------------

    IF :LNOT::DEF:INCLUDED_CYFITTERRV_INC
INCLUDED_CYFITTERRV_INC EQU 1
    GET cydevicerv_trm.inc

; CARD_UART_BUART
CARD_UART_BUART_sRX_RxBitCounter__16BIT_CONTROL_AUX_CTL_REG EQU CYREG_UDB_W16_ACTL_02
CARD_UART_BUART_sRX_RxBitCounter__16BIT_CONTROL_CONTROL_REG EQU CYREG_UDB_W16_CTL_02
CARD_UART_BUART_sRX_RxBitCounter__16BIT_CONTROL_COUNT_REG EQU CYREG_UDB_W16_CTL_02
CARD_UART_BUART_sRX_RxBitCounter__16BIT_COUNT_CONTROL_REG EQU CYREG_UDB_W16_CTL_02
CARD_UART_BUART_sRX_RxBitCounter__16BIT_COUNT_COUNT_REG EQU CYREG_UDB_W16_CTL_02
CARD_UART_BUART_sRX_RxBitCounter__16BIT_MASK_MASK_REG EQU CYREG_UDB_W16_MSK_02
CARD_UART_BUART_sRX_RxBitCounter__16BIT_MASK_PERIOD_REG EQU CYREG_UDB_W16_MSK_02
CARD_UART_BUART_sRX_RxBitCounter__16BIT_PERIOD_MASK_REG EQU CYREG_UDB_W16_MSK_02
CARD_UART_BUART_sRX_RxBitCounter__16BIT_PERIOD_PERIOD_REG EQU CYREG_UDB_W16_MSK_02
CARD_UART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG EQU CYREG_UDB_W8_ACTL_02
CARD_UART_BUART_sRX_RxBitCounter__CONTROL_REG EQU CYREG_UDB_W8_CTL_02
CARD_UART_BUART_sRX_RxBitCounter__CONTROL_ST_REG EQU CYREG_UDB_CAT16_CTL_ST_02
CARD_UART_BUART_sRX_RxBitCounter__COUNT_REG EQU CYREG_UDB_W8_CTL_02
CARD_UART_BUART_sRX_RxBitCounter__COUNT_ST_REG EQU CYREG_UDB_CAT16_CTL_ST_02
CARD_UART_BUART_sRX_RxBitCounter__MASK_CTL_AUX_CTL_REG EQU CYREG_UDB_CAT16_ACTL_MSK_02
CARD_UART_BUART_sRX_RxBitCounter__PER_CTL_AUX_CTL_REG EQU CYREG_UDB_CAT16_ACTL_MSK_02
CARD_UART_BUART_sRX_RxBitCounter__PERIOD_REG EQU CYREG_UDB_W8_MSK_02
CARD_UART_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_AUX_CTL_REG EQU CYREG_UDB_W16_ACTL_02
CARD_UART_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_REG EQU CYREG_UDB_W16_ST_02
CARD_UART_BUART_sRX_RxBitCounter_ST__MASK_REG EQU CYREG_UDB_W8_MSK_02
CARD_UART_BUART_sRX_RxBitCounter_ST__MASK_ST_AUX_CTL_REG EQU CYREG_UDB_CAT16_ACTL_MSK_02
CARD_UART_BUART_sRX_RxBitCounter_ST__PER_ST_AUX_CTL_REG EQU CYREG_UDB_CAT16_ACTL_MSK_02
CARD_UART_BUART_sRX_RxBitCounter_ST__STATUS_AUX_CTL_REG EQU CYREG_UDB_W8_ACTL_02
CARD_UART_BUART_sRX_RxBitCounter_ST__STATUS_CNT_REG EQU CYREG_UDB_CAT16_CTL_ST_02
CARD_UART_BUART_sRX_RxBitCounter_ST__STATUS_CONTROL_REG EQU CYREG_UDB_CAT16_CTL_ST_02
CARD_UART_BUART_sRX_RxBitCounter_ST__STATUS_REG EQU CYREG_UDB_W8_ST_02
CARD_UART_BUART_sRX_RxShifter_u0__16BIT_A0_REG EQU CYREG_UDB_W16_A0_02
CARD_UART_BUART_sRX_RxShifter_u0__16BIT_A1_REG EQU CYREG_UDB_W16_A1_02
CARD_UART_BUART_sRX_RxShifter_u0__16BIT_D0_REG EQU CYREG_UDB_W16_D0_02
CARD_UART_BUART_sRX_RxShifter_u0__16BIT_D1_REG EQU CYREG_UDB_W16_D1_02
CARD_UART_BUART_sRX_RxShifter_u0__16BIT_DP_AUX_CTL_REG EQU CYREG_UDB_W16_ACTL_02
CARD_UART_BUART_sRX_RxShifter_u0__16BIT_F0_REG EQU CYREG_UDB_W16_F0_02
CARD_UART_BUART_sRX_RxShifter_u0__16BIT_F1_REG EQU CYREG_UDB_W16_F1_02
CARD_UART_BUART_sRX_RxShifter_u0__A0_A1_REG EQU CYREG_UDB_CAT16_A_02
CARD_UART_BUART_sRX_RxShifter_u0__A0_REG EQU CYREG_UDB_W8_A0_02
CARD_UART_BUART_sRX_RxShifter_u0__A1_REG EQU CYREG_UDB_W8_A1_02
CARD_UART_BUART_sRX_RxShifter_u0__D0_D1_REG EQU CYREG_UDB_CAT16_D_02
CARD_UART_BUART_sRX_RxShifter_u0__D0_REG EQU CYREG_UDB_W8_D0_02
CARD_UART_BUART_sRX_RxShifter_u0__D1_REG EQU CYREG_UDB_W8_D1_02
CARD_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG EQU CYREG_UDB_W8_ACTL_02
CARD_UART_BUART_sRX_RxShifter_u0__F0_F1_REG EQU CYREG_UDB_CAT16_F_02
CARD_UART_BUART_sRX_RxShifter_u0__F0_REG EQU CYREG_UDB_W8_F0_02
CARD_UART_BUART_sRX_RxShifter_u0__F1_REG EQU CYREG_UDB_W8_F1_02
CARD_UART_BUART_sRX_RxShifter_u0__MSK_DP_AUX_CTL_REG EQU CYREG_UDB_CAT16_ACTL_MSK_02
CARD_UART_BUART_sRX_RxShifter_u0__PER_DP_AUX_CTL_REG EQU CYREG_UDB_CAT16_ACTL_MSK_02
CARD_UART_BUART_sRX_RxSts__16BIT_STATUS_AUX_CTL_REG EQU CYREG_UDB_W16_ACTL_01
CARD_UART_BUART_sRX_RxSts__16BIT_STATUS_REG EQU CYREG_UDB_W16_ST_01
CARD_UART_BUART_sRX_RxSts__3__MASK EQU 0x08
CARD_UART_BUART_sRX_RxSts__3__POS EQU 3
CARD_UART_BUART_sRX_RxSts__4__MASK EQU 0x10
CARD_UART_BUART_sRX_RxSts__4__POS EQU 4
CARD_UART_BUART_sRX_RxSts__5__MASK EQU 0x20
CARD_UART_BUART_sRX_RxSts__5__POS EQU 5
CARD_UART_BUART_sRX_RxSts__MASK EQU 0x38
CARD_UART_BUART_sRX_RxSts__MASK_REG EQU CYREG_UDB_W8_MSK_01
CARD_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG EQU CYREG_UDB_W8_ACTL_01
CARD_UART_BUART_sRX_RxSts__STATUS_REG EQU CYREG_UDB_W8_ST_01
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A0_REG EQU CYREG_UDB_W16_A0_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A1_REG EQU CYREG_UDB_W16_A1_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D0_REG EQU CYREG_UDB_W16_D0_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D1_REG EQU CYREG_UDB_W16_D1_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_DP_AUX_CTL_REG EQU CYREG_UDB_W16_ACTL_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F0_REG EQU CYREG_UDB_W16_F0_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F1_REG EQU CYREG_UDB_W16_F1_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__32BIT_A0_REG EQU CYREG_UDB_W32_A0_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__32BIT_A1_REG EQU CYREG_UDB_W32_A1_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__32BIT_D0_REG EQU CYREG_UDB_W32_D0_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__32BIT_D1_REG EQU CYREG_UDB_W32_D1_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__32BIT_DP_AUX_CTL_REG EQU CYREG_UDB_W32_ACTL_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__32BIT_F0_REG EQU CYREG_UDB_W32_F0_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__32BIT_F1_REG EQU CYREG_UDB_W32_F1_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__A0_A1_REG EQU CYREG_UDB_CAT16_A_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__A0_REG EQU CYREG_UDB_W8_A0_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__A1_REG EQU CYREG_UDB_W8_A1_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_D1_REG EQU CYREG_UDB_CAT16_D_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG EQU CYREG_UDB_W8_D0_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG EQU CYREG_UDB_W8_D1_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__DP_AUX_CTL_REG EQU CYREG_UDB_W8_ACTL_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__F0_F1_REG EQU CYREG_UDB_CAT16_F_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__F0_REG EQU CYREG_UDB_W8_F0_00
CARD_UART_BUART_sTX_sCLOCK_TxBitClkGen__F1_REG EQU CYREG_UDB_W8_F1_00
CARD_UART_BUART_sTX_TxShifter_u0__A0_A1_REG EQU CYREG_UDB_CAT16_A_03
CARD_UART_BUART_sTX_TxShifter_u0__A0_REG EQU CYREG_UDB_W8_A0_03
CARD_UART_BUART_sTX_TxShifter_u0__A1_REG EQU CYREG_UDB_W8_A1_03
CARD_UART_BUART_sTX_TxShifter_u0__D0_D1_REG EQU CYREG_UDB_CAT16_D_03
CARD_UART_BUART_sTX_TxShifter_u0__D0_REG EQU CYREG_UDB_W8_D0_03
CARD_UART_BUART_sTX_TxShifter_u0__D1_REG EQU CYREG_UDB_W8_D1_03
CARD_UART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG EQU CYREG_UDB_W8_ACTL_03
CARD_UART_BUART_sTX_TxShifter_u0__F0_F1_REG EQU CYREG_UDB_CAT16_F_03
CARD_UART_BUART_sTX_TxShifter_u0__F0_REG EQU CYREG_UDB_W8_F0_03
CARD_UART_BUART_sTX_TxShifter_u0__F1_REG EQU CYREG_UDB_W8_F1_03
CARD_UART_BUART_sTX_TxSts__0__MASK EQU 0x01
CARD_UART_BUART_sTX_TxSts__0__POS EQU 0
CARD_UART_BUART_sTX_TxSts__1__MASK EQU 0x02
CARD_UART_BUART_sTX_TxSts__1__POS EQU 1
CARD_UART_BUART_sTX_TxSts__2__MASK EQU 0x04
CARD_UART_BUART_sTX_TxSts__2__POS EQU 2
CARD_UART_BUART_sTX_TxSts__3__MASK EQU 0x08
CARD_UART_BUART_sTX_TxSts__3__POS EQU 3
CARD_UART_BUART_sTX_TxSts__MASK EQU 0x0F
CARD_UART_BUART_sTX_TxSts__MASK_REG EQU CYREG_UDB_W8_MSK_03
CARD_UART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG EQU CYREG_UDB_W8_ACTL_03
CARD_UART_BUART_sTX_TxSts__STATUS_REG EQU CYREG_UDB_W8_ST_03

; CARD_UART_IntClock
CARD_UART_IntClock__DIVIDER_MASK EQU 0x0000FFFF
CARD_UART_IntClock__ENABLE EQU CYREG_CLK_DIVIDER_B00
CARD_UART_IntClock__ENABLE_MASK EQU 0x80000000
CARD_UART_IntClock__MASK EQU 0x80000000
CARD_UART_IntClock__REGISTER EQU CYREG_CLK_DIVIDER_B00

; CARD_UART_RXInternalInterrupt
CARD_UART_RXInternalInterrupt__INTC_CLR_EN_REG EQU CYREG_CM0_ICER
CARD_UART_RXInternalInterrupt__INTC_CLR_PD_REG EQU CYREG_CM0_ICPR
CARD_UART_RXInternalInterrupt__INTC_MASK EQU 0x04
CARD_UART_RXInternalInterrupt__INTC_NUMBER EQU 2
CARD_UART_RXInternalInterrupt__INTC_PRIOR_MASK EQU 0xC00000
CARD_UART_RXInternalInterrupt__INTC_PRIOR_NUM EQU 3
CARD_UART_RXInternalInterrupt__INTC_PRIOR_REG EQU CYREG_CM0_IPR0
CARD_UART_RXInternalInterrupt__INTC_SET_EN_REG EQU CYREG_CM0_ISER
CARD_UART_RXInternalInterrupt__INTC_SET_PD_REG EQU CYREG_CM0_ISPR

; CARD_UART_TXInternalInterrupt
CARD_UART_TXInternalInterrupt__INTC_CLR_EN_REG EQU CYREG_CM0_ICER
CARD_UART_TXInternalInterrupt__INTC_CLR_PD_REG EQU CYREG_CM0_ICPR
CARD_UART_TXInternalInterrupt__INTC_MASK EQU 0x08
CARD_UART_TXInternalInterrupt__INTC_NUMBER EQU 3
CARD_UART_TXInternalInterrupt__INTC_PRIOR_MASK EQU 0xC0000000
CARD_UART_TXInternalInterrupt__INTC_PRIOR_NUM EQU 3
CARD_UART_TXInternalInterrupt__INTC_PRIOR_REG EQU CYREG_CM0_IPR0
CARD_UART_TXInternalInterrupt__INTC_SET_EN_REG EQU CYREG_CM0_ISER
CARD_UART_TXInternalInterrupt__INTC_SET_PD_REG EQU CYREG_CM0_ISPR

; DB_UART
DB_UART_rx__0__DM__MASK EQU 0x07
DB_UART_rx__0__DM__SHIFT EQU 0
DB_UART_rx__0__DR EQU CYREG_PRT4_DR
DB_UART_rx__0__HSIOM EQU CYREG_HSIOM_PORT_SEL4
DB_UART_rx__0__HSIOM_GPIO EQU 0
DB_UART_rx__0__HSIOM_I2C EQU 14
DB_UART_rx__0__HSIOM_I2C_SCL EQU 14
DB_UART_rx__0__HSIOM_MASK EQU 0x0000000F
DB_UART_rx__0__HSIOM_SHIFT EQU 0
DB_UART_rx__0__HSIOM_SPI EQU 15
DB_UART_rx__0__HSIOM_SPI_MOSI EQU 15
DB_UART_rx__0__HSIOM_UART EQU 9
DB_UART_rx__0__HSIOM_UART_RX EQU 9
DB_UART_rx__0__INTCFG EQU CYREG_PRT4_INTCFG
DB_UART_rx__0__INTSTAT EQU CYREG_PRT4_INTSTAT
DB_UART_rx__0__MASK EQU 0x01
DB_UART_rx__0__PC EQU CYREG_PRT4_PC
DB_UART_rx__0__PC2 EQU CYREG_PRT4_PC2
DB_UART_rx__0__PORT EQU 4
DB_UART_rx__0__PS EQU CYREG_PRT4_PS
DB_UART_rx__0__SHIFT EQU 0
DB_UART_rx__DR EQU CYREG_PRT4_DR
DB_UART_rx__INTCFG EQU CYREG_PRT4_INTCFG
DB_UART_rx__INTSTAT EQU CYREG_PRT4_INTSTAT
DB_UART_rx__MASK EQU 0x01
DB_UART_rx__PC EQU CYREG_PRT4_PC
DB_UART_rx__PC2 EQU CYREG_PRT4_PC2
DB_UART_rx__PORT EQU 4
DB_UART_rx__PS EQU CYREG_PRT4_PS
DB_UART_rx__SHIFT EQU 0
DB_UART_SCB__BIST_CONTROL EQU CYREG_SCB0_BIST_CONTROL
DB_UART_SCB__BIST_DATA EQU CYREG_SCB0_BIST_DATA
DB_UART_SCB__CTRL EQU CYREG_SCB0_CTRL
DB_UART_SCB__EZ_DATA00 EQU CYREG_SCB0_EZ_DATA00
DB_UART_SCB__EZ_DATA01 EQU CYREG_SCB0_EZ_DATA01
DB_UART_SCB__EZ_DATA02 EQU CYREG_SCB0_EZ_DATA02
DB_UART_SCB__EZ_DATA03 EQU CYREG_SCB0_EZ_DATA03
DB_UART_SCB__EZ_DATA04 EQU CYREG_SCB0_EZ_DATA04
DB_UART_SCB__EZ_DATA05 EQU CYREG_SCB0_EZ_DATA05
DB_UART_SCB__EZ_DATA06 EQU CYREG_SCB0_EZ_DATA06
DB_UART_SCB__EZ_DATA07 EQU CYREG_SCB0_EZ_DATA07
DB_UART_SCB__EZ_DATA08 EQU CYREG_SCB0_EZ_DATA08
DB_UART_SCB__EZ_DATA09 EQU CYREG_SCB0_EZ_DATA09
DB_UART_SCB__EZ_DATA10 EQU CYREG_SCB0_EZ_DATA10
DB_UART_SCB__EZ_DATA11 EQU CYREG_SCB0_EZ_DATA11
DB_UART_SCB__EZ_DATA12 EQU CYREG_SCB0_EZ_DATA12
DB_UART_SCB__EZ_DATA13 EQU CYREG_SCB0_EZ_DATA13
DB_UART_SCB__EZ_DATA14 EQU CYREG_SCB0_EZ_DATA14
DB_UART_SCB__EZ_DATA15 EQU CYREG_SCB0_EZ_DATA15
DB_UART_SCB__EZ_DATA16 EQU CYREG_SCB0_EZ_DATA16
DB_UART_SCB__EZ_DATA17 EQU CYREG_SCB0_EZ_DATA17
DB_UART_SCB__EZ_DATA18 EQU CYREG_SCB0_EZ_DATA18
DB_UART_SCB__EZ_DATA19 EQU CYREG_SCB0_EZ_DATA19
DB_UART_SCB__EZ_DATA20 EQU CYREG_SCB0_EZ_DATA20
DB_UART_SCB__EZ_DATA21 EQU CYREG_SCB0_EZ_DATA21
DB_UART_SCB__EZ_DATA22 EQU CYREG_SCB0_EZ_DATA22
DB_UART_SCB__EZ_DATA23 EQU CYREG_SCB0_EZ_DATA23
DB_UART_SCB__EZ_DATA24 EQU CYREG_SCB0_EZ_DATA24
DB_UART_SCB__EZ_DATA25 EQU CYREG_SCB0_EZ_DATA25
DB_UART_SCB__EZ_DATA26 EQU CYREG_SCB0_EZ_DATA26
DB_UART_SCB__EZ_DATA27 EQU CYREG_SCB0_EZ_DATA27
DB_UART_SCB__EZ_DATA28 EQU CYREG_SCB0_EZ_DATA28
DB_UART_SCB__EZ_DATA29 EQU CYREG_SCB0_EZ_DATA29
DB_UART_SCB__EZ_DATA30 EQU CYREG_SCB0_EZ_DATA30
DB_UART_SCB__EZ_DATA31 EQU CYREG_SCB0_EZ_DATA31
DB_UART_SCB__I2C_CFG EQU CYREG_SCB0_I2C_CFG
DB_UART_SCB__I2C_CTRL EQU CYREG_SCB0_I2C_CTRL
DB_UART_SCB__I2C_M_CMD EQU CYREG_SCB0_I2C_M_CMD
DB_UART_SCB__I2C_S_CMD EQU CYREG_SCB0_I2C_S_CMD
DB_UART_SCB__I2C_STATUS EQU CYREG_SCB0_I2C_STATUS
DB_UART_SCB__INTR_CAUSE EQU CYREG_SCB0_INTR_CAUSE
DB_UART_SCB__INTR_I2C_EC EQU CYREG_SCB0_INTR_I2C_EC
DB_UART_SCB__INTR_I2C_EC_MASK EQU CYREG_SCB0_INTR_I2C_EC_MASK
DB_UART_SCB__INTR_I2C_EC_MASKED EQU CYREG_SCB0_INTR_I2C_EC_MASKED
DB_UART_SCB__INTR_M EQU CYREG_SCB0_INTR_M
DB_UART_SCB__INTR_M_MASK EQU CYREG_SCB0_INTR_M_MASK
DB_UART_SCB__INTR_M_MASKED EQU CYREG_SCB0_INTR_M_MASKED
DB_UART_SCB__INTR_M_SET EQU CYREG_SCB0_INTR_M_SET
DB_UART_SCB__INTR_RX EQU CYREG_SCB0_INTR_RX
DB_UART_SCB__INTR_RX_MASK EQU CYREG_SCB0_INTR_RX_MASK
DB_UART_SCB__INTR_RX_MASKED EQU CYREG_SCB0_INTR_RX_MASKED
DB_UART_SCB__INTR_RX_SET EQU CYREG_SCB0_INTR_RX_SET
DB_UART_SCB__INTR_S EQU CYREG_SCB0_INTR_S
DB_UART_SCB__INTR_S_MASK EQU CYREG_SCB0_INTR_S_MASK
DB_UART_SCB__INTR_S_MASKED EQU CYREG_SCB0_INTR_S_MASKED
DB_UART_SCB__INTR_S_SET EQU CYREG_SCB0_INTR_S_SET
DB_UART_SCB__INTR_SPI_EC EQU CYREG_SCB0_INTR_SPI_EC
DB_UART_SCB__INTR_SPI_EC_MASK EQU CYREG_SCB0_INTR_SPI_EC_MASK
DB_UART_SCB__INTR_SPI_EC_MASKED EQU CYREG_SCB0_INTR_SPI_EC_MASKED
DB_UART_SCB__INTR_TX EQU CYREG_SCB0_INTR_TX
DB_UART_SCB__INTR_TX_MASK EQU CYREG_SCB0_INTR_TX_MASK
DB_UART_SCB__INTR_TX_MASKED EQU CYREG_SCB0_INTR_TX_MASKED
DB_UART_SCB__INTR_TX_SET EQU CYREG_SCB0_INTR_TX_SET
DB_UART_SCB__RX_CTRL EQU CYREG_SCB0_RX_CTRL
DB_UART_SCB__RX_FIFO_CTRL EQU CYREG_SCB0_RX_FIFO_CTRL
DB_UART_SCB__RX_FIFO_RD EQU CYREG_SCB0_RX_FIFO_RD
DB_UART_SCB__RX_FIFO_RD_SILENT EQU CYREG_SCB0_RX_FIFO_RD_SILENT
DB_UART_SCB__RX_FIFO_STATUS EQU CYREG_SCB0_RX_FIFO_STATUS
DB_UART_SCB__RX_MATCH EQU CYREG_SCB0_RX_MATCH
DB_UART_SCB__SPI_CTRL EQU CYREG_SCB0_SPI_CTRL
DB_UART_SCB__SPI_STATUS EQU CYREG_SCB0_SPI_STATUS
DB_UART_SCB__SS0_POSISTION EQU 0
DB_UART_SCB__SS1_POSISTION EQU 1
DB_UART_SCB__SS2_POSISTION EQU 2
DB_UART_SCB__SS3_POSISTION EQU 3
DB_UART_SCB__STATUS EQU CYREG_SCB0_STATUS
DB_UART_SCB__TX_CTRL EQU CYREG_SCB0_TX_CTRL
DB_UART_SCB__TX_FIFO_CTRL EQU CYREG_SCB0_TX_FIFO_CTRL
DB_UART_SCB__TX_FIFO_STATUS EQU CYREG_SCB0_TX_FIFO_STATUS
DB_UART_SCB__TX_FIFO_WR EQU CYREG_SCB0_TX_FIFO_WR
DB_UART_SCB__UART_CTRL EQU CYREG_SCB0_UART_CTRL
DB_UART_SCB__UART_RX_CTRL EQU CYREG_SCB0_UART_RX_CTRL
DB_UART_SCB__UART_RX_STATUS EQU CYREG_SCB0_UART_RX_STATUS
DB_UART_SCB__UART_TX_CTRL EQU CYREG_SCB0_UART_TX_CTRL
DB_UART_SCB_IRQ__INTC_CLR_EN_REG EQU CYREG_CM0_ICER
DB_UART_SCB_IRQ__INTC_CLR_PD_REG EQU CYREG_CM0_ICPR
DB_UART_SCB_IRQ__INTC_MASK EQU 0x400
DB_UART_SCB_IRQ__INTC_NUMBER EQU 10
DB_UART_SCB_IRQ__INTC_PRIOR_MASK EQU 0xC00000
DB_UART_SCB_IRQ__INTC_PRIOR_NUM EQU 3
DB_UART_SCB_IRQ__INTC_PRIOR_REG EQU CYREG_CM0_IPR2
DB_UART_SCB_IRQ__INTC_SET_EN_REG EQU CYREG_CM0_ISER
DB_UART_SCB_IRQ__INTC_SET_PD_REG EQU CYREG_CM0_ISPR
DB_UART_SCBCLK__DIVIDER_MASK EQU 0x0000FFFF
DB_UART_SCBCLK__ENABLE EQU CYREG_CLK_DIVIDER_A00
DB_UART_SCBCLK__ENABLE_MASK EQU 0x80000000
DB_UART_SCBCLK__MASK EQU 0x80000000
DB_UART_SCBCLK__REGISTER EQU CYREG_CLK_DIVIDER_A00
DB_UART_tx__0__DM__MASK EQU 0x38
DB_UART_tx__0__DM__SHIFT EQU 3
DB_UART_tx__0__DR EQU CYREG_PRT4_DR
DB_UART_tx__0__HSIOM EQU CYREG_HSIOM_PORT_SEL4
DB_UART_tx__0__HSIOM_GPIO EQU 0
DB_UART_tx__0__HSIOM_I2C EQU 14
DB_UART_tx__0__HSIOM_I2C_SDA EQU 14
DB_UART_tx__0__HSIOM_MASK EQU 0x000000F0
DB_UART_tx__0__HSIOM_SHIFT EQU 4
DB_UART_tx__0__HSIOM_SPI EQU 15
DB_UART_tx__0__HSIOM_SPI_MISO EQU 15
DB_UART_tx__0__HSIOM_UART EQU 9
DB_UART_tx__0__HSIOM_UART_TX EQU 9
DB_UART_tx__0__INTCFG EQU CYREG_PRT4_INTCFG
DB_UART_tx__0__INTSTAT EQU CYREG_PRT4_INTSTAT
DB_UART_tx__0__MASK EQU 0x02
DB_UART_tx__0__PC EQU CYREG_PRT4_PC
DB_UART_tx__0__PC2 EQU CYREG_PRT4_PC2
DB_UART_tx__0__PORT EQU 4
DB_UART_tx__0__PS EQU CYREG_PRT4_PS
DB_UART_tx__0__SHIFT EQU 1
DB_UART_tx__DR EQU CYREG_PRT4_DR
DB_UART_tx__INTCFG EQU CYREG_PRT4_INTCFG
DB_UART_tx__INTSTAT EQU CYREG_PRT4_INTSTAT
DB_UART_tx__MASK EQU 0x02
DB_UART_tx__PC EQU CYREG_PRT4_PC
DB_UART_tx__PC2 EQU CYREG_PRT4_PC2
DB_UART_tx__PORT EQU 4
DB_UART_tx__PS EQU CYREG_PRT4_PS
DB_UART_tx__SHIFT EQU 1

; Reset_isr
Reset_isr__INTC_CLR_EN_REG EQU CYREG_CM0_ICER
Reset_isr__INTC_CLR_PD_REG EQU CYREG_CM0_ICPR
Reset_isr__INTC_MASK EQU 0x01
Reset_isr__INTC_NUMBER EQU 0
Reset_isr__INTC_PRIOR_MASK EQU 0xC0
Reset_isr__INTC_PRIOR_NUM EQU 3
Reset_isr__INTC_PRIOR_REG EQU CYREG_CM0_IPR0
Reset_isr__INTC_SET_EN_REG EQU CYREG_CM0_ISER
Reset_isr__INTC_SET_PD_REG EQU CYREG_CM0_ISPR

; Rx_1
Rx_1__0__DM__MASK EQU 0x07
Rx_1__0__DM__SHIFT EQU 0
Rx_1__0__DR EQU CYREG_PRT0_DR
Rx_1__0__HSIOM EQU CYREG_HSIOM_PORT_SEL0
Rx_1__0__HSIOM_MASK EQU 0x0000000F
Rx_1__0__HSIOM_SHIFT EQU 0
Rx_1__0__INTCFG EQU CYREG_PRT0_INTCFG
Rx_1__0__INTSTAT EQU CYREG_PRT0_INTSTAT
Rx_1__0__MASK EQU 0x01
Rx_1__0__PA__CFG0 EQU CYREG_UDB_PA0_CFG0
Rx_1__0__PA__CFG1 EQU CYREG_UDB_PA0_CFG1
Rx_1__0__PA__CFG10 EQU CYREG_UDB_PA0_CFG10
Rx_1__0__PA__CFG11 EQU CYREG_UDB_PA0_CFG11
Rx_1__0__PA__CFG12 EQU CYREG_UDB_PA0_CFG12
Rx_1__0__PA__CFG13 EQU CYREG_UDB_PA0_CFG13
Rx_1__0__PA__CFG14 EQU CYREG_UDB_PA0_CFG14
Rx_1__0__PA__CFG2 EQU CYREG_UDB_PA0_CFG2
Rx_1__0__PA__CFG3 EQU CYREG_UDB_PA0_CFG3
Rx_1__0__PA__CFG4 EQU CYREG_UDB_PA0_CFG4
Rx_1__0__PA__CFG5 EQU CYREG_UDB_PA0_CFG5
Rx_1__0__PA__CFG6 EQU CYREG_UDB_PA0_CFG6
Rx_1__0__PA__CFG7 EQU CYREG_UDB_PA0_CFG7
Rx_1__0__PA__CFG8 EQU CYREG_UDB_PA0_CFG8
Rx_1__0__PA__CFG9 EQU CYREG_UDB_PA0_CFG9
Rx_1__0__PC EQU CYREG_PRT0_PC
Rx_1__0__PC2 EQU CYREG_PRT0_PC2
Rx_1__0__PORT EQU 0
Rx_1__0__PS EQU CYREG_PRT0_PS
Rx_1__0__SHIFT EQU 0
Rx_1__DR EQU CYREG_PRT0_DR
Rx_1__INTCFG EQU CYREG_PRT0_INTCFG
Rx_1__INTSTAT EQU CYREG_PRT0_INTSTAT
Rx_1__MASK EQU 0x01
Rx_1__PA__CFG0 EQU CYREG_UDB_PA0_CFG0
Rx_1__PA__CFG1 EQU CYREG_UDB_PA0_CFG1
Rx_1__PA__CFG10 EQU CYREG_UDB_PA0_CFG10
Rx_1__PA__CFG11 EQU CYREG_UDB_PA0_CFG11
Rx_1__PA__CFG12 EQU CYREG_UDB_PA0_CFG12
Rx_1__PA__CFG13 EQU CYREG_UDB_PA0_CFG13
Rx_1__PA__CFG14 EQU CYREG_UDB_PA0_CFG14
Rx_1__PA__CFG2 EQU CYREG_UDB_PA0_CFG2
Rx_1__PA__CFG3 EQU CYREG_UDB_PA0_CFG3
Rx_1__PA__CFG4 EQU CYREG_UDB_PA0_CFG4
Rx_1__PA__CFG5 EQU CYREG_UDB_PA0_CFG5
Rx_1__PA__CFG6 EQU CYREG_UDB_PA0_CFG6
Rx_1__PA__CFG7 EQU CYREG_UDB_PA0_CFG7
Rx_1__PA__CFG8 EQU CYREG_UDB_PA0_CFG8
Rx_1__PA__CFG9 EQU CYREG_UDB_PA0_CFG9
Rx_1__PC EQU CYREG_PRT0_PC
Rx_1__PC2 EQU CYREG_PRT0_PC2
Rx_1__PORT EQU 0
Rx_1__PS EQU CYREG_PRT0_PS
Rx_1__SHIFT EQU 0

; SW1
SW1__0__DM__MASK EQU 0xE00000
SW1__0__DM__SHIFT EQU 21
SW1__0__DR EQU CYREG_PRT0_DR
SW1__0__HSIOM EQU CYREG_HSIOM_PORT_SEL0
SW1__0__HSIOM_MASK EQU 0xF0000000
SW1__0__HSIOM_SHIFT EQU 28
SW1__0__INTCFG EQU CYREG_PRT0_INTCFG
SW1__0__INTSTAT EQU CYREG_PRT0_INTSTAT
SW1__0__MASK EQU 0x80
SW1__0__PA__CFG0 EQU CYREG_UDB_PA0_CFG0
SW1__0__PA__CFG1 EQU CYREG_UDB_PA0_CFG1
SW1__0__PA__CFG10 EQU CYREG_UDB_PA0_CFG10
SW1__0__PA__CFG11 EQU CYREG_UDB_PA0_CFG11
SW1__0__PA__CFG12 EQU CYREG_UDB_PA0_CFG12
SW1__0__PA__CFG13 EQU CYREG_UDB_PA0_CFG13
SW1__0__PA__CFG14 EQU CYREG_UDB_PA0_CFG14
SW1__0__PA__CFG2 EQU CYREG_UDB_PA0_CFG2
SW1__0__PA__CFG3 EQU CYREG_UDB_PA0_CFG3
SW1__0__PA__CFG4 EQU CYREG_UDB_PA0_CFG4
SW1__0__PA__CFG5 EQU CYREG_UDB_PA0_CFG5
SW1__0__PA__CFG6 EQU CYREG_UDB_PA0_CFG6
SW1__0__PA__CFG7 EQU CYREG_UDB_PA0_CFG7
SW1__0__PA__CFG8 EQU CYREG_UDB_PA0_CFG8
SW1__0__PA__CFG9 EQU CYREG_UDB_PA0_CFG9
SW1__0__PC EQU CYREG_PRT0_PC
SW1__0__PC2 EQU CYREG_PRT0_PC2
SW1__0__PORT EQU 0
SW1__0__PS EQU CYREG_PRT0_PS
SW1__0__SHIFT EQU 7
SW1__DR EQU CYREG_PRT0_DR
SW1__INTCFG EQU CYREG_PRT0_INTCFG
SW1__INTSTAT EQU CYREG_PRT0_INTSTAT
SW1__MASK EQU 0x80
SW1__PA__CFG0 EQU CYREG_UDB_PA0_CFG0
SW1__PA__CFG1 EQU CYREG_UDB_PA0_CFG1
SW1__PA__CFG10 EQU CYREG_UDB_PA0_CFG10
SW1__PA__CFG11 EQU CYREG_UDB_PA0_CFG11
SW1__PA__CFG12 EQU CYREG_UDB_PA0_CFG12
SW1__PA__CFG13 EQU CYREG_UDB_PA0_CFG13
SW1__PA__CFG14 EQU CYREG_UDB_PA0_CFG14
SW1__PA__CFG2 EQU CYREG_UDB_PA0_CFG2
SW1__PA__CFG3 EQU CYREG_UDB_PA0_CFG3
SW1__PA__CFG4 EQU CYREG_UDB_PA0_CFG4
SW1__PA__CFG5 EQU CYREG_UDB_PA0_CFG5
SW1__PA__CFG6 EQU CYREG_UDB_PA0_CFG6
SW1__PA__CFG7 EQU CYREG_UDB_PA0_CFG7
SW1__PA__CFG8 EQU CYREG_UDB_PA0_CFG8
SW1__PA__CFG9 EQU CYREG_UDB_PA0_CFG9
SW1__PC EQU CYREG_PRT0_PC
SW1__PC2 EQU CYREG_PRT0_PC2
SW1__PORT EQU 0
SW1__PS EQU CYREG_PRT0_PS
SW1__SHIFT EQU 7
SW1__SW1__DM__MASK EQU 0xE00000
SW1__SW1__DM__SHIFT EQU 21
SW1__SW1__DR EQU CYREG_PRT0_DR
SW1__SW1__INTCFG EQU CYREG_PRT0_INTCFG
SW1__SW1__INTSTAT EQU CYREG_PRT0_INTSTAT
SW1__SW1__MASK EQU 0x80
SW1__SW1__PA__CFG0 EQU CYREG_UDB_PA0_CFG0
SW1__SW1__PA__CFG1 EQU CYREG_UDB_PA0_CFG1
SW1__SW1__PA__CFG10 EQU CYREG_UDB_PA0_CFG10
SW1__SW1__PA__CFG11 EQU CYREG_UDB_PA0_CFG11
SW1__SW1__PA__CFG12 EQU CYREG_UDB_PA0_CFG12
SW1__SW1__PA__CFG13 EQU CYREG_UDB_PA0_CFG13
SW1__SW1__PA__CFG14 EQU CYREG_UDB_PA0_CFG14
SW1__SW1__PA__CFG2 EQU CYREG_UDB_PA0_CFG2
SW1__SW1__PA__CFG3 EQU CYREG_UDB_PA0_CFG3
SW1__SW1__PA__CFG4 EQU CYREG_UDB_PA0_CFG4
SW1__SW1__PA__CFG5 EQU CYREG_UDB_PA0_CFG5
SW1__SW1__PA__CFG6 EQU CYREG_UDB_PA0_CFG6
SW1__SW1__PA__CFG7 EQU CYREG_UDB_PA0_CFG7
SW1__SW1__PA__CFG8 EQU CYREG_UDB_PA0_CFG8
SW1__SW1__PA__CFG9 EQU CYREG_UDB_PA0_CFG9
SW1__SW1__PC EQU CYREG_PRT0_PC
SW1__SW1__PC2 EQU CYREG_PRT0_PC2
SW1__SW1__PORT EQU 0
SW1__SW1__PS EQU CYREG_PRT0_PS
SW1__SW1__SHIFT EQU 7

; Tx_1
Tx_1__0__DM__MASK EQU 0x38
Tx_1__0__DM__SHIFT EQU 3
Tx_1__0__DR EQU CYREG_PRT0_DR
Tx_1__0__HSIOM EQU CYREG_HSIOM_PORT_SEL0
Tx_1__0__HSIOM_MASK EQU 0x000000F0
Tx_1__0__HSIOM_SHIFT EQU 4
Tx_1__0__INTCFG EQU CYREG_PRT0_INTCFG
Tx_1__0__INTSTAT EQU CYREG_PRT0_INTSTAT
Tx_1__0__MASK EQU 0x02
Tx_1__0__OUT_SEL EQU CYREG_UDB_PA0_CFG10
Tx_1__0__OUT_SEL_SHIFT EQU 2
Tx_1__0__OUT_SEL_VAL EQU 3
Tx_1__0__PA__CFG0 EQU CYREG_UDB_PA0_CFG0
Tx_1__0__PA__CFG1 EQU CYREG_UDB_PA0_CFG1
Tx_1__0__PA__CFG10 EQU CYREG_UDB_PA0_CFG10
Tx_1__0__PA__CFG11 EQU CYREG_UDB_PA0_CFG11
Tx_1__0__PA__CFG12 EQU CYREG_UDB_PA0_CFG12
Tx_1__0__PA__CFG13 EQU CYREG_UDB_PA0_CFG13
Tx_1__0__PA__CFG14 EQU CYREG_UDB_PA0_CFG14
Tx_1__0__PA__CFG2 EQU CYREG_UDB_PA0_CFG2
Tx_1__0__PA__CFG3 EQU CYREG_UDB_PA0_CFG3
Tx_1__0__PA__CFG4 EQU CYREG_UDB_PA0_CFG4
Tx_1__0__PA__CFG5 EQU CYREG_UDB_PA0_CFG5
Tx_1__0__PA__CFG6 EQU CYREG_UDB_PA0_CFG6
Tx_1__0__PA__CFG7 EQU CYREG_UDB_PA0_CFG7
Tx_1__0__PA__CFG8 EQU CYREG_UDB_PA0_CFG8
Tx_1__0__PA__CFG9 EQU CYREG_UDB_PA0_CFG9
Tx_1__0__PC EQU CYREG_PRT0_PC
Tx_1__0__PC2 EQU CYREG_PRT0_PC2
Tx_1__0__PORT EQU 0
Tx_1__0__PS EQU CYREG_PRT0_PS
Tx_1__0__SHIFT EQU 1
Tx_1__DR EQU CYREG_PRT0_DR
Tx_1__INTCFG EQU CYREG_PRT0_INTCFG
Tx_1__INTSTAT EQU CYREG_PRT0_INTSTAT
Tx_1__MASK EQU 0x02
Tx_1__PA__CFG0 EQU CYREG_UDB_PA0_CFG0
Tx_1__PA__CFG1 EQU CYREG_UDB_PA0_CFG1
Tx_1__PA__CFG10 EQU CYREG_UDB_PA0_CFG10
Tx_1__PA__CFG11 EQU CYREG_UDB_PA0_CFG11
Tx_1__PA__CFG12 EQU CYREG_UDB_PA0_CFG12
Tx_1__PA__CFG13 EQU CYREG_UDB_PA0_CFG13
Tx_1__PA__CFG14 EQU CYREG_UDB_PA0_CFG14
Tx_1__PA__CFG2 EQU CYREG_UDB_PA0_CFG2
Tx_1__PA__CFG3 EQU CYREG_UDB_PA0_CFG3
Tx_1__PA__CFG4 EQU CYREG_UDB_PA0_CFG4
Tx_1__PA__CFG5 EQU CYREG_UDB_PA0_CFG5
Tx_1__PA__CFG6 EQU CYREG_UDB_PA0_CFG6
Tx_1__PA__CFG7 EQU CYREG_UDB_PA0_CFG7
Tx_1__PA__CFG8 EQU CYREG_UDB_PA0_CFG8
Tx_1__PA__CFG9 EQU CYREG_UDB_PA0_CFG9
Tx_1__PC EQU CYREG_PRT0_PC
Tx_1__PC2 EQU CYREG_PRT0_PC2
Tx_1__PORT EQU 0
Tx_1__PS EQU CYREG_PRT0_PS
Tx_1__SHIFT EQU 1

; Miscellaneous
CYDEV_BCLK__HFCLK__HZ EQU 15000000
CYDEV_BCLK__HFCLK__KHZ EQU 15000
CYDEV_BCLK__HFCLK__MHZ EQU 15
CYDEV_BCLK__SYSCLK__HZ EQU 15000000
CYDEV_BCLK__SYSCLK__KHZ EQU 15000
CYDEV_BCLK__SYSCLK__MHZ EQU 15
CYDEV_CHIP_DIE_LEOPARD EQU 1
CYDEV_CHIP_DIE_PSOC4A EQU 16
CYDEV_CHIP_DIE_PSOC5LP EQU 2
CYDEV_CHIP_DIE_PSOC5TM EQU 3
CYDEV_CHIP_DIE_TMA4 EQU 4
CYDEV_CHIP_DIE_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_FM0P EQU 5
CYDEV_CHIP_FAMILY_FM3 EQU 6
CYDEV_CHIP_FAMILY_FM4 EQU 7
CYDEV_CHIP_FAMILY_PSOC3 EQU 1
CYDEV_CHIP_FAMILY_PSOC4 EQU 2
CYDEV_CHIP_FAMILY_PSOC5 EQU 3
CYDEV_CHIP_FAMILY_PSOC6 EQU 4
CYDEV_CHIP_FAMILY_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_USED EQU CYDEV_CHIP_FAMILY_PSOC4
CYDEV_CHIP_JTAG_ID EQU 0x04631193
CYDEV_CHIP_MEMBER_3A EQU 1
CYDEV_CHIP_MEMBER_4A EQU 16
CYDEV_CHIP_MEMBER_4D EQU 12
CYDEV_CHIP_MEMBER_4E EQU 6
CYDEV_CHIP_MEMBER_4F EQU 17
CYDEV_CHIP_MEMBER_4G EQU 4
CYDEV_CHIP_MEMBER_4H EQU 15
CYDEV_CHIP_MEMBER_4I EQU 21
CYDEV_CHIP_MEMBER_4J EQU 13
CYDEV_CHIP_MEMBER_4K EQU 14
CYDEV_CHIP_MEMBER_4L EQU 20
CYDEV_CHIP_MEMBER_4M EQU 19
CYDEV_CHIP_MEMBER_4N EQU 9
CYDEV_CHIP_MEMBER_4O EQU 7
CYDEV_CHIP_MEMBER_4P EQU 18
CYDEV_CHIP_MEMBER_4Q EQU 11
CYDEV_CHIP_MEMBER_4R EQU 8
CYDEV_CHIP_MEMBER_4S EQU 10
CYDEV_CHIP_MEMBER_4U EQU 5
CYDEV_CHIP_MEMBER_5A EQU 3
CYDEV_CHIP_MEMBER_5B EQU 2
CYDEV_CHIP_MEMBER_6A EQU 22
CYDEV_CHIP_MEMBER_FM3 EQU 26
CYDEV_CHIP_MEMBER_FM4 EQU 27
CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE1 EQU 23
CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE2 EQU 24
CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE3 EQU 25
CYDEV_CHIP_MEMBER_UNKNOWN EQU 0
CYDEV_CHIP_MEMBER_USED EQU CYDEV_CHIP_MEMBER_4A
CYDEV_CHIP_DIE_EXPECT EQU CYDEV_CHIP_MEMBER_USED
CYDEV_CHIP_DIE_ACTUAL EQU CYDEV_CHIP_DIE_EXPECT
CYDEV_CHIP_REV_LEOPARD_ES1 EQU 0
CYDEV_CHIP_REV_LEOPARD_ES2 EQU 1
CYDEV_CHIP_REV_LEOPARD_ES3 EQU 3
CYDEV_CHIP_REV_LEOPARD_PRODUCTION EQU 3
CYDEV_CHIP_REV_PSOC4A_ES0 EQU 17
CYDEV_CHIP_REV_PSOC4A_PRODUCTION EQU 17
CYDEV_CHIP_REV_PSOC5LP_ES0 EQU 0
CYDEV_CHIP_REV_PSOC5LP_PRODUCTION EQU 0
CYDEV_CHIP_REV_PSOC5TM_ES0 EQU 0
CYDEV_CHIP_REV_PSOC5TM_ES1 EQU 1
CYDEV_CHIP_REV_PSOC5TM_PRODUCTION EQU 1
CYDEV_CHIP_REV_TMA4_ES EQU 17
CYDEV_CHIP_REV_TMA4_ES2 EQU 33
CYDEV_CHIP_REV_TMA4_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_3A_ES1 EQU 0
CYDEV_CHIP_REVISION_3A_ES2 EQU 1
CYDEV_CHIP_REVISION_3A_ES3 EQU 3
CYDEV_CHIP_REVISION_3A_PRODUCTION EQU 3
CYDEV_CHIP_REVISION_4A_ES0 EQU 17
CYDEV_CHIP_REVISION_4A_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_4D_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4E_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION_256K EQU 0
CYDEV_CHIP_REVISION_4G_ES EQU 17
CYDEV_CHIP_REVISION_4G_ES2 EQU 33
CYDEV_CHIP_REVISION_4G_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_4H_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4I_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4J_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4K_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4L_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4M_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4N_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4O_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4P_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4Q_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4R_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4S_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4U_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_5A_ES0 EQU 0
CYDEV_CHIP_REVISION_5A_ES1 EQU 1
CYDEV_CHIP_REVISION_5A_PRODUCTION EQU 1
CYDEV_CHIP_REVISION_5B_ES0 EQU 0
CYDEV_CHIP_REVISION_5B_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_6A_NO_UDB EQU 0
CYDEV_CHIP_REVISION_6A_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_FM3_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_FM4_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_PDL_FM0P_TYPE1_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_PDL_FM0P_TYPE2_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_PDL_FM0P_TYPE3_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_USED EQU CYDEV_CHIP_REVISION_4A_PRODUCTION
CYDEV_CHIP_REV_EXPECT EQU CYDEV_CHIP_REVISION_USED
CYDEV_CONFIG_READ_ACCELERATOR EQU 1
CYDEV_CONFIG_UNUSED_IO_AllowButWarn EQU 0
CYDEV_CONFIG_UNUSED_IO_AllowWithInfo EQU 1
CYDEV_CONFIG_UNUSED_IO_Disallowed EQU 2
CYDEV_CONFIG_UNUSED_IO EQU CYDEV_CONFIG_UNUSED_IO_Disallowed
CYDEV_CONFIGURATION_COMPRESSED EQU 1
CYDEV_CONFIGURATION_MODE_COMPRESSED EQU 0
CYDEV_CONFIGURATION_MODE EQU CYDEV_CONFIGURATION_MODE_COMPRESSED
CYDEV_CONFIGURATION_MODE_DMA EQU 2
CYDEV_CONFIGURATION_MODE_UNCOMPRESSED EQU 1
CYDEV_DEBUG_PROTECT_KILL EQU 4
CYDEV_DEBUG_PROTECT_OPEN EQU 1
CYDEV_DEBUG_PROTECT_PROTECTED EQU 2
CYDEV_DEBUG_PROTECT EQU CYDEV_DEBUG_PROTECT_PROTECTED
CYDEV_DEBUGGING_DPS_Disable EQU 3
CYDEV_DEBUGGING_DPS_SWD EQU 2
CYDEV_DEBUGGING_DPS EQU CYDEV_DEBUGGING_DPS_SWD
CYDEV_DEBUGGING_ENABLE EQU 1
CYDEV_DFT_SELECT_CLK0 EQU 1
CYDEV_DFT_SELECT_CLK1 EQU 2
CYDEV_HEAP_SIZE EQU 0x1f0
CYDEV_IMO_TRIMMED_BY_USB EQU 0
CYDEV_IMO_TRIMMED_BY_WCO EQU 0
CYDEV_IS_EXPORTING_CODE EQU 0
CYDEV_IS_IMPORTING_CODE EQU 0
CYDEV_PROJ_TYPE EQU 0
CYDEV_PROJ_TYPE_BOOTLOADER EQU 1
CYDEV_PROJ_TYPE_LAUNCHER EQU 5
CYDEV_PROJ_TYPE_LOADABLE EQU 2
CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER EQU 4
CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER EQU 3
CYDEV_PROJ_TYPE_STANDARD EQU 0
CYDEV_STACK_SIZE EQU 0x0400
CYDEV_USE_BUNDLED_CMSIS EQU 1
CYDEV_VARIABLE_VDDA EQU 1
CYDEV_VDD_MV EQU 3300
CYDEV_WDT_GENERATE_ISR EQU 1
CYIPBLOCK_M0S8_CTBM_VERSION EQU 0
CYIPBLOCK_m0s8cpuss_VERSION EQU 0
CYIPBLOCK_m0s8csd_VERSION EQU 0
CYIPBLOCK_m0s8gpio2_VERSION EQU 0
CYIPBLOCK_m0s8hsiom4a_VERSION EQU 0
CYIPBLOCK_m0s8lcd_VERSION EQU 0
CYIPBLOCK_m0s8lpcomp_VERSION EQU 0
CYIPBLOCK_m0s8pclk_VERSION EQU 0
CYIPBLOCK_m0s8sar_VERSION EQU 0
CYIPBLOCK_m0s8scb_VERSION EQU 0
CYIPBLOCK_m0s8srssv2_VERSION EQU 1
CYIPBLOCK_m0s8tcpwm_VERSION EQU 0
CYIPBLOCK_m0s8udbif_VERSION EQU 0
CYIPBLOCK_S8_GPIO_VERSION EQU 2
CYDEV_BOOTLOADER_ENABLE EQU 0
    ENDIF
    END