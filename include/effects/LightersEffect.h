#ifndef LIGHTERS_EFFECT
#define LIGHTERS_EFFECT

#include "Effect.h"
#include <FastLED.h>
#include <Utility.h>

#define LIGHTERS_AM 100U

class LightersEffect: public Effect {
private:
	int32_t lightersPos[2U][LIGHTERS_AM];
	int8_t lightersSpeed[2U][LIGHTERS_AM];
	CHSV lightersColor[LIGHTERS_AM];
	uint8_t loopCounter;

public:
	LightersEffect(uint8_t speed, uint8_t scale): Effect(speed, scale) {
		randomSeed(millis());
		
		for (uint8_t i = 0U; i < LIGHTERS_AM; i++) {
			this->lightersPos[0U][i] = random(0, WIDTH * 10);
			this->lightersPos[1U][i] = random(0, HEIGHT * 10);
			this->lightersSpeed[0U][i] = random(-10, 10);
			this->lightersSpeed[1U][i] = random(-10, 10);
			this->lightersColor[i] = CHSV(random(0U, 255U), 255U, 255U);
		}

		this->loopCounter = 0;
	}

	void generateFrame() {
		if (++this->loopCounter > 20U) 
			loopCounter = 0U;
			for (uint8_t i = 0U; i < this->scale; i++) {
				if (loopCounter == 0U) {
					this->lightersSpeed[0U][i] += random(-3, 4);
					this->lightersSpeed[1U][i] += random(-3, 4);
					this->lightersSpeed[0U][i] = constrain(this->lightersSpeed[0U][i], -20, 20);
					this->lightersSpeed[1U][i] = constrain(this->lightersSpeed[1U][i], -20, 20);
				}

				this->lightersPos[0U][i] += this->lightersSpeed[0U][i];
				this->lightersPos[1U][i] += this->lightersSpeed[1U][i];

				if (this->lightersPos[0U][i] < 0) this->lightersPos[0U][i] = (WIDTH - 1) * 10;
				if (this->lightersPos[0U][i] >= (int32_t)(WIDTH * 10)) this->lightersPos[0U][i] = 0;

				if (this->lightersPos[1U][i] < 0) {
					this->lightersPos[1U][i] = 0;
					this->lightersSpeed[1U][i] = -this->lightersSpeed[1U][i];
				}
				if (this->lightersPos[1U][i] >= (int32_t)(HEIGHT - 1) * 10) {
					this->lightersPos[1U][i] = (HEIGHT - 1U) * 10;
					this->lightersSpeed[1U][i] = -this->lightersSpeed[1U][i];
				}
				drawPixelXY(this->lightersPos[0U][i] / 10, this->lightersPos[1U][i] / 10,
							this->lightersColor[i]);
			}
	}
};

#endif