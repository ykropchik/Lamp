#ifndef WARNING_EFFECT
#define WARNING_EFFECT

#include "Effect.h"
#include <FastLED.h>
#include <Utility.h>
#include <CubicBezier.h>

enum ColorPulseState {
	Increasing,
	Decreasing
};

class ColorPulseEffect: public Effect {
private:
	uint32_t duration;
	uint8_t brightness;
	CubicBezier *bezierFunction;
	ColorPulseState state;
	uint32_t blinkHalfPeriod;
	uint32_t startTime;

public:
	ColorPulseEffect(
		uint32_t duration, 
		CRGB color, 
		uint8_t brightness, 
		CubicBezier *bezierFunction = new CubicBezier(0.785, 0.135, 0.150, 0.860)
	): Effect(50, 0, color) {
		this->duration = duration;
		this->brightness = brightness;
		this->bezierFunction = bezierFunction;
		this->state = ColorPulseState::Increasing;
		this->blinkHalfPeriod = this->duration / 2;
		this->startTime = 0;
	}

	void generateFrame() {
		if (this->startTime == 0 || millis() - this->startTime >= this->duration) {
			this->state = ColorPulseState::Increasing;
			this->startTime = millis();
		}

		if (millis() - this->startTime >= blinkHalfPeriod) {
			this->state = ColorPulseState::Decreasing;
		}

		float mappedPassedTime;
		float bezierValue;
		uint8_t newBrightness;

		uint16_t passedTime = millis() - this->startTime;

		if (this->state == ColorPulseState::Increasing) {
			mappedPassedTime = mapFloat(passedTime, 0, blinkHalfPeriod, 0, 1);
			bezierValue = bezierFunction->getValue(mappedPassedTime);
			newBrightness = (uint8_t) mapFloat(bezierValue, 0, 1, 0, 255);
		} else {
			mappedPassedTime = mapFloat(passedTime, blinkHalfPeriod, this->duration, 1, 0);
			bezierValue = bezierFunction->getValue(mappedPassedTime);
			newBrightness = (uint8_t) mapFloat(bezierValue, 0, 1, 0, 255);
		}

		FastLED.setBrightness(newBrightness);
		fillAll(this->color);
	}
};

#endif