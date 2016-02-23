/*************************************************************************//**
 * @file ANNtest.cpp
 *
 * @brief SOURCE - Artificial Neural Network - ANNtest Trainer program file. 
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
 ./ANNtest <parameterfile>
 @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 *
 ******************************************************************************/

/******************************************************************************
 *
 * INCLUDE
 *
 ******************************************************************************/

#include "../inc/ANNtest.h"

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
 * @author Julian Brackins, Samuel Carroll, Alex Nienhueser
 *
 * @par Description:
 * This is the starting point to the program.  
 *
 * @param[in] argc - the number of arguments from the command prompt.
 * @param[in] argv - a 2d array of characters containing the arguments.
 *
 * @returns 0 - Program Ends Gracefully
 * @returns -1 - Program Ends with error.
 *
 *****************************************************************************/
int main(int argc, char ** argv)
{
  if( argc != 2 )
  {
  	usage( argv );
  	return -1;
  }  

  Prm * p = new Prm( argv[1] );

  //Read in a .prm file  
  p->readPrm();
  // Handle this parameter opening in the neural net
  // open and read the csv file
  // set the csv file input to the neural net
  // open and set weights values (if present, else return -1)
  // run the neural net
  // output the result

  printInfo( p );

  testPrintout(  );

  return 0;

}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print out the testing header.
 *
 * @returns nothing
 *
 *****************************************************************************/
void printHeader( )
{
  cout << "*---------------------------------------*" << endl;
  cout << "| SAMPLE | ACTUAL | PREDICTED | RESULT  |" << endl;
  cout << "*---------------------------------------*" << endl;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print out a testing iteration.
 *
 * @param[in] sample     - sample number
 * @param[in] actual     - actual forest fire activity from PDSI data
 * @param[in] predicted  - prediction made by the neural network
 *
 * @returns nothing
 *
 *****************************************************************************/
void printTesting( int sample, int actual, int predicted )
{
  string str_actual    = formatResult(actual);
  string str_predicted = formatResult(predicted);
  string str_result;

  ///Prints out a single line of output. This line is a given sample's
  ///actual and predicted values, which can each be low (LOW), medium (MED), 
  ///or high (HI ) fire severity. If the actual and predicted values are 
  ///identical, this means that the neural net was successful in predicting 
  ///a given sample. If these values do not match, then the neural network
  ///did not predict the given sample properly.
  
  //If the actual and predicted are identical,
  //This prediction was successful.
  if( actual == predicted && predicted != 000 )
  	str_result = "SUCCESS";
  else
  	str_result = "FAILURE";
  
  //print the sample 
  cout << "|" << setw(8) << sample;
  cout << "|" << " " << str_actual    << "    ";
  cout << "|" << " " << str_predicted << "       ";
  cout << "|" << " " << str_result    << " ";
  cout << "|" << endl;
  cout << "*---------------------------------------*" << endl;;

}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print out the testing summary.
 *
 * @param[in] equation  - error equation used for training
 * @param[in] error     - error value 
 * @param[in] accuracy  - percentage of samples correctly predicted
 *
 * @returns nothing
 *
 *****************************************************************************/
void printSummary( string equation, double error, double accuracy )
{
  
  ///This function will print out the summary statistics of how well the 
  ///neural network performed in the tests.
  cout << endl;
  cout << equation << "error: ";
  cout << setiosflags(ios::fixed) << setprecision(3)  << error << endl; 
  cout << "accuracy: " << setprecision(1) << accuracy * 100 << "%%" << endl;

}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Format the Actual and Predicted strings so they're pretty!
 *
 * @param[in] result - A given value, either actual or predicted
 *
 * @returns "LOW" - value passed in was 100
 * @returns "MED" - value passed in was 010
 * @returns "Hi " - value passed in was 001
 * @returns "ERR" - value passed in was invalid (anything other than above)
 *
 *****************************************************************************/
string formatResult( int result )
{
  
  ///This function rewrites each integer value of a given result, either 
  ///actual or predicted, and displays it in a readable manner.
  ///The conversions are as follows:

	
  ///100 = LOW
  if(result == 100 )
  	return "LOW";
  ///010 = MED
  else if(result == 010 )
  	return "MED";
  ///001 = HI
  else if(result == 001 )
  	return "HI ";
  ///Invalid otherwise
  else
  	return "ERR";

}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Test the output of our program
 *
 * @returns nothing
 *
 *****************************************************************************/
void testPrintout(  )
{
  string eq = "RMS";
  double err = 0.328345;
  double acc = .91332;


  int samp;
  int act;
  int pred;

  printHeader( );

  //verify matches work
  samp = 10;
  act = 100;
  pred = 100;
  printTesting( samp, act, pred );

  //verify non match doesn't...
  samp = 2;
  act  = 010;
  pred = 001;
  printTesting( samp, act, pred ); 

  //verify invalid...
  samp = 1000;
  act  = 001;
  pred = 000;
  printTesting( samp, act, pred );  

  printSummary( eq, err, acc );
}
