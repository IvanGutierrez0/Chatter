#ifndef __KEYPAD_MANAGER_H__
#define __KEYPAD_MANAGER_H__

#include <Keypad.h>

#define ROWS 4
#define COLS 4


class KeypadManager{
private:
  byte rowPins[ROWS] = {3, 2, 1, 0};
  byte colPins[COLS] = {7, 6, 5, 4};

  const char characters[ROWS][COLS] = {
    {'0','1','2','3'},
    {'4','5','6','7'},
    {'8','9','A','B'},
    {'C','D','E','F'}
  };

  Keypad *keypad;

  char latestKey;

public:
  KeyBoardManager();

  char GetKey();
};

#endif