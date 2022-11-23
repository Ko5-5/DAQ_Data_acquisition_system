#include "structs/hardware_manager.h"

bool HardwareManager::hardware_init() {
  Serial.println(" --- I2C init --- ");
  myI2C.begin(I2C_SDA, I2C_SCL, 100E3);
  myI2C.setTimeOut(20);

  Serial.println("SPI init");
  mySPI.begin();
}

bool HardwareManager::uart_init() {
  Serial.println(" --- UART2 init --- ");
  mySerial.begin(115200, SERIAL_8N1, UART2_RX, UART2_TX);
}

bool HardwareManager::uart_deinit() {
  Serial.println(" --- UART2 deinit --- ");
  mySerial.end();
}