// this is the code that i got to work in the video.
// be sure to edit the begining of uip.c to match apps-conf.h  -- sigh

#include <SPI.h>
#include <Ethernet.h>
#include "mypassword.h"  // put my passwords in this file and put this file in .gitignore

#define WIRELESS_MODE_INFRA	1
#define WIRELESS_MODE_ADHOC	2

// Wireless configuration parameters ----------------------------------------
//unsigned char local_ip[]       = { 
//  192,168,1,132 };	// IP address of WiShield
//unsigned char gateway_ip[]     = { 
//  192,168,1,1 };	// router or gateway IP address
//unsigned char subnet_mask[]    = { 
//  255,255,255,0 };	// subnet mask for the local network
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
  YOUR_WEP_PASSWD_HERE // Key 0  -- looks like: 0xDE, 0xAD, 0xBE, OxEF, ...
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

void initNetwork() {
  byte mac[] = {  
    0x00, 0x1e, 0xc0, 0x4, 0xca, 0x44     };

  // Initialize the Ethernet client library
  // with the IP address and port of the server 
  // that you want to connect to (port 80 is default for HTTP):
  EthernetClient client;
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();
  return;
}



