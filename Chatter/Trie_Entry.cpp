#include "Trie_Entry.h"

/*------------------------------------Public methods---------------------------------------*/
Trie_array::Trie_array(int size){
	allocate(size);
}

Trie_array::~Trie_array(){
	deallocate();
}

void Trie_array::insert(const TrieEntry &elem){
	if(_size == _capacity){
		reallocate(_size << 1);
	}
	
	int i = 0;
	
	while(i < _size && _array[i] < elem) i++;
	
	for(int j = _size - 1; j >= i; j--){
		_array[j+1] = _array[j];
	}
	
	_array[i] = elem;
	_size++;
}

void Trie_array::erase(int pos){
	while(pos < _size){
		_array[pos] = _array[pos+1];
	}
	
	_size--;
}

TrieEntry* Trie_array::operator[](char tag) const{
	byte mid;
	byte left = 0, right = _size;
	
	while (left <= right) {
    mid = left + (right - left) / 2;

    if (_array[mid].tag == tag) {
      return &_array[mid];
    }
    if (_array[mid].tag < tag) {
      left = mid + 1;
    }
    else {
      right = mid - 1;
    }
  }

  return NULL;
}

/*---------------------------Private methods------------------------------*/
void Trie_array::allocate(int size){
	_array = (TrieEntry*) malloc(sizeof(TrieEntry)*size);
}

void Trie_array::reallocate(int size){
	//Warning: if there is not enough memory left it will return null causing a memory leak
	// as the original block is not freed
	_array = (TrieEntry*) realloc(_array, size * sizeof(TrieEntry));
}

void Trie_array::deallocate(){
	free(_array);
}