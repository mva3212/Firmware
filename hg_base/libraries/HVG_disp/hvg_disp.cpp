// hvg_comms.cppi
// Author: Rowan Gifford
// Date: 23/06/2014
// 20x4 Character Display Driver
// Raystar RX2004A-BIW

#include <hvg_disp.h>
//#include <arduino.h>

// Arduino I2C driver, requires twi.h & twi.c
extern "C" {
  #include <twi.h>
}

// Initialise I2C module
// Uses Arduino TWI driver
// Inputs: None
// Returns: None
void HVGDISP::initI2C( void ) { twi_init(); }

// Send initialisation sequence to display
// Inputs:
// pin - Unsigned char, Reset pin for the display
// Returns: Unsigned char, Result of I2C transmission:
// 0 = Success
// 2 = Error: address send, nack received
// 3 = Error: data send, nack received
// 4 = Other twi error
uint8_t HVGDISP::initDisplay(uint8_t pin) {
/*
  // * Delay 5ms, wait for power to be stable
  delay(10);

  // * Pull RESET low
  digitalWrite(pin, 0);

  // Hold low for 20us
  delay(50);

  // Set RESET high again
  digitalWrite(pin, 1);

  // Delay 1ms after reset before init
  delay(100);
*/
  twi_init();

  // Send initialisation sequence to display and return result
  return twi_writeTo(0x3C, (uint8_t *)SSD1803a_init_seq, 30, 1, 1);
}

// Draws character c on display
// Inputs:
// c - Unsigned char, the data to be displayed. ASCII code.
// Returns: Unsigned char, Result of I2C transmission:
// 0 = Success
// 2 = Error: address send, nack received
// 3 = Error: data send, nack received
// 4 = Other twi error
uint8_t HVGDISP::drawChar(uint8_t c) {

  // Put character to be display in sequence array
  SSD1803a_writeChar_seq[1] = c;

  // Send data to display and return result
  return twi_writeTo(0x3C, SSD1803a_writeChar_seq, 2, 1, 1);
}

// Sets position on the display
// Inputs:
// x - Unsigned char, Represent x position in the range 0 - (WIDTH-1)
// y - Unsigned char, Represent the line to write on in the range 0 - (HEIGHT-1)
// (0,0) is top left
// Returns: Unsigned char, Result of I2C transmission:
// 0 = Success
// 2 = Error: address send, nack received
// 3 = Error: data send, nack received
// 4 = Other twi error
// 5 = x or y out of bounds
uint8_t HVGDISP::setPrintPos(uint8_t x, uint8_t y) { 

	// Check to see if dimensions are in bound
	if ((x>=WIDTH) || (y>=HEIGHT)) return 5;

	//Row 1 is DDRAM address 0x00~0x13, Row 2 0x20~0x33, Row 3 0x40~0x53, Row 4 0x60~0x73
	// Check which row we are on and add appropriate DDRAM base
	if (y==0) SSD1803a_setPrintPos_seq[3] |= x;
	else if (y==1) SSD1803a_setPrintPos_seq[3] |= x + 0x20;
	else if (y==2) SSD1803a_setPrintPos_seq[3] |= x + 0x40;
	else if (y==3) SSD1803a_setPrintPos_seq[3] |= x + 0x60;

	// Send command to display and return result
	return twi_writeTo(0x3C, SSD1803a_setPrintPos_seq, 4, 1, 1);
  //return 0;
}

// Clears to screen by blanking the conents of display DRAM and reset position to 0,0
// Inputs: None
// Returns: Unsigned char, Result of I2C transmission:
// 0 = Success
// 2 = Error: address send, nack received
// 3 = Error: data send, nack received
// 4 = Other twi error
uint8_t HVGDISP::clearDisplay ( void ) { return twi_writeTo(0x3C, SSD1803a_clearDisplay_seq, 2, 1, 1); }

// Calculates the required position of a string on a line to center it
// Inputs:
// buffer - Char *, Pointer to string to center on display
// Returns:
// Unsigned char, Center position of the string on a line if it fits, 0 if string is too big
uint8_t HVGDISP::centerString(char * buffer) {
  
  uint8_t count = 0; // Loop variable
  
  // Count the number of characters stored in buffer (look for null terminator)
  for (;;) {
    if (buffer[count]==0) break;
    count++;
  }

  // If string is to big (i.e. as long as or longer than WIDTH) return 0
  if (count < WIDTH) return ((WIDTH-count)/2);
  else return 0;
}
