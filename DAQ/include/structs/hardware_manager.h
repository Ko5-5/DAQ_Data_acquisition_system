#ifndef HARDWARE_MANAGER_H
#define HARDWARE_MANAGER_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include <MCP23018.h>
#include <SPI.h>
#include <Wire.h>
#include <i2c_adc_ads7828.h>
#include <mutex>

#include "config/config.h"
#include "config/pinout_esp.h"

struct HardwareManager {
  private:
    static HardwareManager *pInstance;
    static std::mutex pMutex;

  protected:
    HardwareManager(){};
    ~HardwareManager(){};

  public:
    HardwareManager(const HardwareManager &) = delete;
    void operator=(const HardwareManager &) = delete;
    HardwareManager(HardwareManager &) = delete;
    void operator=(HardwareManager &) = delete;

    static HardwareManager *GetInstance();

    // Voltage measurement
    // Voltage_Measure_t myVoltage = VOLTAGE_MEASURE_INIT(VBAT_MES_CHANNEL);

    // Communication interfaces
    SPIClass mySPI = SPIClass(VSPI);
    TwoWire myI2C = TwoWire(0);
    HardwareSerial mySerial = HardwareSerial(EXT_UART);

    // Expanders
    MCP23017 gpioExpander = MCP23017(&myI2C, GPIO_EXP_ADDR);
    // ADS7828 adcExpander;

    // Contructor

    // Initialization methods
    bool hardware_init();
    bool uart_init();
    bool uart_deinit();
};

#endif