#ifndef __OLED_DISPLAY_H__
#define __OLED_DISPLAY_H__

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define MAX_ROWS 5
#define MAX_COLS 21
#define MAX_SCROLL_LINES 32
#define MAX_MESSAGE_SIZE 200

//Spi interface pins
#define HSPI_SCK 14
#define HSPI_SDA 13
#define HSPI_DC 27
#define HSPI_RES 26
#define HSPI_CS 15

const uint8_t SCREEN_WIDTH = 128; // OLED display width, in pixels
const uint8_t SCREEN_HEIGHT = 64; // OLED display height, in pixels

class OLED_Display{
private:
  //Spi interface to use
  SPIClass *hspi;

  //Adafriut class to operate the SSD1306 display
  Adafruit_SSD1306 *display;

  //Variables for managing the messages on the screen
  char screenBuffer[MAX_SCROLL_LINES][MAX_COLS];
  uint8_t currentWriteLine = 0;
  uint8_t currentReadLine = 0;

  //Buffer to store the status bar
  char statusBuffer[MAX_COLS];

  //Buffer to store the message that is being written
  char messageBuffer[MAX_MESSAGE_SIZE];
  uint8_t messageSize = 0;

public:
  /*
    @brief The class constructor
  */
  OLED_Display();

  /*
    @brief Updates the status bar of the screen
    @param time a string containing the current time
    @param signal a number between 0 to 4 indicating the signal integrity
    @param battery a number between 0 to 3 indicating the battery level
  */
  void updateDisplayStatus(const String& time, uint8_t signal, uint8_t battery);

  /*
    @brief Updates the time in the status bar
    @param time a string containing the current time
  */
  void updateTime(const String& time);

  /*
    @brief Updates the signal integrity in the status bar
    @param signal a number between 0 to 4 indicating the signal integrity
  */
  void updateSignal(uint8_t signal);

  /*
    @brief Updates the battery level in the status bar
    @param battery a number between 0 to 3 indicating the battery level
  */
  void updateBattery(uint8_t battery);
  
  /*
    @brief rites one character in the message buffer
    @param c character to be written
    @return true if it didn't exceed the max message size and false otherwise
  */
  bool userWrite(char c);

  /*
    @brief clears the message buffer
  */
  void userClear();

  /*
    @brief writes a message sent or received by the user
    @param message message to be written
    @param size size of the message
    @param isUser true if the message was sent by the user and false otherwise
  */
  void writeMessage(const char* message, uint8_t size, bool isUser = false);

  /*
    @param scroll the display up one line
  */
  void scrollUp();

  /*
    @param scroll the display down one line
  */
  void scrollDown();

  /*
    @param clear the display
  */
  void clear();

  /*
    @param show all the changes made to the buffers on the display
  */
  void showDisplay();
};

#endif