// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by:

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Stack.h"
#include "Queue.h"
#include <iostream>
#include <iomanip>

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree
	void _indentedInorder(BinaryNode<ItemType>* nodePtr, int level) const;


public:
	BinaryTree() { rootPtr = 0; count = 0; }
	BinaryTree(const BinaryTree<ItemType> & tree) { }
	virtual ~BinaryTree() { }

	bool isEmpty() const { return count == 0; }
	int size() const { return count; }
	void clear() { destroyTree(rootPtr); rootPtr = 0; count = 0; };
	virtual bool insert(ItemType newEntry, bool isGreater(ItemType data1, ItemType data2)) = 0;
	virtual bool remove(ItemType anEntry, bool isGreater(ItemType data1, ItemType data2), Stack<ItemType> * deleteStack, Stack<ItemType> * undoStack) = 0;
	void printInorderIndented();
	void printToFile(string outputFile);
};

template<class ItemType>
void BinaryTree<ItemType>::printInorderIndented()
{
	BinaryNode<ItemType> *node = rootPtr;
	int level = 0;
	_indentedInorder(node, level);
	cout << "There are " << count << " nodes in the tree." << endl;
}

template<class ItemType>
void BinaryTree<ItemType>::_indentedInorder(BinaryNode<ItemType>* nodePtr, int level) const
{
	if (nodePtr != 0)
	{
		level++;
		_indentedInorder(nodePtr->getRightPtr(), level);
		Bike *bike = nodePtr->getItem();
		cout << setw(10 * (level - 1)) << level << ". SerialNumber: " << bike->getSerialString() << " Make: " << bike->getMake() << endl;
		_indentedInorder(nodePtr->getLeftPtr(), level);
	}
}

template<class ItemType>
void BinaryTree<ItemType>::printToFile(string outputTextFile)
{
	ofstream oFile;
	oFile.open(outputTextFile);
	oFile << left << setw(15) << "Serial" << setw(20) << "Make" << setw(20) << "Frame" << setw(10) << "Size" << setw(20) << "Saddle" << endl;

	Queue<BinaryNode<ItemType>*> *queue = new Queue<BinaryNode<ItemType>*>;

	if (rootPtr == 0)
		return;
	BinaryNode<ItemType> * node = rootPtr;
	queue->enqueue(node);
	while (!queue->isEmpty())
	{
		queue->dequeue(node);
		Bike * bike = new Bike();
		bike = node->getItem();
		oFile << left << setw(15) << bike->getSerialString() << setw(20) << bike->getMake() << setw(20) << bike->getFrameMaterial() << setw(10) << bike->getFrameSize() << setw(20) << bike->getSaddle() << endl;
		if (node->getLeftPtr() != 0)
			queue->enqueue(node->getLeftPtr());
		if (node->getRightPtr() != 0)
			queue->enqueue(node->getRightPtr());
	}

}

#endif
