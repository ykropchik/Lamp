// #include <WiFi.h>
// #include <vars.h>
// #include <effects.h>

// void connection(void *params) {
//   auto previousLampStatus = lampStatus;
//   lampStatus = WiFiConnecting;

//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//       delay(500);
//       Serial.println("Connecting to WiFi..");
//   }
  
//   lampStatus = previousLampStatus;
// }

// void connectionWaiting(void *params) {
//   while (true) {
//     wifiWaiting(CRGB(66, 170, 255));
//   }
// }

// void connectToWifi() {
//   TaskHandle_t connectionHandler;
//   TaskHandle_t waitingHandler;
//   xTaskCreatePinnedToCore(connection, "connection", 1000, NULL, 1, &connectionHandler, 0);
//   xTaskCreatePinnedToCore(connectionWaiting, "connectionWaiting", 1000, NULL, 1, &connectionHandler, 0);
// }