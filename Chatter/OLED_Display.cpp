#include "Adafruit_SSD1306.h"
#include "OLED_Display.h"

OLED_Display::OLED_Display(){
  hspi = new SPIClass(HSPI);
  display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, hspi, HSPI_DC, HSPI_RES, HSPI_CS);
  
  hspi->begin();
  
  if(!display->begin(SSD1306_SWITCHCAPVCC)) {
    for(;;); // Don't proceed, loop forever
  }
  
  display->display();
  delay(2000);
  display->clearDisplay();

  display->setTextSize(1);
  display->setTextColor(SSD1306_WHITE);
  display->setCursor(0, 0);
  display->cp437(true);

  for(uint8_t i = 0; i < MAX_COLS; i++) statusBuffer[i] = ' ';

  for(uint8_t j = 0; j < MAX_SCROLL_LINES; j++){
    for(uint8_t i = 0; i < MAX_COLS; i++) screenBuffer[j][i] = 'A' + j; 
  }

  for(uint8_t i = 0; i < MAX_MESSAGE_SIZE; i++) messageBuffer[i] = ' '; 
}

void OLED_Display::updateDisplayStatus(const String& time, uint8_t signal, uint8_t battery){
  updateTime(time);

  updateSignal(signal);

  updateBattery(battery);
}

void OLED_Display::updateTime(const String& time){
  for(uint8_t i = 0; i < 5; i++){
    statusBuffer[i] = time[i];
  }
}

void OLED_Display::updateSignal(uint8_t signal){
  switch(signal){
    case 0:
      statusBuffer[16] = ' ';
      statusBuffer[17] = ' ';
      statusBuffer[18] = ' ';
    break;
    
    case 1:
      statusBuffer[16] = 248;
      statusBuffer[17] = 249;
      statusBuffer[18] = ' ';
    break;
    
    case 2:
      statusBuffer[16] = 250;
      statusBuffer[17] = 251;
      statusBuffer[18] = ' ';
    break;
    
    case 3:
      statusBuffer[16] = 252;
      statusBuffer[17] = 253;
      statusBuffer[18] = ' ';
    break;

    case 4:
      statusBuffer[16] = 254;
      statusBuffer[17] = 255;
      statusBuffer[18] = ' ';
    break;
  }
}

void OLED_Display::updateBattery(uint8_t battery){
  switch(battery){
    case 0:
      statusBuffer[19] = 1;
      statusBuffer[20] = 2;
    break;
    
    case 1:
      statusBuffer[19] = 3;
      statusBuffer[20] = 4;
    break;
    
    case 2:
      statusBuffer[19] = 5;
      statusBuffer[20] = 6;
    break;
    
    case 3:
      statusBuffer[19] = 7;
      statusBuffer[20] = 8;
    break;
  }
}

bool OLED_Display::userWrite(char c){
  bool messageWritten = false;

  if(messageSize < MAX_MESSAGE_SIZE){
    messageBuffer[messageSize] = c;
    messageSize++;

    messageWritten = true;
  }

  return messageWritten;
}

void OLED_Display::userClear(){
  messageSize = 0;
}


void OLED_Display::writeMessage(const char* message, uint8_t size, bool isUser){
  
}

void OLED_Display::scrollUp(){
  if(currentReadLine > 0){
    currentReadLine--;
  }
}

void OLED_Display::scrollDown(){
  if(currentReadLine < (MAX_SCROLL_LINES - MAX_ROWS)){
    currentReadLine++;
  }
}

void OLED_Display::clear(){
  display->clearDisplay();
}

void OLED_Display::showDisplay(){
  clear();

  //Display status buffer
  display->setCursor(0,0);
  
  for(uint8_t i = 0; i < MAX_COLS; i++){
    display->write(statusBuffer[i]);
  }
  
  display->writeFastHLine(0, 8, SCREEN_WIDTH, SSD1306_WHITE);

  //Display message buffer
  display->setCursor(0,12);

  for(uint8_t i = currentReadLine; (i - currentReadLine) < MAX_ROWS; i++){
    for(uint8_t j = 0; j < MAX_COLS; j++){
      display->write(screenBuffer[i][j]);
    }
  }

  //Display the message buffer
  display->writeFastHLine(0, 55, SCREEN_WIDTH, SSD1306_WHITE);
  display->setCursor(0,57);

  int8_t i = messageSize - MAX_COLS;

  for(i = ((i < 0) ? 0 : i); i < messageSize; i++){
    display->write(messageBuffer[i]);
  }

  //Update the display
  display->display();
}