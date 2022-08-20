#ifndef SPARKLES_EFFECT
#define SPARKLES_EFFECT

#include "Effect.h"
#include <Utility.h>
#include <FastLED.h>

class SparklesEffect: public Effect {
private:
	uint8_t fadeOutSpeed;
public:
	SparklesEffect(uint8_t speed, uint8_t scale, uint8_t fadeOutSpeed = 70): Effect(speed, scale) {
		this->fadeOutSpeed = fadeOutSpeed;
	}

	uint8_t getFadeOutSpeed() {
		return this->fadeOutSpeed;
	}

	void setFadeOutSpeed(uint8_t newFadeOutSpeed) {
		this->fadeOutSpeed = newFadeOutSpeed;
	}

	void generateFrame() {
		for (uint8_t i = 0; i < this->scale; i++) {
			uint8_t x = random(0U, WIDTH);
			uint8_t y = random(0U, HEIGHT);
			if (getPixColorXY(x, y) == 0U) {
				leds[getPixelNumber(x, y)] = CHSV(random(0U, 255U), 255U, 255U);
			}
		}
		fader(fadeOutSpeed);
	}
};

#endif