#ifndef UTILITY
#define UTILITY

#include <FastLED.h>
#include <Settings.h>
#include <Vars.h>

#define CONNECTION_ANGLE 2
#define STRIP_DIRECTION 2

// ************* НАСТРОЙКА МАТРИЦЫ *****
#if (CONNECTION_ANGLE == 0 && STRIP_DIRECTION == 0)
#define _WIDTH WIDTH
#define THIS_X x
#define THIS_Y y

#elif (CONNECTION_ANGLE == 0 && STRIP_DIRECTION == 1)
#define _WIDTH HEIGHT
#define THIS_X y
#define THIS_Y x

#elif (CONNECTION_ANGLE == 1 && STRIP_DIRECTION == 0)
#define _WIDTH WIDTH
#define THIS_X x
#define THIS_Y (HEIGHT - y - 1)

#elif (CONNECTION_ANGLE == 1 && STRIP_DIRECTION == 3)
#define _WIDTH HEIGHT
#define THIS_X (HEIGHT - y - 1)
#define THIS_Y x

#elif (CONNECTION_ANGLE == 2 && STRIP_DIRECTION == 2)
#define _WIDTH WIDTH
#define THIS_X (WIDTH - x - 1)
#define THIS_Y (HEIGHT - y - 1)

#elif (CONNECTION_ANGLE == 2 && STRIP_DIRECTION == 3)
#define _WIDTH HEIGHT
#define THIS_X (HEIGHT - y - 1)
#define THIS_Y (WIDTH - x - 1)

#elif (CONNECTION_ANGLE == 3 && STRIP_DIRECTION == 2)
#define _WIDTH WIDTH
#define THIS_X (WIDTH - x - 1)
#define THIS_Y y

#elif (CONNECTION_ANGLE == 3 && STRIP_DIRECTION == 1)
#define _WIDTH HEIGHT
#define THIS_X y
#define THIS_Y (WIDTH - x - 1)

#else
#define _WIDTH WIDTH
#define THIS_X x
#define THIS_Y y
#pragma message "Wrong matrix parameters! Set to default"

#endif

// функция плавного угасания цвета для всех пикселей
void fader(uint8_t step);

// новый фейдер
void fadePixel(uint8_t i, uint8_t j, uint8_t step);

// получить номер пикселя в ленте по координатам
uint16_t getPixelNumber(uint8_t x, uint8_t y);

void fillnoise8();

// залить все
void fillAll(CRGB color);

void fillAllHSV(CHSV color);

// функция отрисовки точки по координатам X Y
void drawPixelXY(int16_t x, int16_t y, CRGB color);

// функция получения цвета пикселя по его номеру
uint32_t getPixColor(uint32_t thisSegm);

// функция получения цвета пикселя в матрице по его координатам
uint32_t getPixColorXY(uint8_t x, uint8_t y);

// Trivial XY function for the SmartMatrix; use a different XY
// function for different matrix grids. See XYMatrix example for code.
uint16_t XY(uint8_t x, uint8_t y);

CHSV rgb2hsv(CRGB color);

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);

#endif