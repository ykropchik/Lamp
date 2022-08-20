#ifndef ZEBRA_NOISE_EFFECT
#define ZEBRA_NOISE_EFFECT

#include "NoiseEffect.h"

class ZebraNoiseEffect: public NoiseEffect {
public:
	ZebraNoiseEffect(uint8_t speed, uint8_t scale): NoiseEffect(PartyColors_p, true, speed, scale) {
		fill_solid(this->palette, 16, CRGB::Black);
		this->palette[0] = CRGB::White;
		this->palette[4] = CRGB::White;
		this->palette[8] = CRGB::White;
		this->palette[12] = CRGB::White;
	}
	
	void generateFrame() {
		this->fillNoiseLED();
	}
};

#endif