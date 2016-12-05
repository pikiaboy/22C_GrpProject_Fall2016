#ifndef HASHTABLE_H
#define HASHTABE_H

#include <string>

using namespace std;

const int TABLE_SIZE = 23;

template <class ItemType>
class HashTable
{
private: 
	struct node {
		ItemType *data;
		node* next;
	};

	node table[];

public:
	HashTable() {
		table = new node[TABLE_SIZE];

		//Table element is 0 if nothing is in it
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			table[i] = 0;
		}

	};
	
	
	
	void insert(int key, const ItemType * newEntry);
	void remove(int key);
	void search(int key);
	int hashFunction(int serial);
};

template<class ItemType>
void HashTable<ItemType>::insert(int key, const ItemType *newEntry)
{
	int address = hashFunction(key);

	//current postion in linked list
	node *curr = table[address];

	//if table postion has been empty from start
	if (table[address] == NULL)
	{
		table[address] = newEntry;
	}


	//if table postion is not empty
	if (table[address] != 0)
	{
		//going to end of linked list
		while (curr->next != NULL)
		{
			curr = curr->next;
		}

		//Once found end of list, adding another node
		node *newNode;
		newNode->data = newEntry;
		newNode->next = NULL;

		curr->next = newNode;
	}

}

template<class ItemType>
int HashTable<ItemType>::hashFunction(int serial)
{
	const int primeA = 29;
	const int primeB = 3;
	int address;
	address = (primeA * serial + primeB) % TABLE_SIZE;
	return address;
}

#endif