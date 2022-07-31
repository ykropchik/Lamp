#ifndef WIFI
#define WIFI

#include <WiFi.h>
#include <Vars.h>
#include <Effects.h>

void connection(void *params) {
  // auto previousLampStatus = lampStatus;
  // lampStatus = WiFiConnecting;

  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //     delay(500);
  //     Serial.println("Connecting to WiFi..");
  // }
  
  // lampStatus = previousLampStatus;
}

void connectionWaiting(void *params) {
  return;
  // wifiWaiting(CRGB(66, 170, 255));
  // fireRoutine(true);
  // FastLED.show();
}

#endif