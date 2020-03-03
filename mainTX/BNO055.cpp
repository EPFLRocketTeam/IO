#include "BNO055.h"

extern int fail;

BNO055::BNO055()
  : bno(-1, 0x28)
{}

void BNO055::begin()
{
    if (!bno.begin())
    {
        Serial.println(F("Ooops, no BNO055 detected!"));
        fail = true;
        return;
    }

    Serial.println(F("BNO055 Online."));
}

imu::Vector<3>& BNO055::GetOrientation()
{
    return bno.getVector(Adafruit_BNO055::VECTOR_EULER);
}

imu::Vector<3>& BNO055::GetAcc()
{
    return bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
}