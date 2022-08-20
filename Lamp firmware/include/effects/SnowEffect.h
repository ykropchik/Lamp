#ifndef SNOW_EFFECT
#define SNOW_EFFECT

#include <Effects/effect.h>
#include <FastLED.h>
#include <Utility.h>

class SnowEffect: public Effect {
public:
	SnowEffect(uint8_t speed, uint8_t scale): Effect(speed, color) {};

	void generateFrame() {
		for (uint8_t x = 0U; x < WIDTH; x++) {
			for (uint8_t y = 0U; y < HEIGHT - 1; y++) {
				drawPixelXY(x, y, getPixColorXY(x, y + 1U));
			}
		}

		for (uint8_t x = 0U; x < WIDTH; x++) {
			// заполняем случайно верхнюю строку
			// а также не даём двум блокам по вертикали вместе быть
			if (getPixColorXY(x, HEIGHT - 2U) == 0U &&
				(random(0, 100 - this->scale) == 0U))
				drawPixelXY(x, HEIGHT - 1U, 0xE0FFFF - 0x101010 * random(0, 4));
			else
				drawPixelXY(x, HEIGHT - 1U, 0x000000);
		}
	}
};

#endif