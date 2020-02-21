#include "LoRa_TX.h"
#include "BMP280.h"
#include "BNO055.h"
#include "LSD.h"
#include "Data.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

unsigned long time;

BMP280 bmp;
LoRa_TX LoRaTX;

double lastLoop = millis();
double curTime(0);
/* This driver reads raw data from the BNO055

   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3.3V DC
   Connect GROUND to common ground

   History
   =======
   2015/MAR/03  - First release (KTOWN)
*/

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address
Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28);

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void)
{
  Serial.begin(115200);
  Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  delay(10);
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);

  /* Display the current temperature */
  int8_t temp = bno.getTemp();
  Serial.print("Current Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.println("");

  bno.setExtCrystalUse(true);

  Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");
   LSD::begin();
   delay(10);
   bmp.begin(); 
}

String mess = "";
int msgCount(0);


void loop(void)
{
  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2
  imu::Vector<3> acc = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  imu::Vector<3> angle = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  Data d[NBDATA];
  time=millis();
  /* Display the floating point data */
  Serial.print("accX: ");
  d[0].f = acc.x();
  Serial.print(acc.x());
  Serial.print(" accY: ");
  d[1].f = acc.x();
  Serial.print(acc.y());
  Serial.print(" accZ: ");
  d[2].f = acc.x();
  Serial.print(acc.z());
  d[3].f = bmp.getAltitude();
  Serial.print(" altitude: ");
  Serial.print(bmp.getAltitude());
  Serial.print(" X :");
  d[4].f = angle.x();
  Serial.print(angle.x());
  Serial.print(" Y :");
  d[5].f = angle.y();
  Serial.print(angle.y());
  Serial.print(" Z :");
  d[6].f = angle.z();
  Serial.print(angle.z());
  
  Serial.print("\t\t");

  
  LSD::logData(d);
  LoRaTX.sendData(d);
  /*
  // Quaternion data
  imu::Quaternion quat = bno.getQuat();
  Serial.print("qW: ");
  Serial.print(quat.w(), 4);
  Serial.print(" qX: ");
  Serial.print(quat.x(), 4);
  Serial.print(" qY: ");
  Serial.print(quat.y(), 4);
  Serial.print(" qZ: ");
  Serial.print(quat.z(), 4);
  Serial.print("\t\t");
  */

  /* Display calibration status for each sensor. */
  uint8_t system, gyro, accel, mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);
  Serial.print("CALIBRATION: Sys=");
  Serial.print(system, DEC);
 // Serial.print(" Gyro=");
 // Serial.print(gyro, DEC);
 // Serial.print(" Accel=");
 // Serial.print(accel, DEC);
 // Serial.print(" Mag=");
 // Serial.println(mag, DEC);

  delay(BNO055_SAMPLERATE_DELAY_MS);
    msgCount++;
}


void awaitActivation(){
  while(!LoRaTX.awaitActivation()){
    if (millis() - lastLoop > WAITPERIOD) {
      Serial.println(F("no or wrong code received in determined interval"));
      LoRaTX.sleep();
      delay(60000);
    }
    lastLoop = millis();
  }
}

float sum(Data d[]){
  float s(0);
  for(int i(0); i < NBDATA-1; i++){
    s += d[i].f;
  }
  return s;
}

void printData(Data d[]){
  for(int i(0); i < NBDATA; i++){
    Serial.println(d[i].f);
  }
  Serial.println();
}

void printTimeLapse(){
  curTime = millis();
  //Serial.println(curTime - lastLoop);
  lastLoop = curTime;
}
