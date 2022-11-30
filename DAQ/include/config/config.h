#ifndef CONFIG_H
#define CONFIG_H

#define SD_FRAME_ARRAY_SIZE 1024

// ## UART ##
#define UART_2 2U

// ## EXPANDERS ##
#define GPIO_EXP_ADDR 0x20 // (A2/A1/A0 = LOW)
#define ADC_EXP_ADDR 0x03 // (A1/A0 = HIGH)

// ## LORA ##
#define LORA_FRAME_ARRAY_SIZE 256
#define LORA_FREQUENCY_KHZ 867000
#define LORA_PERIOD 500
#define LORA_TX_DATA_PREFIX "DAQ;"
#define LORA_TX_OPTIONS_PREFIX "DAQ;"

#endif