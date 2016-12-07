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
	Stack<ItemType>* undoStack;

	BinaryNode<ItemType>* undoSave(BinaryNode<ItemType>* nodePtr);
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNodePtr, bool isGreater(ItemType data1, ItemType data2));
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, ItemType target, bool & success, bool isGreater(ItemType data1, ItemType data2), Stack<ItemType>* deleteStack);
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, ItemType * target, bool isGreater(ItemType data1, ItemType data2), bool isEqual(ItemType data1, ItemType data2)) const;
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
		ItemType * successor);

public:
	BinarySearchTree()
	{
		undoStack = new Stack<ItemType>;
	}
	~BinarySearchTree()
	{
		delete undoStack;
	}
	void undo(bool isGreater(ItemType data1, ItemType data2));
	bool insert(ItemType newEntry, bool isGreater(ItemType data1, ItemType data2));
	bool remove(ItemType target, bool isGreater(ItemType data1, ItemType data2), Stack<ItemType> * deleteStack);
	void clearUndo();

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
bool BinarySearchTree<ItemType>::remove(ItemType target, bool isGreater(ItemType data1, ItemType data2), Stack<ItemType> * deleteStack)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful, isGreater, deleteStack);
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
void BinarySearchTree<ItemType>::undo(bool isGreater(ItemType data1, ItemType data2))
{
	ItemType oldNodeData;
	while (!undoStack->isEmpty())
	{
		undoStack->pop(oldNodeData);
		insert(oldNodeData, isGreater);
	}
	return;

}

template <class ItemType>
void BinarySearchTree<ItemType>::clearUndo()
{
	ItemType oldNodeData;
	while(!undoStack->isEmpty())
	{
		undoStack->pop(oldNodeData);
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
	return deleteNode(nodePtr);
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType> * nodePtr, ItemType target, bool & success, bool isGreater(ItemType data1, ItemType data2), Stack<ItemType> *deleteStack)
{

	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (isGreater(nodePtr->getItem() , target))
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success, isGreater, deleteStack));
	else if (isGreater(target, nodePtr->getItem()))
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success, isGreater, deleteStack));
	else
	{
		deleteStack->push(nodePtr->getItem());
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
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* treePtr, ItemType * target, bool isGreater(ItemType data1, ItemType data2), bool isEqual(ItemType data1, ItemType data2)) const
{
	if (nodePtr == 0)
		return 0;
	//	cout << "Searching" << nodePtr->getItem() << endl;
	if (isEqual(nodePtr->getItem(), target))
		return nodePtr;
	if (isGreater(target, nodePtr->getItem()))
		return findNode(nodePtr->getRightPtr(), target);
	return findNode(nodePtr->getLeftPtr(), target);
}
#endif