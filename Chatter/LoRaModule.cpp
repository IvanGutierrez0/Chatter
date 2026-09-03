#include "LoRa.h"
#include "LoRaModule.h"
#include <cstring>

//volatile byte LoRaModule::messagesPending = 0;

LoRaModule::LoRaModule(SPIClass &spi) : _spi(spi){
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

byte LoRaModule::MessagePending(){
	return messagesPending;
}

byte LoRaModule::ReceiveMessage(unsigned char* buffer){
  byte j = 0;

  if(messagesPending){
    messagesPending--;

    for(j = 0; j < packetSize[messagesPending]; j++){
      buffer[j] = _buffer[messagesPending][j];
    }

    buffer[j] = '\0';

    packetSize[messagesPending] = 0;
  }

  return j;
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
  if(messagesPending < BUFFER_ROWS && size > 0){
    byte j;

    packetSize[messagesPending] = size;
    
    for(j = 0; j < size && LoRa.available() && j < BUFFER_COLS - 1; j++){
      _buffer[messagesPending][j] = (unsigned char)LoRa.read();
    }

    _buffer[messagesPending][j] = '\0';

    messagesPending++;
  }
}