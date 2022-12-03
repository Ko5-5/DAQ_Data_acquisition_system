#include "apps/launchpad_control_app.h"

#include "touchscreen/screen.h"

void LaunchpadControl::appTask(void *arg){
    ScreenManager* screen = ScreenManager::GetInstance();

    screen->app_logo_screen(AppName::LAUNCHPAD_APP);

    vTaskDelay(pdMS_TO_TICKS(1000));

    while(1){
        Serial.println("Lanuchpad control app working");
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
    vTaskDelete(NULL);
}