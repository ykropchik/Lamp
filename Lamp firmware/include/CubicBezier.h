#ifndef CUBIC_BEZIER
#define CUBIC_BEZIER

class CubicBezier {
private:
	const float x0 = 0;
	const float y0 = 0;
	float x1;
	float y1;
	float x2;
	float y2;
	const float x3 = 1;
	const float y3 = 1;

public:
	CubicBezier(float x1, float y1, float x2, float y2) {
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}

	float getValue(float input) {
		return pow(1 - input, 3) * y0 + 3 * pow(1 - input, 2) * input * y1 + 3 * (1 - input) * pow(input, 2) * y2 + pow(input, 3) * y3;
	}
};

#endif