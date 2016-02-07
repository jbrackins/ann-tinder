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
 * Blah blah blahhh.
 *
 *****************************************************************************/
string Prm::getFilename()
{
  return _filename;
}


/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Read in the parameter file, put everything where it needs to be
 *
 * @param[in] input - input from the .prm file
 *
 * @return 1 - Read Parameter file completely
 * @return 0 - Failed to open prm file.
 * @return <0 - Failed to read prm file properly. See printErrorCode() for 
 *              details
 *
 *****************************************************************************/
int Prm::ReadPrm( string filename )
{
  ///Read in the file
  ifstream infile( filename );
  if( !infile )
  {
    printf("error opening file...\n");
    return 0;
  }

  string buffer;
  int index;
  char first_char;

  ///index for parameter values
  int i = 0;
  while(getline(infile, buffer))
  {
    index = buffer.find_first_not_of(" \t");
    //printf("%c\n", buffer[index]);
    first_char = buffer[index];
    //buffer.erase(remove(buffer.begin(), buffer.end(), ' '), buffer.end());

    ///we only want the lines that do NOT start with a # and are NOT empty
    if( first_char != '#' && first_char != '\0' )
    {
      //printf("%s\n", buffer.c_str()); 
      



      ///Set parameter file line to whatever variable is next.
      ///Based on the i iterator and this case statement


      switch( i )
      {
        case 0:
          if( !setWtsFile( buffer ) )
            i = -100;
          break;
        case 1:
          if( !setEpochs( buffer ) )
            i = -101;
          break;
        case 2:
          if( !setLearningRate( buffer ) )
            i = -102;
          break;
        case 3:
          if( !setMomentum( buffer ) )
            i = -103;
          break;
        case 4:
          if( !setThreshold( buffer ) )
            i = -104;
          break;
        case 5:
          if( !setLayers( buffer ) )
            i = -105;
          break;
        case 6:
          if( !setNodeCount( buffer ) )
            i = -106;
          break;
        case 7:
          if( !setCsvFile( buffer ) )
            i = -107;
          break;
        case 8:
          if( !setYears( buffer ) )
            i = -108;
          break;
        case 9:
          if( !setMonths( buffer ) )
            i = -109;
          break;
        case 10:
          if( !setEndMonth( buffer ) )
            i = -110;
          break;
        case 11:
          if( !setNumClasses( buffer ) )
            i = -111;
          break;
        case 12:
          if( !setLowMed( buffer ) )
            i = -112;
          break;
        case 13:
          if( !setMedHigh( buffer ) )
            i = -113;
          break;
      }
      if( i < 0 )
      {
        Prm::printErrorCode(i);
        return -1;
      }

      ///Go on to filling the next parameter
      i++;    
    }

  }

  infile.close();
  return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set wts File Parameter
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setWtsFile( string input )
{

  printf("set Weights: %s \n", input.c_str());

  return 1;
}


/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Epochs Parameter
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setEpochs( string input )
{

  printf("set Epochs: %s \n", input.c_str());
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Learning Rate Parameter
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setLearningRate( string input )
{

  printf("set Learning Rate: %s \n", input.c_str());
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Momentum Parameter
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setMomentum( string input )
{

  printf("set Momentum: %s \n", input.c_str());
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Threshold Parameter
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setThreshold( string input )
{

  printf("set Threshold: %s \n", input.c_str());
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Layers Parameter
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setLayers( string input )
{

  printf("set Layers: %s \n", input.c_str());
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Node Count Parameter
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setNodeCount( string input )
{

  printf("set Node Count: %s \n", input.c_str());
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set csv file Parameter
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setCsvFile( string input )
{

  printf("set Csv File: %s \n", input.c_str());
  return 1;
}


/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Years of Burned Acreage Parameter
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setYears( string input )
{

  printf("set Years of Burned Acreage: %s \n", input.c_str());
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Months of PDSI data Parameter
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setMonths( string input )
{

  printf("set Months of PDSI data: %s \n", input.c_str());
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set End month of current year Parameter
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setEndMonth( string input )
{

  printf("set End month of current year: %s \n", input.c_str());
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Num Classes Parameter
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setNumClasses( string input )
{

  printf("set Num Classes: %s \n", input.c_str());
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Fire Severity Parameter (low/med)
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setLow( string input )
{

  printf("set Fire Severity (low/med): %s \n", input.c_str());
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Fire Severity Parameter (med/high)
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setMedHigh( string input )
{

  printf("set Fire Severity (med/high): %s \n", input.c_str());
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Error Handler that will let you know what you SCREWED UP. Specific to Prm
 *
 *****************************************************************************/
void Prm::printErrorCode( int err )
{
  err = err * -1;
  printf("Error Code %d: ", err);
  
  switch( err )
  {
    case 100:
      printf("Couldn't extract wts file name from %s\n", Prm::getFilename().c_str());
      break;
    case 101:
      printf("Couldn't extract epochs value from %s\n", Prm::getFilename().c_str());
      break;
    case 102:
      printf("Couldn't extract learning rate from %s\n", Prm::getFilename().c_str());
      break;
    case 103:
      printf("Couldn't extract momentum value from %s\n", Prm::getFilename().c_str());
      break;
    case 104:
      printf("Couldn't extract threshold value from %s\n", Prm::getFilename().c_str());
      break;
    case 105:
      printf("Couldn't extract layers value from %s\n", Prm::getFilename().c_str());
      break;
    case 106:
      printf("Couldn't extract node counts from %s\n", Prm::getFilename().c_str());
      break;
    case 107:
      printf("Couldn't extract cvs file name from %s\n", Prm::getFilename().c_str());
      break;
    case 108:
      printf("Couldn't extract years of burned acreage from %s\n", Prm::getFilename().c_str());
      break;
    case 109:
      printf("Couldn't extract months of PDSI data from %s\n", Prm::getFilename().c_str());
      break;
    case 110:
      printf("Couldn't extract end month of current year from %s\n", Prm::getFilename().c_str());
      break;
    case 111:
      printf("Couldn't extract number of classes from %s\n", Prm::getFilename().c_str());
      break;
    case 112:
      printf("Couldn't extract fire severity range (low/med) from %s\n", Prm::getFilename().c_str());
      break;
    case 113:
      printf("Couldn't extract fire severity range (med/high) from %s\n", Prm::getFilename().c_str());
      break;
    default:
      printf("Couldn't tell ya what happened....\n");
  }  
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Remove the Comment portion of a given string
 *
 * @param[in] input - input string
 *
 * @return output - string without the comment
 *
 *****************************************************************************/
string  Prm::stripComment( string input )
{
  string output = input.substr(0, input.find("#",0));
  return output;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Remove the spaces of a given string. 
 *
 * @param[in] input - input string
 *
 * @return output - string without the spaces
 *
 *****************************************************************************/
string  Prm::stripComment( string input )
{
  string output = input;
  output.erase(remove(output.begin(), output.end(), ' '), output.end());
  return output;
}
