#include "LoRa_TX.h"

void LoRa_TX::begin(long freq){
  LoRa.setPins(csPin, resetPin, irqPin);
  if (!LoRa.begin(freq)) {
    Serial.println("LoRa init failed. Check your connections.");
    while (true);                    // if failed, do nothing
  }
  Serial.println("LoRaTX Online; awaiting activation.");

}

bool LoRa_TX::awaitActivation(int packetSize){
  if (packetSize == 0) return false;
  if(LoRa.read() != LOCALADDRESS){
    Serial.println("Message not for me");
  }
  else if(LoRa.read() != DESTINATION){
    Serial.println("Wrong sender address");
  }
  LoRa.read(); //incoming msgCount
  
  float timeStamp = 0;
  {
    char buf[BYTE];
    for(int i(0); i < BYTE; i++)
      buf[i] = LoRa.read();
    memcpy(&timeStamp,buf,sizeof(timeStamp));
  }
  
  uint8_t codelength = LoRa.read();
  
  String incoming = "";
  while(LoRa.available()){
    incoming += (char)LoRa.read();                                        
  }
  Serial.println(incoming);
  
  if(incoming == activationCode){
    Serial.print(F("Avionics Activated at time(")); 
    Serial.print(timeStamp/1000., 4); 
    Serial.print(F(") with code: "));
    Serial.println(incoming);
    sendMessage("Active");
    return true;
  }

  sendMessage("INCORRECT ACTIVATION CODE");
  return false;
}

void LoRa_TX::sendData(float data[]){//, int leng){
  uint8_t buf[BYTE*NBDATA];                                                        
  memcpy(buf,data,sizeof(data)); //copy float data to buf[]
  
  LoRa.beginPacket();
  LoRa.write(DATA);
  LoRa.write(DESTINATION);
  LoRa.write(LOCALADDRESS);
  LoRa.write(msgCount); 
  LoRa.write(*buf, sizeof(buf)); for(int i(0); i < NBDATA*BYTE ; i++){Serial.print(buf[i]); Serial.print(" ");} Serial.println();
  LoRa.endPacket();
  msgCount++; 
}

void LoRa_TX::sendMessage(String outgoing) {
  LoRa.beginPacket();                   // start packet
  LoRa.write(MESSAGE);
  LoRa.write(DESTINATION);              // add destination address
  LoRa.write(LOCALADDRESS);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(outgoing.length());        // add payload length
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                   // finish packet and send it
  msgCount++;                           // increment message ID
}

bool LoRa_TX::sleep(){
    LoRa.sleep();
}
