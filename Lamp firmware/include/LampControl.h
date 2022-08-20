#ifndef LAMP_CONTROL
#define LAMP_COMTROL

#include <BedLamp.h>
#include <GyverButton.h>

class LampControl {
private:
	BedLamp *lamp;
	GButton *btn;

public:
	LampControl(BedLamp *lamp, GButton *btn) {
		this->lamp = lamp;
		this->btn = btn;
	}

	void tick() {
		this->btn->tick();

		if (this->btn->isSingle()) {
			Serial.println("Single click");
			this->lamp->nextEffect();
		}

		if (this->btn->isDouble()) {
			Serial.println("Double click");
			this->lamp->previousEffect();
		}

		if (this->btn->isStep()) {
			this->lamp->incBrightness(10);
			Serial.println("Inc");
		}

		if (this->btn->isStep(1)) {
			this->lamp->decBrightness(10);
			Serial.println("Dec");
		}
	}
};

#endif