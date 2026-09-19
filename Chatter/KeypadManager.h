#ifndef __KEYPAD_MANAGER_H__
#define __KEYPAD_MANAGER_H__

#include <Keypad.h>

#define ROWS 4
#define COLS 4


class KeypadManager{
private:
  byte rowPins[ROWS] = {22, 16, 17, 0};
  byte colPins[COLS] = {34, 32, 33, 25};

  char characters[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };

  Keypad keypad;

  char lastKey;

public:
  KeypadManager();

  char GetKey();
};

#endif