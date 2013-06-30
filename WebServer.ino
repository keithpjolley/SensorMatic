#define APP_WISERVER
#include <WiServer.h> 
//#include <WiShield.h>

// This is our page serving function that generates web pages
boolean sendMyPage(char* URL) {
  digitalWrite(LED, HIGH);
  if (VERBOSE) { 
    Serial.print("got page: ");
    Serial.println(URL);
  }
  // lowercase the URL
  for(int i=0; URL[i]; i++){
    URL[i] = tolower(URL[i]);
  }  
  boolean json = (strcmp(URL, "/json") == 0);
  boolean help = (strcmp(URL, "/help") == 0) || (strcmp(URL, "/?") == 0);
  if (help) {
    showHelp();
  } 
  else {
    getReadings(json, URL);
  }
  digitalWrite(LED, LOW);
  return true;
}




