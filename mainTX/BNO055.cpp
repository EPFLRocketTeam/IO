#include "BNO055.h"

#include "common.h"

BNO055::BNO055()
  : bno(-1, 0x28)
{}

void BNO055::Begin()
{
    if (!bno.begin())
    {
        Serial.println(F("Ooops, no BNO055 detected!"));
        return;
    }

    Serial.println(F("BNO055 Online."));
}

imu::Vector<3> BNO055::GetEuler()
{
    return bno.getVector(Adafruit_BNO055::VECTOR_EULER);
}

imu::Vector<3> BNO055::GetAcceleration()
{
    return bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
}