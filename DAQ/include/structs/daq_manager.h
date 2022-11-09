#ifndef DAQ_MANAGER_H
#define DAQ_MANAGER_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <string>
#include "freertos/FreeRTOS.h"

#include "config/data_structs.h"
#include "config/config.h"
#include "config/pinout_esp.h"

#include "structs/hardware_manager.h"
#include "structs/task_manager.h"

#define LORA_RX_QUEUE_LENGTH 5
#define LORA_TX_QUEUE_LENGTH 5
#define SD_QUEUE_LENGTH 10
#define FLASH_QUEUE_LENGTH 20
#define ESP_NOW_QUEUE_LENGTH 5

#define CONNECTION_CHECK_DEVICE_NUMBER 6

enum ValveState{
  Close = 0,
  Open = 1,
  IDK = 2 ,
  Vent = 3,
  AttemptToOpen = 4,
  AttemptToClose = 5
};

struct DAQManager{
  HardwareManager hardware;
  TaskManager tasks;

  bool isConnectedFlags[CONNECTION_CHECK_DEVICE_NUMBER];
  uint8_t connectedStatus;

  DAQManager() = default;
  ~DAQManager() = default;
  
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