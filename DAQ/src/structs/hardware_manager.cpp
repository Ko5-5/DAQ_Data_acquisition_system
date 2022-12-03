#include "structs/hardware_manager.h"

HardwareManager* HardwareManager::pInstance{nullptr};
std::mutex HardwareManager::pMutex;

HardwareManager* HardwareManager::GetInstance() {
  std::lock_guard<std::mutex> lock(pMutex);
  if (pInstance == nullptr) {
    pInstance = new HardwareManager();
  }
  return pInstance;
}

bool HardwareManager::hardware_init() {
  Serial.println(" --- I2C init --- ");
  myI2C.begin(ESP_I2C_SDA, ESP_I2C_SCL, 100E3);
  myI2C.setTimeOut(20);

  Serial.println("SPI init");
  mySPI.begin();
}

bool HardwareManager::uart_init() {
  Serial.println(" --- UART2 init --- ");
  mySerial.begin(115200, SERIAL_8N1, ESP_UART2_RX, ESP_UART2_TX);
}

bool HardwareManager::uart_deinit() {
  Serial.println(" --- UART2 deinit --- ");
  mySerial.end();
}