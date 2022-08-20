#ifndef MATRIX_EFFECT
#define MATRIX_EFFECT

#include "Effect.h"
#include <FastLED.h>
#include <Utility.h>

class MatrixEffect: public Effect {
public:
	MatrixEffect(uint8_t speed, uint8_t scale): Effect(speed, scale) {}

	void generateFrame() {
		for (uint8_t x = 0U; x < WIDTH; x++) {
			// заполняем случайно верхнюю строку
			uint32_t thisColor = getPixColorXY(x, HEIGHT - 1U);
			if (thisColor == 0U)
				drawPixelXY(
					x, HEIGHT - 1U,
					0x00FF00 * (random(0, 100 - this->scale) == 0U));
			else if (thisColor < 0x002000)
				drawPixelXY(x, HEIGHT - 1U, 0U);
			else
				drawPixelXY(x, HEIGHT - 1U, thisColor - 0x002000);
		}

		// сдвигаем всё вниз
		for (uint8_t x = 0U; x < WIDTH; x++) {
			for (uint8_t y = 0U; y < HEIGHT - 1U; y++) {
				drawPixelXY(x, y, getPixColorXY(x, y + 1U));
			}
		}
	}
};

#endif