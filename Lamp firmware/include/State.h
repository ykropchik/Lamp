#ifndef STATE
#define STATE

#include <BedLamp.h>

class State {
protected:
	BedLamp *lamp;
public:
	State(BedLamp *lamp) {
		this->lamp = lamp;
	}

	virtual void singleClick();

	virtual void doubleClick();

	virtual void hold();

	virtual void clickAndHold();
};

#endif