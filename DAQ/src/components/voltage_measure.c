#include "sensors/voltage_measure.h"

/*********************************  PRIVATE INCLUDES  *********************************************/

#include "esp_log.h"

/*********************************  PRIVATE VARIABLES  ********************************************/

static const char *TAG = "VOLTAGE_MEASURE";

/*********************************  PRIVATE FUNCTIONS  ********************************************/

static bool adc_calibration_init(Voltage_Measure_t *voltage_ptr) {
  esp_err_t ret;
  bool cali_enable = false;

  ret = esp_adc_cal_check_efuse(ADC_EXAMPLE_CALI_SCHEME);
  if (ret == ESP_ERR_NOT_SUPPORTED) {
    ESP_LOGW(TAG, "Calibration scheme not supported, skip software calibration");
  } else if (ret == ESP_ERR_INVALID_VERSION) {
    ESP_LOGW(TAG, "eFuse not burnt, skip software calibration");
  } else if (ret == ESP_OK) {
    cali_enable = true;
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_VOLTAGE, ADC_WIDTH_BIT_DEFAULT, 0, &(voltage_ptr->adc1_chars));
  } else {
    ESP_LOGE(TAG, "Invalid arg");
  }

  return cali_enable;
}

/*********************************  CODE  *********************************************************/

uint16_t voltage_measure_init(Voltage_Measure_t *voltage_ptr, adc1_channel_t adc_chan) {
  voltage_ptr->adc_channel = adc_chan;

  voltage_ptr->cali_enable = adc_calibration_init(voltage_ptr);

  adc1_config_width(ADC_WIDTH_BIT_DEFAULT);

  adc1_config_channel_atten(voltage_ptr->adc_channel, ADC_ATTEN_VOLTAGE);

  return RET_SUCCESS;
}

float get_voltage(Voltage_Measure_t *voltage_ptr) {
  voltage_ptr->adc_raw = adc1_get_raw(voltage_ptr->adc_channel);

  ESP_LOGI(TAG, "raw  data: %d", voltage_ptr->adc_raw);

  // if (voltage_ptr->cali_enable) {
  //   voltage_ptr->voltage = esp_adc_cal_raw_to_voltage(voltage_ptr->adc_raw, &(voltage_ptr->adc1_chars));
  //   ESP_LOGI(TAG, "cali data: %f mV", (double)voltage_ptr->voltage);
  // }

  // voltage_ptr->voltage = ((voltage_ptr->adc_raw * VOL_REF) / 4095.0) * DIV_MULTIPLIER_VOL;

  voltage_ptr->voltage = 3.3/4095.0 * voltage_ptr->adc_raw * DIV_MULTIPLIER_VOL + 3;

  return voltage_ptr->voltage;
}