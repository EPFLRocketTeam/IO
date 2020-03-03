#ifndef BMP280_H
#define BMP280_H

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (9)

//BMP     ARD
//VCC     3.3v
//GND     GND
//SCL     A5(CLK)
//SDA     A4
//CSB     -
//SDD     3.3v
//VERIFIEE***

class BMP280{
  private:
  Adafruit_BMP280 bmp;
  public:
  BMP280();
  void begin();
  void printAltitude();
  float getAltitude();
  void printPressure();
  float getPressure();
};

#endif // BMP280_H_INCLUDED
