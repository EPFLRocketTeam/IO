#include "BNO055.h"

BNO055::BNO055()
  : bno(-1, 0x28)
{}

void BNO055::begin(){
  if (!bno.begin())
  {
    Serial.println(F("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!"));
    for(;;);
  }
  
  Serial.println(F("BNO055 Online."));
}

//imu::Vector<3> BNO055::getOrientation(){
 // return bno.getVector(Adafruit_BNO055::VECTOR_EULER);
//}

imu::Vector<3> BNO055::getAcc(){
  return bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
}
