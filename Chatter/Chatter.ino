#include <SPI.h>
#include <Wire.h>
#include <ESP32Time.h>
#include <LoRaModule.h>
#include "OLED_Display.h"

//Screen parameters and pins


//LoRa module parameters and pins

//Screen parameters and pins

OLED_Display screen;

void setup() {

}

void loop() {
  screen.updateDisplayStatus("12:37", 3, 1);
  screen.showDisplay();
  delay(2000);
  screen.updateDisplayStatus("12:41", 4, 2);
  screen.showDisplay();
  delay(2000);
}
