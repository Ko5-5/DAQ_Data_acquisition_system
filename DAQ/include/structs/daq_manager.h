#ifndef DAQ_MANAGER_H
#define DAQ_MANAGER_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include <string>

#include "config/config.h"
#include "config/pinout_esp.h"
#include "freertos/FreeRTOS.h"
#include "structs/hardware_manager.h"
#include "structs/task_manager.h"
#include "touchscreen/screen.h"

#include "apps/apps.h"

#define LORA_RX_QUEUE_LENGTH 5
#define LORA_TX_QUEUE_LENGTH 5
#define SD_QUEUE_LENGTH 10
#define FLASH_QUEUE_LENGTH 20
#define ESP_NOW_QUEUE_LENGTH 5

struct DAQManager {
  private:
    static DAQManager *pInstance;
    static std::mutex pMutex;

  protected:
    DAQManager(){};
    ~DAQManager(){};

  public:
    DAQManager(const DAQManager &) = delete;
    void operator=(const DAQManager &) = delete;
    DAQManager(DAQManager &) = delete;
    void operator=(DAQManager &) = delete;

    static DAQManager *GetInstance();

    AppName selectedApp = AppName::NO_APP;
    App app;

    // OBC old functions

    void updateCurrentState();
    void sendLog(const char *message);
    uint32_t getDisconnectRemainingTime();
    void restartDisconnectTimer(bool _force = false);
    bool deactiveDisconnectTimer();
    bool queueSend(xQueueHandle _handle, char *data);
    bool allDevicesWokenUp();

    void createOptionsFrame(char *_array, Options options);
    void createLoRaFrame(char *_array);
    void createSDFrame(char *_array);
};

#endif