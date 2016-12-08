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

bool isGreaterEqualMake(Bike* obj1, Bike* obj2)
{
	if (obj1->getSerialString() == obj2->getSerialString())
		return false;
	else
		return (obj1->getMake() > obj2->getMake());
}
<<<<<<< HEAD
void readFile(BinarySearchTree<Bike*>*, BinarySearchTree<Bike*>*, HashList<Bike*> *bikeHash, string);
void outputFile(BinarySearchTree<Bike*>*, string);
void remove(BinarySearchTree<Bike*>*, BinarySearchTree<Bike*>*, HashList<Bike*> *bikeHash);
void removeSecondaryKey(BinarySearchTree<Bike*>*);
void about();

void menu(BinarySearchTree<Bike*>*, BinarySearchTree<Bike*>*, HashList<Bike*>*);
void options();
=======

>>>>>>> 942e65cdf5c19359d6e264088bc47a84c39b35be

void readFile(BinarySearchTree<Bike*>*, BinarySearchTree<Bike*>*, HashList<Bike*> *bikeHash, string);
void outputFile(BinarySearchTree<Bike*>*, string, Stack<Bike*>*, Stack<Bike*>*);
void remove(BinarySearchTree<Bike*>*, BinarySearchTree<Bike*>*,  HashList<Bike*> *bikeHash, Stack<Bike*>*, Stack<Bike*>*);
void removeSecondaryKey(BinarySearchTree<Bike*>*, BinarySearchTree<Bike*>*);
void about();
void undo(Stack<Bike*> *, Stack<Bike*>*, BinarySearchTree<Bike*> *, BinarySearchTree<Bike*>*);
void menu(BinarySearchTree<Bike*>*, BinarySearchTree<Bike*>*, HashList<Bike*>*, Stack<Bike*>*, Stack<Bike*>*);
void options();

int main()
{
	BinarySearchTree<Bike*> * bikeST = new BinarySearchTree<Bike*>;
	BinarySearchTree<Bike*> * bikeMakeSt = new BinarySearchTree<Bike*>;
<<<<<<< HEAD
	HashList<Bike*> *bikeHash = new HashList<Bike*>;
	Queue<Bike*> *deleteQueue = new Queue<Bike*>;
=======
	Stack<Bike*> *undoStackSerial = new Stack<Bike*>;
	Stack<Bike*> *undoStackMake = new Stack<Bike*>;
	HashList<Bike*> *bikeHash = new HashList<Bike*>;
>>>>>>> 942e65cdf5c19359d6e264088bc47a84c39b35be
	ifstream inFile;
	const char inputFileName[] = "InputData.txt";

	readFile(bikeST, bikeMakeSt, bikeHash, inputFileName);


	int x = 279; 
	
	//This must be done in order to check if passed the serach
<<<<<<< HEAD
	Bike *bike = new Bike();

	//bikeHash->hashSearch(279,bike);

	//cout << bike->getSerialString() << endl;
=======
	Bike bikes;
	Bike * _bikes = &bikes;
	bikeHash->hashSearch(279,_bikes);

	cout << _bikes->getSerialString() << endl;
>>>>>>> 942e65cdf5c19359d6e264088bc47a84c39b35be

	menu(bikeST, bikeMakeSt, bikeHash, undoStackSerial, undoStackMake);



	system("pause");
	return 0;
}

//This displays the options the user has
void options()
{
	cout << "~^&~!Please enter in a choice~^&~!" << endl;
	cout << "P - Print BST as indented list to screen" << endl;
	cout << "O - Save BST and Hash to output.txt" << endl;
	cout << "D - Delete a node from BST and Hash" << endl;
	cout << "E - Delete a node from Bike Make Search Tree" << endl;
	cout << "S - Serach the BST or Hash" << endl;
	cout << "A - About the Devs" << endl;
	cout << "U - Undo Delete since last save" << endl;
	cout << "H - Help" << endl;
	cout << "Q - Quit" << endl;
}

