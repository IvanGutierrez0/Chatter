#include "OLED_Display.h"

OLED_Display::OLED_Display(){
  hspi = new SPIClass(HSPI);
  display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, hspi, HSPI_DC, HSPI_RES, HSPI_CS);
  
  hspi->begin();
  
  if(!display->begin(SSD1306_SWITCHCAPVCC)) {
    //Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display->display();
  delay(2000);
  display->clearDisplay();

  display->setTextSize(1);
  display->setTextColor(SSD1306_WHITE);
  display->setCursor(0, 0);
  display->cp437(true);

  for(uint8_t i = 0; i < 21; i++) statusBuffer[i] = ' '; 
}

void OLED_Display::updateDisplayStatus(const String& time, uint8_t signal, uint8_t battery){
  updateTime(time);

  updateSignal(signal);

  updateBattery(battery);

  display->writeFastHLine(0, 9, 128, SSD1306_WHITE);

  display->display();
}

void OLED_Display::updateTime(const String& time){
  display->setCursor(0, 0);
  
  for(uint8_t i = 0; i < 5; i++){
    statusBuffer[i] = time[i];
  }

  display->write(statusBuffer);
  display->display();
}

void OLED_Display::updateSignal(uint8_t signal){
  display->setCursor(0, 0);
  
  switch(signal){
    case 0:
      statusBuffer[16] = ' ';
      statusBuffer[17] = ' ';
      statusBuffer[18] = ' ';
    break;
    
    case 1:
      statusBuffer[16] = 248;
      statusBuffer[17] = ' ';
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

  display->write(statusBuffer);
  display->display();
}

void OLED_Display::updateBattery(uint8_t battery){
  display->setCursor(0, 0);
  
  switch(battery){
    case 0:
      statusBuffer[19] = (char)0;
      statusBuffer[20] = 1;
    break;
    
    case 1:
      statusBuffer[19] = 2;
      statusBuffer[20] = 3;
    break;
    
    case 2:
      statusBuffer[19] = 4;
      statusBuffer[20] = 5;
    break;
    
    case 3:
      statusBuffer[19] = 6;
      statusBuffer[20] = 7;
    break;
  }

  display->write(statusBuffer);
  display->display();
}

void OLED_Display::writeMessage(const char *message, uint8_t size){

}

void OLED_Display::scrollUp(){

}

void OLED_Display::scrollDown(){

}