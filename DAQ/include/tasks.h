#ifndef TASKS_H
#define TASKS_H

#include <LoRa.h>

#include "config/pinout_esp.h"
#include "config/config.h"
#include "config/data_structs.h"

#include "components/sd_card.h"

// Touchscreen
void screen_refresher_task(void *arg);
void screen_touch_task(void *arg);
void screen_control_task(void *arg);

// LORA
void lora_task(void *arg);
void lora_rx_handler_task(void *arg);

// Memory
void sd_task(void *arg);
void flash_task(void *arg);

// UART
void uart_rx_handler_task(void *arg);

#endif