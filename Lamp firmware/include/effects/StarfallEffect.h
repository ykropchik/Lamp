#ifndef STARFALL_EFFECT
#define STARFALL_EFFECT

#include "Effect.h"
#include <FastLED.h>
#include <Utility.h>

class StarfallEffect: public Effect {
private:
	uint8_t starDense;
	uint8_t starSaturation;
	uint8_t starTailStep;

public:
	StarfallEffect(uint8_t speed, uint8_t scale, uint8_t starDense = 60, uint8_t starSaturation = 150, uint8_t starTailStep = 100): Effect(speed, scale) {
		this->starDense = starDense;
		this->starSaturation = starSaturation;
		this->starTailStep = starTailStep;
	}

	void generateFrame() {
		for (uint8_t i = HEIGHT / 2U; i < HEIGHT; i++) {
			if (getPixColorXY(0U, i) == 0U && (random(0, this->starDense) == 0) &&
				getPixColorXY(0U, i + 1U) == 0U &&
				getPixColorXY(0U, i - 1U) == 0U) {
				leds[getPixelNumber(0U, i)] =
					CHSV(random(0, 200), this->starSaturation, 255U);
			}
		}

		for (uint8_t i = 0U; i < WIDTH / 2U; i++) {
			if (getPixColorXY(i, HEIGHT - 1U) == 0U &&
				(random(0, map(this->scale, 0U, 255U, 10U, 120U)) ==
					0U) &&
				getPixColorXY(i + 1U, HEIGHT - 1U) == 0U &&
				getPixColorXY(i - 1U, HEIGHT - 1U) == 0U) {
				leds[getPixelNumber(i, HEIGHT - 1U)] =
					CHSV(random(0, 200), this->starSaturation, 255U);
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
			fadePixel(0U, i, this->starTailStep);
		}
		for (uint8_t i = 0U; i < WIDTH / 2U; i++) {
			fadePixel(i, HEIGHT - 1U, this->starTailStep);
		}
	}
};

#endif