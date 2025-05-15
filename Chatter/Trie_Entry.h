#ifndef __TRIE_ENTRY__H__
#define __TRIE_ENTRY__H__

#include <stdlib.h>

typedef struct TrieEntry;
typedef uint8_t byte;

class Trie_array{
private:
	TrieEntry* _array;
	byte _size;
	byte _capacity;
	
	void allocate(int size);
	void reallocate(int size);
	void deallocate();
	
public:
	Trie_array(int size = 0);
	
	~Trie_array();
	
	void insert(const TrieEntry &elem);
	
	void erase(int pos);
	
	TrieEntry* operator[](char tag) const;

	int size() const{
		return _size;
	}
};

struct TrieEntry{
	char tag;
	TrieEntry* most_probable_son;
	Trie_array sons;

	bool operator< (const TrieEntry &other){
		return tag < other.tag;
	}
};

#endif