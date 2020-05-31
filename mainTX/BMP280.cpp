#include "BMP280.h"

BMP280::BMP280()
  : bmp()
{}

void BMP280::begin(){
  if (!bmp.begin())
  {
    Serial.println(F("ERROR::No BMP280 sensor detected!"));
    for(;;);
  }
  
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
              Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
              Adafruit_BMP280::SAMPLING_X4,    /* Pressure oversampling */
              Adafruit_BMP280::FILTER_X8,      /* Filtering. */
              Adafruit_BMP280::STANDBY_MS_63); /* Standby time. */
  Serial.println("BMP280 Online.");
}

void BMP280::printAltitude(){
  Serial.print(F("Altitude (m): "));
  Serial.print(bmp.readAltitude(1005));
  Serial.println();
}

float BMP280::getAltitude(){
  return bmp.readAltitude(1005);
}

void BMP280::printPressure(){
  Serial.print(F("Pressure (Pa): "));
  Serial.print(bmp.readPressure());
  Serial.println();
}

float BMP280::getPressure(){
  return bmp.readPressure();
}
