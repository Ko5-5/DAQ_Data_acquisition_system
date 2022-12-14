#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <Arduino.h>
#include <stdio.h>
#include <LoRa.h>
#include "SPIMemory.h"

#include "config/pinout_esp.h"
#include "config/config.h"
#include "data_structs/pysd_data_structs.h"
#include "structs/hardware_manager.h"
#include "touchscreen/screen.h"

struct TaskManager {
  // ## FreeRTOS ##
  // tasks
  TaskHandle_t configTask;
  TaskHandle_t appConfigTask;
  TaskHandle_t appTask;
  TaskHandle_t loraTask;
  TaskHandle_t rxHandlingTask;
  TaskHandle_t sdTask;
  TaskHandle_t flashTask;
  // queues
  QueueHandle_t loraRxQueue;
  QueueHandle_t loraTxQueue;
  QueueHandle_t sdQueue;
  QueueHandle_t flashQueue;
  // mutexes
  SemaphoreHandle_t spiMutex;
  SemaphoreHandle_t i2cMutex;

  // spinlock
  portMUX_TYPE stateLock = portMUX_INITIALIZER_UNLOCKED;

  // software timers
  TimerHandle_t heartbeatTimer;
  TimerHandle_t disconnectTimer;

  TaskManager()
      : configTask(NULL),
        appConfigTask(NULL),
        appTask(NULL),
        loraTask(NULL),
        rxHandlingTask(NULL),
        sdTask(NULL),
        flashTask(NULL),
        loraRxQueue(NULL),
        loraTxQueue(NULL),
        sdQueue(NULL),
        flashQueue(NULL),
        spiMutex(NULL),
        i2cMutex(NULL),
        heartbeatTimer(NULL),
        disconnectTimer(NULL) {}
};

#endif