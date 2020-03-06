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

void LSD::LogData(Data d[], int length)
{
    String dataString = "";
    for (int i(0); i < length; i++)
        dataString += (String(d[i].f) + " ");

    File dataFile = SD.open(log_file_name, FILE_WRITE);

    if (dataFile)
    {
        dataFile.println(dataString);
        dataFile.close();
    }
  
    else
        Serial.println(F("ERROR::Can\'t open the file!"));
}
