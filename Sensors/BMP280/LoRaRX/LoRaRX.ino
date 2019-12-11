#include <SPI.h>              
#include <LoRa.h>
#include "Data.h"

#define NBDATA 8
#define BYTE 4

const int csPin = 7;       //CS  
const int resetPin = 6;   //RST    
const int irqPin = 3;    //G0     

String outgoing;              // outgoing message

byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0xFF;     // address of this device
byte destination = 0xBB;      // destination to send to

float lastTime = 0;

void setup() {
  Serial.begin(74880);                   
  while (!Serial);

  Serial.println("Ground Station initialisation");
  beginLora();
}

void loop() {
  onReceive(LoRa.parsePacket());
}

void sendMessage(String outgoing) {
  LoRa.beginPacket();                   // start packet
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(outgoing.length());        // add payload length
  Data t;
  t.f = millis();
  LoRa.write(t.i, 4); 
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;                           // increment message ID
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;          // if there's no packet

  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  
  //***********Je vais mettre un checkSum et quelques verifications sur les donnees quelque part ici

  if (recipient != localAddress && recipient != 0xFF) {
    Serial.println("This message is not for me.");
    return;                            
  }

  //Serial.println("Received from: 0x" + String(sender, HEX)); 
  //Serial.println("Sent to: 0x" + String(recipient, HEX));
  Serial.println("Message ID: " + String(incomingMsgId));
  Data t; //le temps
  for(int i(0); i < BYTE; i++)
    t.i[i] = LoRa.read();
  Serial.println("Time interval: " + String((t.f - lastTime))); //Pour tester la frequence d'echantillonage
  lastTime = t.f;
  
  for(int i(0); i < NBDATA; i++){
    for(int j(0); j < BYTE; j++){
      Serial.print(LoRa.read());//LoRa.read() lit les donnees un octet a la fois et chaque float compte 4 octets
      Serial.print(" "); 
    }
    Serial.println();
  }
  //Serial.println("RSSI: " + String(LoRa.packetRssi())); //signal strength
  //Serial.println("Snr: " + String(LoRa.packetSnr())); //Ca mesure le niveau de bruit et le signal strength
  
  Serial.println();
}

void beginLora(){
  LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRaRX init failed. Check your connections.");
    while (true);                       // if failed, do nothing
  }

  Serial.println("LoRaRX online.");
  
  Serial.println("Activate Avionics? Y / N");
  while(!Serial.available() && !(Serial.readString() == "Y"));
  sendMessage("1234");
}
