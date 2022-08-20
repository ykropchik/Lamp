#ifndef RAINBOW_EFFECT
#define RAINBOW_EFFECT

#include "Effect.h"
#include <Utility.h>
#include <FastLED.h>

enum RainbowType {
	Vertical,
	Horizontal,
	Diagonal
};

class RainbowEffect: public Effect {
private:
	RainbowType type;
	int scale;
	int hue;

	void rainbowVertical() {
		this->hue += 4;
		for (uint8_t j = 0; j < HEIGHT; j++) {
			CHSV thisColor =
				CHSV((uint8_t)(hue + j * this->scale), 255, 255);
			for (uint8_t i = 0U; i < WIDTH; i++) {
				drawPixelXY(i, j, thisColor);
			}
		}
	}

	void rainbowHorizontal() {
		this->hue += 4;
		for (uint8_t i = 0U; i < WIDTH; i++) {
			CHSV thisColor =
				CHSV((uint8_t)(hue + i * this->scale), 255, 255);
			for (uint8_t j = 0U; j < HEIGHT; j++) {
				drawPixelXY(i, j, thisColor);
			}
		}
	}

	void rainbowDiagonal() {
		this->hue += 8;
		for (uint8_t i = 0U; i < WIDTH; i++) {
			for (uint8_t j = 0U; j < HEIGHT; j++) {
				float twirlFactor = 3.0F * (this->scale / 100.0F);
				CRGB thisColor = CHSV(
					(uint8_t)(hue + (float)(WIDTH / HEIGHT * i + j * twirlFactor) *
										(float)(255 / MAX_DIMENSION)),
					255, 255);
				drawPixelXY(i, j, thisColor);
			}
		}
	}

public:
	RainbowEffect(RainbowType type, uint8_t speed, uint8_t scale): Effect(speed, scale) {
		this->type = type;
		this->hue = 0;
	}

	void generateFrame() {
		switch (this->type) {
		case Vertical:
			this->rainbowVertical();
			break;
		case Horizontal:
			this->rainbowHorizontal();
			break;
		case Diagonal:
			this->rainbowDiagonal();
			break;
		}
	}
};

#endif