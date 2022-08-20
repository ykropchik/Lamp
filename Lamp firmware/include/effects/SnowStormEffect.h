#ifndef SNOW_STORM_EFFECT
#define SNOW_STORM_EFFECT

#include "Effect.h"
#include <FastLED.h>
#include <Utility.h>

class SnowStormEffect: public Effect {
private:
	uint8_t snowDense;
	uint8_t snowSaturation;
	uint8_t snowTailStep;

public:
	SnowStormEffect(uint8_t speed, uint8_t scale, uint8_t snowDense = 60, uint8_t snowSaturation = 0, uint8_t snowTailStep = 100): Effect(speed, scale) {
		this->snowDense = snowDense;
		this->snowSaturation = snowSaturation;
		this->snowTailStep = snowTailStep;
	}

	void generateFrame() {
		for (uint8_t i = HEIGHT / 2U; i < HEIGHT; i++) {
			if (getPixColorXY(0U, i) == 0U && (random(0, this->snowDense) == 0) &&
				getPixColorXY(0U, i + 1U) == 0U &&
				getPixColorXY(0U, i - 1U) == 0U) {
				leds[getPixelNumber(0U, i)] =
					CHSV(random(0, 200), snowSaturation, 255U);
			}
		}

		for (uint8_t i = 0U; i < WIDTH / 2U; i++) {
			if (getPixColorXY(i, HEIGHT - 1U) == 0U &&
				(random(0, map(this->scale, 0U, 255U, 10U, 120U)) ==
				0U) &&
				getPixColorXY(i + 1U, HEIGHT - 1U) == 0U &&
				getPixColorXY(i - 1U, HEIGHT - 1U) == 0U) {
				leds[getPixelNumber(i, HEIGHT - 1U)] =
					CHSV(random(0, 200), this->snowSaturation, 255U);
			}
		}

		// сдвигаем по диагонали
		for (uint8_t y = 0U; y < HEIGHT - 1U; y++) {
			for (uint8_t x = WIDTH - 1U; x > 0U; x--) {
				drawPixelXY(x, y, getPixColorXY(x - 1U, y + 1U));
			}
		}

		// уменьшаем яркость левой и верхней линии, формируем "хвосты"
		for (uint8_t i = HEIGHT / 2U; i < HEIGHT; i++) {
			fadePixel(0U, i, this->snowTailStep);
		}
		for (uint8_t i = 0U; i < WIDTH / 2U; i++) {
			fadePixel(i, HEIGHT - 1U, this->snowTailStep);
		}
	}
};

#endif