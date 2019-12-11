#include "LoRa_TX.h"
#include "Data.h"

LoRa_TX LoRaTX;

double lastLoop = millis();
double curTime(0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);
  
  LoRaTX.begin();
  awaitActivation();
}

String mess = "";
int msgCount(0);

void loop() {
  // put your main code here, to run repeatedly;
  Data d[NBDATA];
  for(int i(0); i < NBDATA; i++)
    d[i].f = random(1500);

  LoRaTX.sendData(d);
  curTime = millis();
  Serial.println(curTime - lastLoop);
  lastLoop = curTime;
}

void awaitActivation(){
  while(!LoRaTX.awaitActivation()){
    if (millis() - lastLoop > WAITPERIOD) {
      LoRaTX.sleep();
      delay(60000);
      lastLoop = millis();
    }
  }
}
