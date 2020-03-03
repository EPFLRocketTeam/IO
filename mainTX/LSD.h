#ifndef LSD_H
#define LSD_H

#include <SPI.h>
#include <SD.h>
#include "common.h"

class LSD
{
public:
  LSD();
  static void begin();
  static void logData(Data d[], int leng = NBDATA);
};

#endif // LSD_H
