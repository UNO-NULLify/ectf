# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Admin\Documents\GitHub\ectf\CARD.cydsn\CARD.cyprj
# Date: Sat, 17 Mar 2018 18:29:01 GMT
#set_units -time ns
create_clock -name {USB_UART_SCBCLK(FFB)} -period 708.33333333333326 -waveform {0 354.166666666667} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {CyRouted1} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFCLK} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFCLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySYSCLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {USB_UART_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 17 35} -nominal_period 708.33333333333326 [list]
create_generated_clock -name {ATM_UART_IntClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 27 53} -nominal_period 1083.3333333333333 [list [get_pins {ClockBlock/udb_div_0}]]


# Component constraints for C:\Users\Admin\Documents\GitHub\ectf\CARD.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Admin\Documents\GitHub\ectf\CARD.cydsn\CARD.cyprj
# Date: Sat, 17 Mar 2018 18:28:58 GMT
