#ifndef NOISE_EFFECT
#define NOISE_EFFECT

#include "Effect.h"
#include <FastLED.h>
#include <Vars.h>
#include <Utility.h>

class NoiseEffect: public Effect {
protected:
	CRGBPalette16 palette;
	bool colorLoop;
	uint8_t scale;
	uint8_t ihue;
	uint16_t x;
	uint16_t y;
	uint16_t z;
	uint8_t noise[HEIGHT][HEIGHT];

	void fillnoise8() {
		for (uint8_t i = 0; i < HEIGHT; i++) {
			int32_t ioffset = this->scale * i;
			for (uint8_t j = 0; j < HEIGHT; j++) {
				int32_t joffset = this->scale * j;
				this->noise[i][j] = inoise8(this->x + ioffset, this->y + joffset, this->z);
			}
		}
		
		this->z += this->speed;
	}

	void fillNoiseLED() {
		uint8_t dataSmoothing = 0;
		if (this->speed < 50) {
			dataSmoothing = 200 - (this->speed * 4);
		}
		for (uint8_t i = 0; i < MAX_DIMENSION; i++)
		{
			int32_t ioffset = this->scale * i;
			for (uint8_t j = 0; j < MAX_DIMENSION; j++) {
				int32_t joffset = this->scale * j;

				uint8_t data = inoise8(x + ioffset, y + joffset, z);

				data = qsub8(data, 16);
				data = qadd8(data, scale8(data, 39));

				if (dataSmoothing) {
					uint8_t olddata = noise[i][j];
					uint8_t newdata = scale8( olddata, dataSmoothing) + scale8( data, 256 - dataSmoothing);
					data = newdata;
				}

				noise[i][j] = data;
			}
		}
		this->z += this->speed;

		// apply slow drift to X and Y, just for visual variation.
		this->x += this->speed / 8;
		this->y -= this->speed / 16;

		for (uint8_t i = 0; i < WIDTH; i++) {
			for (uint8_t j = 0; j < HEIGHT; j++) {
				uint8_t index = noise[j][i];
				uint8_t bri =   noise[i][j];
				// if this palette is a 'loop', add a slowly-changing base value
				if (this->colorLoop) {
					index += ihue;
				}
				// brighten up, as the color palette itself often contains the
				// light/dark dynamic range desired
				if ( bri > 127 ) {
					bri = 255;
				}
				else {
					bri = dim8_raw( bri * 2);
				}

				CRGB color = ColorFromPalette(this->palette, index, bri);      
				drawPixelXY(i, j, color);
			}
		}
		ihue += 1;
	}

public:
	NoiseEffect(CRGBPalette16 colorPalette, bool colorLoop, uint8_t speed = 10, uint8_t scale = 10): Effect(speed, scale) {
		this->palette = colorPalette;
		this->colorLoop = false;
	};

	virtual void generateFrame() {};
};

#endif