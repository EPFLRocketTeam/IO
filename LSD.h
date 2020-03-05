#ifndef LSD_H
#define LSD_H

#include <SPI.h>
#include <SD.h>
#include "common.h"

class LSD
{
public:
    LSD();
    
    static void Begin();
    static void LogData(Data d[], int leng = NBDATA);
};

#endif // LSD_H