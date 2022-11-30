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

struct HardwareManager {
public:
  // Voltage measurement
  // Voltage_Measure_t myVoltage = VOLTAGE_MEASURE_INIT(VBAT_MES_CHANNEL);

  // Communication interfaces
  SPIClass mySPI = SPIClass(VSPI);
  TwoWire myI2C = TwoWire(0);
  HardwareSerial mySerial = HardwareSerial(EXT_UART);

  // Expanders
  MCP23017 gpioExpander = MCP23017(&myI2C, GPIO_EXP_ADDR);
  //ADS7828 adcExpander;

  // Contructor

  // Initialization methods
  bool hardware_init();
  bool uart_init();
  bool uart_deinit();
};

#endif