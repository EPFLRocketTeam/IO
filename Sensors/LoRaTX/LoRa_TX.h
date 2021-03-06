#ifndef LORA_TX_H
#define LORA_TX_H

#include <SPI.h>
#include <LoRa.h>
#include "Data.h"

#define WAITPERIOD 120000
#define LOCALADDRESS 0xBB    // address of this device
#define DESTINATION 0xFF      // destination to send to
#define INTERVAL 2000
#define DATA 1
#define MESSAGE 2

//LORA    ARD

//Vin     3.3v
//GND     GND
//EN      ---
//G0      D3
//SCK     D13
//MISO    D12
//MOSI    D11
//CS      D7
//RST     D6
//VERIFIEE    

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
