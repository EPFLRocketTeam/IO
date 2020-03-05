#ifndef BMP280_H
#define BMP280_H

#include <Wire.h>
#include <Adafruit_BMP280.h>

class BMP280
{
public:
    BMP280();
    void Begin();

    void PrintAltitude();
    float GetAltitude();
    
    void PrintPressure();
    float GetPressure();

private:
    Adafruit_BMP280 bmp;
};

#endif // BMP280_H