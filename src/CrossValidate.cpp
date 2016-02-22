/*************************************************************************//**
 * @file CrossValidate.cpp
 *
 * @brief SOURCE - Artificial Neural Network - CrossValidate program file. 
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
 * Program Info
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      (Linux) - make
 *
 * @par Usage:
 @verbatim
 ./CrossValidate <parameterfile>
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

#include "../inc/CrossValidate.h"

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
 * @returns 0 - Program Ends.
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


  printInfo( p );

  testPrintout();

}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print out the cross validation header.
 *
 * @returns nothing
 *
 *****************************************************************************/
void printHeader( )
{
  cout << "*-----------------------------------------------------------------*" << endl;
  cout << "| YEAR | BURNED | SEVERITY | PREDICTED | RESULT  | TRAINING ERROR |" << endl;
  cout << "*-----------------------------------------------------------------*" << endl;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print out a cross validation iteration.
 *
 * @param[in] year      - year 
 * @param[in] burned    - number of acres burned in a given year
 * @param[in] severity  - actual PDSI severity based on data
 * @param[in] predicted - predicted PDSI severity based on neural network
 * @param[in] error     - training error
 *
 * @returns nothing
 *
 *****************************************************************************/
void printCrossValidate( int year, int burned, int severity, int predicted, double error )
{
  string str_severity    = formatResult(severity);
  string str_predicted   = formatResult(predicted);
  string str_result;

  ///Prints out a single line of output. This line is a given year's
  ///total number of burned acreage, the actual and predicted  PDSI severity 
  ///rating, which can each be low (LOW), medium (MED), 
  ///or high (HI ) fire severity. If the actual and predicted values are 
  ///identical, this means that the neural net was successful in predicting 
  ///a given sample. If these values do not match, then the neural network
  ///did not predict the given sample properly. The training error for the 
  ///year is also output.
  
  //If the actual and predicted are identical,
  //This prediction was successful.
  if( severity == predicted && predicted != 000 )
    str_result = "SUCCESS";
  else
    str_result = "FAILURE";
  
  //print the year's statistics     
  cout << "|" << " " << setw(4) << year << " ";
  cout << "|" << " " << setw(6) << burned << " ";
  cout << "|" << "   " << str_severity    << "    ";
  cout << "|" << "   " << str_predicted   << "     ";
  cout << "|" << " " << str_result    << " ";
  cout << "|" << "    (" << setiosflags(ios::fixed) << setprecision(3)  << error;
  cout << ")     " << "|" << endl;
  cout << "*-----------------------------------------------------------------*" << endl;;

}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print out the testing summary.
 *
 * @param[in] accuracy  - percentage of samples correctly predicted
 *
 * @returns nothing
 *
 *****************************************************************************/
void printSummary( double accuracy )
{
  
  ///This function will print out the summary statistics of how well the 
  ///neural network performed in the tests.
  cout << endl;
  cout << "Overall Accuracy: " << setprecision(1) << accuracy * 100 << "%%" << endl;

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

  double acc = .91332;
  int yr;
  double burn;
  int sev;
  int pred;
  double err;

  printHeader( );

  //verify matches work
  yr = 1999;
  burn = 123485;
  sev = 010;
  pred = 010;
  err = 0.2348239743;
  printCrossValidate( yr, burn, sev, pred, err );

  //verify non match doesn't...
  yr = 1999;
  burn = 0;
  sev = 001;
  pred = 100;
  err = 0.2348239743;
  printCrossValidate( yr, burn, sev, pred, err );

  //verify invalid...
  yr = 0;
  burn = 1000;
  sev = 000;
  pred = 000;
  err = 0.2348239743;
  printCrossValidate( yr, burn, sev, pred, err );

  printSummary( acc );
}