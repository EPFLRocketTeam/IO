#include "LSD.h"

LSD::LSD(){}

static void LSD::begin(){
  if (!SD.begin(CS))
  {
    Serial.println("Card failed, or not present");
    for(;;);
  }
  
  Serial.println(F("SD card initialized."));
}

static void LSD::logData(Data d[], int leng = NBDATA){
  String dataString = "";
  for (int i(0); i < leng; i++) {
    dataString += (String(d[i].f) + " ");
  }

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    //Serial.println(dataString);
  }
  
  else {
    Serial.println("error opening datalog.txt");
  }
}
