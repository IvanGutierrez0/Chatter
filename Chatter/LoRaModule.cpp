#include "LoRaModule.h"

/*-------------------------------Public methods------------------------------------*/
LoRaModule::LoRaModule(const SPIClass &spi);

void LoRaModule::Optimize(){
  OptimizeRSSI();
  OptimizeSNR();
  OptimizeError();
}

bool LoRaModule::SendMessage(const char buffer[255], byte size);
bool LoRaModule::MessagePending();
byte LoRaModule::ReceiveMessage(char buffer[255]);

/*-------------------------------Private methods------------------------------------*/
float LoRaModule::GetAverage(const int v[HISTORY_SIZE]){
  float aux = 0;

  for(byte i = 0; i < HISTORY_SIZE; i++){
    aux += v[i];
  }

  return aux/(HISTORY_SIZE*1.0);
}

void LoRaModule::OptimizeRSSI();

void LoRaModule::OptimizeSNR();

void LoRaModule::OptimizeError();

void LoRaModule::Encrypt(char buffer[255], byte size){
  for(byte i = 0; i < size; i++){
    buffer[i] ^= PASSWORD[i];
  }
}

void LoRaModule::Decrypt(char buffer[255], byte size){
  Encrypt(buffer, size);
}