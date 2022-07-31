#ifndef MADNESS_NOISE_EFFECT
#define MADNESS_NOISE_EFFECT

#include "NoiseEffect.h"
#include <FastLED.h>
#include <Utility.h>

class MadnessNoiseEffect: public NoiseEffect {

public:
	MadnessNoiseEffect(uint8_t speed, uint8_t scale): NoiseEffect(PartyColors_p, false, speed, scale) {}

	void generateFrame() {
		this->fillnoise8();
		for (uint8_t i = 0; i < WIDTH; i++)
		{
			for (uint8_t j = 0; j < HEIGHT; j++)
			{
			CRGB thisColor = CHSV(this->noise[j][i], 255, this->noise[i][j]);
			drawPixelXY(i, j, thisColor);
			}
		}
	}
};

#endif