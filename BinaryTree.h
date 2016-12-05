// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by:

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
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
	void clear() { destroyTree(rootPtr); rootPtr = 0; count = 0; }
	void _printIndented(void visit(ItemType &), BinaryNode<ItemType>* node, int level);
	virtual bool insert(const ItemType & newData) = 0;
	virtual bool remove(const ItemType & data) = 0;
	void printInorderIndented();
};

template<class ItemType>
void BinaryTree<ItemType>::printInorderIndented()
{
	BinaryNode<ItemType> *node = rootPtr;
	int level = 0;
	_indentedInorder(node, level);
}

template<class ItemType>
void BinaryTree<ItemType>::_indentedInorder(BinaryNode<ItemType>* nodePtr, int level) const
{
	if (nodePtr != 0)
	{
		level++;
		_indentedInorder(nodePtr->getRightPtr(), level);
		Bike bike = nodePtr->getItem();
		cout << setw(10 * (level - 1)) << level << ". SerialNumber: " << bike.getSerialNumber() << " Make: " << bike.getMake() << endl;
		_indentedInorder(nodePtr->getLeftPtr(), level);
	}
}

#endif
