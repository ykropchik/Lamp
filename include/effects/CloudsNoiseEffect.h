#ifndef CLOUDS_NOISE_EFFECT
#define CLOUDS_NOISE_EFFECT

#include "NoiseEffect.h"

class CloudsNoiseEffect: public NoiseEffect {
public:
	CloudsNoiseEffect(uint8_t speed, uint8_t scale): NoiseEffect(CloudColors_p, false, speed, scale) {}

	void generateFrame() {
		this->fillNoiseLED();
	}
};

#endif