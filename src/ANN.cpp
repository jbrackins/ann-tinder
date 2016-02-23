/*************************************************************************//**
 * @file ANN.cpp
 *
 * @brief SOURCE - ANN Tinder Main Source file. 
 *
 * @mainpage Program 1 - TINDER
 *
 * @section course_section CSC 447/547
 *
 * @author Julian Brackins, Samuel Carroll, Alex Nienhueser
 *
 * @date January 29, 2016
 *
 * @par Professor:
 *         Dr. John Weiss
 *
 * @par Course:
 *         CSC 447/546 - 9:00am
 *
 * @par Location:
 *         McLaury - 313
 *
 * @section program_section Program Information
 *
 * @details
 * TINDER stands for Tree Intelligence Network for Determining Ember Risk and 
 * is, to our knowledge, probably the first software program to ever have this 
 * name. Any other similarities in name are purely coincidental and are in no 
 * relation to the TINDER project and its morals or values.
 *
 * TINDER is an artificial neural network that utilizes a back-propagation 
 * network to determine a given year's fire severity risk based on PDSI 
 * (Palmer Drought Severity Index) data. This program is strictly for 
 * educational purposes for our academic understanding of how a neural network 
 * is designed and how it operates. This program in no way ensures 100% accurate 
 * fire predictions and should not be held to such a standard.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      (Linux) - make
 *
 * @par Usage:
 @verbatim
 ./ANNtrain <parameterfile>
 ./ANNtest <parameterfile>
 ./CrossValidate <parameterfile>
 @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @par Modifications and Development Timeline:
 @verbatim
 Date              Modification
 ----------------  --------------------------------------------------------------
 January  27, 2016  * Began project.
 January  30, 2016  * Set up project directory structure.
 February 03, 2016  * Prm Class started for reading/writing .prm parameter 
                      files.
 February 06, 2016  * Finished basic setter methods for Prm Class
 February 09, 2016  * Finished getter, writing and printing methods for Prm 
                      Class.
 February 11, 2016  * Started work on perceptron class.
 February 21, 2016  * Set up executable outputs.
                    * Set up Perceptron class.
                    * Set up NeuralNet class.
                    * Added Prm class behaviour to validate whether or not a 
                      .prm file was successfully read in.
                    * Added .csv file reading and .wts file reading.
 February 22, 2016  * Modified Perceptron behavior
 February 23, 2016  * Documentation cleanup, Split code into .h and .cpp files.
                    * Modified readCSV to read entire csv file and return it as 
                      a Linked list. 
                    * Added readCSVEntry function to perform the
                      way readCSV previously did.

 @endverbatim
 *
 ******************************************************************************/

#include "../inc/ANN.h"


/******************************************************************************
 *
 * NAMESPACES
 *
 ******************************************************************************/

using namespace std;

/******************************************************************************
 *
 * GLOBALS
 *
 ******************************************************************************/

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print out training information
 *
 * @param[in] paramFile - Parameter file that has been read in.
 *
 * @returns nothing
 *
 *****************************************************************************/
void printInfo( Prm * paramFile )
{
  ///Print out the info for what file was read in.
  //Parameter File: <FILE.prm>
  //CSV Data  File: <FILE.csv>

  cout << "Parameter File: " << paramFile->getFilename( false ) << endl;
  cout << "CSV  Data File: " << paramFile->getCsvFile()         << endl;
  cout << endl;
}

 /**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print program Usage statements
 *
 * @returns nothing
 *
 *****************************************************************************/
void usage( char ** argv )
{
  ///Print out the usage statement for each executable.
  ///This is effectively identical in each instance, so one usage statement
  ///Will suffice.
  cout << "Usage: " << argv[0] << " <parameterfile>" << endl;
  cout << endl;
  cout << "<parameterfile> - Parameter file used for configuring net" << endl;
}
