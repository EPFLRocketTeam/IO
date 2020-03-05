#include "LSD.h"

extern bool fail;

LSD::LSD()
{

}

static void LSD::begin()
{
    if (!SD.begin(CS))
    {
        Serial.println(F("Card failed, or not present"));
        fail = true;
        return;
    }

    Serial.println(F("SD card initialized."));
}

static void LSD::logData(Data d[], int leng = NBDATA)
{
    String dataString = "";
    for (int i(0); i < leng; i++)
        dataString += (String(d[i].f) + " ");

    File dataFile = SD.open(log_file_name, FILE_WRITE);

    if (dataFile)
    {
        dataFile.println(dataString);
        dataFile.close();
        //Serial.println(dataString);
    }
  
    else
        Serial.println(F("error opening datalog.txt"));
}