#ifndef BMP280_H
#define BMP280_H

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include "common.h"

class BMP280
{
public:
    BMP280();
    void Begin();

    void PrintAltitude() const;
    float& GetAltitude() const;
    
    void PrintPressure() const;
    float& GetPressure() const;

private:
    Adafruit_BMP280 bmp;
};

#endif // BMP280_H