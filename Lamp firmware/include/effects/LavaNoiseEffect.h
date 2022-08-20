#ifndef LAVA_NOISE_EFFECT
#define LAVA_NOISE_EFFECT

#include "NoiseEffect.h"

class LavaNoiseEffect: public NoiseEffect {
public:
	LavaNoiseEffect(uint8_t speed, uint8_t scale): NoiseEffect(LavaColors_p, false, speed, scale) {}

	void generateFrame() {
		this->fillNoiseLED();
	}
};

#endif