#ifndef RAINBOW_NOISE_EFFECT
#define RAINBOW_NOISE_EFFECT

#include "NoiseEffect.h"
#include <FastLED.h>
#include <Utility.h>

class RainbowNoiseEffect: public NoiseEffect {
public:
	RainbowNoiseEffect(uint8_t speed, uint8_t scale): NoiseEffect(RainbowColors_p, false, speed, scale) {}

	void generateFrame() {
		this->fillNoiseLED();
	}
};

#endif