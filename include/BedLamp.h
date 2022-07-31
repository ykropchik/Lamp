#ifndef BED_LAMP
#define BED_LAMP

#include <effects/Effect.h>
#include <effects/WaitingEffect.h>
#include <effects/ColorPulseEffect.h>
#include <FastLED.h>

enum BedLampStatus {
	WiFiConnecting,
	OFF,
	RegularMode,
	AlarmMode
};

class BedLamp {
private:
	BedLampStatus status;
	Effect **effects;
	WaitingEffect *waitingEffect;
	ColorPulseEffect *errorEffect;
	ColorPulseEffect *warningEffect;
	uint8_t effectsAmount;
	uint8_t brightness;
	uint8_t currentEffectIndex;

public:
	BedLamp(
		Effect **effects,
		uint8_t effectsAmount,
		WaitingEffect *waitingEffect,
		ColorPulseEffect *errorEffect,
		ColorPulseEffect *warningEffect,
		uint8_t defaultBrightness
	) {
		this->effects = effects;
		this->effectsAmount = effectsAmount;
		this->waitingEffect = waitingEffect;
		this->errorEffect = errorEffect;
		this->warningEffect = warningEffect;
		this->currentEffectIndex = 0;
		this->brightness = defaultBrightness;
		this->status = BedLampStatus::RegularMode;
	}

	BedLampStatus getStatus() {
		return this->status;
	}

	void setStatus(BedLampStatus newStatus) {
		this->status = newStatus;
	}

	void turnOn() {
		this->status = BedLampStatus::RegularMode;
	}

	void turnOff() {
		this->status = BedLampStatus::OFF;
	}

	void nextEffect() {
		if (this->currentEffectIndex == this->effectsAmount - 1) {
			this->currentEffectIndex = 0;
		} else {
			this->currentEffectIndex++;
		}
		Serial.println(this->currentEffectIndex);
		FastLED.clear();
	}

	void previousEffect() {
		if (this->currentEffectIndex == 0) {
			this->currentEffectIndex = this->effectsAmount - 1;
		} else {
			this->currentEffectIndex--;
		}
		Serial.println(this->currentEffectIndex);
		FastLED.clear();
	}

	uint8_t getBrightnes() {
		return this->brightness;
	}

	void setBrightness(uint8_t newBrightness) {
		this->brightness = newBrightness;
	}

	void incBrightness(uint8_t step = 1) {
		if (this->brightness == 255) {
			return;
		}

		if (this->brightness + step > 255) {
			this->brightness = 255;
		} else {
			this->brightness += step;
		}
	}

	void decBrightness(uint8_t step = 1) {
		if (this->brightness == 1) {
			return;
		}

		if (this->brightness - step < 1) {
			this->brightness = 1;
		} else {
			this->brightness -= step;
		}
		
		Serial.print(this->brightness);
	}

	void effectTick() {
		FastLED.setBrightness(this->brightness);
		this->effects[currentEffectIndex]->showEffect();
		FastLED.show();
	}

	void warningTick() {
		this->warningEffect->showEffect();
	}

	void errorTick() {
		this->errorEffect->showEffect();
		FastLED.show();
	}

	void waitingTick() {
		this->waitingEffect->showEffect();
		FastLED.show();
	}

	void alarmTick() {
		this->errorEffect->showEffect();
		FastLED.show();
	}
};

#endif