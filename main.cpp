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

bool isEqualMake(Bike* obj1, Bike* obj2)
{
	return (obj1->getMake() == obj2->getMake());
}


void readFile(BinarySearchTree<Bike*>*, BinarySearchTree<Bike*>*, HashList<Bike*> *bikeHash, string);
void outputFile(string, BinarySearchTree<Bike*>*, Stack<Bike*>*, Stack<Bike*>*);
void remove(BinarySearchTree<Bike*>*, BinarySearchTree<Bike*>*,  HashList<Bike*> *bikeHash, Stack<Bike*>*, Stack<Bike*>*);
void removeSecondaryKey(BinarySearchTree<Bike*>* bikeMakeSt, BinarySearchTree<Bike*>* bikeSerialSt, HashList<Bike*> *bikeHash, Stack<Bike*> *, Stack<Bike*> *);
void about();
void undo(Stack<Bike*> *, Stack<Bike*>*, BinarySearchTree<Bike*> *, BinarySearchTree<Bike*>*, HashList<Bike*> *);
void undoClear(Stack<Bike*>*, Stack<Bike*>*);
void menu(string, BinarySearchTree<Bike*>*, BinarySearchTree<Bike*>*, HashList<Bike*>*, Stack<Bike*>*, Stack<Bike*>*);
void search(BinarySearchTree<Bike*>*);
void options();

void hashSearch(HashList<Bike*>*);

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



	menu(outputFileName, bikeST, bikeMakeSt, bikeHash, undoStackSerial, undoStackMake);



	system("pause");
	return 0;
}

void hashSearch(HashList<Bike*>*bikeHash)
{
	string target;
	int serialNumber = 0;

	Bike bikes;
	Bike * _bikes = &bikes;

	cout << "Please enter in the serial key to search: ";
	cin >> target;

	//converting the target into ASCII values
	for (int i = 0; i < target.length(); i++)
	{
		serialNumber += target[i];
	}

	if (bikeHash->hashSearch(serialNumber, _bikes))
	{
		cout << "Bike found!" << endl;
		cout << "Serial Num: " << _bikes->getSerialString() << endl;
		cout << "Make: " << _bikes->getMake() << endl;
		cout << "Frame Material: " << _bikes->getFrameMaterial() << endl;
		cout << "Frame Size: " << _bikes->getFrameSize() << endl;
		cout << "Saddle Type: " << _bikes->getSaddle() << endl;
		cout << "************************************" << endl;
	}
	else
		cout << "Bike not found!" << endl;
	
	
}

void options()
{
	cout << "~^&~!Please enter in a choice~^&~!" << endl;
	cout << "P - Print BST as indented list to screen" << endl;
	cout << "R - Print Hash Table" << endl;
	cout << "D - Delete a node from BST and Hash" << endl;
	cout << "E - Delete a from BST and Hash based on Secondary Key" << endl;
	cout << "T - Hash Serach" << endl;
	cout << "S - Hash Statistics" << endl;
	cout << "U - Undo Delete since last save" << endl;
	cout << "O - Save BST and Hash to output.txt" << endl;
	cout << "C - Serach the BST or Hash" << endl;
	cout << "A - About the Devs" << endl;
	cout << "H - Help" << endl;
	cout << "Q - Quit" << endl;
}

void menu(string outputFileName, BinarySearchTree<Bike*> *bikeBST, BinarySearchTree<Bike*> *bikeMakeST, HashList<Bike*> *bikeHash, Stack<Bike*> *undoStackSerial, Stack<Bike*> *undoStackMake)
{
	char choice = ' ';

	//display options
	options();
	cout << ">> ";
	
	while (choice != 'Q' || choice != 'q')
	{
		cin >> choice; 
		switch (choice)
		{
		case'T':
		case 't':
			hashSearch(bikeHash);
			break;
		case 'H':
		case 'h':
			options();
			break;
		case 'R':
		case 'r':
			cout << "Hash Table: " << endl;
			bikeHash->hashPrint();
			break;
		case 'P':
		case 'p':
			cout << "Primary Key: " << endl;
			bikeBST->printInorderIndented();
			cout << endl;
			cout << "Secondary Key: " << endl;
			bikeMakeST->printInorderIndented();
			break;
		case 'c':
		case 'C':
			search(bikeMakeST);
			break;
		case 'A' :
		case 'a':
			about();
			break;
		case 'S':
		case 's':
			bikeHash->hashStats();
			break;
		case 'O':
		case 'o':
			outputFile(outputFileName, bikeBST, undoStackSerial, undoStackMake);
			break;
		case 'u':
		case 'U':
			undo(undoStackSerial, undoStackMake, bikeBST, bikeMakeST, bikeHash);
			break;
		case 'D':
		case 'd':
			remove(bikeBST, bikeMakeST, bikeHash, undoStackSerial, undoStackMake);
			break;
		case 'E':
		case 'e':
			removeSecondaryKey(bikeMakeST, bikeBST, bikeHash, undoStackSerial, undoStackMake);
			break;
		case 'Q':
		case 'q':
			exit(111);
			break;

		}
	}

}

void search(BinarySearchTree<Bike*>* bikeMakeST)
{
	Queue<Bike*> * bikeQueue = new Queue<Bike*>;
	string target;
	cout << "What bike make would you like to search?" << endl;
	cin >> target;

	Bike *searchBikeMake = new Bike();
	searchBikeMake->setMake(target);
	bikeMakeST->findNode(searchBikeMake, isGreaterMake, )



}

void about()
{
	cout << "Avi, Jasdeep, Christian, Thomas" << endl;
	cout << "22C Delia Gârbacea" << endl;
	cout << "Winter 2016" << endl;
}

void undo(Stack<Bike*> * undoStackSerial, Stack<Bike*> * undoStackMake, BinarySearchTree<Bike*> *serialBST, BinarySearchTree<Bike*> * makeBST, HashList<Bike*> *bikeHash)
{
	while(!undoStackSerial->isEmpty())
	{
		Bike* bike = new Bike;
		undoStackSerial->pop(bike);
		serialBST->insert(bike, isGreaterSerial);
		makeBST->insert(bike, isGreaterMake);
		bikeHash->hashInsert(bike->getSerialNumber(), bike);
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

void outputFile(string outputFileName, BinarySearchTree<Bike*>* bikenarySearchTree, Stack<Bike*> *undoStackSerial, Stack<Bike*> *undoStackMake) {
	
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
		bikeHash->hashDelete(removeBikeMake->getSerialNumber());
		deleteStack->pop(removeBikeMake);
	}
}

void removeSecondaryKey(BinarySearchTree<Bike*>* bikeMakeSt, BinarySearchTree<Bike*>* bikeSerialSt, HashList<Bike*> *bikeHash, Stack<Bike*> * undoStackMake, Stack<Bike*> * undoStackSerial)
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
		bikeHash->hashDelete(removeBikeMake->getSerialNumber());
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
