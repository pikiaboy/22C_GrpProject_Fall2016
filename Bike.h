//Specification File for the Bike Class
#ifndef  BIKE_H
#define BIKE_H
#include <string>

using namespace std;

class Bike
{
private:
	string serialNumber;
	string make;
	string frameMaterial;
	int frameSize;
	string saddle;

public:
	//accessor
	const string getSerialNumber() { return serialNumber; };
	const string getMake() { return make; };
	const string getFrameMaterial() { return frameMaterial; };
	const int getFrameSize() { return frameSize; };
	const string getSaddle() { return saddle; };

	//mutator
	void setSerialNumber(string s) { serialNumber = s; };
	void setMake(string m) { make = m; };
	void setFrameMaterial(string f) { frameMaterial = f; };
	void setFrameSize(int f) { frameSize = f; };
	void setSaddle(string s) { saddle = s; };

	//constructor
	Bike()
	{
		serialNumber = "";
		make = "";
		frameMaterial = "";
		frameSize = 0;
		saddle = "";
	};
	Bike(string s, string m, string fM, int fS, string sa)
	{
		serialNumber = s;
		make = m;
		frameMaterial = fM;
		frameSize = fS;
		saddle = sa;
	};

};
#endif
//! BIKE_H