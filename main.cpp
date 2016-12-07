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

bool isEqualSerial(Bike* obj1, Bike* obj2)
{
	return obj1->getSerialNumber() == obj2->getSerialNumber();
}

bool isGreaterMake(Bike* obj1, Bike* obj2)
{
	return (obj1->getMake() > obj2->getMake());
}

bool isEqualMake(Bike* obj1, Bike* obj2)
{
	return obj1->getMake() == obj2->getMake();
}
void readFile(BinarySearchTree<Bike*>*, BinarySearchTree<Bike*>*, HashList<Bike> *bikeHash, string);
void outputFile(BinarySearchTree<Bike*>*, string);
void remove(BinarySearchTree<Bike*>*, HashList<Bike> *bikeHash);
void removeSecondaryKey(BinarySearchTree<Bike*>*);
void about();

void menu(BinarySearchTree<Bike*>*, BinarySearchTree<Bike*>*, HashList<Bike>*);
void options();


int main()
{
	BinarySearchTree<Bike*> * bikeST = new BinarySearchTree<Bike*>;
	BinarySearchTree<Bike*> * bikeMakeSt = new BinarySearchTree<Bike*>;
	HashList<Bike> *bikeHash = new HashList<Bike>;
	Queue<Bike*> *deleteQueue = new Queue<Bike*>;
	ifstream inFile;
	const char inputFileName[] = "InputData.txt";

	readFile(bikeST, bikeMakeSt, bikeHash, inputFileName);


	int x = 279; 
	
	//This must be done in order to check if passed the serach
	Bike bikes;
	//Bike * _bikes = &bikes;
	//bikeHash->hashSearch(279,_bikes);

	//cout << _bikes->getSerialString() << endl;

	menu(bikeST, bikeMakeSt, bikeHash);



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

void menu(BinarySearchTree<Bike*> *bikeBST, BinarySearchTree<Bike*> *bikeMakeST, HashList<Bike> *bikeHash )
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
			outputFile(bikeBST, outFile);
			break;
		case 'u':
		case 'U':
			bikeBST->undo(isGreaterSerial);
			break;
		case 'D':
		case 'd':
			//this should also delete from the hash too correct?
			remove(bikeBST, bikeHash);
			break;
		case 'E':
		case 'e':
			removeSecondaryKey(bikeMakeST);
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

void outputFile(BinarySearchTree<Bike*>* bikenarySearchTree, string fileName) {
	cout << "Saving Updated List to File..." << endl;
	 
	ofstream outFile; 

	outFile.open(fileName);

	if (!outFile)
	{
		cout << "Error with output file" << endl;
	}

	outFile << "Hello!" << endl;

	bikenarySearchTree->clearUndo();
	cout << "Saved" << endl;
}


//Remove should remove from the Hash too correct?
// get the bike
// detele from hash and bst and bst
void remove(BinarySearchTree<Bike*>* bikenarySearchTree, HashList<Bike> *bikeHash)
{
	Bike *removeBike = new Bike();

	string target;
	cout << "What would you like to remove?" << endl;
	cin >> target;
	
	removeBike->setSerialNumber(target);
	


	//bikeHash->hashSearch(x.getSerialNumber());

	//Remove by Serial
	if (bikenarySearchTree->remove(&removeBike, isGreaterSerial))
		cout << "Deleted" << endl;
	else
		cout << "Error in deleting" << endl;
	delete removeBike;
}

void removeSecondaryKey(BinarySearchTree<Bike*>* bikeMakeSt)
{
	Bike *removeBike = new Bike();

	string target;
	cout << "What would you like to remove?" << endl;
	cin >> target;

	removeBike->setMake(target);

	while(bikeMakeSt->remove(&removeBike, isGreaterMake))
	{
		cout << "Item deleted." << endl;
	}
}

void readFile(BinarySearchTree<Bike*>* bikenarySearchTree, BinarySearchTree<Bike*> * bikeMakeSt, HashList<Bike> *bikeHash, string inputFileName)
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

		bikenarySearchTree->insert(&bicicleta, isGreaterSerial);
		bikeMakeSt->insert(&bicicleta, isGreaterMake);

		//bikeHash->hashInsert(bicicleta->getSerialNumber(), bicicleta);
	};

	cout << "Compelted File input!" << endl;
}
