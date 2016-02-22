/*************************************************************************//**
 * @file ANNtrain.cpp
 *
 * @brief SOURCE - ANNtrain program file. 
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
 ./ANNtrain <parameterfile>
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

#include "../inc/ANNtrain.h"

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
 * @returns 0 - Program Ends Gracefully.
 * @returns -1 - Program Ends because YOU GOOFED UP
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
 * Print out a training iteration.
 *
 * @param[in] epoch     - Epoch of a given training iteration
 * @param[in] equation  - error equation used for training
 * @param[in] error     - error value
 *
 * @returns nothing
 *
 *****************************************************************************/
void printTraining( int epoch, string equation, double error )
{
  
  cout << "Epoch" << setw(7) << epoch;
  cout << ": " << equation << " error = ";
  cout << setiosflags(ios::fixed) << setprecision(3)  << error << endl; 

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
  int e;
  string eq = "RMS";
  double err;

  srand (time(NULL));


  for( e = 0; e < 1000; e+=10 )
  {
	err = (double)rand() / RAND_MAX;
    err = err * (1.00 - 0.00);
    printTraining( e, eq, err );
  }
}

