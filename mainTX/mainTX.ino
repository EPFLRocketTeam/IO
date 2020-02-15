#include "LoRa_TX.h"
#include "BMP280.h"
#include "BNO055.h"
#include "LSD.h"
#include "Data.h"

BMP280 bmp;
BNO055 bno;
LoRa_TX LoRaTX;

double lastLoop = millis();
double curTime(0);

void setup() {
  Serial.begin(9600);
  while(!Serial);

  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  delay(10);
  
  bmp.begin();
  bno.begin();
  LSD::begin();
  LoRaTX.begin();
  awaitActivation();
}

String mess = "";
int msgCount(0);

void loop() {
  Data d[NBDATA];
  d[0].f = bmp.getAltitude();
  imu::Vector<3> acc = bno.getAcc();
  d[1].f = acc.x();
  d[2].f = acc.y();
  d[3].f = acc.z();
  imu::Vector<3> orient = bno.getOrientation();
  d[4].f = orient.x();
  d[5].f = orient.y();
  d[6].f = orient.z();
  d[7].f = sum(d);
  printData(d);
  LoRaTX.sendData(d);
  LSD::logData(d);
  
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
