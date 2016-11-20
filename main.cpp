#include <iostream>
#include <fstream>
#include "Bike.h"

using namespace std; 

void readFile(Bike array[],string);

int main()
{
	Bike bikeList[100];
	ifstream inFile; 
	const char inputFileName[] = "InputData.txt";
	readFile(bikeList, inputFileName);


	return 0; 
}



void readFile(Bike bikeList[] , string inputFileName)
{
	fstream inFile;

	string data = "";
	int data2 = 0; 
	int i = 0; //postion in list
	inFile.open(inputFileName);

	if (!inFile) 
	{
		cout << "error opening input file" << endl; 
		exit(111); 
	}

	getline(inFile, data); //geting rid of first line

	while (!inFile.eof())
	{
		
		inFile >> data; 
		bikeList[i].setSerialNumber(data);
		
		cout << data << " ";
	
		inFile >> data; 
		bikeList[i].setMake(data);

		cout << data << " ";

		inFile >> data; 
		bikeList[i].setFrameMaterial(data);
		
		cout << data << " ";

		inFile >> data2; 
		bikeList[i].setFrameSize(data2);
		
		cout << data2 << " "; 

		inFile >> data; 
		bikeList[i].setSaddle(data); 
		
		cout << data << endl;
		
		i++; 
	}
	
	cout << "Compelted File input!" << endl; 
} 