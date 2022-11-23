#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <Arduino.h>

struct TaskManager {
  /**RTOS**/
  // tasks
  TaskHandle_t loraTask;
  TaskHandle_t rxHandlingTask;
  TaskHandle_t stateTask;
  TaskHandle_t dataTask;
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
  TimerHandle_t watchdogTimer;
  TimerHandle_t disconnectTimer;

  TaskManager()
      : loraTask(NULL),
        rxHandlingTask(NULL),
        stateTask(NULL),
        dataTask(NULL),
        sdTask(NULL),
        flashTask(NULL),
        loraRxQueue(NULL),
        loraTxQueue(NULL),
        sdQueue(NULL),
        flashQueue(NULL),
        spiMutex(NULL),
        watchdogTimer(NULL),
        disconnectTimer(NULL) {}
};

#endif