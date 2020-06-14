#include "LoRa_TX.h"
#include "BMP280.h"
#include "BNO055.h"
#include "LSD.h"
#include "Data.h"
#define BPM 120
#define C4  261.63
#define C8  4186.01
#define Q 60000/BPM

BMP280 bmp;
BNO055 bno;
LoRa_TX LoRaTX;

double lastLoop = millis();
double curTime(0);

void setup() {
  onTone();
  Serial.begin(9600);
  while (!Serial);

  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  delay(10);
  bmp.begin();
  bno.begin();
  //LSD::begin();
  LoRaTX.begin();
  awaitActivation();
  onlineTone();
}

String mess = "";
//int msgCount(0);
float data[] = {5,1,2,3,4,5,6,7,8,9};

void loop() {
  /*data[0] = millis();
  data[1] = LoRaTX.msgCount;
  data[2] = bmp.getAltitude();
  imu::Vector<3> acc = bno.getAcc();
  data[3] = acc.x();
  data[4] = acc.y();
  data[5] = acc.z();
  imu::Vector<3> orient = bno.getOrientation();
  data[6] = orient.x();
  data[7] = orient.y();
  data[8] = orient.z();
  data[9] = sum(data);*/
  //printData(data);
  LoRaTX.sendData(data);
  //LSD::logData(data);

  //LoRaTX.msgCount++;
}

float sum(float d[]) {
  float s(0);
  for (int i(0); i < NBDATA - 1; i++) {
    s += d[i];
  }
  return s;
}

void printData(float d[]) {
  for (int i(0); i < NBDATA; i++) {
    Serial.print((String)d[i] + F(" "));
  }
  Serial.println();
}

void printTimeLapse() {
  curTime = millis();
  //Serial.println(curTime - lastLoop);
  lastLoop = curTime;
}

void onTone(){
  //tone(pin, note, duration)
  for(int i(0); i < 2000; i++){
    tone(9,C8-i,Q+4); 
  }
}

void onlineTone(){
  tone(9, C4, Q*4);
}


void awaitActivation() {
  while (!LoRaTX.awaitActivation()){
    delay(50);
  }
}
