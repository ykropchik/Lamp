#ifndef OFF_STATE
#define OFF_STATE

#include <BedLamp.h>
#include <State.h>

class OffState: public State {
public:
	OffState(BedLamp *lamp): State(lamp){};

	void singleClick() {
		this->lamp->turnOn();
	}

	void doubleClick() {
		return;
	};

	void hold() {
		return;
	};

	void clickAndHold() {
		return;
	};
};

#endif