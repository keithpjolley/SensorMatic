
#include <WiServer.h>
#define MYNAME "SensorMatic"
#define VERBOSE (1==1)   // 0 is false, !0 is true

// twiggle this LED whenever I get a ping
#define LED 13 // Onboard

unsigned long blinky  = 10 * 1000; // blink the LED every "blinky" seconds to let everyone know we are still running...
unsigned long lastblink = 0;

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);

  if (VERBOSE) {
    Serial.begin(57600);
    Serial.print(MYNAME);
    Serial.println(": initializing server.");
  }

initNetwork();
  

  // Initialize WiServer and have it use the sendMyPage function to serve pages
  WiServer.init(sendMyPage);
  WiServer.enableVerboseMode(VERBOSE); // i'm not sure what this is but i don't think i want it in production

  if (VERBOSE) {
    Serial.begin(57600);
    Serial.print(MYNAME);
    Serial.println(": server started.");
  }
  digitalWrite(LED, LOW);
  return;
}


void loop(){
  // Run WiServer
  WiServer.server_task();
  if (millis() - lastblink > blinky) {
    blinkme();
  }
  return;
}

void blinkme() {
  for (int i=0; i<2; i++) {    
    digitalWrite(LED, HIGH);
    delay(50);
    digitalWrite(LED, LOW);
    delay(50);
  }
  lastblink = millis();
  return;
}








