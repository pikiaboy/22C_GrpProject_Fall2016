#include <iostream>
#include <fstream>
#include "Bike.h"
#include "BinarySearchTree.h"
#include "BinaryNode.h"
#include "BinaryTree.h"
#include "HashHead.h"

using namespace std;

void display(Bike* &obj)
{
	cout << obj->getSerialNumber() << endl;
}

bool isGreaterSerial(Bike* obj1, Bike* obj2)
{
	return obj1->getSerialString() > obj2->getSerialString();
}

bool isGreaterMake(Bike* obj1, Bike* obj2)
{
	return (obj1->getMake() > obj2->getMake());
}

bool isGreaterEqualMakeSerial(Bike* obj1, Bike* obj2)
{
	if (obj1->getSerialString() == obj2->getSerialString())
		return false;
	return (obj1->getMake() >= obj2->getMake());
}

bool isGreaterEqualMake(Bike* obj1, Bike* obj2)
{
	if (obj1->getMake() == obj2->getMake())
		return false;
	return(obj1->getMake() > obj2->getMake());
}


void readFile(BinarySearchTree<Bike*>*, BinarySearchTree<Bike*>*, HashList<Bike*> *bikeHash, string);
void outputFile(string, BinarySearchTree<Bike*>*, string, Stack<Bike*>*, Stack<Bike*>*);
void remove(BinarySearchTree<Bike*>*, BinarySearchTree<Bike*>*,  HashList<Bike*> *bikeHash, Stack<Bike*>*, Stack<Bike*>*);
void removeSecondaryKey(BinarySearchTree<Bike*>* bikeMakeSt, BinarySearchTree<Bike*>* bikeSerialSt, Stack<Bike*> *, Stack<Bike*> *);
void about();
void undo(Stack<Bike*> *, Stack<Bike*>*, BinarySearchTree<Bike*> *, BinarySearchTree<Bike*>*);
void undoClear(Stack<Bike*>*, Stack<Bike*>*);
void menu(string, BinarySearchTree<Bike*>*, BinarySearchTree<Bike*>*, HashList<Bike*>*, Stack<Bike*>*, Stack<Bike*>*);
void options();

int main()
{
	BinarySearchTree<Bike*> * bikeST = new BinarySearchTree<Bike*>;
	BinarySearchTree<Bike*> * bikeMakeSt = new BinarySearchTree<Bike*>;
	Stack<Bike*> *undoStackSerial = new Stack<Bike*>;
	Stack<Bike*> *undoStackMake = new Stack<Bike*>;
	HashList<Bike*> *bikeHash = new HashList<Bike*>;
	ifstream inFile;
	const char inputFileName[] = "InputData.txt";
	const char outputFileName[] = "OutputData.txt";

	readFile(bikeST, bikeMakeSt, bikeHash, inputFileName);

/*
	bikeHash->hashPrint();
	int x = 279; */
	
	//This must be done in order to check if passed the serach
	Bike bikes;
	Bike * _bikes = &bikes;
	bikeHash->hashSearch(279,_bikes);

	cout << _bikes->getSerialString() << endl;

	menu(outputFileName, bikeST, bikeMakeSt, bikeHash, undoStackSerial, undoStackMake);



	system("pause");
	return 0;
}

void options()
{
	cout << "~^&~!Please enter in a choice~^&~!" << endl;
	cout << "P - Print BST as indented list to screen" << endl;
	cout << "O - Save BST and Hash to output.txt" << endl;
	cout << "D - Delete a node from BST and Hash" << endl;
	cout << "S - Serach the BST or Hash" << endl;
	cout << "A - About the Devs" << endl;
	cout << "U - Undo Delete since last save" << endl;
	cout << "H - Help" << endl;
	cout << "Q - Quit" << endl;
}

void menu(string outputFileName, BinarySearchTree<Bike*> *bikeBST, BinarySearchTree<Bike*> *bikeMakeST, HashList<Bike*> *bikeHash, Stack<Bike*> *undoStackSerial, Stack<Bike*> *undoStackMake)
{
	string outFile = "output.txt";
	char choice = ' ';

	//display options
	options();
	cout << ">> ";
	
	while (choice != 'Q' || choice != 'q')
	{
		cin >> choice; 
		switch (choice)
		{
		case 'H':
		case 'h':
			options();
			break;

		case 'P':
		case 'p':
			cout << "Primary Key: " << endl;
			bikeBST->printInorderIndented();
			cout << endl;
			cout << "Secondary Key: " << endl;
			bikeMakeST->printInorderIndented();
			break;

		case 'A' :
		case 'a':
			about();
			break;

		case 'O':
		case 'o':
			outputFile(outputFileName, bikeBST, outFile, undoStackSerial, undoStackMake);
			break;
		case 'u':
		case 'U':
			undo(undoStackSerial, undoStackMake, bikeBST, bikeMakeST);
			break;
		case 'D':
		case 'd':
			//this should also delete from the hash too correct?
			remove(bikeBST, bikeMakeST, bikeHash, undoStackSerial, undoStackMake);
			break;
		case 'E':
		case 'e':
			removeSecondaryKey(bikeMakeST, bikeBST, undoStackSerial, undoStackMake);
			break;
		case 'Q':
		case 'q':
			exit(111);
			break;

		}
	}

}

