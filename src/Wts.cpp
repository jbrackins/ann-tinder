/*************************************************************************//**
 * @file Wts.cpp
 *
 * @brief SOURCE - Methods for reading in Wts File information
 *
 ******************************************************************************/

/******************************************************************************
 *
 * INCLUDE
 *
 ******************************************************************************/

#include "../inc/Wts.h"

/******************************************************************************
 *
 * NAMESPACES
 *
 ******************************************************************************/

using namespace std;

/**************************************************************************//**
 * @author Alex Nienhueser
 *
 * @par Description:
 * Read in and parse the wts file
 *
 *****************************************************************************/
bool readWeights(string fileName, double wieghts[], int arraySize)
{
	string strInput;
	ifstream file;
	file.open ("wts/"+fileName);
	
	if (!file)
	{
                cout << "Couldn't open file " << fileName << endl;
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

/**************************************************************************//**
 * @author Alex Nienhueser
 *
 * @par Description:
 * Write to the wts file
 *
 *****************************************************************************/

bool setWeights(string fileName, double wieghts[], int arraySize)
{
  ofstream file;
  file.open("wts/"+fileName);
  if (!file)
  {
    cout << "File unsuccessfully open, nothing was written in "<< 
      fileName << endl;
    return 1;
  }

  for(int fileCounter = 0; fileCounter < arraySize; fileCounter++)
    file<<wieghts[fileCounter]<< " ";

  file.close();
  return 0;
}
