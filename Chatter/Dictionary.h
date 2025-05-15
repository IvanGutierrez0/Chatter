#ifndef __DICTIONARY__H__
#define __DICTIONARY__H__

#define MAX_WORD_SIZE 256

struct DictionaryEntry{
  short code;
  char* word;
  uint8_t size;
};

#endif