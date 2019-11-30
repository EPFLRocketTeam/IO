#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (10)
#define BMP_MOSI (12)
#define BMP_CS   (11)

Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

void setup()
{
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));

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
}

void loop() {
    //Serial.print(F("Temperature(°C): "));
    //Serial.print(bmp.readTemperature());
    //Serial.print(" ");

    //Serial.print(F("Pressure (Pa): "));
    //Serial.print(bmp.readPressure());
    //Serial.print(" ");

    Serial.print(F("Altitude (m): "));
    Serial.print(bmp.readAltitude(1005));
    Serial.println();
}
