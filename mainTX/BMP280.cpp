#include "BMP280.h"

BMP280::BMP280()
  : bmp() 
{}

void BMP280::Begin()
{
    if (!bmp.begin())
    {
        Serial.println(F("ERROR::No BMP280 sensor detected!"));
        return;
    }

    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,   /* Operating Mode. */
        Adafruit_BMP280::SAMPLING_X2,               /* Temp. oversampling */
        Adafruit_BMP280::SAMPLING_X4,               /* Pressure oversampling */
        Adafruit_BMP280::FILTER_X8,
        Adafruit_BMP280::STANDBY_MS_63);

    Serial.println(F("BMP280 Online"));
}

void BMP280::PrintAltitude()
{
    Serial.print(F("Altitude [m]: "));
    Serial.print(GetAltitude());
    Serial.println();
}

float BMP280::GetAltitude()
{
    return bmp.readAltitude(LOCAL_PRESSURE);
}

void BMP280::PrintPressure()
{
    Serial.print(F("Pressure [Pa]: "));
    Serial.print(GetPressure());
    Serial.println();
}

float BMP280::GetPressure()
{
    return bmp.readPressure();
}
