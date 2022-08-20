#ifndef WAITING_EFFECT
#define WAITING_EFFECT

#include "Effect.h"
#include <FastLED.h>
#include <Utility.h>

class WaitingEffect: public Effect {
public:
	WaitingEffect(uint8_t speed = 128, uint8_t scale = 5, CRGB color = CRGB(240,127,19)): Effect(speed, scale, color) {}

	void generateFrame() {
		for (uint8_t i = 0; i < WIDTH; i++) {
			leds[getPixelNumber(i, 0)] = CRGB(66, 170, 255);
		}

		for (int i = 1; i < HEIGHT; i++) {
			uint8_t bottom = i - scale <= 1 ? 1 : i - scale;

			for (uint8_t y = i; y >= bottom; y--) {
				for (uint8_t x = 0; x < WIDTH; x++) {
					drawPixelXY(x, y, getPixColorXY(x, y - 1));
				}

				for (uint8_t x = 0U; x < WIDTH; x++) {
					fadePixel(x, 0, 30);
				}

			}
			FastLED.show();
			delay(5);
		}

		delay(200 * map(this->speed, 0, 255, 0, 2));

		for (int i = HEIGHT - 2; i >= 0; i--) {
			uint8_t top = i + scale >= HEIGHT - 2 ? HEIGHT - 2 : i + scale;

			for (uint8_t y = i; y <= top; y++) {
				for (uint8_t x = 0; x < WIDTH; x++) {
					drawPixelXY(x, y, getPixColorXY(x, y + 1));
				}

				for (uint8_t x = 0U; x < WIDTH; x++) {
					fadePixel(x, HEIGHT - 1, 30);
				}

			}
			FastLED.show();
			delay(5);
		}
	};
};

#endif