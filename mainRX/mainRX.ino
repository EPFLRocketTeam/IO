#include <SPI.h>              
#include <LoRa.h>
#include "Data.h"

const int csPin = 7;       //CS  
const int resetPin = 6;   //RST    
const int irqPin = 3;    //G0

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

String outgoing;              // outgoing message
byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0xFF;     // address of this device
byte destination = 0xBB;      // destination to send to

float lastTime = 0;

void setup() {
  Serial.begin(9600);                   
  while (!Serial);

  Serial.println("Ground Station initialisation");
  beginLora();
}

void loop() {
  onReceive(LoRa.parsePacket());
}

void beginLora(){
  LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRaRX init failed. Check your connections.");
    while (true);                       // if failed, do nothing
  }

  Serial.println("LoRaRX online.");
  Serial.println("Activate Avionics? Y / N");
  
  //while(!(Serial.available() && Serial.read() == 'Y'));
  sendMessage("1234");
  Serial.println("Activating...\n");
}

void sendMessage(String outgoing) {
  LoRa.beginPacket();                   // start packet
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  uint8_t buf[BYTE];
  float ti = millis();
  memcpy(buf,&ti,sizeof(ti));
  LoRa.write(buf, sizeof(buf));         // add current time*/
  LoRa.write((uint8_t)outgoing.length());        // add payload length
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;                           // increment message ID
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;          // if there's no packet
                                                          Serial.println("PacketSize = " + (String)packetSize);
  switch(LoRa.read()){
   case MESSAGE  :
      stringReceive();
      break;
  
   default : 
      dataReceive();
  }
}

void dataReceive(){
  uint8_t recipient = LoRa.read();          // recipient address
  uint8_t sender = LoRa.read();            // sender address
  uint8_t incomingMsgId = LoRa.read();     // incoming msg ID
  
  Serial.println("incoming Msg : " + (String)incomingMsgId);
  
  Data data[NBDATA];                   //le temps?????????????????
  
  //Serial.println("Received from: 0x" + String(sender, HEX)); 
  //Serial.println("Sent to: 0x" + String(recipient, HEX));
  //Serial.println("Message ID: " + String(incomingMsgId));

  //Serial.print("Temps : ");
  //Serial.println(t.f/1000);
  //Serial.println("Time interval: " + String((t.f - lastTime))); //Pour tester la frequence d'echantillonage
  
  for(int j(0); j < NBDATA; j++){
      for(int k(0); k < BYTE; k++){
        data[j].i[k] = LoRa.read();
      }
    }
  
  printData(data);
  
  /*if(checkSum(d))
    Serial.println("Checksum verified");
  else
    Serial.println("False Checksum");
  */         
  //Serial.println("RSSI: " + String(LoRa.packetRssi())); //signal strength
  //Serial.println("Snr: " + String(LoRa.packetSnr())); //Ca mesure le niveau de bruit et le signal strength
  Serial.println();
}

void stringReceive(){
  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
/*  float t;
  char buf[BYTE];
  for(int i(0); i < 4; i++)
    buf[i] = LoRa.read();
  t = atof(buf);
  */
  byte incomingLength = LoRa.read();    // incoming msg length
  String incoming = "";

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }
  if (incomingLength != incoming.length()) {   // check length for error
    Serial.println("error: message length does not match length");
    return;                             // skip rest of function
  }

  // if the recipient isn't this device or broadcast,
  if (recipient != localAddress && recipient != 0xFF) {
    Serial.println("This message is not for me.");
    return;                             // skip rest of function
  }

  // if message is for this device, or broadcast, print details:
  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Sent to: 0x" + String(recipient, HEX));
  Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message length: " + String(incomingLength));
//  Serial.println("Time:" + String(t/1000.));
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();
}

void printData(Data d[]){
  for(int i(0); i < NBDATA; i++){
    Serial.print(d[i].f);
    Serial.print(" ");
  }
  Serial.println();
}

bool checkSum(float d[]){
  float s(0);
  for(int i(0); i < NBDATA-1; i++){
    s += d[i];
  }
  
  if(s == d[NBDATA-1])
    return true;
  return false;
}
