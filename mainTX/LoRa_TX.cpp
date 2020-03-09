#include "LoRa_TX.h"

LoRa_TX::LoRa_TX()
    :   activationCode{"1234"}, msgCount{0}  
{}

void LoRa_TX::Begin(long int freq)
{
    LoRa.setPins(csPin, resetPin, irqPin);
    if (!LoRa.begin(freq))
    {
    	Serial.println(F("ERROR::LoRa init failed!"));
    	return;
    }

    Serial.println(F("LoRaTX Online, awaiting activation"));
}

bool LoRa_TX::AwaitActivation(int packetSize = LoRa.parsePacket())
{
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
    
    while (LoRa.available())
    {
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

    if(incoming == activationCode)
    {
    	Serial.print(F("Avionics Activated at time("));
    	Serial.print(timeStamp.f/1000., 4);
    	Serial.print(F(") with code: "));
    	Serial.println(incoming);
    	SendMessage("Active");
    	return true;
    }

    SendMessage(F("INCORRECT ACTIVATION CODE"));
    return false;
}

void LoRa_TX::SendData(Data data[], int length = NBR_DATA)
{
    LoRa.beginPacket();
    LoRa.write(DATA);
    WriteHeader();
    Serial.print(F("no"));
    Serial.println(msgCount);

    for(int j(0); j < length; j++)
        for(int h(0); h < BYTE; h++)
            LoRa.write(data[j].i[h]);

    LoRa.endPacket();
    msgCount++;
}

void LoRa_TX::SendMessage(String outgoing)
{
    LoRa.beginPacket();                   // start packet
    LoRa.write(MESSAGE);
    WriteHeader();
    LoRa.write(outgoing.length());        // add payload length
    LoRa.print(outgoing);                 // add payload
    LoRa.endPacket();                     // finish packet and send it
    msgCount++;                           // increment message ID
}

void LoRa_TX::WriteHeader()
{
    LoRa.write(DESTINATION);              // add destination address
    LoRa.write(LOCALADDRESS);             // add sender address
    LoRa.write(msgCount);                 // add message ID
    Data t;
    t.f = millis();
    LoRa.write(t.i, 4);                   //add time stamp
}

bool LoRa_TX::Sleep()
{
    LoRa.sleep();
}