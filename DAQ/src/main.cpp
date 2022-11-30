#include <Arduino.h>
#include "structs/hardware_manager.h"
#include "touchscreen/screen.h"

HardwareManager hardware;
ScreenManager screen(&hardware.mySPI, SCREEN_CS, SCREEN_D_C, -1);

void setup() {
  Serial.begin(115200);

  hardware.hardware_init();
  screen.init();

  delay(1000);

  screen.app_sel_screen();

  // delay(5000);

  // screen.welcome_screen();

  // delay(5000);

  // screen.logo_screen();
}

void loop() {
  // gonna be left empty
}