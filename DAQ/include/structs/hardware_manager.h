#ifndef HARDWARE_MANAGER_H
#define HARDWARE_MANAGER_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <MCP23018.h>
#include <i2c_adc_ads7828.h>

#include "config/pinout_esp.h"
#include "config/config.h"
#include "components/voltage_measure.h"

struct HardwareManager {
public:
  // Voltage measurement
  Voltage_Measure_t myVoltage = VOLTAGE_MEASURE_INIT(VBAT_MES_CHANNEL);

  // Communication interfaces
  SPIClass mySPI;
  TwoWire myI2C;
  HardwareSerial mySerial(UART_2);

  // Expanders
  MCP23017 gpioExpander(myI2C, GPIO_EXP_ADDR);
  ADS7828 adcExpander;

  // Contructor
  HardwareManager() : mySPI(SPIClass(VSPI)), myI2C(TwoWire(0)) {}

  // Initialization methods
  bool hardware_init();
  bool uart_init();
  bool uart_deinit();
};

#endif