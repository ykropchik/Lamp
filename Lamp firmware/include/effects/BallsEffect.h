#ifndef BALLS_EFFECT
#define BALLS_EFFECT

#include "Effect.h"
#include <FastLED.h>
#include <Utility.h>

class BallsEffect: public Effect {
private:
	int16_t (*coord)[2U];
	int8_t (*vector)[2U];
	CRGB *ballColors;
	uint8_t trackStep;
	uint8_t ballAmount;

public:
	BallsEffect(uint8_t speed, uint8_t scale, uint8_t trackStep = 70, uint8_t ballAmount = 3): Effect(speed, scale) {
		this->coord = new int16_t[ballAmount][2U];
		this->vector = new int8_t[ballAmount][2U];
		this->ballColors = new CRGB[ballAmount];

		for (uint8_t j = 0U; j < ballAmount; j++) {
			int8_t sign;
			this->coord[j][0U] = WIDTH / 2 * 10;
			random(0, 2) ? sign = 1 : sign = -1;
			this->vector[j][0U] = random(4, 15) * sign;
			this->coord[j][1U] = HEIGHT / 2 * 10;
			random(0, 2) ? sign = 1 : sign = -1;
			this->vector[j][1U] = random(4, 15) * sign;
			this->ballColors[j] = CHSV(random(0, 9) * 28, 255U, 255U);
		}

		this->trackStep = trackStep;
		this->ballAmount = ballAmount;
	}

	uint8_t getTrackStep() {
		return this->trackStep;
	}

	void setTrackStep(uint8_t newTrackStep) {
		this->trackStep = newTrackStep;
	}

	uint8_t getBallAmount() {
		return this->ballAmount;
	}

	void setBallAmount(uint8_t newBallAmount) {
		this->ballAmount = newBallAmount;

		this->coord = new int16_t[ballAmount][2U];
		this->vector = new int8_t[ballAmount][2U];
		this->ballColors = new CRGB[ballAmount];

		FastLED.clear();
	}

	void generateFrame() {
		if (trackStep > 0) {
			fader(trackStep);
		}

		// движение шариков
		for (uint8_t j = 0U; j < this->ballAmount; j++) {
			// движение шариков
			for (uint8_t i = 0U; i < 2U; i++) {
				this->coord[j][i] += this->vector[j][i];
				if (this->coord[j][i] < 0) {
					this->coord[j][i] = 0;
					this->vector[j][i] = -this->vector[j][i];
				}
			}

			if (this->coord[j][0U] > (int16_t)((WIDTH - 1) * 10)) {
				this->coord[j][0U] = (WIDTH - 1) * 10;
				this->vector[j][0U] = -this->vector[j][0U];
			}
			if (this->coord[j][1U] > (int16_t)((HEIGHT - 1) * 10)) {
				this->coord[j][1U] = (HEIGHT - 1) * 10;
				this->vector[j][1U] = -this->vector[j][1U];
			}
			leds[getPixelNumber(this->coord[j][0U] / 10, this->coord[j][1U] / 10)] =
				this->ballColors[j];
		}
	}
};

#endif