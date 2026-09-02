#include "LoRaModule.h"
#include <cstring>

LoRaModule::LoRaModule(SPIClass &spi) : _spi(spi){
	packetSize = 0;
}

LoRaModule::~LoRaModule(){
  LoRa.end();
}

bool LoRaModule::begin() {
  LoRa.setSPI(_spi);
  LoRa.setPins(CS, RST, DIOO);

  if (!LoRa.begin(FREQUENCY)) {
    return false;
  }

  LoRa.setTxPower(TX_POWER);
	RXMode();
  
  return true;
}

bool LoRaModule::SendMessage(const unsigned char* buffer, byte size){
  unsigned char bufferCopy[MAX_PACKET];

  /*bufferCopy[0] = DEVICE_ID;
  memcpy(bufferCopy+1, buffer, size - 1);*/

  TXMode();
  LoRa.beginPacket();
  LoRa.write(buffer, size);

  return LoRa.endPacket();
}

bool LoRaModule::MessagePending(){
	packetSize = LoRa.parsePacket();

	return packetSize;
}

byte LoRaModule::ReceiveMessage(unsigned char* buffer){
  if(packetSize){
    byte i;
    for(i = 0; i < packetSize && LoRa.available(); i++){
      buffer[i] = (char)LoRa.read();
    }

    buffer[i] = '\0';
  }

  RXMode();

  return packetSize;
}

void LoRaModule::Sleep(){
  LoRa.sleep();
}

void LoRaModule::Idle(){
  LoRa.idle();
}

void LoRaModule::RXMode(){
  LoRa.disableInvertIQ();
  LoRa.receive();                       
}

void LoRaModule::TXMode(){
  LoRa.idle();
  LoRa.disableInvertIQ();
}