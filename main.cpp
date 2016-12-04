#include <iostream>
#include <fstream>
#include "Bike.h"
#include "BinarySearchTree.h"
#include "BinaryNode.h"
#include "BinaryTree.h"
#include "HashTable.h"
#include "HashHead.h"

using namespace std;

void readFile(BinarySearchTree<Bike>*, HashList *bikeHash, string);
void outputFile(BinarySearchTree<Bike>*, string);
void remove(BinarySearchTree<Bike>*);
void about();

void menu(BinarySearchTree<Bike>*, HashList*);

int main()
{
	BinarySearchTree<Bike> * bikeST = new BinarySearchTree<Bike>;
	HashList *bikeHash = new HashList();
	ifstream inFile;
	const char inputFileName[] = "InputData.txt";
	const char outputFileName[] = "OutputData.txt";

	readFile(bikeST, bikeHash, inputFileName);

	menu(bikeST, bikeHash);

	bikeST->printInorderIndented();
	
	bikeHash->hashSearch(471);
	bikeHash->hashDelete(471);
	bikeHash->hashSearch(471);

	system("pause");
	return 0;
}


void menu(BinarySearchTree<Bike> *bikeBST, HashList *bikeHash )
{
	string outFile = "output.txt";
	char choice = ' ';
	cout << "~^&~!Please enter in a choice~^&~!" << endl; 
	cout << "P - Print BST as indented list to screen" << endl;
	cout << "A - About the Devs" << endl;
	cout << "S - Save BST and Hash to output.txt" << endl;
	cout << "D - Delete a node from BST and Hash" << endl;
	cout << "Q - Quit" << endl;

	while (choice != 'Q' || choice != 'q')
	{
		cin >> choice; 
		switch (choice)
		{
		case 'P':
		case 'p':
			bikeBST->printInorderIndented();
			break;

		case 'A' :
		case 'a':
			//print about the devs. How do you want to structure this?
			break;

		case 'S':
		case 's':
			outputFile(bikeBST, outFile);
			break;

		case 'D':
		case 'd':
			//this should also delete from the hash too correct?
			remove(bikeBST);
			break;

		case 'Q':
		case 'q':
			exit(111);
			break;

		default: 
			cout << "Invalid input" << endl;
			break;
		}
	}

}

void about()
{
	// just cout the names and date of making the code? 
	// how do we want to structure this?
}

void outputFile(BinarySearchTree<Bike>* bikenarySearchTree, string fileName) {
	cout << "Saving Updated List to File..." << endl;
	 
	cout << "Saved" << endl;
}


//Remove should remove from the Hash too correct?
void remove(BinarySearchTree<Bike>* bikenarySearchTree) 
{
	Bike x;

	string target;
	cout << "What would you like to remove?" << endl;
	getline(cin, target, '\n');
	
	x.setSerialNumber(target);
	bikenarySearchTree->remove(x);
}

void readFile(BinarySearchTree<Bike>* bikenarySearchTree, HashList *bikeHash, string inputFileName)
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
