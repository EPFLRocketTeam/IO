#include <SPI.h>
#include <RH_RF95.h>
#include "common.h"
#include "Data.h"

const int csPin = 7;

RH_RF95 rf95(csPin);

//LORA    ARD

//Vin     3.3v
//GND     GND
//EN      ---
//G0      D3
//SCK     D13
//MISO    D12
//MOSI    D11
//CS      D7
//RST     D6 

void setup() 
{  
  Serial.begin(9600);
  while (!Serial);
  if (!rf95.init())
    Serial.println("init failed");
  Serial.println("Ground Station Online.");
}

void loop()
{
  if (rf95.available())
    readLora();
}

void readLora(){
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  if(rf95.recv(buf, &len)){
    if(buf[0] = LOCALADDRESS){
      Data data;
      readHeader(buf);
      if(buf[1] = DATA){
        for(int i(HEADER); i < NBR_DATA+HEADER; i++){
          for(int j(0); j < BYTE; j++){
            data.i[j] = buf[i+j];
          }
          Serial.print(data.f);
          Serial.print(" ");
        }
        Serial.println();
      }
      else{
        Serial.print("got request: ");
        Serial.println((char*)buf);
      }
    }
  }
  else{
    Serial.println("recv failed");
  }
}

void readHeader(uint8_t buf[]){
  Serial.print(buf[1]);
  Serial.print(" ");
  Serial.print(buf[2]);
  Serial.print(" ");
}
  
