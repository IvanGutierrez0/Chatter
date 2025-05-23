#ifndef __OLED_DISPLAY_H__
#define __OLED_DISPLAY_H__

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define MAX_ROWS 7
#define MAX_COLS 21
#define MAX_SCROLL_LINES 32

#define HSPI_SCK 14
#define HSPI_SDA 13
#define HSPI_DC 27
#define HSPI_RES 26
#define HSPI_CS 15

const uint8_t SCREEN_WIDTH = 128; // OLED display width, in pixels
const uint8_t SCREEN_HEIGHT = 64; // OLED display height, in pixels

class OLED_Display{
private:
  SPIClass *hspi;
  Adafruit_SSD1306 *display;

  char screenBuffer[MAX_SCROLL_LINES][MAX_COLS];
  int currentWriteLine = 0;
  int currentReadLine = 0;

  /*
  Format {HH:MM           SS BB}
  - H: hour
  - M: minutes
  - S: signal
  - B: battery
  */
  char statusBuffer[MAX_COLS]; 

public:
  OLED_Display();

  void updateDisplayStatus(const String& time, uint8_t signal, uint8_t battery);

  void updateTime(const String& time);

  void updateSignal(uint8_t signal);

  void updateBattery(uint8_t battery);

  void writeMessage(const char* message, uint8_t size);

  void scrollUp();

  void scrollDown();

  void clear();

  void showDisplay();
};

#endif