#ifndef EFFECT
#define EFFECT

#include <FastLED.h>

class Effect {
protected:
	uint32_t speed;
	uint8_t scale;
	CRGB color;
	uint32_t lastFrameTime;

public:
	Effect(uint32_t speed = 50, uint8_t scale = 10, CRGB color = CRGB(70, 170, 230)) {
		this->speed = speed;
		this->scale = scale;
		this->color = color;
		this->lastFrameTime = millis();
	}

	virtual void generateFrame() {
		return;
	};
	
	virtual void showEffect() {
		if (millis() - this->lastFrameTime >= this->speed) {
			this->lastFrameTime = millis();
			this->generateFrame();
			FastLED.show();
		}
	};

	uint8_t getSpeed() {
		return this->speed;
	}

	void setSpeed(uint8_t newSpeed) {
		this->speed = newSpeed;
	}

	uint8_t getScale() {
		return this->scale;
	}

	void setScale(uint8_t newScale) {
		this->scale = newScale;
	}

	CRGB getColor() {
		return this->color;
	}

	void setColor(CRGB newColor) {
		this->color = newColor;
	}
};

#endif