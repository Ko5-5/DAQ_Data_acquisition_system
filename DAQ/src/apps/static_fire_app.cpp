#include "apps/static_fire_app.h"

#include "touchscreen/screen.h"

void StaticFire::appTask(void *arg){
    ScreenManager* screen = ScreenManager::GetInstance();

    screen->app_logo_screen(AppName::STATIC_FIRE_APP);

    vTaskDelay(pdMS_TO_TICKS(1000));

    while(1){
        Serial.println("Static fire app working");
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
    vTaskDelete(NULL);
}