#ifndef BNO055_H
#define BNO055_H

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

class BNO055
{
public:
    BNO055();
    
    void Begin();
    imu::Vector<3> GetEuler();
    imu::Vector<3> GetAcceleration();

private:
    Adafruit_BNO055 bno;
};

#endif // BNO055_H
