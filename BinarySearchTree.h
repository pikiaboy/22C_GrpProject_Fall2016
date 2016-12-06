// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by:

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"
#include "Stack.h"
#include "Queue.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
	Stack<ItemType>* undoStack;

	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
	BinaryNode<ItemType>* undoSave(BinaryNode<ItemType>* nodePtr);
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
		ItemType & successor);
	
public:
	BinarySearchTree()
	{
		undoStack = new Stack<ItemType>;
	}
	~BinarySearchTree()
	{
		delete undoStack;
	}
	void undo();
	bool insert(const ItemType & newEntry);
	bool remove(const ItemType & anEntry);

};

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr);
	count++;
	return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
	count--;
	return isSuccessful;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
	BinaryNode<ItemType>* newNodePtr)
{
	if (nodePtr == 0)
		return newNodePtr;
	else if (newNodePtr->getItem() > nodePtr->getItem())
	{
		nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
	}
	else
	{

		nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
	}
	return nodePtr;

}

template<class ItemType>
void BinarySearchTree<ItemType>::undo()
{
	ItemType oldNodeData;
	while(!undoStack->isEmpty())
	{
		undoStack->pop(oldNodeData);
		insert(oldNodeData);
	}
	return;

};

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::undoSave(BinaryNode<ItemType>* nodePtr)
{
	ItemType oldNodeData;
	cout << "item hopefully saved" << endl;
	oldNodeData = nodePtr->getItem();
	undoStack->push(oldNodeData);
	deleteNode(nodePtr);
	return 0;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
	const ItemType target,
	bool & success)

{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem()> target)
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem()> target)
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else
	{
		nodePtr = undoSave(nodePtr);
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
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
	ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
	const ItemType & target) const
{
	if (nodePtr == 0)
		return 0;
	//	cout << "Searching" << nodePtr->getItem() << endl;
	if (nodePtr->getItem() == target)
		return nodePtr;
	if (target > nodePtr->getItem())
		return findNode(nodePtr->getRightPtr(), target);
	return findNode(nodePtr->getLeftPtr(), target);
}
#endif