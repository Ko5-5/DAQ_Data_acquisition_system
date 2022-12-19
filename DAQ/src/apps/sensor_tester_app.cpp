#include "apps/sensor_tester_app.h"

#include "touchscreen/screen.h"

void SensorTester::appTask(void* arg) {
  ScreenManager* screen = ScreenManager::GetInstance();

  screen->app_logo_screen(AppName::SENSOR_APP);

  vTaskDelay(pdMS_TO_TICKS(1000));

  int graph[278] = {0};
  int refresh_graph = 0;

  for (int i = 0; i < MAX_X_GRAPH; i++) {
    graph[i] = 250;
  }

  screen->tester_graph_screen("Sensor", graph);

  while (1) {
    Serial.println("Sensor tester app working");
    refresh_graph++;

    if (refresh_graph > 4) {
      screen->tester_graph_screen("Sensor", graph);
      refresh_graph = 0;
      for (int i = 0; i < MAX_X_GRAPH; i++) {
        graph[i] = 250 + 50 * sin(20 * i);
      }
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  }
  vTaskDelete(NULL);
}