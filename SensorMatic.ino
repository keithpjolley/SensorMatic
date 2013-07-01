
#define MYNAME "SensorMatic"
#define VERBOSE (1==1)   // 0 is false, !0 is true

// twiggle this LED whenever I get a ping
#define LED 13 // Onboard

unsigned long blinky  = 10 * 1000; // blink the LED every "blinky" seconds to let everyone know we are still running...
unsigned long lastblink = 0;

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  Serial.begin(57600);
  initNetwork(VERBOSE);
  initServer(VERBOSE);
  digitalWrite(LED, LOW);
  return;
}

void loop(){
  serverLoop();
  if (millis() - lastblink > blinky) {
    blinkme();
  }
  return;
}

// this throws an LED blink every once in a while so people know it's still running
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











