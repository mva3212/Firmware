#ifndef DisplayString_H_
#define DisplayString_H_
#include <avr/pgmspace.h>


const static char eth_pb[] PROGMEM = "Ethernet Problem";
const static char dhcp_pb[] PROGMEM = "DHCP Problem";
const static char init_start[] PROGMEM = "Initializing";
const static char init_done[] PROGMEM = "Initialization done";
const static char no_eth_conn[] PROGMEM = "No Internet Connection";
const static char comm_pb[] PROGMEM = "Communication problem";
const static char dev_reg[] PROGMEM = "Register your device";
const static char nrf_pb[] PROGMEM = "NRF problem";

#endif
