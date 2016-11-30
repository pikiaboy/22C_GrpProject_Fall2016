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

int main()
{
	BinarySearchTree<Bike> * bikeST = new BinarySearchTree<Bike>;
	HashList *bikeHash = new HashList();
	ifstream inFile;
	const char inputFileName[] = "InputData.txt";
	const char outputFileName[] = "OutputData.txt";

	readFile(bikeST, bikeHash, inputFileName);


	bikeST->printInorderIndented();

	remove(bikeST);

	bikeST->printInorderIndented();

	bikeHash->hashSearch(471);

	system("pause");
	return 0;
}

void outputFile(BinarySearchTree<Bike>* bikenarySearchTree, string fileName) {
	cout << "Saving Updated List to File..." << endl;
	 
	cout << "Saved" << endl;
}

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
