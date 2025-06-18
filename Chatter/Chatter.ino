#include <SPI.h>
#include <Wire.h>
#include <ESP32Time.h>
#include <LoRaModule.h>
#include "OLED_Display.h"
#include <string.h>

OLED_Display screen;

ESP32Time rtc(3600);  // offset in seconds GMT+1

String womp;

void setup() {
  rtc.setTime(0, 14, 12, 24, 5, 2025);
}

void loop() {
  womp = rtc.getTime();
  womp.remove(5);

  screen.updateTime(womp);
  screen.showDisplay();
  delay(200);
  delay(200);
}
