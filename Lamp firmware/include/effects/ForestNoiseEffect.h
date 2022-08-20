#ifndef FOREST_NOISE_EFFECT
#define FOREST_NOISE_EFFECT

#include "NoiseEffect.h"
#include <FastLED.h>

class ForestNoiseEffect: public NoiseEffect {
public:
	ForestNoiseEffect(uint8_t speed, uint8_t scale): NoiseEffect(ForestColors_p, false, speed, scale) {}

	void generateFrame() {
		this->fillNoiseLED();
	}
};

#endif