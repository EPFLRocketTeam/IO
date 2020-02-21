#ifndef DATA_H
#define DATA_H

#define NBDATA 9
#define BYTE 4

union Data{
  float f;
  uint8_t i[4];
};

#endif // DATA_H
