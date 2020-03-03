#ifndef COMMON_H
#define COMMON_H

#include "../Data.h"

//From bmp
#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (9)

//From BNO055 
#define BNO055_SAMPLERATE_DELAY_MS (100)

//From LoRa
#define WAITPERIOD 120000
#define LOCALADDRESS 0xBB    // address of this device
#define DESTINATION 0xFF      // destination to send to
#define INTERVAL 2000
#define DATA 1
#define MESSAGE 2

//From LSD
#define CS_LSD (8)

bool fail = false;

#endif // COMMON_H
