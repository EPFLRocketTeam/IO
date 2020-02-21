#ifndef BNO055_H
#define BNO055_H

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//BNO     ARD
//VDD     3.3v
//GND     GND
//SCL     A5(CLK)
//SDA     A4
//VERIFIEE***

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

class BNO055{
  private:
  Adafruit_BNO055 bno;
  public:
  BNO055();
  void begin();
 // imu::Vector<3> getOrientation();
  imu::Vector<3> getAcc();
};

#endif // BNO055_H_INCLUDED
