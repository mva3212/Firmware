// hvg_comms.h
// Author: Mathieu Stephan
// Copyright (C) 2013 Mathieu Stephan

#ifndef hvg_comms_h
#define hvg_comms_h

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <wiring.h>
#include <pins_arduino.h>
#endif

#include <EEPROM.h>
#include <SPI.h>
#include <Ethernet.h>

/***************************/
/*          DBG DEF        */
/***************************/
// Comment if you don't want debug info
#define HTTP_DBG_OUTPUT
#define ETH_DBG_OUTPUT
#define ETH_ADV_DBG_OUTPUT
#define API_TEST
// For the first version of the hardware
// Commented out OLD_HW_VERSION define RG 30/07/2014
//#define OLD_HW_VERSION

/***************************/
/*          JSON           */
/***************************/
// Length of our init GUID packet
#define INIT_PACKET_LENGTH	53
// Length of our registered query packet
#define QUERY_REG_LENGTH	97
// Fixed length of our json data for report
#define REPORT_FIX_LENGTH 	130
// Additional length for each platform report
#define REPORT_ITEM_LENGTH  127

/***************************/
/*          PROTOCOL       */
/***************************/
// Max platforms in a setup
#define MAX_PLATFORMS   	40
// Timeout to consider we lost the sensor station
#define TIMEOUT_PLAT_REPORT	40
// GUID number of bytes
#define GUID_LGTH       	16
// Empty platform ID
#define NO_ID_PID       	0

/***************************/
/*          RETURNS        */
/***************************/
#define RETURN_NOK			0
#define	RETURN_OK			1
#define RETURN_ETH_PB		2
#define RETURN_GUID_PB		3
#define RETURN_NO_CON_PB	4
#define RETURN_TIMEOUT		5
#define RETURN_NFOUND		6
#define RETURN_NREGISTERED	7
#define RETURN_DHCP_TIMEOUT	8
#define RETURN_SOCKET_PB	9
#define RETURN_TIMEOUT_TCP	10


/***************************/
/*          MACROS         */
/***************************/
#define htons(x)	((((x) >> 8) & 0xff) | (((x) & 0xff) << 8))

// Last message received from a platform
typedef struct _platform_log
{
  unsigned char platform_id;
  unsigned char last_mess_sec;
  unsigned short temperature;
  unsigned short humidity;
  unsigned short temp_ground;
  unsigned short moisture;
  unsigned short lux;
  unsigned short ir;
}
message_log_t, *p_message_log_t;

class HVGCOMMS
{
  public:

	// Contructor, to which we pass the eeprom addresses of the guid
	HVGCOMMS(uint8_t eth_ss_pin, uint16_t guid_init_addr, uint16_t guid_reged_addr, uint16_t guid_addr);

	// Convert hex to string
	void convert_hex_to_hexstring(char* hex_string, char* string, uint8_t nb_bytes);

	// Parse http answer and look for a specific json field
	uint8_t parse_close_http_answer_for_field(char* field, char* val);

	// Send report data (internal call)
	void send_report_text(uint8_t* mac_addr, message_log_t* mess_log);

	// Send data to Harvestgeek server (called by arduino)
	void send_report(uint8_t* mac_addr, message_log_t* mess_log);

	// Convert an ascii hex string to a string
	void convert_hexstring_to_hex(char* string, char* result);

	// Know the length of our report data
	uint16_t get_report_data_length(message_log_t* mess_log);

	// Send GUID init text
	void send_init_text(uint8_t* mac_addr, bool has_guid);

	// Initialize the connection to the server
	uint8_t init_HTTP_POST_connect(uint16_t nb_bytes);

	// Convert an int to a string
	void int_to_string(uint16_t value, char* string);

	// Ask the server is the user is registered
	uint8_t get_register_status(uint8_t* mac_addr);

	// Ask GUID to the server
	uint8_t get_new_guid(uint8_t* mac_addr);

	// Init the HTTP connection
	uint8_t init_HTTP_connect(void);

	// Called to init the library
    uint8_t init(uint8_t* mac_addr);

	// Homemade strlen
	uint16_t hm_strlen(char* ptr);

	// Big buffer for communications
	uint8_t hvg_comms_buffer[100];

	// Our platform GUID
	char guid[GUID_LGTH];

  private:

  	// Ethernet client
  	EthernetClient w5100;

  	// Harvest geek server
  	char pucHvgServer[20];

	// Where the bool is stored in the eeprom
	uint16_t _guid_init_addr;

	// Where the bool is stored in the eeprom
	uint16_t _guid_reged_addr;

	// Ethernet chip select pin
	uint8_t _eth_ss_pin;

	// Where the guid is stored in the eeprom
	uint16_t _guid_addr;

	// What is our server ip
	//uint8_t ip_server[4];

	// Are we connected?
	bool eth_configured;
};

#endif
