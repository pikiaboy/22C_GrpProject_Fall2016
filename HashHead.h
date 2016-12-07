//
//  HashHead.h
//  hash
//
//  Created by Jasdeep Mundra on 11/28/16.
//  Edited by Thomas Pham on 11/29/16.
//  Copyright © 2016 Jasdeep Mundra. All rights reserved.
//

#ifndef HashHead_h
#define HashHead_h
#include <iostream>
#include <iomanip>

// table size
const int tableSize = 53;

using namespace std;
template<class ItemType>
class HashList
{
private:
	struct ListNode
	{
		// make variable for hash class with variables
		ItemType data;
		ListNode *next;
		ListNode(ItemType holder)
		{
			this->data = holder;
			this->next = NULL;
		}

	};
	// hash table pointer
	ListNode** hashTable;


public:
	// constructor
	HashList()
	{
		// initialize hashashTable to null
		// create hashashTable
		hashTable = new ListNode*[tableSize];
		for (int i = 0; i < tableSize; i++)
		{
			hashTable[i] = NULL;
		}

	};

	//print hash
	void hashPrint();
	// insert function
	void hashInsert(int key, ItemType holder);
	// delete function
	void hashDelete(int key);
	bool hashSearch(int key, ItemType &bikes);

	// compute hash index
	int hashFunc(int key);

	~HashList()
	{
		// goes to each index in hashtable
		for (int i = 0; i < tableSize; ++i)
		{
			ListNode *holder = hashTable[i];
			// go through each node in array index and delete
			while (holder != NULL)
			{
				ListNode *prev = holder;
				holder = holder->next;
				delete prev;
			}
		}

		delete hashTable;

	};

};

template<class ItemType>
void HashList<ItemType>::hashPrint()
{
	ListNode* holder;
	cout << "Printed in Hash Sequence: " << endl;
	int count = 0;
	for (int i = 0; i < tableSize; i++)
	{
		holder = hashTable[i];
		cout << setw(5) << i << ": ";
		while (holder != NULL)
		{
			cout << "Bike: ";
			cout << setw(10) << holder->data->getSerialString() << " ";
			cout << setw(15) << holder->data->getMake() << " |";
			if(holder->next != 0)
			{
				cout << " --> "; 
			}
			holder = holder->next;
			count++;
		}
		cout << endl;

	}
	cout << "The total nodes is: " << count << endl;
}


template<class ItemType>
void HashList<ItemType>::hashDelete(int key)
{
	int hashVal = hashFunc(key);
	// holder points to spot in hashtable array
	ListNode *holder = hashTable[hashVal];
	ListNode *prev = NULL;

	// if index is empty then show message 
	if (holder == NULL) // || holder->data->getSerialNumber() != key)
	{
		cout << "Nothing to delete." << endl;
	}

	// loop until end of linked list or if key matches up
	while (holder->next != NULL && holder->data->getSerialNumber() != key)
	{
		prev = holder;
		holder = holder->next;
	}

	// if deleting holder and holder is head, make new listnode ptr which points to holder->next. 
	// delete holder. then make index in hashtable equal to entry ptr.
	// not sure if we should delete holder before setting new hashIndex first node or after. 
	if (prev == NULL)
	{
		ListNode *entry = holder->next;
		delete holder;
		hashTable[hashVal] = entry;
	}

	// if there is a node before, then make the next node points to the node after holder. skips holder. then deletes holder
	if (prev != NULL)
	{
		prev->next = holder->next;
		delete holder;
	}

};

//changed to return an item instead of cout'ing everything
template<class ItemType>
bool HashList<ItemType>::hashSearch(int key, ItemType &bikes)
{

	int address;
	address = hashFunc(key);
	// holder points to element spot in hashtable
	ListNode *holder = hashTable[address];
	bool found = false;
	// keeps going through linked list until eaches the end
	while (holder != NULL && found != true)
	{
		// if the node serial number matches with the key then print all the info out
		if (holder->data->getSerialNumber() == key) // this line is full of black magic
		{
			bikes = holder->data;
			return true;
		}
		// point to next node
		holder = holder->next;
	}

	return false;

}

template <class ItemType>
int HashList<ItemType>::hashFunc(int key)
{
	const int hashSize = 53;
	const int primeA = 29;
	const int primeB = 3;
	int address;
	address = (primeA * key + primeB) % hashSize;
	return address;

}

template <class ItemType>
void HashList<ItemType>::hashInsert(int key, ItemType holder)
{
	int address = hashFunc(key);
	ListNode *prev = NULL;
	//hashTable[address] = new ListNode(holder);
	ListNode *entry = hashTable[address];


	//If the array address is empty
	if (entry == NULL)
	{
		hashTable[address] = new ListNode(holder);
		return;
	}

	//if address is not null, traverse till end of list
	while (entry != NULL)
	{
		prev = entry;
		entry = entry->next;
	}
	// allocate new node and link the nodes
	entry = new ListNode(holder);
	prev->next = entry;

};

#endif /* HashHead_h */