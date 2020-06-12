#include "LoRa_TX.h"

void LoRa_TX::begin(long freq = 433E6){
  LoRa.setPins(csPin, resetPin, irqPin);
  if (!LoRa.begin(freq)) {
    Serial.println("LoRa init failed. Check your connections.");
    while (true);                    // if failed, do nothing
  }
  Serial.println("LoRaTX Online; awaiting activation.");
}

bool LoRa_TX::awaitActivation(int packetSize = LoRa.parsePacket()){
  if (packetSize == 0) return false;
  Serial.println("Something received");
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
    timeStamp = atof(buf);
  }

  String incoming = "";

  while(LoRa.available()) {
    incoming += (char)LoRa.read();
    Serial.println(incoming);
  }
  
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

void LoRa_TX::sendData(float data[], int leng = NBDATA){
  LoRa.beginPacket();
  LoRa.write(DATA);
  
  char buf[BYTE*NBDATA];
  memcpy(buf,data,sizeof(data)); //copy float data to buf[]
  LoRa.write(buf, sizeof(buf));
  LoRa.endPacket();
  msgCount++;
}

void LoRa_TX::sendMessage(String outgoing) {
  LoRa.beginPacket();                   // start packet
  LoRa.write(MESSAGE);
  LoRa.write(outgoing.length());        // add payload length
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;                           // increment message ID
}

bool LoRa_TX::sleep(){
    LoRa.sleep();
}
