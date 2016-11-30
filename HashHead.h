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
#include "Bike.h"

// table size
const int tableSize = 23;

using namespace std;
class HashList
{
private:
    struct ListNode
    {
        // make variable for hash class with variables
        Bike *data;
        ListNode *next;
        ListNode (int key, Bike *holder)
        {
            this->data = holder;
            this->next = NULL;
        }
        
    };
    ListNode *head;
    // hash table pointer
    ListNode** hashTable;
    
    
public:
    // constructor
    HashList()
    {
        // initialize hashashTable to null
        // create hashashTable
        hashTable = new ListNode*[tableSize];
        for (int i =0; i < tableSize; i++)
        {
            hashTable[i] = NULL;
        }
        
    };
    
    // insert function
    void hashInsert(int key, Bike *holder)
    {
        int hash = hashFunc(key);
        ListNode *prev = NULL;
        ListNode *entry = hashTable[hash];
        while (entry != NULL)
        {
            prev = entry;
            entry = entry->next;
        }
        if (entry == NULL)
        {
            entry = new ListNode(key, holder);
            if (prev == NULL)
            {
                hashTable[hash] = entry;
            }
            else
                prev->next = entry;
        }
        else
            entry->data = holder;
        
    };
    
    // delete function
    void hashDelete(int key)
    {
        int hashVal = hashFunc(key);
        // holder points to spot in hashtable array
        ListNode *holder = hashTable[hashVal];
        ListNode *prev = NULL;

        // if empty or key is not equal to serial number then show messages
        if (holder == NULL || holder->data->getSerialNumber() != key)
        {
            cout << "Nothing to delete." << endl;
        }
        
        // loop until end of linked list or if key matches up
        while (holder->next != NULL || holder->data->getSerialNumber() != key)
        {
            prev = holder;
            holder = holder->next;
        }
        // if there is a node before, then make the next node points to the node after holder. skips holder. then deletes holder
        if (prev != NULL)
        {
            prev->next = holder->next;
        }
        delete holder;
        
        
        
    };
    
    void hashSearch (int key)
    {
        
        int hashVal;
        hashVal = hashFunc(key);
        // holder points to element spot in hashtable
        ListNode *holder = hashTable[hashVal];
        
        // keeps going through linked list until eaches the end
        while (holder != NULL)
        {
            // if the node serial number matches with the key then print all the info out
            if (holder->data->getSerialNumber() == key)
            {
                cout << "Serial number is: " << holder->data->getSerialNumber() << endl;
                cout << "Frame Material is: " << holder->data->getFrameMaterial() << endl;
                cout << "Saddle is: " << holder->data->getSaddle() << endl;
                cout << "Make is: " << holder->data->getMake() << endl;
                cout << "Frame size is: " << holder->data->getFrameSize() << endl;
            }
            // point to next node
            holder = holder->next;
        }
        
    };
    
    // computer hash function index
    int hashFunc(int key)
    {
        const int hashSize = 23;
        const int primeA = 29;
        const int primeB = 3;
        int address;
        address = (primeA * key + primeB) % hashSize;
        return address;
        
    }
    
    ~HashList()
    {
        // goes to each index in hashtable
        for (int i=0; i < tableSize; ++i)
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




#endif /* HashHead_h */
