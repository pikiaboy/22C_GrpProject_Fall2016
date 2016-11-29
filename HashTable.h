#ifndef HASHTABLE_H
#define HASHTABE_H

#include <string>

using namespace std;

template <class ItemType>
class HashTable<ItemType>
{
	

public:
	HashTable() {};
	void Insert(int key, const ItemType & newEntry);
	void Delete(int key);
	void Search(int key);
};
#endif
