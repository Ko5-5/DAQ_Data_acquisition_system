#ifndef PINOUT_ESP_H
#define PINOUT_ESP_H

// ## Status led ##
#define ESP_LED 5U

// ## Voltage measurement ##
#define VBAT_MES 36U
#define VBAT_MES_CHANNEL ADC1_CHANNEL_0

// ## TFT Touchscreen ##
#define SCREEN_CS 25U
#define SCREEN_D_C 26U

// ## Rotary encoder ##
#define ENCODER_A 32U
#define ENCODER_B 33U
#define ENCODER_BUT 35U

// ## Flash memory ##
#define FLASH_CS 2U

// ## LORA ##
#define LORA_CS 27U
#define LORA_RS 4U
#define LORA_D0 39U

// ## Free pin ##
#define ESP_FREE_34 34U

// ## Communication interfaces ##
// I2C
#define I2C_SDA 21U
#define I2C_SCL 22U
// SPI
#define SPI_MOSI 23U
#define SPI_MISO 19U
#define SPI_CLK 18U
// UART
#define UART2_RX 16U
#define UART2_TX 17U

#endif