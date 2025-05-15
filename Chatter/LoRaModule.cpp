#include <cstring>
#include "LoRaModule.h"

/*-------------------------------Public methods------------------------------------*/
LoRaModule::LoRaModule(SPIClass &spi){
  size = 0;
  messagePending = false;

  LoRa.setSPI(spi);
  
  while(!LoRa.begin(FREQUENCY));
  
  LoRa.setTxPower(TX_POWER);
  LoRa.onReceive(onReceive);
  LoRa.onTxDone(onTxDone);

  RXMode();
}

LoRaModule::~LoRaModule(){
  LoRa.end();
}

void LoRaModule::Optimize(){
  OptimizeRSSI();
  OptimizeSNR();
  OptimizeError();
}

bool LoRaModule::SendMessage(const char* buffer, byte size){
  unsigned char bufferCopy[MAX_PACKET];

  bufferCopy[0] = DEVICE_ID;
  memcpy(bufferCopy+1, buffer, size - 1);

  Encrypt(bufferCopy, size);

  TXMode();
  LoRa.beginPacket();
  LoRa.write(bufferCopy, size);

  return LoRa.endPacket(true);
}

bool LoRaModule::MessagePending(){
  return messagePending;
}

byte LoRaModule::ReceiveMessage(char* buffer){
  byte packetSize = LoRa.parsePacket();

  for(byte i = 1; i < packetSize - 1 && LoRa.available(); i++){
    buffer[i] = (char)LoRa.read();

    previousRSSI[size] = LoRa.packetRssi();
    previousSNR[size] = LoRa.packetSnr();
    previousError[size] = LoRa.packetFrequencyError();
    size++;
  }

  Decrypt(buffer, packetSize);

  messagePending = false;

  return packetSize;
}

void LoRaModule::Sleep(){
  LoRa.sleep();
}

void LoRaModule::Idle(){
  LoRa.idle();
}

void RXMode(){
  LoRa.enableInvertIQ();                
  LoRa.receive();                       
}

void TXMode(){
  LoRa.idle();
  LoRa.disableInvertIQ();
}

void onReceive(int packetSize){
  LoRaModule::messagePending = packetSize > 0;
}

void onTxDone() {
  RXMode();
}

/*-------------------------------Private methods------------------------------------*/
float LoRaModule::GetAverage(const int* v){
  float aux = 0;

  for(byte i = 0; i < HISTORY_SIZE; i++){
    aux += v[i];
  }

  return aux/(HISTORY_SIZE*1.0);
}

void LoRaModule::OptimizeRSSI(){}

void LoRaModule::OptimizeSNR(){}

void LoRaModule::OptimizeError(){}

void LoRaModule::Encrypt(unsigned char* buffer, byte size){
  for(byte i = 0; i < size; i++){
    buffer[i] ^= PASSWORD[i];
  }
}

void LoRaModule::Decrypt(char *buffer, byte size){
  Encrypt((unsigned char*)buffer, size);
}