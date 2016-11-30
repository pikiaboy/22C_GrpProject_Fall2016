//
//  HashHead.h
//  hash
//
//  Created by Jasdeep Mundra on 11/28/16.
//  Copyright © 2016 Jasdeep Mundra. All rights reserved.
//

#ifndef HashHead_h
#define HashHead_h
#include <iostream>

// table size
const int tableSize = 23;

using namespace std;

// class to hold all variables
class Hash
{
private:
    int serial;
    string make;
    string material;
    int frameSize;
    string seat;
    
public:
    Hash();
    
    // get functions
    int getSerial(){return serial;}
    string getMake(){return make;}
    string getMaterial(){return material;}
    int getFrameSize(){return frameSize;}
    string getSeat(){return seat;}
    
    // set functions
    void setSerial(int x){x = serial;}
    void setMake(string x){x = make;}
    void setMaterial(string x){x = material;}
    void setFrameSize(int x){x = frameSize;}
    void setSeat(string x){x = seat;}
    
    ~Hash();
    
};


class HashList
{
private:
    struct ListNode
    {
        // make variable for hash class with variables
        Hash data;
        ListNode *next;
        ListNode (int key, Hash holder)
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
        
        // not necessary
        /*
        head = new ListNode;
        head->next = NULL;
        
        head->data.setSerial(0);
        head->data.setFrameSize(0);
  
        head->data.getMake() = "";
        head->data.getSeat() = "";
        head->data.getMaterial() = "";
         */
        
        
    };
    
    // insert function
    void hashInsert(int key, Hash holder)
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
        if (holder == NULL || holder->data.getSerial() != key)
        {
            cout << "Nothing to delete." << endl;
        }
        
        // loop until end of linked list or if key matches up
        while (holder->next != NULL || holder->data.getSerial() != key)
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
            if (holder->data.getSerial() == key)
            {
                cout << holder->data.getSerial() << endl;
                cout << holder->data.getMaterial() << endl;
                cout << holder->data.getSeat() << endl;
                cout << holder->data.getMake() << endl;
                cout << holder->data.getFrameSize() << endl;
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
        
        /*
        ListNode *nodePtr = head;
        ListNode *nextNode;
        while (nodePtr != NULL)
        {
            nextNode = nodePtr->next;
            delete nodePtr;
            nodePtr = nextNode;
        }
        */
    };
    
};




#endif /* HashHead_h */
