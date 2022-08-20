#ifndef MQTT
#define MQTT

#include <PubSubClient.h>
#include <Vars.h>
#include <Settings.h>

// ------------- Settings ----------------------
#define MQTT_BROKER "m8.wqtt.ru"
#define TOPIC "/lamp/test"
#define MQTT_USERNAME "u_HS4YEN"
#define MQTT_PASSWORD "GlyRjJ24"
#define MQTT_PORT 12308
#define MQTT_CLIENT_ID "smart-lamp-"

// inline const char *mqtt_broker = "m8.wqtt.ru";
// inline const char *topic = "lamp/test";
// inline const char *mqtt_username = "u_HS4YEN";
// inline const char *mqtt_password = "GlyRjJ24";
// inline const int mqtt_port = 12308;

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
      Serial.print((char) payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
}

void mqttInitialize() {
  client.setServer(MQTT_BROKER, MQTT_PORT);
  client.setCallback(callback);

  while (!client.connected()) {
      String client_id = MQTT_CLIENT_ID + String(WiFi.macAddress());
      Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());

      if (client.connect(client_id.c_str(), MQTT_USERNAME, MQTT_PASSWORD)) {
          Serial.println("Public emqx mqtt broker connected");
      } else {
          Serial.print("failed with state ");
          Serial.print(client.state());
          delay(2000);
      }
  }
  
  client.subscribe(TOPIC);
}

#endif