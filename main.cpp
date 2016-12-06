#include <iostream>
#include <fstream>
#include "Bike.h"
#include "BinarySearchTree.h"
#include "BinaryNode.h"
#include "BinaryTree.h"
#include "HashHead.h"

using namespace std;

void readFile(BinarySearchTree<Bike>*, HashList<Bike> *bikeHash, string);
void outputFile(BinarySearchTree<Bike>*, string);
void remove(BinarySearchTree<Bike>*, HashList<Bike> *bikeHash);
void about();

void menu(BinarySearchTree<Bike>*, HashList<Bike>*);
void options();


int main()
{
	BinarySearchTree<Bike> * bikeST = new BinarySearchTree<Bike>;
	HashList<Bike> *bikeHash = new HashList<Bike>();
	ifstream inFile;
	const char inputFileName[] = "InputData.txt";
	const char outputFileName[] = "OutputData.txt";

	readFile(bikeST, bikeHash, inputFileName);


	int x = 279; 
	
	//This must be done in order to check if passed the serach
	Bike bikes;
	Bike * _bikes = &bikes;
	bikeHash->hashSearch(279,_bikes);

	cout << _bikes->getSerialString() << endl;

	menu(bikeST, bikeHash);



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

void menu(BinarySearchTree<Bike> *bikeBST, HashList<Bike> *bikeHash )
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
			bikeBST->printInorderIndented();
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
			bikeBST->undo();
			break;
		case 'D':
		case 'd':
			//this should also delete from the hash too correct?
			remove(bikeBST, bikeHash);
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

void outputFile(BinarySearchTree<Bike>* bikenarySearchTree, string fileName) {
	cout << "Saving Updated List to File..." << endl;
	 

	bikenarySearchTree->clearUndo();
	cout << "Saved" << endl;
}


//Remove should remove from the Hash too correct?
// get the bike
// detele from hash and bst and bst
void remove(BinarySearchTree<Bike>* bikenarySearchTree, HashList<Bike> *bikeHash)
{
	Bike x;

	string target;
	cout << "What would you like to remove?" << endl;
	cin >> target;
	
	x.setSerialNumber(target);
	


	//bikeHash->hashSearch(x.getSerialNumber());

	//BST deleteing half of tree every time.
	if (bikenarySearchTree->remove(x))
		cout << "Deleted" << endl;
	else
		cout << "Error in deleting" << endl;
}

void readFile(BinarySearchTree<Bike>* bikenarySearchTree, HashList<Bike> *bikeHash, string inputFileName)
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

		Bike *bikePointer = new Bike(); 
		bikePointer->setSerialNumber(serialNumber);
		bikePointer->setMake(make);
		bikePointer->setFrameMaterial(frameMaterial); 
		bikePointer->setFrameSize(frameSize);
		bikePointer->setSaddle(saddle);

		Bike bicicleta(serialNumber, make, frameMaterial, frameSize, saddle);

		bikenarySearchTree->insert(bicicleta);

		bikeHash->hashInsert(bikePointer->getSerialNumber(), bikePointer);
	};

	cout << "Compelted File input!" << endl;
}
