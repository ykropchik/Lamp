#ifndef WIFI
#define WIFI

#include <WiFi.h>
#include <Vars.h>
#include <Effects.h>

void connection() {
  // auto previousLampStatus = lampStatus;
  // lampStatus = WiFiConnecting;

  WiFi.begin("ykropchik", "pasholnaxui");
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connected to the WiFi");
  // lampStatus = previousLampStatus;
}

void connectionWaiting(void *params) {
  return;
  // wifiWaiting(CRGB(66, 170, 255));
  // fireRoutine(true);
  // FastLED.show();
}

#endif