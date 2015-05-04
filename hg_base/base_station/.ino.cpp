//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2015-02-19 19:32:09

#include "Arduino.h"
#include <hvg_comms.h>
#include <EEPROM.h>
#include "DisplayStrings.h"
#include <NRF24.h>
#include <hvg_disp.h>
#include <SPI.h>
void setup() ;
void loop(void) ;
ISR(TIMER3_COMPA_vect) ;
void displayPlatformRegistrationGuid();
void displayPlatformMessages();
void draw(void)  ;
unsigned char get_string_to_display(char id) ;
void disp_loop(void) ;
unsigned char get_new_pid() ;
void printDebug(char* s);
void printDebug(unsigned char s);


#include "base_station.ino"
