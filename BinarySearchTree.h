// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by:

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"
#include "Stack.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:

	BinaryNode<ItemType>* undoSave(BinaryNode<ItemType>* nodePtr, Stack<ItemType> * undoStack);
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNodePtr, bool isGreater(ItemType data1, ItemType data2));
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, ItemType target, bool & success, bool isGreater(ItemType data1, ItemType data2), Stack<ItemType>* deleteStack, Stack<ItemType> * undoStack);
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
	BinaryNode<ItemType>* _findNode(BinaryNode<ItemType>* treePtr, ItemType * target, bool isGreater(ItemType data1, ItemType data2), bool isEqual(ItemType data1, ItemType data2)) const;
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
		ItemType * successor);
	bool inQueue(ItemType item, Queue<ItemType>*foundQueue, bool isEqual(ItemType data1, ItemType data2));

public:
	BinarySearchTree()
	{
	}
	~BinarySearchTree()
	{
	}
	//void undo(bool isGreater(ItemType data1, ItemType data2), Stack<ItemType> * undoStack);
	bool insert(ItemType newEntry, bool isGreater(ItemType data1, ItemType data2));
	bool remove(ItemType target, bool isGreater(ItemType data1, ItemType data2), Stack<ItemType> * deleteStack, Stack<ItemType> * undoStack);
	bool findNode(ItemType target, bool isGreater(ItemType data1, ItemType data2),  bool isEqual(ItemType data1, ItemType data2), Queue<ItemType> * foundQueue);
	//void clearUndo(Stack<ItemType> * undoStack);

};

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(ItemType newEntry, bool isGreater(ItemType data1, ItemType data2))
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr, isGreater);
	count++;
	return true;
}


template<class ItemType>
bool BinarySearchTree<ItemType>::remove(ItemType target, bool isGreater(ItemType data1, ItemType data2), Stack<ItemType> * deleteStack, Stack<ItemType> * undoStack)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful, isGreater, deleteStack, undoStack);
	if (isSuccessful)
		count--;
	return isSuccessful;
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNodePtr, bool isGreater(ItemType data1, ItemType data2))
{
	if (nodePtr == 0)
		return newNodePtr;
	else if (isGreater(nodePtr->getItem(), newNodePtr->getItem()))
	{
		nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr, isGreater));
	}
	else
	{
		nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr, isGreater));
	}
	return nodePtr;

}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::undoSave(BinaryNode<ItemType>* nodePtr, Stack<ItemType> * undoStack)
{
	Bike * bike = new Bike;
	bike = nodePtr->getItem();
	cout << "item hopefully saved" << endl;
	undoStack->push(bike);
	return deleteNode(nodePtr);
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType> * nodePtr, ItemType target, bool & success, bool isGreater(ItemType data1, ItemType data2), Stack<ItemType> *deleteStack, Stack<ItemType> * undoStack)
{

	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (isGreater(target, nodePtr->getItem()))
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success, isGreater, deleteStack, undoStack));
	else if (isGreater(nodePtr->getItem() , target))
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success, isGreater, deleteStack, undoStack));
	else
	{
		deleteStack->push(nodePtr->getItem());
		nodePtr = undoSave(nodePtr, undoStack);
		success = true;
	}
	return nodePtr;
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else
	{
		ItemType * newNodeValue = new ItemType;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(*newNodeValue);
		return nodePtr;
	}
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
	ItemType * successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		*successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_findNode(BinaryNode<ItemType>* treePtr, ItemType * target, bool isGreater(ItemType data1, ItemType data2), bool isEqual(ItemType data1, ItemType data2)) const
{
	if (nodePtr == 0)
		return 0;
	if (isEqual(nodePtr->getItem(), target))
		return nodePtr;
	if (isGreater(target, nodePtr->getItem()))
		return findNode(nodePtr->getRightPtr(), target);
	return findNode(nodePtr->getLeftPtr(), target);
}

template <class ItemType>
bool BinarySearchTree<ItemType>::findNode(ItemType target, bool isGreater(ItemType data1, ItemType data2), bool isEqual(ItemType data1, ItemType data2), Queue<ItemType>* foundQueue)
{
	bool isSuccessful = false;
	Bike * bike = new Bike;
	bike = _findNode(this->rootPtr, target, isGreater, isEqual, foundQueue);
	if(bike != 0)
	{	
		bike = bike->getItem();
		foundQueue->enqueue(bike);
	}
}

template <class ItemType>
bool BinarySearchTree<ItemType>::inQueue(ItemType item, Queue<ItemType>* foundQueue, bool isEqual(ItemType data1, ItemType data2))
{
	if (foundQueue->isEmpty())
		return false;
	Bike* bike = new Bike();
	for(int i = 0; i < foundQueue->getCount(); i++)
	{
		foundQueue->dequeue(bike);
		if (isEqual(item, bike))
			return true;
		foundQueue->enqueue(bike);
	}
	return false;
}


#endif