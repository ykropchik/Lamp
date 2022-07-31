#ifndef READY_STATE
#define READY_STATE

#include <BedLamp.h>
#include <State.h>

class ReadyState: public State {
public:
	ReadyState(BedLamp *lamp): State(lamp){};

	void singleClick() {
		this->lamp->nextEffect();
	}

	void doubleClick() {
		this->lamp->previousEffect();
	};

	void hold() {
		this->lamp->incBrightness(5);
	};

	void clickAndHold() {
		this->lamp->decBrightness(5);
	};
};

#endif