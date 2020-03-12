#ifndef COMMON_H
#define COMMON_H

#define LOCAL_PRESSURE (1015)
#define BNO055_SAMPLERATE_DELAY_MS (100)

#define WAITPERIOD 120000
#define LOCALADDRESS 0xBB    // address of this device
#define DESTINATION 0xFF      // destination to send to
#define INTERVAL 2000
#define DATA 1
#define MESSAGE 2
#define HEADER 3

#define CS_LSD (8)
#define log_file_name F("datalog.txt")

#endif // COMMON_H
