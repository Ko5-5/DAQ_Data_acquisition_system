#include "apps/sensor_tester_app.h"

#include "touchscreen/screen.h"

void SensorTester::appTask(void *arg){
    ScreenManager* screen = ScreenManager::GetInstance();

    screen->app_logo_screen(AppName::SENSOR_APP);

    vTaskDelay(pdMS_TO_TICKS(1000));

    while(1){
        Serial.println("Sensor tester app working");
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
    vTaskDelete(NULL);
}