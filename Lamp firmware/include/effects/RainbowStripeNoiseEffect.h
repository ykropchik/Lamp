#ifndef RAINBOW_SRIPE_NOISE_EFFECT
#define RAINBOW_SRIPE_NOISE_EFFECT

#include "NoiseEffect.h"
#include <FastLED.h>

class RainbowStripeNoise: public NoiseEffect {
public:
	RainbowStripeNoise(uint8_t speed, uint8_t scale): NoiseEffect(RainbowStripeColors_p, false, speed, scale) {}
	
	void generateFrame() {
		this->colorLoop = true;
		this->fillNoiseLED();
	}

};

#endif