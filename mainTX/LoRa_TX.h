#ifndef LORA_TX_H
#define LORA_TX_H

#include <SPI.h>
#include <RH_RF95.h>
#include "common.h"
#include "Data.h"

class LoRa_TX
{
public:
    LoRa_TX();
    void Begin();
    void SendMessage(String outgoing);
    void SendData(uint8_t data[], int length = NBR_DATA);
private:
    const int csPin = 7;          // LoRa radio chip select
    const int resetPin = 6;       // LoRa radio reset
    const int irqPin = 3;         // must be a hardware interrupt pin

    void writeHeader(uint8_t packet[], uint8_t data[], byte messageType);
    RH_RF95 rf95;
    String outgoing;
    String activationCode;
    byte msgCount;
};

#endif // LORA_TX_H
