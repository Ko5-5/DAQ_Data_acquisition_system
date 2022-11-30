#ifndef SENSOR_TESTER_APP_H
#define SENSOR_TESTER_APP_H

#define SENSOR_TEST_APP_NUM 1

#define NUM_I2C_SENSORS 4
#define NUM_SPI_SENSORS 2
#define NUM_ADC_READS 2

class SensorTester{
private:
    bool is_connected_i2c[NUM_I2C_SENSORS];
    bool is_connected_spi[NUM_SPI_SENSORS];
    bool is_connected_adc[NUM_ADC_READS];

public:
    SensorTester();
    ~SensorTester();

    static void SensorTesterApp(void);

    bool measure_i2c_sensors();
    bool measure_spi_sensors();
    bool measure_adc_reads();

};

#endif