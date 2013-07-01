// be sure to edit the begining of uip.c to match apps-conf.h  -- sigh

#define APP_WISERVER
#include <WiServer.h>

#define WIRELESS_MODE_INFRA	1
#define WIRELESS_MODE_ADHOC	2

#define YOUR_SSID_NAME_HERE   "dorknet"
#define YOUR_WPA_PASSWD_HERE "12345678901234567890123456"

// Wireless configuration parameters ----------------------------------------
unsigned char local_ip[]       = {  
  192,168,1,132 };	// IP address of WiShield
unsigned char gateway_ip[]     = {   
  192,168,1,1 };	// router or gateway IP address
unsigned char subnet_mask[]    = {   
  255,255,255,0 };	// subnet mask for the local network
const prog_char ssid[] PROGMEM = {  
  YOUR_SSID_NAME_HERE };		// (ssid name in quotes) max 32 bytes
unsigned char security_type = 1;	// 0 - open; 1 - WEP; 2 - WPA; 3 - WPA2
// WPA/WPA2 passphrase
const prog_char security_passphrase[] PROGMEM = {
  YOUR_WPA_PASSWD_HERE
};	// max 64 characters  -- passwd in quotes
// WEP 128-bit keys
// sample HEX keys
prog_uchar wep_keys[] PROGMEM = {
  0x12, 0x34, 0x56, 0x78, 0x90, 0x12, 0x34, 0x56, 0x78, 0x90, 0x12, 0x34, 0x56, // Key 0
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Key 1
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Key 2
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	// Key 3
};

// setup the wireless mode
// infrastructure - connect to AP
// adhoc - connect to another WiFi device
unsigned char wireless_mode = WIRELESS_MODE_INFRA;
unsigned char ssid_len;
unsigned char security_passphrase_len;

void initNetwork(boolean verbose) {

  if (verbose) {
    Serial.print(MYNAME);
    Serial.println(": initializing network.");
  }

  // um, there's no here, here.

  if (verbose) {
    Serial.println("");
    Serial.print(MYNAME);
    Serial.println(": finished initializing network.");
  }
  return;
}








