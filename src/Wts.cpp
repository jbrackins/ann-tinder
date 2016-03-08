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
 * @return  0 file read correctly
 *          1 file couldn' be open
 *****************************************************************************/
bool readWeights(string fileName, double weights[], int arraySize)
{
    string strInput;
    ifstream file;
    file.open ("wts/" + fileName);

    //Check if file is open
    if (!file)
    {
        cout << "Couldn't open file " << fileName << " for weights" << endl;
        return 1;
    }

    //Read from desginated weights file
    for (int fileCounter = 0; fileCounter < arraySize; fileCounter++)
    {
        file >> strInput;
        weights[fileCounter] = strtod(strInput.c_str(), NULL);
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
 * @return  0 file read correctly
 *          1 file couldn' be open
 *****************************************************************************/

bool setWeights(string fileName, double weights[], int arraySize)
{
    ofstream file;
    file.open("wts/" + fileName);

    //Check if file opens
    if (!file)
    {
        cout << "File unsuccessfully open, nothing was written in " <<
             fileName << endl;
        return 1;
    }

    //Write to designated weight file.
    for (int fileCounter = 0; fileCounter < arraySize; fileCounter++)
    {
        file << weights[fileCounter] << " ";
    }

    file.close();
    return 0;
}
