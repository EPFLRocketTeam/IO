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
    void LogData(uint8_t packet[], int length = NBR_DATA*BYTE);
};

#endif // LSD_H
