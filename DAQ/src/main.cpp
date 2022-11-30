#include <Arduino.h>

#include "structs/hardware_manager.h"
#include "touchscreen/screen.h"

HardwareManager hardware;
ScreenManager screen(&hardware.mySPI, SCREEN_CS, SCREEN_D_C, -1);

void setup() {
  Serial.begin(115200);

  hardware.hardware_init();
  screen.init(&hardware.myI2C);

  delay(2000);

  screen.welcome_screen();

  delay(2000);

  screen.logo_screen();

  delay(2000);

  screen.app_sel_screen();
}

void loop() {
  ScreenManager::touchPoint point;
  while (screen.touch.read_touch(&point.x, &point.y, &point.z1, &point.z2)) {
    if (point.z1 > 200) {
      if (point.y > 600 && point.y < 3500) {
        if (point.x > 600 && point.x < 1100) {
          Serial.println("Sensors app");
        }
        if (point.x > 1700 && point.x < 2300) {
          Serial.println("Static fire app");
        }
        if (point.x > 2800 && point.x < 3500) {
          Serial.println("Launchpad app");
        }
      }
    }
  }
}