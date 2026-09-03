#include <SPI.h>
#include <Wire.h>
#include <ESP32Time.h>
#include <LoRaModule.h>
#include "OLED_Display.h"
#include <string.h>

//Pinout for LoRa SPI interface
#define VSCK  18
#define VMISO 19
#define VMOSI 23
#define VCS   5


OLED_Display screen;

SPIClass vspi(VSPI);
LoRaModule lora(vspi);

unsigned char buffer[32];

void setup(){
  //Initialize serial comunication
  Serial.begin(9600);
  while (!Serial);

  //Initialize teh SPI Interface for the LoRa module
  vspi.begin(VSCK, VMISO, VMOSI, VCS);
  
  //Initialize the LoRa module
  if (!lora.begin()) {
    Serial.println("LoRa initialization failed!");
    while (1);
  }
  Serial.println("LoRa initialized successfully!");

  screen.updateDisplayStatus("12:23", 2, 3);
  screen.showDisplay();
}

void loop() {
  if(lora.MessagePending()){
    byte size = lora.ReceiveMessage(buffer);
    Serial.println((char*)buffer);
    screen.writeMessage(buffer, size);
    screen.showDisplay();
  }
}
