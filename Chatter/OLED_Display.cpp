#include "Adafruit_SSD1306.h"
#include "OLED_Display.h"

OLED_Display::OLED_Display(){
  hspi = new SPIClass(HSPI);
  display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, hspi, HSPI_DC, HSPI_RES, HSPI_CS);
  
  hspi->begin();
  
  if(!display->begin(SSD1306_SWITCHCAPVCC)) {
    for(;;); // Don't proceed, loop forever
  }

  display->setFont(&Picopixel_custom); //Fuente custom
  
  display->display();
  delay(2000);
  display->clearDisplay();
  display->display();

  display->setTextSize(1);
  display->setTextColor(SSD1306_WHITE);
  display->setCursor(0, 0);
  display->cp437(true);

  for(uint8_t j = 0; j < MAX_SCROLL_LINES; j++){
    for(uint8_t i = 0; i < MAX_COLS; i++) screenBuffer[j][i] = '\0'; 
  }

  for(uint8_t i = 0; i < MAX_MESSAGE_SIZE; i++) messageBuffer[i] = '\0'; 

  _time = "XX:XX";
  _signal = -1;
  _battery = -1;
}

void OLED_Display::updateDisplayStatus(const String& time, uint8_t signal, uint8_t battery){
  _time = time;
  _signal = signal;
  _battery = battery;
}

void OLED_Display::printDisplayStatus(){
  display->setCursor(0, 5);
  printTime(_time);

  display->setCursor(109, 5);
  printSignal(_signal);

  display->setCursor(117, 5);
  printBattery(_battery);

  display->writeFastHLine(0, 8, SCREEN_WIDTH, SSD1306_WHITE);
}

void OLED_Display::printTime(const String& time){
  for(uint8_t i = 0; i < 5; i++){
    display->write(time[i]);
  }
}

void OLED_Display::printSignal(uint8_t signal){
  switch(signal){
    case 0:
      display->write(ICON_NET_MIN);
    break;
    
    case 1:
      display->write(ICON_NET_MID);
    break;
    
    case 2:
      display->write(ICON_NET_MAX);
    break;

    default:
      display->write("X");
    break;
  }
}

void OLED_Display::printBattery(uint8_t battery){
  switch(battery){
    case 0:
      display->write(ICON_BAT_EMPT);
    break;
    
    case 1:
      display->write(ICON_BAT_MID_EMPT);
    break;
    
    case 2:
      display->write(ICON_BAT_MID_FULL);
    break;
    
    case 3:
      display->write(ICON_BAT_FULL);
    break;

    default:
      display->write("X");
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


void OLED_Display::writeMessage(const unsigned char* message, uint8_t size, bool isUser){
  for(int i = 0; i < size || i < MAX_COLS; i++){
    screenBuffer[currentWriteLine][i] = (char)message[i];
  }
  currentWriteLine++;
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
  display->display();
}

void OLED_Display::showDisplay(){
  display->clearDisplay();

  printDisplayStatus();

  

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