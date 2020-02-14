#ifndef LSD_H
#define LSD_H

#include <SPI.h>
#include <SD.h>
#include "Data.h"

#define CS (8)

//LSD     ARD
//VCC     3.3v
//GND     GND
//CLK     D13(SCK)
//D0      D12(MISO)
//D1      D11(MOSI)
//CS      D8
//VERIFIEE***

class LSD{
  public:
  LSD();
  static void begin();
  static void logData(Data d[], int leng = NBDATA);
};

#endif // LSD_H
