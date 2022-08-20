#ifndef COLOR_EFFECT
#define COLOR_EFFECT

#include "Effect.h"
#include <FastLED.h>
#include <Vars.h>
#include <Utility.h>

class ColorEffect: public Effect {
public:
	ColorEffect(CRGB color): Effect(50, 0, color) {}

	void generateFrame() {
		fillAll(this->color);
	}
};

#endif