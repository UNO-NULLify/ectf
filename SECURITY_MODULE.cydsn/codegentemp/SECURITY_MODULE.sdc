# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Admin\Documents\GitHub\ectf\SECURITY_MODULE.cydsn\SECURITY_MODULE.cyprj
# Date: Tue, 20 Mar 2018 01:11:26 GMT
#set_units -time ns
create_clock -name {DB_UART_SCBCLK(FFB)} -period 733.33333333333326 -waveform {0 366.666666666667} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {CyRouted1} -period 66.666666666666657 -waveform {0 33.3333333333333} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFCLK} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 66.666666666666657 -waveform {0 33.3333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFCLK} -period 66.666666666666657 -waveform {0 33.3333333333333} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySYSCLK} -period 66.666666666666657 -waveform {0 33.3333333333333} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {DB_UART_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 11 23} [list]
create_generated_clock -name {CARD_UART_IntClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 17 33} [list [get_pins {ClockBlock/udb_div_0}]]


# Component constraints for C:\Users\Admin\Documents\GitHub\ectf\SECURITY_MODULE.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Admin\Documents\GitHub\ectf\SECURITY_MODULE.cydsn\SECURITY_MODULE.cyprj
# Date: Tue, 20 Mar 2018 01:11:22 GMT
