#include "BMP280.h"
#include "BNO055.h"
#include "LSD.h"
#include "LoRa_TX.h"

BMP280 bmp;
BNO055 bno;
LSD lsd;
LoRa_TX lora;

void addData(int index, int length = NBR_DATA);

void setup() 
{
  Serial.begin(9600);
  while (!Serial);
  bmp.Begin(); 
  bno.Begin();
  lsd.Begin();
  lora.Begin();
}

int msgCount;
Data data;
uint8_t packet[NBR_DATA*BYTE];

void loop()
{
  data.f = millis();
  addData(0);
  imu::Vector<3> acc = bno.GetAcceleration();
  data.f = acc.x();
  addData(1);
  data.f = acc.y();
  addData(2);
  data.f = acc.z();
  addData(3);
  data.f = bmp.GetAltitude();
  addData(4);
  imu::Vector<3> ang = bno.GetEuler();
  data.f = ang.x();
  addData(5);
  data.f = ang.y();
  addData(6);
  data.f = ang.z();
  addData(7);

  lsd.LogData(packet);
  lora.SendData(packet);
  
  delay(400);
}

void addData(int index, int length = NBR_DATA){
  for(int j(0); j < BYTE; j++){
   packet[index+j] = data.i[j];
  }
}
