#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>

#include "Adafruit_TFTLCD.h"
#include "Adafruit_TSC2007.h"

#include "colors.h"

class ScreenManager : public Adafruit_TFTLCD {
private:
  bool isChanged;
  uint16_t identifier;
  Adafruit_TSC2007 touchscreen;

  unsigned long testFillScreen();
  unsigned long testText();
  unsigned long testLines(uint16_t color);

public:
  ScreenManager(uint8_t cs, uint8_t cd, uint8_t wr, uint8_t rd, uint8_t rst)
      : Adafruit_TFTLCD(cs, cd, wr, rd, rst), isChanged(false) {}

  void register_change() { isChanged = true; }

  bool init();

  void welcome_screen();

  uint8_t app_sel_screen();
};

#endif