#ifndef WEB_SERVER
#define WEB_SERVER

#include <WiFi.h>

inline WiFiServer server(80);

inline const char* ssid = "WIFI_LED_LAMP";
inline const char* password = "ledlamp";

void startWebServer() {
	
}

#endif
