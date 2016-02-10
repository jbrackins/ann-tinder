/*************************************************************************//**
 * @file ANNtest.cpp
 *
 * @brief SOURCE - ANNtest program file. 
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
 * @par Modifications and Development Timeline:
 @verbatim
 Date              Modification
 ----------------  --------------------------------------------------------------
 January  27, 2016  * Began project.
 February 03, 2016  * Prm Class started for reading/writing .prm parameter files
 February 06, 2016  * Finished basic setter methods for Prm Class
 February 09, 2016  * Finished getter, writing and printing methods for Prm Class
 @endverbatim
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


/******************************************************************************
 *
 * PROTOTYPES
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
  
  cout << "T.\tree\nI.\tntelligence\nN.\tetwork for\n";
  cout << "D.\tetecting\nE.\tmber\nR.\tisk\n";
  cout << "ANNtest" << endl;
  return 0;

}
