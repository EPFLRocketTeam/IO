#ifndef LORA_TX_H
#define LORA_TX_H

#include <SPI.h>
#include <LoRa.h>
#include "common.h"

class LoRa_TX{
    public:
    void begin(long freq = 433E6);
    bool awaitActivation(int packetSize = LoRa.parsePacket());
    void sendData(Data d[], int leng = NBDATA);
    void sendMessage(String outgoing);
    void onReceive(int packetSize);
    bool sleep();

    private:
    void writeHeader();
    const int csPin = 7;          // LoRa radio chip select
    const int resetPin = 6;       // LoRa radio reset
    const int irqPin = 3;         // change for your board; must be a hardware interrupt pin

    String outgoing;              // outgoing message
    String activationCode = "1234";
    byte msgCount = 0;            // count of outgoing messages
};

#endif // LORATX_H_INCLUDED
