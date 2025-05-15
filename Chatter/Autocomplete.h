#ifndef __AUTOCOMPLETE__H__
#define __AUTOCOMPLETE__H__

#include "Dictionary.h"
#include "Trie_Entry.h"

class Autocomplete{
private:  
  TrieEntry root;

public:
  Autocomplete(const DictionaryEntry* dictionary, int size){
    root.tag = '\0';
    createTrie(root, dictionary, size);
  }

  void createTrie(TrieEntry& root, const DictionaryEntry* dictionary, int size){
    for(int i = 0; i < size; i++){
      insertWord(dictionary[i]);
    }
  }

  void insertWord(const DictionaryEntry& entry){
    TrieEntry* aux, *prev = &root;
    
    for(int i = 0; i < entry.size; i++){
      aux = prev->sons[entry.word[i]];
      
      if(aux == NULL){ // creamos el nodo
        TrieEntry node;
        node.tag = entry.word[i];

        prev->sons.insert(node);

        if(prev->most_probable_son == NULL){
          prev->most_probable_son = &node;
        }
      }

      prev = aux;
    }

    if(aux != NULL){
      aux->most_probable_son = aux;
    }
  }

  const char* complete(const char* word, byte size){
    char buffer[MAX_WORD_SIZE];
    char *aux;
    byte size_aux = 0;
    
    memcpy(buffer, word, size);

    TrieEntry node = getWordNode(word, size);
    aux = mostProbaleWord(node, size_aux);
    
    memcpy(buffer+size, aux, size_aux);

    return buffer;
  }

  const TrieEntry& getWordNode(const char* word, byte size){
    TrieEntry* current = &root;

    for(int i = 0; i < size && current != NULL; i++){
      current = (*current).sons[word[i]];
    }

    return *current;
  }

  char* mostProbaleWord(TrieEntry& node, byte& size) const{
    char word[MAX_WORD_SIZE];

    TrieEntry* current = &node;

    while(node.most_probable_son != &node && size < MAX_WORD_SIZE){
      current = (*current).most_probable_son;
      word[size] = (*current).tag;
      size++;
    }

    return word;
  }
};

#endif