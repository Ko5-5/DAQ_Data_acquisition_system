#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <SPI.h>

#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"
#include "Adafruit_TSC2007.h"

#define TOUCH_MAX 3800

class ScreenManager {
private:
    bool isChanged;

    unsigned long testFillScreen();
    unsigned long testText();
    unsigned long testLines(uint16_t color);

public:
    ScreenManager(SPIClass *_spi, int8_t _cs, int8_t _dc, int8_t _rst);

    Adafruit_HX8357 tft;
    Adafruit_TSC2007 touch;

    typedef struct touchPoint{
      uint16_t x;
      uint16_t y;
      uint16_t z1;
      uint16_t z2;
    };

    void register_change() { isChanged = true; }

    touchPoint read_touch();

    void init(TwoWire *wire);

    void welcome_screen();

    void logo_screen();

    uint8_t app_sel_screen();
};

#endif