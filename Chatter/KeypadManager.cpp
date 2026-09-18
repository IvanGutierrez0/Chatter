#include "KeypadManager.h"

KeypadManager::KeypadManager() :keypad( makeKeymap(characters), rowPins, colPins, ROWS, COLS){
}

char KeypadManager::GetKey(){
  return keypad.getKey();
}