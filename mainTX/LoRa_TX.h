#ifndef LORA_TX_H
#define LORA_TX_H

#include <SPI.h>
#include <LoRa.h>
#include "common.h"
#include "Data.h"

class LoRa_TX
{
public:
    void Begin(long int freq = 433E6);
    bool AwaitActivation(int packetSize = LoRa.parsePacket());
    void SendData(Data data[], int length = NBR_DATA);
    void SendMessage(String outgoing);
    void OnReceive(int packetSize);
    bool Sleep();

private:
    void WriteHeader();

    const int csPin = 7;          // LoRa radio chip select
    const int resetPin = 6;       // LoRa radio reset
    const int irqPin = 3;         // change for your board; must be a hardware interrupt pin

    String outgoing;
    String activationCode;
    byte msgCount;
};

#endif // LORA_TX_H