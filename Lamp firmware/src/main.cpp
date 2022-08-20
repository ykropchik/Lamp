#include <Arduino.h>
#include <FastLED.h>
#include <Effects.h>
#include <Settings.h>
#include <Utility.h>
#include <WifiUtility.h>
#include <WebServer.h>
#include <BedLamp.h>
#include <LampControl.h>
#include <Mqtt.h>

BedLamp lamp = BedLamp(
	effects,
	18U,
	waiting,
	error,
	warning,
	100
);
GButton *btn = new GButton(BTN_PIN, LOW_PULL);
LampControl lampControl = LampControl(&lamp, btn);

TaskHandle_t lampControlTaskHandler;
void lampControlTask(void *params) {
	delay(100);
	btn->resetStates();
	while (true) {
		lampControl.tick();
	}
}

void setup() {
	Serial.begin(9600);

	FastLED.addLeds<WS2812, PIN, COLOR_ORDER>(leds, NUM_LEDS);
	FastLED.setBrightness(BRIGHTNESS);
	
	if (CURRENT_LIMIT > 0) {
		FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
	}

	FastLED.clear();
	FastLED.show();

	connection();
	mqttInitialize();

	xTaskCreatePinnedToCore(lampControlTask, "connectionWaiting", 1000, NULL, 1, &lampControlTaskHandler, 1);
}

void loop() {
	Serial.println(WiFi.status());
	switch (lamp.getStatus()) {
		case BedLampStatus::WiFiConnecting: 
			lamp.waitingTick();
			break;
		case BedLampStatus::OFF:
			break;
		case BedLampStatus::RegularMode: 
			lamp.effectTick();
			break;
		case BedLampStatus::AlarmMode:
			break;
	}
}