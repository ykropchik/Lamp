#ifndef INITIALIZE_VARS
#define INITIALIZE_VARS

#include <FastLED.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <Settings.h>

inline int BRIGHTNESS = 100;

inline WiFiClient espClient;
inline PubSubClient client(espClient);

inline CRGB leds[NUM_LEDS];

inline uint8_t currentMode = 0;
inline const int MAX_DIMENSION = max(WIDTH, HEIGHT);

#endif