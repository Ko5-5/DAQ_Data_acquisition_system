#include "tasks.h"

void config_task(void* arg) {
  HardwareManager* hardware = HardwareManager::GetInstance();
  ScreenManager* screen = ScreenManager::GetInstance();

  Serial.begin(115200);
  hardware->hardware_init();
  screen->init(&hardware->myI2C);

  vTaskDelay(pdMS_TO_TICKS(2000));

  screen->welcome_screen();

  vTaskDelay(pdMS_TO_TICKS(2000));

  screen->logo_screen();

  vTaskDelay(pdMS_TO_TICKS(2000));

  screen->app_sel_screen();

  ScreenManager::touchPoint point;
  uint8_t app_sel[3] = {0};  // target number of points for the app to launch is 10
  while (app_sel[0] < 11 && app_sel[1] < 11 && app_sel[2] < 11) {
    if (screen->read_touch(&point)) {
      if (point.z1 > 200) {
        if (point.y > 600 && point.y < 3500) {
          if (point.x > 600 && point.x < 1100) {
            app_sel[0]++;
          }
          if (point.x > 1700 && point.x < 2300) {
            app_sel[1]++;
          }
          if (point.x > 2800 && point.x < 3500) {
            app_sel[2]++;
          }
        }
      }
    }
  }

  DAQManager* daq = DAQManager::GetInstance();

  if (app_sel[0] > 9) {
    Serial.println("Sensors app");
    daq->selectedApp = AppName::SENSOR_APP;
    daq->app = SensorTester();
    xTaskCreatePinnedToCore(SensorTester::appTask, "Sensor Tester App Task", 8192, NULL, 5,
                            &tasks.appTask, APP_CPU_NUM);
  } else if (app_sel[1] > 9) {
    Serial.println("Static fire app");
    daq->selectedApp = AppName::STATIC_FIRE_APP;
    daq->app = StaticFire();
    xTaskCreatePinnedToCore(StaticFire::appTask, "Static Fire App Task", 8192, NULL, 5,
                            &tasks.appTask, APP_CPU_NUM);
  } else if (app_sel[2] > 9) {
    Serial.println("Launchpad app");
    daq->selectedApp = AppName::LAUNCHPAD_APP;
    daq->app = LaunchpadControl();
    xTaskCreatePinnedToCore(LaunchpadControl::appTask, "Launchpad Control App Task", 8192, NULL, 5,
                            &tasks.appTask, APP_CPU_NUM);
  }

  Serial.print("Launch app number: ");
  Serial.println((uint8_t)daq->selectedApp);

  vTaskDelete(tasks.configTask);
}