#include <SPI.h>
#include <Wire.h>
#include <ESP32Time.h>
#include <LoRaModule.h>
#include "OLED_Display.h"
#include <string.h>

OLED_Display screen;

SPIClass vspi(VSPI);
LoRaModule lora(vspi);

unsigned char buffer[256];

void setup(){
  //Initialize serial comunication
  Serial.begin(9600);
  while (!Serial);

  //Initialize teh SPI Interface for the LoRa module
  vspi.begin(18, 19, 23, 5);
  
  //Initialize the LoRa module
  if (!lora.begin()) {
    Serial.println("LoRa initialization failed!");
    while (1);
  }
  Serial.println("LoRa initialized successfully!");
}

void loop() {
  if(lora.MessagePending()){
    lora.ReceiveMessage(buffer);
    Serial.println((char*)buffer);
  }
}
