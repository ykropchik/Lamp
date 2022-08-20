#include <Utility.h>
#include <FastLED.h>
#include <Settings.h>
#include <Vars.h>

void fader(uint8_t step) {
	for (uint8_t i = 0U; i < WIDTH; i++) {
		for (uint8_t j = 0U; j < HEIGHT; j++) {
			fadePixel(i, j, step);
		}
	}
}

void fadePixel(uint8_t i, uint8_t j, uint8_t step) {
	int32_t pixelNum = getPixelNumber(i, j);
	if (getPixColor(pixelNum) == 0U) return;

	if (leds[pixelNum].r >= 30U || leds[pixelNum].g >= 30U ||
		leds[pixelNum].b >= 30U) {
		leds[pixelNum].fadeToBlackBy(step);
	} else {
		leds[pixelNum] = 0U;
	}
}

uint16_t getPixelNumber(uint8_t x, uint8_t y) {
	if ((THIS_Y % 2 == 0) || MATRIX_TYPE)  // если чётная строка
	{
		return (THIS_Y * _WIDTH + THIS_X);
	} else	// если нечётная строка
	{
		return (THIS_Y * _WIDTH + _WIDTH - THIS_X - 1);
	}
}

// залить все
void fillAll(CRGB color) {
	for (int32_t i = 0; i < NUM_LEDS; i++) {
		leds[i] = color;
	}
}

void fillAllHSV(CHSV color) {
	for (int32_t i = 0; i < NUM_LEDS; i++) {
		leds[i] = color;
	}
}

// функция отрисовки точки по координатам X Y
void drawPixelXY(int16_t x, int16_t y, CRGB color) {
	if (x < 0 || x > (int16_t)(WIDTH - 1) || y < 0 || y > (int16_t)(HEIGHT - 1)) return;
	uint32_t thisPixel = getPixelNumber((uint8_t)x, (uint8_t)y) * SEGMENTS;
	for (uint8_t i = 0; i < SEGMENTS; i++) {
		leds[thisPixel + i] = color;
	}
}

// функция получения цвета пикселя по его номеру
uint32_t getPixColor(uint32_t thisSegm) {
	uint32_t thisPixel = thisSegm * SEGMENTS;
	if (thisPixel > NUM_LEDS - 1) return 0;
	return (((uint32_t)leds[thisPixel].r << 16) | ((uint32_t)leds[thisPixel].g << 8) | (uint32_t)leds[thisPixel].b);
}

// функция получения цвета пикселя в матрице по его координатам
uint32_t getPixColorXY(uint8_t x, uint8_t y) { return getPixColor(getPixelNumber(x, y)); }

// Trivial XY function for the SmartMatrix; use a different XY
// function for different matrix grids. See XYMatrix example for code.
uint16_t XY(uint8_t x, uint8_t y) {
	uint16_t i;
	if (y & 0x01) {
		// Odd rows run backwards
		uint8_t reverseX = (WIDTH - 1) - x;
		i = (y * WIDTH) + reverseX;
	} else {
		// Even rows run forwards
		i = (y * WIDTH) + x;
	}
	return i;
}

CHSV rgb2hsv(CRGB color) {
    CHSV result;
    double min, max, delta;

    min = color.r < color.g ? color.r : color.g;
    min = min  < color.b ? min  : color.b;

    max = color.r > color.g ? color.r : color.g;
    max = max  > color.b ? max  : color.b;

    result.v = max;                                // v
    delta = max - min;
	
    if (delta < 0.00001) {
        result.s = 0;
        result.h = 0; // undefined, maybe nan?
        return result;
    }

    if ( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        result.s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0              
        // s = 0, h is undefined
        result.s = 0.0;
        result.h = NAN;                            // its now undefined
        return result;
    }
    
	if (color.r >= max) {
		result.h = (color.g - color.b) / delta;        // between yellow & magenta
	} else if(color.g >= max) {
        result.h = 2.0 + (color.b - color.r) / delta;  // between cyan & yellow
	} else {
        result.h = 4.0 + (color.r - color.g) / delta;  // between magenta & cyan
	}

    result.h *= 60.0;                              // degrees

    if(result.h < 0.0) {
        result.h += 360.0;
	}

    return result;
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}