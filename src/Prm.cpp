/*************************************************************************//**
 * @file Prm.cpp
 *
 * @brief SOURCE - Class for reading and writing Parameter Files.
 *
 * @mainpage Program 1 - TINDER
 *
 * @section course_section CSC 447/547
 *
 * @author Julian Brackins
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

 @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @par Modifications and Development Timeline:
 @verbatim
 Date              Modification
 ----------------  --------------------------------------------------------------
 January 31, 2016  * Started work on File IO.
 * 
 @endverbatim
 *
 ******************************************************************************/

/******************************************************************************
 *
 * INCLUDE
 *
 ******************************************************************************/

#include "../inc/Prm.h"

/******************************************************************************
 *
 * NAMESPACES
 *
 ******************************************************************************/

using namespace std;

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Prm Constructor without a filename specified.
 *
 *****************************************************************************/
Prm::Prm( )
{

}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Prm Constructor with a filename specified.
 *
 * @param[in] filename - the .prm file to be used with this parameter class
 *
 *****************************************************************************/
Prm::Prm( string filename )
{
  _filename = filename;
  ReadPrm( filename );
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Prm DEstructor.
 *
 *****************************************************************************/
Prm::~Prm()
{

}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Read in the parameter file, put everything where it needs to be
 *
 *****************************************************************************/
int Prm::ReadPrm( string filename )
{
  ///Read in the file
  ifstream infile( filename );
  if( !infile )
  {
    printf("error opening file...\n");
    return -1;
  }

  string buffer;
  while(getline(infile, buffer))
  {
    buffer.erase(remove(buffer.begin(), buffer.end(), ' '), buffer.end());
    printf("%s\n", buffer.c_str()); 


  }

  infile.close();
  return 0;
}
