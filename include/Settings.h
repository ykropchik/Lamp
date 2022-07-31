#ifndef SETTINGS
#define SETTINGS

// MQTT Broker
inline const char *mqtt_broker = "m8.wqtt.ru";
inline const char *topic = "esp8266/status";
inline const char *mqtt_username = "u_HS4YEN";
inline const char *mqtt_password = "GlyRjJ24";
inline const int mqtt_port = 12308;

#define PIN 4

#define BTN_PIN 33

#define HEIGHT 16
#define WIDTH 16
#define SEGMENTS 1 // Колличество диодов на один контроллер
#define NUM_LEDS WIDTH*HEIGHT
#define MATRIX_TYPE 0

#define COLOR_ORDER GRB
#define CURRENT_LIMIT 2000
#define MAX_BRIGHTNESS 255

#endif