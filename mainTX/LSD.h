#ifndef LSD_H
#define LSD_H

#include <SPI.h>
#include <SD.h>
#include "common.h"
#include "Data.h"

class LSD
{
public:
    LSD();
    
    void Begin();
    void LogData(Data d[], int length = NBR_DATA);
};

#endif // LSD_H
