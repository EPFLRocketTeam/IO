#include "LSD.h"

LSD::LSD()
{

}

void LSD::Begin()
{
    if (!SD.begin(CS_LSD))
    {
        Serial.println(F("ERROR::SD Card init failed!"));
        return;
    }

    Serial.println(F("SD card initialized"));
}

void LSD::LogData(uint8_t packet[], int length = NBR_DATA*BYTE)
{
    Data data;
    String dataString = "";
    for (int i(0); i < length; i++){
      for(int j(0); j < BYTE; j++){
        data.i[0] = packet[i+j];
      }
      dataString += (String(data.f) + " ");
    }

    File dataFile = SD.open(log_file_name, FILE_WRITE);

    if (dataFile){
        dataFile.println(dataString);
        dataFile.close();
    }
    else
        Serial.println(F("ERROR::Can\'t open the file!"));
}
