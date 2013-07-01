
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

void serverLoop() {
  WiServer.server_task();
  return;
}

void initServer(boolean verbose) {
  if (verbose) {
    Serial.print(MYNAME);
    Serial.println(": initializing server.");
  }
  // Initialize WiServer and have it use the sendMyPage function to serve pages
  WiServer.init(sendMyPage);
  WiServer.enableVerboseMode(verbose); // i'm not sure what this is but i don't think i want it in production
  if (verbose) {
    Serial.print(MYNAME);
    Serial.println(": finished initializing server.");
  }
  return;
}