void about()
{
	cout << "Avi, Jasdeep, Christian, Thomas" << endl;
	cout << "22C Delia Gârbacea" << endl;
	cout << "Winter 2016" << endl;
}

void undo(Stack<Bike*> * undoStackSerial, Stack<Bike*> * undoStackMake, BinarySearchTree<Bike*> *serialBST, BinarySearchTree<Bike*> * makeBST)
{
	while(!undoStackSerial->isEmpty())
	{
		Bike* bike = new Bike;
		undoStackSerial->pop(bike);
		serialBST->insert(bike, isGreaterSerial);
		makeBST->insert(bike, isGreaterMake);
	}

	while(!undoStackMake->isEmpty())
	{
		Bike * bikeMake = new Bike;
		undoStackMake->pop(bikeMake);
	}

}

void undoClear(Stack<Bike*>* undoStackSerial, Stack<Bike*>* undoStackMake)
{
	while(!undoStackSerial->isEmpty())
	{
		Bike * bike = new Bike;
		undoStackSerial->pop(bike);
		undoStackMake->pop(bike);
		delete bike;
	}
}

void outputFile(string outputFileName, BinarySearchTree<Bike*>* bikenarySearchTree, string fileName, Stack<Bike*> *undoStackSerial, Stack<Bike*> *undoStackMake) {
	
	cout << "Saving Updated List to File..." << endl;
	bikenarySearchTree->printToFile(outputFileName);
	undoClear(undoStackSerial, undoStackMake);
	cout << "Saved" << endl;
}


//Remove should remove from the Hash too correct?
// get the bike
// detele from hash and bst and bst
void remove(BinarySearchTree<Bike*>* bikenarySearchTree, BinarySearchTree<Bike*>* bikeMakeTree,HashList<Bike*> *bikeHash, Stack<Bike*>* undoStackSerial, Stack<Bike*>* undoStackMake)
{
	Stack<Bike*> *deleteStack = new Stack<Bike*>;

	string target;
	cout << "What would you like to remove?" << endl;
	cin >> target;

	//bikeHash->hashSearch(x.getSerialNumber());

	//Remove by Serial
	Bike *removeBikeSerial = new Bike();
	removeBikeSerial->setSerialNumber(target);
	if (bikenarySearchTree->remove(removeBikeSerial, isGreaterSerial, deleteStack, undoStackSerial))
		cout << "Deleted" << endl;
	else
		cout << "Error in deleting" << endl;


	while (!deleteStack->isEmpty())
	{
		Bike *removeBikeMake = new Bike();
		deleteStack->pop(removeBikeMake);
		bikeMakeTree->remove(removeBikeMake, isGreaterEqualMakeSerial, deleteStack, undoStackMake);
		deleteStack->pop(removeBikeMake);
	}
}

void removeSecondaryKey(BinarySearchTree<Bike*>* bikeMakeSt, BinarySearchTree<Bike*>* bikeSerialSt, Stack<Bike*> * undoStackMake, Stack<Bike*> * undoStackSerial)
{
	Stack<Bike*> *deleteStack = new Stack<Bike*>;
	bool success = true;

	string target;
	cout << "What would you like to remove?" << endl;
	cin >> target;

	while(success)
	{
		Bike *removeBike = new Bike();
		removeBike->setMake(target);
		cout << "Item deleted." << endl;
		success = bikeMakeSt->remove(removeBike, isGreaterEqualMake, deleteStack, undoStackMake);
	}

	while (!deleteStack->isEmpty())
	{
		Bike *removeBikeMake = new Bike();
		deleteStack->pop(removeBikeMake);
		bikeSerialSt->remove(removeBikeMake, isGreaterSerial, deleteStack, undoStackSerial);
		deleteStack->pop(removeBikeMake);
	}


}

void readFile(BinarySearchTree<Bike*>* bikenarySearchTree, BinarySearchTree<Bike*> * bikeMakeSt, HashList<Bike*> *bikeHash, string inputFileName)
{
	string serialNumber, make, frameMaterial, frameSize, saddle;

	fstream inFile;
	inFile.open(inputFileName);

	if (!inFile)
	{
		cout << "error opening input file" << endl;
		exit(111);
	};

	while (inFile.good())
	{
		inFile >> serialNumber >> make >> frameMaterial >> frameSize;
		getline(inFile, saddle);

		Bike* bicicleta = new Bike(serialNumber, make, frameMaterial, frameSize, saddle);

		bikenarySearchTree->insert(bicicleta, isGreaterSerial);
		bikeMakeSt->insert(bicicleta, isGreaterMake);

		bikeHash->hashInsert(bicicleta->getSerialNumber(), bicicleta);
	};

	cout << "Compelted File input!" << endl;
}
