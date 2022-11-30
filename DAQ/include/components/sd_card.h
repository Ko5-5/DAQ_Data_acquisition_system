#ifndef SD_CARD_H
#define SD_CARD_H

#include <FS.h>
#include <SPI.h>
#include <SD.h>
#include "vfs_api.h"


class SDCard{
  SPIClass spi;
  uint8_t cs;
  SDFS __mySD;

  public:
  SDCard(SPIClass &_spi, uint8_t _cs);
  bool init();
  bool write(String path, const String & data); 
  bool write(String path, char *dataFrame);
  bool fileExists(String path);
};

#endif