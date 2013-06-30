
// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN       2  // Digible
#define PHOTOCELLPIN 0  // Analog
#define IRSENSORPIN  1  // Analog

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);

// Reading temperature or humidity takes about 250 milliseconds!
// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
float humidity  = -999;
float temp_c    = -999;
float temp_f    = -999;
int   photocell = -999;
int   irSensor  = -999;

unsigned long wait    = 3 * 1000; // always wait more than three seconds before reporting
unsigned long last    = -2*wait;
unsigned long current = 0;

void showHelp() {
  WiServer.print("<p><h2>");
  WiServer.print(MYNAME);
  WiServer.print(" help</h2></p>");
  WiServer.print("<p>point your browser at:<ul>");
  WiServer.print("  <li><a href=\"/help\">/help</a> to get this helpful information (but i suspect you already knew that.</li>");
  WiServer.print("  <li><a href=\"/json\">/json</a> to get readings in JSON format.</li>");
  WiServer.print("  <li><a href=\"/\">/</a> to get readings in good old fashioned html.</li>");
  WiServer.print("</ul></p>");
  WiServer.print("<p>Project homepage: <a href=\"https://github.com/keithpjolley/TempIRHumPho/\">https://github.com/keithpjolley/TempIRHumPho</a></p>");
  WiServer.print("<p></p>");
  WiServer.print("<p>Humidity returns a percentage from 0.00 to 100.0.</p>");
  WiServer.print("<p>Temperature readings hopefully are self explanitory.</p>");
  WiServer.print("<p>Photocell returns an integer from 0 (dark) to 1024 (very bright).</p>");
  WiServer.print("<p>Infrared Proximity returns an integer from 0 to 1024. The curve of values returned is complex. ");
  WiServer.print("See page 5, Figure 2, of <a href=\"http://sharp-world.com/products/device/lineup/data/pdf/datasheet/gp2y0a21yk_e.pdf\">");
  WiServer.print("the documentation</a> to understand the output better.</p>");
  WiServer.print("<p>Milliseconds is how old this data is.</p>");
  WiServer.print("<p>The temperature/humidity sensor takes about 2 seconds to update. Values may be a second or two old.</p>");
  WiServer.print("<p></p>");
}

// all this html/json stuff should not be in here. i should create a struct and export that back to the webserver function and let the webserver code sort it out.
void getReadings(boolean json, char* URL) {
  // if it's been long enough, get new sensor readings, if not, use the old values
  current = millis();
  if (current - last > wait) {
    humidity = dht.readHumidity();
    temp_c = dht.readTemperature();
    temp_f = temp_c * 9.0/5.0 + 32.0;
    photocell = analogRead(PHOTOCELLPIN);
    irSensor = analogRead(IRSENSORPIN);
    last = millis();
  }
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(temp_c) || isnan(humidity)) {
    WiServer.println("Failed to read from DHT");
    Serial.println("Failed to read from DHT");
  } 
  else {
    if (json) {
      // Use WiServer’s print and println functions to write out the page content
      WiServer.println("{");
      WiServer.print("  \"humidity_%\": "); 
      WiServer.print(humidity);
      WiServer.println(",");
      WiServer.print("  \"temperature_celsius\": "); 
      WiServer.print(temp_c);
      WiServer.println(",");
      WiServer.print("  \"temperature_fahrenheit\": "); 
      WiServer.print(temp_f);
      WiServer.println(",");
      WiServer.print("  \"photocell\": "); 
      WiServer.print(photocell);
      WiServer.println(",");
      WiServer.print("  \"infrared\": "); 
      WiServer.print(irSensor);
      WiServer.println(",");
      WiServer.print("  \"milliseconds\": "); 
      WiServer.print(millis()-last);
      WiServer.println("");
      WiServer.println("}");
    } 
    else {
      WiServer.print("<!DOCTYPE html><html><head><title>");
      WiServer.print(MYNAME);
      WiServer.print(": ");
      WiServer.print(URL);
      WiServer.print("</title></head><body>");
      WiServer.print("<h2>");
      WiServer.print( MYNAME);
      WiServer.print("</h2>");
      WiServer.print("<pre>\n\n");
      WiServer.print("Humidity: "); 
      WiServer.print(humidity);
      WiServer.print("%\nTemperature: "); 
      WiServer.print(temp_c);
      WiServer.print("C\nTemperature: ");
      WiServer.print(temp_f);
      WiServer.print("F\nphotocell: ");
      WiServer.print(photocell);
      WiServer.print("\nInfraRed: ");
      WiServer.print(irSensor);
      WiServer.print("\nMilliseconds: ");
      WiServer.print(millis()-last);
      WiServer.print("\n</pre>");
      WiServer.print("<a href=\"/help\">documentation</a>");
      WiServer.print("</body></html>");
    }
  }
}