<<<<<<< HEAD
//This takes in a char and determines what the user wants to do.
void menu(BinarySearchTree<Bike*> *bikeBST, BinarySearchTree<Bike*> *bikeMakeST, HashList<Bike*> *bikeHash )
=======
void menu(BinarySearchTree<Bike*> *bikeBST, BinarySearchTree<Bike*> *bikeMakeST, HashList<Bike*> *bikeHash, Stack<Bike*> *undoStackSerial, Stack<Bike*> *undoStackMake)
>>>>>>> 942e65cdf5c19359d6e264088bc47a84c39b35be
{
	string outFile = "OutputData.txt";
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
			outputFile(bikeBST, outFile, undoStackSerial, undoStackMake);
			break;
		case 'u':
		case 'U':
			undo(undoStackSerial, undoStackMake, bikeBST, bikeMakeST);
			break;
		case 'D':
		case 'd':
			//this should also delete from the hash too correct?
<<<<<<< HEAD
			remove(bikeBST, bikeMakeST, bikeHash);
=======
			remove(bikeBST, bikeMakeST, bikeHash, undoStackSerial, undoStackMake);
>>>>>>> 942e65cdf5c19359d6e264088bc47a84c39b35be
			break;
		case 'E':
		case 'e':
			//removeSecondaryKey(bikeBST, bikeMakeST);
			break;
		case 'Q':
		case 'q':
			exit(111);
			break;

		}
	}

}

//About the devs
void about()
{
	cout << "Avi, Jasdeep, Christian, Thomas" << endl;
	cout << "22C Delia Gârbacea" << endl;
	cout << "Winter 2016" << endl;
}

<<<<<<< HEAD
//Outputting the two BST to file and the Hash to file.
void outputFile(BinarySearchTree<Bike*>* bikenarySearchTree, string fileName) {
=======
void undo(Stack<Bike*> * undoStackSerial, Stack<Bike*> * undoStackMake, BinarySearchTree<Bike*> * makeBST, BinarySearchTree<Bike*> *serialBST)
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


void outputFile(BinarySearchTree<Bike*>* bikenarySearchTree, string fileName, Stack<Bike*> *undoStackSerial, Stack<Bike*> *undoStackMake) {
>>>>>>> 942e65cdf5c19359d6e264088bc47a84c39b35be
	cout << "Saving Updated List to File..." << endl;
	 
	ofstream outFile; 

	outFile.open(fileName);

	if (!outFile)
	{
		cout << "Error with output file" << endl;
	}

	outFile << "Hello!" << endl;

	//bikenarySearchTree->clearUndo(undoStack);
	cout << "Saved" << endl;
}


<<<<<<< HEAD

// Remove a node from the data structures.
void remove(BinarySearchTree<Bike*>* bikenarySearchTree, BinarySearchTree<Bike*>* bikeMakeST, HashList<Bike*> *bikeHash)
=======
//Remove should remove from the Hash too correct?
// get the bike
// detele from hash and bst and bst
void remove(BinarySearchTree<Bike*>* bikenarySearchTree, BinarySearchTree<Bike*>* bikeMakeTree,HashList<Bike*> *bikeHash, Stack<Bike*>* undoStackSerial, Stack<Bike*>* undoStackMake)
>>>>>>> 942e65cdf5c19359d6e264088bc47a84c39b35be
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

<<<<<<< HEAD
//remove from the bikeMakeST
void removeSecondaryKey(BinarySearchTree<Bike*>* bikeMakeSt)
{
	Bike *removeBike = new Bike();
=======
>>>>>>> 942e65cdf5c19359d6e264088bc47a84c39b35be

	while(!deleteStack->isEmpty())
	{
		Bike *removeBikeMake = new Bike();
		removeBikeMake->setSerialNumber(target);
		deleteStack->pop(removeBikeMake);
		bikeMakeTree->remove(removeBikeMake, isGreaterEqualMake, deleteStack, undoStackMake);
		deleteStack->pop(removeBikeMake);
	}

}

<<<<<<< HEAD
//Read the original input file to build the BSTs and the hash
=======
//void removeSecondaryKey(BinarySearchTree<Bike*>* bikeMakeSt, BinarySearchTree<Bike*>* bikeSerialSt)
//{
//	Bike *removeBike = new Bike();
//	Stack<Bike*> *deleteStack = new Stack<Bike*>;
//
//	string target;
//	cout << "What would you like to remove?" << endl;
//	cin >> target;
//
//	removeBike->setMake(target);
//
//	while(bikeMakeSt->remove(removeBike, isGreaterMake, deleteStack, undoStack))
//	{
//		cout << "Item deleted." << endl;
//	}
//
//	while (!deleteStack->isEmpty())
//	{
//		deleteStack->pop(removeBike);
//		bikeSerialSt->remove(removeBike, isGreaterSerial, deleteStack, undoStack);
//		deleteStack->pop(removeBike);
//	}
//
//
//}

>>>>>>> 942e65cdf5c19359d6e264088bc47a84c39b35be
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
