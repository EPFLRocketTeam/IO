#include "LSD.h"

LSD::LSD(){}

static uint8_t i=0;
static void LSD::begin(){
  if (!SD.begin(CS))
  {
    Serial.println(F("Card failed, or not present"));
    for(;;);
  }
  
  Serial.println(F("SD card initialized."));
}

static void LSD::logData(float d[], int leng = NBDATA){
  String dataString = "";
  for (int i(0); i < leng-1; i++) {
    dataString += (String(d[i]) + " ");
  }
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
  if (i == 0){
    delay(3000);
    i=1;
  }
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }
  
  else {
    Serial.println(F("error opening datalog.txt"));
  }
}
