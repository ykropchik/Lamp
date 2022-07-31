#ifndef OCEAN_NOISE_EFFECT
#define OCEAN_NOISE_EFFECT

#include "NoiseEffect.h"
#include <FastLED.h>

class OceanNoiseEffect: public NoiseEffect {
public:
	OceanNoiseEffect(uint8_t speed, uint8_t scale): NoiseEffect(OceanColors_p, false, speed, scale) {}

	void generateFrame() {
		this->fillNoiseLED();
	}
};

#endif