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
  /*
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length
  */
  Data timeStamp;
  for(int i(0); i < BYTE; i++)
    timeStamp.i[i] = LoRa.read();

  String incoming = "";

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
    Serial.println(incoming);
  }

  /*
  if (incomingLength != incoming.length()) {   // check length for error
    Serial.println("error: message length does not match length");
    return false;                             // skip rest of function
  }

  // if the recipient isn't this device or broadcast,
  if (recipient != LOCALADDRESS && sender != DESTINATION) {
    Serial.println("This message is not for me.");
    return false;                             // skip rest of function
  }
  */
  
  if(incoming == activationCode){
    Serial.print(F("Avionics Activated at time(")); 
    Serial.print(timeStamp.f/1000., 4); 
    Serial.print(F(") with code: "));
    Serial.println(incoming);
    sendMessage("Active");
    return true;
  }

  sendMessage("INCORRECT ACTIVATION CODE");
  return false;
}

void LoRa_TX::sendData(Data d[], int leng = NBDATA){
  LoRa.beginPacket();
  LoRa.write(DATA);
  writeHeader();
  Serial.print(F("no. "));
  Serial.println(msgCount);
  
  for(int j(0); j < leng; j++){
    for(int h(0); h < BYTE; h++){
      LoRa.write(d[j].i[h]);
    }
  }
  LoRa.endPacket();
  msgCount++;
}

void LoRa_TX::sendMessage(String outgoing) {
  LoRa.beginPacket();                   // start packet
  LoRa.write(MESSAGE);
  writeHeader();
  LoRa.write(outgoing.length());        // add payload length
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;                           // increment message ID
}

void LoRa_TX::writeHeader(){
  LoRa.write(DESTINATION);              // add destination address
  LoRa.write(LOCALADDRESS);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  Data t;
  t.f = millis();
  LoRa.write(t.i, 4);                   //add time stamp
}

/*
void LoRa_TX::onReceive(int packetSize) {
  if (packetSize == 0) return;          // if there's no packet, return

  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length
  Data t;
  for(int i(0); i < 4; i++)
    t.i[i] = LoRa.read();
  
  String incoming = "";

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  if (incomingLength != incoming.length()) {   // check length for error
    Serial.println("error: message length does not match length");
    return;                             // skip rest of function
  }

  // if the recipient isn't this device or broadcast,
  if (recipient != LOCALADDRESS && recipient != 0xFF) {
    Serial.println("This message is not for me.");
    return;                             // skip rest of function
  }

  // if message is for this device, or broadcast, print details:
  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Sent to: 0x" + String(recipient, HEX));
  Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message length: " + String(incomingLength));
  Serial.println("Time:" + String(t.f/1000.));
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();
}
*/

bool LoRa_TX::sleep(){
    LoRa.sleep();
}
