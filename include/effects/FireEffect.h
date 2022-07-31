#ifndef FIRE_EFFECT
#define FIRE_EFFECT

#include "Effect.h"
#include <FastLED.h>
#include <Utility.h>
#include <Vars.h>

inline static const uint8_t valueMask[8][16] PROGMEM = {
	{32, 0, 0, 0, 0, 0, 0, 32, 32, 0, 0, 0, 0, 0, 0, 32},
	{64, 0, 0, 0, 0, 0, 0, 64, 64, 0, 0, 0, 0, 0, 0, 64},
	{96, 32, 0, 0, 0, 0, 32, 96, 96, 32, 0, 0, 0, 0, 32, 96},
	{128, 64, 32, 0, 0, 32, 64, 128, 128, 64, 32, 0, 0, 32, 64, 128},
	{160, 96, 64, 32, 32, 64, 96, 160, 160, 96, 64, 32, 32, 64, 96, 160},
	{192, 128, 96, 64, 64, 96, 128, 192, 192, 128, 96, 64, 64, 96, 128, 192},
	{255, 160, 128, 96, 96, 128, 160, 255, 255, 160, 128, 96, 96, 128, 160, 255},
	{255, 192, 160, 128, 128, 160, 192, 255, 255, 192, 160, 128, 128, 160, 192, 255}
};

// these are the hues for the fire,
// should be between 0 (red) to about 25 (yellow)
inline static const uint8_t hueMask[8][16] PROGMEM = {
	{1, 11, 19, 25, 25, 22, 11, 1, 1, 11, 19, 25, 25, 22, 11, 1},
	{1, 8, 13, 19, 25, 19, 8, 1, 1, 8, 13, 19, 25, 19, 8, 1},
	{1, 8, 13, 16, 19, 16, 8, 1, 1, 8, 13, 16, 19, 16, 8, 1},
	{1, 5, 11, 13, 13, 13, 5, 1, 1, 5, 11, 13, 13, 13, 5, 1},
	{1, 5, 11, 11, 11, 11, 5, 1, 1, 5, 11, 11, 11, 11, 5, 1},
	{0, 1, 5, 8, 8, 5, 1, 0, 0, 1, 5, 8, 8, 5, 1, 0},
	{0, 0, 1, 5, 5, 1, 0, 0, 0, 0, 1, 5, 5, 1, 0, 0},
	{0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0}
};

class FireEffect: public Effect {
private:
	bool isSparkles;

private:
	uint8_t line[WIDTH];
	uint8_t hue;
	uint8_t pcnt = 0U;
	unsigned char matrixValue[8][16];

	void generateLine() {
		for (uint8_t x = 0U; x < WIDTH; x++) {
			line[x] = random(64, 255);
		}
	}

	void shiftUp() {
		for (uint8_t y = HEIGHT - 1U; y > 0U; y--) {
			for (uint8_t x = 0U; x < WIDTH; x++) {
				uint8_t newX = x;
				if (x > 15U) newX = x % 16U;
				if (y > 7U) continue;
				matrixValue[y][newX] = matrixValue[y - 1U][newX];
			}
		}

		for (uint8_t x = 0U; x < WIDTH; x++) {
			uint8_t newX = x;
			if (x > 15U) newX = x % 16U;
			matrixValue[0U][newX] = line[newX];
		}
	}

	// draw a frame, interpolating between 2 "key frames"
	// @param pcnt percentage of interpolation
	void drawFrame(uint8_t pcnt) {
		CHSV hsvColor = rgb2hsv(this->color);
		int32_t nextv;

		// each row interpolates with the one before it
		for (uint8_t y = HEIGHT - 1U; y > 0U; y--) {
			for (uint8_t x = 0U; x < WIDTH; x++) {
				uint8_t newX = x;
				if (x > 15U) newX = x % 16U;
				if (y < 8U) {
					nextv = (((100.0 - pcnt) * matrixValue[y][newX] +
							pcnt * matrixValue[y - 1][newX]) /
							100.0) -
							pgm_read_byte(&valueMask[y][newX]);

					CRGB color = CHSV(this->hue + pgm_read_byte(&hueMask[y][newX]), 255U, (uint8_t)max(0, nextv));
						
					leds[getPixelNumber(x, y)] = color;
				} else if (y == 8U && this->isSparkles) {
					if (random(0, 20) == 0 && getPixColorXY(x, y - 1U) != 0U)
						drawPixelXY(x, y, getPixColorXY(x, y - 1U));
					else
						drawPixelXY(x, y, 0U);
				} else if (this->isSparkles) {
					// старая версия для яркости
					if (getPixColorXY(x, y - 1U) > 0U)
						drawPixelXY(x, y, getPixColorXY(x, y - 1U));
					else
						drawPixelXY(x, y, 0U);
				}
			}
		}

		// first row interpolates with the "next" line
		for (uint8_t x = 0U; x < WIDTH; x++) {
			uint8_t newX = x;
			if (x > 15U) newX = x % 16U;
			CRGB color = CHSV( this->hue + pgm_read_byte(&(hueMask[0][newX])), 255U, (uint8_t)(((100.0 - pcnt) * matrixValue[0][newX] + pcnt * line[newX]) / 100.0));
			leds[getPixelNumber(x, 0)] = color;
		}
	}

public:
	FireEffect(uint8_t speed, uint8_t scale, uint8_t hue, bool isSparkles = true): Effect(speed) {
		this->hue = hue;
		this->isSparkles = isSparkles;
		generateLine();
		memset(matrixValue, 0, sizeof(matrixValue));
	};

	void generateFrame() {
		if (pcnt >= 100) {
			shiftUp();
			generateLine();
			pcnt = 0;
		}

		drawFrame(pcnt);
		pcnt += 30;
	}
};

#endif