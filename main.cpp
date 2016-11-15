#include <iostream>
#include <fstream>


using namespace std; 

void readFile(string);

int main()
{
	const char inputFileName[] = "InputData.txt";
	readFile(inputFileName);
	

	return 0; 
}



void readFile(string inputFileName)
{
	fstream inFile;

	string data = "";

	while (!inFile.eof())
	{

	}
		
}