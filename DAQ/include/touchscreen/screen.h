#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <SPI.h>

#include <mutex>

#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"
#include "Adafruit_TSC2007.h"

#include "structs/hardware_manager.h"
#include "apps/apps.h"

#define TOUCH_MAX 3800

class ScreenManager {
  private:
    static ScreenManager *pInstance;
    static std::mutex pMutex;

  protected:
    ScreenManager(SPIClass *_spi, int8_t _cs, int8_t _dc, int8_t _rst)
        : isChanged(false), tft(Adafruit_HX8357(_spi, _cs, _dc, _rst, HX8357D)) {}
    ~ScreenManager();

    bool isChanged;

    unsigned long testFillScreen();
    unsigned long testText();
    unsigned long testLines(uint16_t color);

  public:
    ScreenManager(const ScreenManager &) = delete;
    void operator=(const ScreenManager &) = delete;
    ScreenManager(ScreenManager &) = delete;
    void operator=(ScreenManager &) = delete;

    static ScreenManager *GetInstance();

    Adafruit_HX8357 tft;
    Adafruit_TSC2007 touch;

    struct touchPoint {
        uint16_t x;
        uint16_t y;
        uint16_t z1;
        uint16_t z2;
    };

    void register_change() { isChanged = true; }

    bool read_touch(touchPoint *point);

    void init(TwoWire *wire);

    void welcome_screen();

    void logo_screen();

    void app_sel_screen();

    void app_logo_screen(AppName app);
};

#endif