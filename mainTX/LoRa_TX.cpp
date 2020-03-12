#include "LoRa_TX.h"
#include "Data.h"

LoRa_TX::LoRa_TX()
    :   activationCode{"1234"}, msgCount{0}, rf95{csPin}  
{}

void LoRa_TX::Begin()
{
    if (!rf95.init())
    {
    	Serial.println(F("ERROR::LoRa init failed!"));
    	return;
    }

    Serial.println(F("LoRaTX Online, awaiting activation"));
}

void LoRa_TX::SendMessage(String outgoing){
  
}

void LoRa_TX::SendData(uint8_t data[], int length = NBR_DATA){
  uint8_t packet[NBR_DATA+HEADER];
  writeHeader(packet, data, DATA);
  rf95.send(packet, sizeof(packet));
  rf95.waitPacketSent();
  msgCount++;
}

void LoRa_TX::writeHeader(uint8_t packet[], uint8_t data[], byte messageType){
  packet[0] = LOCALADDRESS;
  packet[1] = messageType;
  packet[2] = msgCount;
  for(int k(0); k < NBR_DATA; k++){
    for(int j(0); j < BYTE; j++){
      packet[HEADER+k+j] = data[k+j];
    }
  }
}
