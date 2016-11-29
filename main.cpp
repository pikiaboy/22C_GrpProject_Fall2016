#include <iostream>
#include <fstream>
#include "Bike.h"
#include "BinarySearchTree.h"

using namespace std;

void readFile(BinarySearchTree<Bike>*, string);
void outputFile(BinarySearchTree<Bike>*, string);
void remove(BinarySearchTree<Bike>*);

int main()
{
	BinarySearchTree<Bike> * bikeST = new BinarySearchTree<Bike>;
	ifstream inFile;
	const char inputFileName[] = "InputData.txt";
	const char outputFileName[] = "OutputData.txt";

	readFile(bikeST, inputFileName);


	bikeST->printInorderIndented();

	system("pause");
	return 0;
}

void outputFile(BinarySearchTree<Bike>* bikenarySearchTree, string fileName) {
	cout << "Saving Updated List to File..." << endl;
	 
	cout << "Saved" << endl;
}

void remove(BinarySearchTree<Bike>* bikenarySearchTree)
{
	string target;
	cout << "What would you like to remove?" << endl;
	getline(cin, target, '\n');
	bikenarySearchTree->remove(target);

}

void readFile(BinarySearchTree<Bike>* bikenarySearchTree, string inputFileName)
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
		getline(inFile, saddle, '\n');


		Bike bicicleta(serialNumber, make, frameMaterial, frameSize, saddle);

		bikenarySearchTree->insert(bicicleta);
	};

	cout << "Compelted File input!" << endl;
}
