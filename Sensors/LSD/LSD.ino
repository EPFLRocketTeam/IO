#include "LSD.h"
#include "Data.h"

void setup() {
  Serial.begin(9600);
  while(!Serial);
  LSD::begin();
}

void loop() {
  Data d[NBDATA];
  for(int i(0); i < NBDATA; i++){
    d[i].f = float(millis());
  }
  LSD::logData(d);
}
