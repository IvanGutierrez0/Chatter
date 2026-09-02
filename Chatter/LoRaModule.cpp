#include "LoRa.h"
#include "LoRaModule.h"
#include <cstring>

volatile byte LoRaModule::packetSize = 0;

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

  LoRa.onReceive(LoRaModule::onReceive);

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
  LoRa.endPacket();

  RXMode();

  return true;
}

bool LoRaModule::MessagePending(){
	return packetSize;
}

byte LoRaModule::ReceiveMessage(unsigned char* buffer){
  byte i;

  if(packetSize){
    for(i = 0; i < packetSize && LoRa.available(); i++){
      buffer[i] = (char)LoRa.read();
    }

    buffer[i] = '\0';
  }

  RXMode();
  packetSize = 0;

  return i;
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

void LoRaModule::onReceive(int size){
  packetSize = size;
}