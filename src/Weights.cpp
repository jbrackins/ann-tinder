#include <iostream>
#include <list>
#include <string>
#include <fstream>

using namespace std;

bool setWeights(string fileName, double wieghts[], int arraySize);
bool readWeights(string fileName, double wieghts[], int arraySize);


bool readWeights(string fileName, double wieghts[], int arraySize)
{
	string strInput;
	ifstream file;
	file.open ("../wts/"+fileName);
	
	if (!file.is_open())
	{
		cout << "File unsuccessfully open, nothing was read from "<< fileName;
		return 1;
	}

	for(int fileCounter = 0; fileCounter < arraySize; fileCounter++)
	{
		file>>strInput;
		wieghts[fileCounter]=strtod(strInput.c_str(), NULL);
	}
	file.close();
	return 0;
}

bool setWeights(string fileName, double wieghts[], int arraySize)
{
	ofstream file;
	file.open("../wts/"+fileName);
	if (!file.is_open())
	{
		cout << "File unsuccessfully open, nothing was written in "<< fileName;
		return 1;
	}

	for(int fileCounter = 0; fileCounter < arraySize; fileCounter++)
		file<<wieghts[fileCounter]<< " ";

	file.close();
	return 0;
}