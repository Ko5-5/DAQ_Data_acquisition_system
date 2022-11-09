#ifndef HARDWARE_MANAGER_H
#define HARDWARE_MANAGER_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include <SPI.h>
#include <Wire.h>

struct HardwareManager {
  /** SERIAL COMMUNICATION **/
  SPIClass mySPI;
  TwoWire i2c;
  HardwareSerial serialPort(2);

  HardwareManager() : mySPI(SPIClass(VSPI)), i2c(TwoWire(0)) {}
};

#endif