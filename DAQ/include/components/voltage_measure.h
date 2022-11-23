#ifndef VOLTAGE_MEASURE_HH
#define VOLTAGE_MEASURE_HH

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "driver/adc.h"
#include "esp_adc_cal.h"

/*********************************  CONFIG INCLUDES  **********************************************/

#include "config/config.h"

/*********************************  DEFINES  ******************************************************/

#define ADC_ATTEN_VOLTAGE ADC_ATTEN_DB_11  // ADC channel attenuation - can be changed

// ADC Calibration
#if CONFIG_IDF_TARGET_ESP32
#define ADC_EXAMPLE_CALI_SCHEME ESP_ADC_CAL_VAL_EFUSE_VREF
#elif CONFIG_IDF_TARGET_ESP32S2
#define ADC_EXAMPLE_CALI_SCHEME ESP_ADC_CAL_VAL_EFUSE_TP
#elif CONFIG_IDF_TARGET_ESP32C3
#define ADC_EXAMPLE_CALI_SCHEME ESP_ADC_CAL_VAL_EFUSE_TP
#elif CONFIG_IDF_TARGET_ESP32S3
#define ADC_EXAMPLE_CALI_SCHEME ESP_ADC_CAL_VAL_EFUSE_TP_FIT
#endif

/*********************************  INIT **********************************************************/

#define VOLTAGE_MEASURE_INIT(X) {.adc_channel = X, .cali_enable = false, .adc_raw = 0, .voltage = 0}

/*********************************  PUBLIC VARIABLES  *********************************************/

/*********************************  CODE **********************************************************/

typedef struct Voltage_Measure {
  adc1_channel_t adc_channel;
  bool cali_enable;
  int adc_raw;
  float voltage;
  esp_adc_cal_characteristics_t adc1_chars;
} Voltage_Measure_t;

uint16_t voltage_measure_init(Voltage_Measure_t *voltage_ptr, adc1_channel_t adc_chan);

float get_voltage(Voltage_Measure_t *voltage_ptr);

#endif  // VOLTAGE_MEASURE_HH