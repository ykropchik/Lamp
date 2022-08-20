#ifndef PLASMA_NOISE_EFFECT
#define PLASMA_NOISE_EFFECT

#include "NoiseEffect.h"

class PlasmaNoiseEffect: public NoiseEffect {
public:
	PlasmaNoiseEffect(uint8_t speed, uint8_t scale): NoiseEffect(PartyColors_p, true, speed, scale) {}

	void generateFrame() {
		this->fillNoiseLED();
	}
};

#endif