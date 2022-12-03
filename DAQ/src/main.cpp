#include <Arduino.h>

#include "tasks.h"

TaskManager tasks;

void setup() {
  vTaskDelay(pdMS_TO_TICKS(5000));

  xTaskCreatePinnedToCore(config_task, "Config Task", 8192, NULL, 5, &tasks.configTask, PRO_CPU_NUM);

  Serial.println("END setup");
}

void loop() {
  
}