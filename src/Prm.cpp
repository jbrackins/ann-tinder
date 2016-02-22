/*************************************************************************//**
 * @file Prm.cpp
 *
 * @brief SOURCE - Class for reading and writing Prm (Parameter) Files.
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
 * Prm Constructor without a filename specified. Generally a bad idea, since 
 * you will ordinarily have to supply a filename for the parameter file 
 * immediately afterwards...
 *
 *****************************************************************************/
Prm::Prm( )
{
  ///Initialize the Parameter file when you have constructed it. This 
  ///Constructor sets the valid flag of the parameter file as False on 
  ///construction.

  ///This flag value will become true upon a successfully 
  ///read prm file. Otherwise, this will be false to indicate there has 
  ///been an error in reading a parameter file
  _valid = false;
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
  ///Validity of the prm file is false by default, will become true
  ///upon a successfully read prm file.
  _valid = false;
  setFilename( filename );
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Prm Destructor.
 *
 *****************************************************************************/
Prm::~Prm()
{
  ///The destructor will simply double check your file_pointer variable. If 
  ///for whatever reason this has still hung open, just close it out upon 
  ///destruction of the class.
  if( file_pointer != NULL )
  {
    fclose( file_pointer );
  }
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
int Prm::readPrm( )
{

  string buffer;
  int index;
  char first_char;

  ///This function will read in the parameter file. First, the parameter file 
  ///name will be used to verify that the parameter file actually exists. 
  ///If the file does not exist, then the program will output an error and will 
  ///not set the valid flag to true. After running readPrm(), valid() can be used 
  ///to validate whether the file has been read properly.
  string filename = Prm::getFilename();
  ifstream infile( filename );
  if( !infile )
  {
    printf("error opening file...\n");
    return 0;
  }



  //index for parameter values
  int i = 0;

  ///The function will read in each line of the prm file, one after another. 
  ///The program only cares about lines that do NOT start with a 
  ///Hashtag - # (or do you call them 'pound signs', I don't even know lmaooo)

  ///A loop structure will parse each line of the input file that does not have 
  ///the # symbol and determine which parameter this line handles. The handling 
  ///structure is briefly discussed as follows:
  //Read in each line of the prm file
  while(getline(infile, buffer))
  {
    index = buffer.find_first_not_of(" \t");

    first_char = buffer[index];
    //we only want the lines that do NOT start with a # and are NOT empty

    if( first_char != '#' && first_char != '\0' )
    {
      //Set parameter file line to whatever variable is next.
      //Based on the i iterator and this case statement


      switch( i )
      {
        case 0:
          ///case 0 - Set the .wts file
          if( !setWtsFile( buffer ) )
            i = -100;
          break;
        case 1:
          ///case 1 - Set the epoch value
          if( !setEpochs( buffer ) )
            i = -101;
          break;
        case 2:
          ///case 2 - Set the learning rate
          if( !setLearningRate( buffer ) )
            i = -102;
          break;
        case 3:
          ///case 3 - Set the momentum
          if( !setMomentum( buffer ) )
            i = -103;
          break;
          ///case 4 - Set the threshold
        case 4:
          if( !setThreshold( buffer ) )
            i = -104;
          break;
        case 5:
          ///case 5 - Set the layers
          if( !setLayers( buffer ) )
            i = -105;
          break;
        case 6:
          ///case 6 - Set the node count
          if( !setNodeCount( buffer ) )
            i = -106;
          break;
        case 7:
          ///case 7 - Set the .csv file
          if( !setCsvFile( buffer ) )
            i = -107;
          break;
        case 8:
          ///case 8 - Set the years
          if( !setYears( buffer ) )
            i = -108;
          break;
        case 9:
          ///case 9 - Set the months
          if( !setMonths( buffer ) )
            i = -109;
          break;
        case 10:
          ///case 10 - Set the end month
          if( !setEndMonth( buffer ) )
            i = -110;
          break;
        case 11:
          ///case 11 - Set the number of classes
          if( !setNumClasses( buffer ) )
            i = -111;
          break;
        case 12:
          ///case 12 - Set the fire severity low/med value
          if( !setLowMed( buffer ) )
            i = -112;
          break;
        case 13:
          ///case 13 - Set the fire severity med/high value
          if( !setMedHigh( buffer ) )
            i = -113;
          break;
      }
      if( i < 0 )
      {
        ///If something goes wrong, an error code is generated. I don't think this 
        ///will ever really happen since this assignment should generally have the 
        ///same order to the parameters.
        Prm::printErrorCode(i);
        return -1;
      }

      //Go on to filling the next parameter
      i++;    
    }

  }

  //close the file.
  infile.close();

  ///Upon successfully reading in all of the parameters, the Prm instance will 
  ///have its valid flag set to true, which means the class has all the information 
  //necessary for the neural network.
  _valid = true;

  return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Write a new parameter file, put everything where it needs to be. PLEASE 
 * DON'T BE MAD AT ME FOR USING STDIO FILE WRITING EVEN THOUGH I USED 
 * FSTREAM FOR READING IN THE FILE......
 *
 * @param[in] input - input from the .prm file
 *
 * @return 1 - Read Parameter file completely
 * @return 0 - Failed to write prm file.
 *
 *****************************************************************************/
int Prm::writePrm( )
{
  ///This function will use all of the information contained in the Prm class 
  ///to generate a new parameter file if necessary.

  time_t curr_time;
  char* timestamp;

  //Get Timestamp
  curr_time = time(NULL);  
  timestamp = ctime(&curr_time);
  if(timestamp == NULL)
  {
    printf("error getting the time...\n");
    return 0;
  }

  //Open the file
  file_pointer = fopen( Prm::getFilename().c_str(), "w" );
  if( file_pointer == NULL )
  {
    printf("error opening .prm file...\n");
    return 0;
  }

  //Write the header
  //Pass False into here so that you just get prm file name
  Prm::writeFilename( );
  fprintf( file_pointer, "#\n" );
  fprintf( file_pointer, "# Generated Parameter file for ");
  fprintf( file_pointer, "ANN TINDER project: \n" );
  fprintf( file_pointer, "#\n" );
  fprintf( file_pointer, "# Modify this parameter file as needed.\n" );
  fprintf( file_pointer, "#\n" );
  fprintf( file_pointer, "# The order of fields is specified in ");
  fprintf( file_pointer, "the example below, and cannot be changed.\n" );
  fprintf( file_pointer, "# Fields are separated by white space.\n" );
  fprintf( file_pointer, "# Anything following # (or %%) on a line ");
  fprintf( file_pointer, "is ignored as a comment.\n" );
  fprintf( file_pointer, "#\n" );
  fprintf( file_pointer, "# Class:        CSC447/547 ");
  fprintf( file_pointer, "Artificial Intelligence\n");
  fprintf( file_pointer, "# Author:       Julian Brackins,");
  fprintf( file_pointer, " Samuel Carroll, Alex Nienhueser\n");
  fprintf( file_pointer, "# Date:         %s", timestamp);
  fprintf( file_pointer, "#\n" );
  fprintf( file_pointer, "#*****************************************");
  fprintf( file_pointer, "**************************************\n");

  //Write ANN parameters
  fprintf( file_pointer, "\n" );
  fprintf( file_pointer, "#---------------\n" );
  fprintf( file_pointer, "# ANN parameters\n" );
  fprintf( file_pointer, "#---------------\n" );
  fprintf( file_pointer, "\n" );

  Prm::writeWtsFile( );
  Prm::writeEpochs(  );
  Prm::writeLearningRate(  );
  Prm::writeMomentum(  );
  Prm::writeThreshold(  );
  Prm::writeLayers(  );
  Prm::writeAllNodes();

  //Write training and testing data file
  fprintf( file_pointer, "\n" );
  fprintf( file_pointer, "#-------------------------------\n" );
  fprintf( file_pointer, "# training and testing data file\n" );
  fprintf( file_pointer, "#-------------------------------\n" );
  fprintf( file_pointer, "\n" );

  Prm::writeCsvFile(  );

  //Write input feature vector info
  fprintf( file_pointer, "\n" );
  fprintf( file_pointer, "#------------------------------------------\n" );
  fprintf( file_pointer, "# input feature vector info:\n" );
  fprintf( file_pointer, "# years of burned acreage,\n" );  
  fprintf( file_pointer, "# months of PDSI data (no fewer than # of input");
  fprintf( file_pointer, ") layer nodes),\n" );
  fprintf( file_pointer, "# and end month of current year (1=Jan, 2=Feb,");
  fprintf( file_pointer, ") 3=Mar, etc.) for PDSI data\n" );
  fprintf( file_pointer, "#------------------------------------------\n" );
  fprintf( file_pointer, "\n" );

  Prm::writeYears(  );
  Prm::writeMonths(  );
  Prm::writeEndMonth(  );

  //Write Class info
  fprintf( file_pointer, "\n" );
  fprintf( file_pointer, "#------------------------------------------\n" );
  fprintf( file_pointer, "# output class info:\n" );
  fprintf( file_pointer, "# number of classes (no fewer than # of ");
  fprintf( file_pointer, "input layer nodes)\n" );
  fprintf( file_pointer, "#------------------------------------------\n" );
  fprintf( file_pointer, "\n" );
  
  Prm::writeNumClasses(  );

  //Write Fire Severity Parameters
  fprintf( file_pointer, "\n" );
  fprintf( file_pointer, "#------------------------------------------\n" );
  fprintf( file_pointer, "# fire severity parameters:\n" );
  fprintf( file_pointer, "# burned acres cutoffs, corresponding to ");
  fprintf( file_pointer, "low/medium/high fire severity\n" );
  fprintf( file_pointer, "#------------------------------------------\n" );
  fprintf( file_pointer, "\n" );

  Prm::writeLowMed(  );
  Prm::writeMedHigh(  );

  fprintf( file_pointer, "\n" );

  //Write Footer
  Prm::writeFilename( );

  //Close .prm File
  fclose( file_pointer );

  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Verify that the prm file was read in alright
 *
 * @returns _valid - validity of the file
 *
 *****************************************************************************/
bool Prm::valid( )
{
  ///If this method returns FALSE, the file has not been read in successfully. 
  ///The rest of the program should not commence, as this will cause errors 
  ///from missing variables.

  ///If this method returns TRUE, the file has been read in successfully. 
  return _valid;
}


/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Get the Filename
 *
 * @param[in] path - whether or not you get the full path
 *
 * @returns filename - no seriously what did you even think
 *
 *****************************************************************************/
string Prm::getFilename( bool path )
{

  if( path )
    ///Return the full path to file if path var is TRUE (Default)
    return _filename;
  else
  {
    ///Else
    ///Get position of the last slash.
    ///The remainder of the path should just be the name of the file
    size_t pos = _filename.find_last_of("/"); 
    string name = _filename.substr (pos+1); 
    return name;    
  }

}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Get the wts file param
 *
 * @param[in] path - whether or not you get the full path
 *
 * @returns _wts_file - wts file string
 *
 *****************************************************************************/
string Prm::getWtsFile( bool path )
{
  if( path )
    ///Return the full path to file if path var is TRUE (Default)
    return _wts_file;
  else
  {
    ///Else
    ///Get position of the last slash.
    ///The remainder of the path should just be the name of the file
    size_t pos  = _wts_file.find_last_of("/"); 
    string name = _wts_file.substr (pos+1); 
    return name;    
  }
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Get the epochs param
 *
 * @returns _epochs - epochs integer
 *
 *****************************************************************************/
int Prm::getEpochs()
{
  return _epochs;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Get the learning rate param
 *
 * @returns _learning_rate - learning rate double
 *
 *****************************************************************************/
double Prm::getLearningRate()
{
  return _learning_rate;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Get the momentum param
 *
 * @returns _momentum - momentum double
 *
 *****************************************************************************/
double Prm::getMomentum()
{
  return _momentum;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Get the threshold param
 *
 * @returns _threshold - threshold double
 *
 *****************************************************************************/
double Prm::getThreshold()
{
  return _threshold;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Get the layers param
 *
 * @returns _layers - layers integer
 *
 *****************************************************************************/
int Prm::getLayers()
{
  return _layers;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Get the wts file param
 * 
 * @param[in] index - index into vector
 *
 * @returns node_count - specific node value. Return last value in vector if 
 *                       the index exceeds bounds, returns first value in 
 *                       vector if < 0 is indexed
 * @returns -100 - nodeCount vector is uninitialized.
 *
 *****************************************************************************/
int Prm::getNodeCount( int index )
{
  ///getNodeCount will give you how many nodes are in each layer of the neural 
  ///network. There should be three values you can extract from this method.
  
  ///getNodeCount(0) - Input Layer
  
  ///getNodeCount(1) - Hidden Layer

  ///getNodeCount(2) - Output Layer
  int sz = _node_count.size();
  if( _node_count.empty() )
  {
    return -100;
  }
  else if( index < 0 )
  {
    index = 0;
  }
  else if( index > sz )
  {
    index = _node_count.back();
  }
  return _node_count[index];
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Get the csv file param
 *
 * @param[in] path - whether or not you get the full path
 *
 * @returns _csv_file - csv file string
 *
 *****************************************************************************/
string Prm::getCsvFile( bool path )
{
  if( path )
    ///Return the full path to file if path var is TRUE (Default)
    return _csv_file;
  else
  {
    ///Else
    ///Get position of the last slash.
    ///The remainder of the path should just be the name of the file
    size_t pos  = _csv_file.find_last_of("/"); 
    string name = _csv_file.substr (pos+1); 
    return name;    
  }}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Get the years param
 *
 * @returns _years - years integer
 *
 *****************************************************************************/
int Prm::getYears()
{
  return _years;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Get the months param
 *
 * @returns _months - months integer
 *
 *****************************************************************************/
int Prm::getMonths()
{
  return _months;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Get the end month param
 *
 * @returns _end_month - end month integer
 *
 *****************************************************************************/
int Prm::getEndMonth()
{
  return _end_month;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Get the number of classes param
 *
 * @returns _num_classes - number of classes integer
 *
 *****************************************************************************/
int Prm::getNumClasses()
{
  return _num_classes;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Get the low/med fire severity cutoff param
 *
 * @returns _low_med - low/med integer
 *
 *****************************************************************************/
int Prm::getLowMed()
{
  return _low_med;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Get the med/high fire severity cutoff param
 *
 * @returns _med_high - med/high integer
 *
 *****************************************************************************/
int Prm::getMedHigh()
{
  return _med_high;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set prm Filename Parameter
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setFilename( string input )
{
  if( input.empty() )
  {
    return 0;
  }
  _filename = input;
  return 1;
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
  string wts;

  ///Read in the wts file name from the parameter file. This is stored as a 
  ///string in the Prm class.

  ///The wts file contains the weights of each node in the input, hidden, and 
  ///output layers, respectively. These values are generated when running 
  ///ANNtrain, and read in for use for ANNtest and CrossValidate.

  //Remove comment from input
  wts = stripComment(input);
  //Remove spaces just in case
  wts = stripSpaces(wts); 

  //Set value to private variable
  Prm::_wts_file = wts;
  return 1;
}


/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Epochs Parameter (read from prm)
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setEpochs( string input )
{
  int epoch;

  ///When reading in the epochs parameter, the input string 
  ///needs to be converted to an integer value.

  //Convert param file input to an integer
  string buffer = stripComment(input);
  buffer = stripSpaces(buffer);
  string::size_type sz;
  epoch = stoi(buffer, &sz);
  
  //Set value to private variable
  Prm::setEpochs( epoch );
  return 1;
}


/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Epochs Parameter (int value)
 *
 * @param[in] input - input value
 *
 * @return 0 - Failed to set parameter
 * @return 1 - Succeeded to set parameter
 *
 *****************************************************************************/
int Prm::setEpochs( int input )
{
  //Set value to private variable
  Prm::_epochs = input;
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Learning Rate Parameter (read from .prm)
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setLearningRate( string input )
{
  double learn;

  ///When reading in the learning rate parameter, the input string 
  ///needs to be converted to an double value.

  //Convert param file input to a double
  string buffer = stripComment(input);
  buffer = stripSpaces(buffer);
  string::size_type sz;
  learn = stod(buffer, &sz);
  
  //Set value to private variable
  Prm::setLearningRate( learn );
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Learning Rate Parameter (double value)
 *
 * @param[in] input - input value
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setLearningRate( double input )
{
  //Set value to private variable
  Prm::_learning_rate = input;
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Momentum Parameter (read from prm)
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setMomentum( string input )
{
  double momentum;

  ///When reading in the momentum parameter, the input string 
  ///needs to be converted to an double value.

  //Convert param file input to a double
  string buffer = stripComment(input);
  buffer = stripSpaces(buffer);
  string::size_type sz;
  momentum = stod(buffer, &sz);
  
  //Set value to private variable
  Prm::setMomentum( momentum );
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Momentum Parameter (double value)
 *
 * @param[in] input - input value
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setMomentum( double input )
{
  //Set value to private variable
  Prm::_momentum = input;
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Threshold Parameter (read from prm)
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setThreshold( string input )
{

  double thresh;

  ///When reading in the threshold parameter, the input string 
  ///needs to be converted to an double value.

  //Convert param file input to a double
  string buffer = stripComment(input);
  buffer = stripSpaces(buffer);
  string::size_type sz;
  thresh = stod(buffer, &sz);
  
  //Set value to private variable
  Prm::setThreshold( thresh );
  return 1;
}


/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Threshold Parameter (double value)
 *
 * @param[in] input - input value
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setThreshold( double input )
{
  //Set value to private variable
  Prm::_threshold = input;
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Layers Parameter (read from prm)
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setLayers( string input )
{
  int layers;

  ///When reading in the layers parameter, the input string 
  ///needs to be converted to an integer value.

  //Convert param file input to an integer
  string buffer = stripComment(input);
  buffer = stripSpaces(buffer);
  string::size_type sz;
  layers = stoi(buffer, &sz);
  
  //Set value to private variable
  Prm::setLayers( layers );
  return 1;
}


/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Layers Parameter (int value)
 *
 * @param[in] input - input value
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setLayers( int input )
{
  //Set value to private variable
  Prm::_layers = input;
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
  string buffer = stripComment(input);

  ///The input line for the node counts will be three numbers separated by 
  ///spaces. The first (index 0) number is the input layer count, 
  ///the second (index 1) value is the hidden layer count, and the last 
  ///(index 2) value is the output layer count.

  istringstream iss(buffer);
  int val;

  while(iss >> val)
  {
      ///Push each node count value into the node_count vector
      Prm::addNodeCount( val );
  }

  return 1;
}


/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Add individual node count to vector
 *
 * @param[in] input - input value
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::addNodeCount( int input )
{
  ///Pushes an individual layer value into the node count vector.

  ///_node_count index values:

  ///0 is the input layer count

  ///1 is the hidden layer count

  ///2 is the output layer count
  Prm::_node_count.push_back( input );
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
  string csv;

  ///Read in the csv file name from the parameter file. This is stored as a 
  ///string in the Prm class.
  
  ///This csv file contains the PDSI data used to train or test the neural 
  ///network.

  //Remove comment from input
  csv = stripComment(input);
  //Remove spaces just in case
  csv = stripSpaces(csv); 
  
  //Set value to private variable
  Prm::_csv_file = csv;
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Years of Burned Acreage Parameter (read from prm)
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setYears( string input )
{
  int yrs;

  ///When reading in the years parameter, the input string 
  ///needs to be converted to an integer value.

  //Convert param file input to an integer
  string buffer = stripComment(input);
  buffer = stripSpaces(buffer);
  string::size_type sz;
  yrs = stoi(buffer, &sz);
  
  //Set value to private variable
  Prm::setYears( yrs );
  return 1;
}


/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Years of Burned Acreage Parameter ( int value )
 *
 * @param[in] input - input value
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setYears( int input )
{
  //Set value to private variable
  Prm::_years = input;
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Months of PDSI data Parameter (read from prm)
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setMonths( string input )
{
  int months;

  ///When reading in the months parameter, the input string 
  ///needs to be converted to an integer value.

  //Convert param file input to an integer
  string buffer = stripComment(input);
  buffer = stripSpaces(buffer);
  string::size_type sz;
  months = stoi(buffer, &sz);
  
  //Set value to private variable
  Prm::setMonths( months );
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Months of PDSI data Parameter (int value)
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setMonths( int input )
{
  //Set value to private variable
  Prm::_months = input;
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set End month of current year Parameter (read from prm)
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setEndMonth( string input )
{
  int end;

  ///When reading in the end month parameter, the input string 
  ///needs to be converted to an integer value.

  //Convert param file input to an integer
  string buffer = stripComment(input);
  buffer = stripSpaces(buffer);
  string::size_type sz;
  end = stoi(buffer, &sz);
  
  //Set value to private variable
  Prm::setEndMonth( end );
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set End month of current year Parameter (int value)
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setEndMonth( int input )
{
  //Set value to private variable
  Prm::_end_month = input;
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Num Classes Parameter (read from prm)
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setNumClasses( string input )
{
  int num;

  ///When reading in the number of classes parameter, the input string 
  ///needs to be converted to an integer value.

  //Convert param file input to an integer
  string buffer = stripComment(input);
  buffer = stripSpaces(buffer);
  string::size_type sz;
  num = stoi(buffer, &sz);
  
  //Set value to private variable
  Prm::setNumClasses( num );
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Num Classes Parameter (int value)
 *
 * @param[in] input - input value
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setNumClasses( int input )
{
  //Set value to private variable
  Prm::_num_classes = input;
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Fire Severity Parameter (low/med) (read from prm)
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setLowMed( string input )
{
  int lowmed;

  ///When reading in the Fire Severity (low/med) parameter, the input string 
  ///needs to be converted to an integer value.

  //Convert param file input to an integer
  string buffer = stripComment(input);
  buffer = stripSpaces(buffer);
  string::size_type sz;
  lowmed = stoi(buffer, &sz);
  
  //Set value to private variable
  Prm::setLowMed( lowmed );
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Fire Severity Parameter (low/med) (int value)
 *
 * @param[in] input - input value
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setLowMed( int input )
{
  Prm::_low_med = input;
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Fire Severity Parameter (med/high) (read from prm)
 *
 * @param[in] input - input from the .prm file
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setMedHigh( string input )
{
  int medhi;

  ///When reading in the Fire Severity (med/high) parameter, the input string 
  ///needs to be converted to an integer value.

  //Convert param file input to an integer
  string buffer = stripComment(input);
  buffer = stripSpaces(buffer);
  string::size_type sz;
  medhi = stoi(buffer, &sz);
  
  //Set value to private variable
  Prm::setMedHigh( medhi );
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Set Fire Severity Parameter (med/high) (int value)
 *
 * @param[in] input - input value
 *
 * @return 0 - Failed to read parameter
 * @return 1 - Succeeded to read parameter
 *
 *****************************************************************************/
int Prm::setMedHigh( int input )
{
  //Set value to private variable
  Prm::_med_high = input;
  return 1;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Write the Filename to .prm
 *
 * @return 1 - successfully written to file
 * @return 0 - file i/o issue
 *
 *****************************************************************************/
int Prm::writeFilename()
{
  ///check if file pointer is valid, then write the filename with appropriate
  ///header style to the prm file
  if( file_pointer )
  {
    fprintf(file_pointer, "#************************** %s ", 
            Prm::getFilename( false ).c_str() );
    fprintf(file_pointer, "***********************************\n");
    return 1;
  }
  return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Write the wts file to .prm
 *
 * @return 1 - successfully written to file
 * @return 0 - file i/o issue
 *
 *****************************************************************************/
int Prm::writeWtsFile()
{
  ///check if file pointer is valid, then write the wts file name with 
  ///appropriate comment style to the prm file
  if( file_pointer )
  {
    fprintf(file_pointer, "%s", Prm::getWtsFile().c_str() );
    fprintf(file_pointer, "     # name of ANN weight file\n");
    return 1;
  }
  return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Write the Epochs to .prm
 *
 * @return 1 - successfully written to file
 * @return 0 - file i/o issue
 *
 *****************************************************************************/
int Prm::writeEpochs()
{
  ///check if file pointer is valid, then write the epochs value with 
  ///appropriate comment style to the prm file
  if( file_pointer )
  {
    fprintf(file_pointer, "%d", Prm::getEpochs() );
    fprintf(file_pointer, "     # number of training epochs\n");
    return 1;
  }
  return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Write the Learning Rate to .prm
 *
 * @return 1 - successfully written to file
 * @return 0 - file i/o issue
 *
 *****************************************************************************/
int Prm::writeLearningRate()
{
  ///check if file pointer is valid, then write the learning rate value with 
  ///appropriate comment style to the prm file
  if( file_pointer )
  {
    fprintf(file_pointer, "%lf", Prm::getLearningRate() );
    fprintf(file_pointer, "     # learning rate\n");
    return 1;
  }
  return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Write the Momentum to .prm
 *
 * @return 1 - successfully written to file
 * @return 0 - file i/o issue
 *
 *****************************************************************************/
int Prm::writeMomentum()
{
  ///check if file pointer is valid, then write the momentum value with 
  ///appropriate comment style to the prm file
  if( file_pointer )
  {
    fprintf(file_pointer, "%lf", Prm::getMomentum() );
    fprintf(file_pointer, "     # momentum\n");
    return 1;
  }
  return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Write the Threshold to .prm
 *
 * @return 1 - successfully written to file
 * @return 0 - file i/o issue
 *
 *****************************************************************************/
int Prm::writeThreshold()
{
  ///check if file pointer is valid, then write the threshold value with 
  ///appropriate comment style to the prm file
  if( file_pointer )
  {
    fprintf(file_pointer, "%lf", Prm::getThreshold() );
    fprintf(file_pointer, "     # threshold for ANN error");
    fprintf(file_pointer, " (training cutoff OR testing acceptance)\n");
    return 1;
  }
  return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Write the Layers to .prm
 *
 * @return 1 - successfully written to file
 * @return 0 - file i/o issue
 *
 *****************************************************************************/
int Prm::writeLayers()
{
  ///check if file pointer is valid, then write the layers value with 
  ///appropriate comment style to the prm file
  if( file_pointer )
  {
    fprintf(file_pointer, "%d", Prm::getLayers() );
    fprintf(file_pointer, "     # layers of adjustable weights");
    fprintf(file_pointer, " (one less than layers of nodes)\n");
    return 1;
  }
  return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Write all the nodes to .prm
 *
 * @return 1 - successfully written to file
 * @return 0 - file i/o issue
 *
 *****************************************************************************/
int Prm::writeAllNodes()
{
  ///check if file pointer is valid, then write the nodes counts for each layer 
  ///(input, hidden, output) with appropriate comment style to the prm file

  if( file_pointer )
  {
    int sz = Prm::_node_count.size();
    for(int i = 0; i < sz; i++)
    {
      Prm::writeNodeCount( i );
      fprintf( file_pointer, " " );
    }
    fprintf(file_pointer, "    # how many nodes in each layer\n");
    return 1;
  }
  return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Write individual node count to .prm
 *
 * @return 1 - successfully written to file
 * @return 0 - file i/o issue
 *
 *****************************************************************************/
int Prm::writeNodeCount( int index )
{
  ///check if file pointer is valid, then write an individual layer node count 
  ///with appropriate comment style to the prm file

  if( file_pointer )
  {
    fprintf(file_pointer, "%d", Prm::getNodeCount( index ) );
    return 1;
  }
  return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Write the csv file name to .prm
 *
 * @return 1 - successfully written to file
 * @return 0 - file i/o issue
 *
 *****************************************************************************/
int Prm::writeCsvFile()
{
  ///check if file pointer is valid, then write the csv file name with 
  ///appropriate comment style to the prm file

  if( file_pointer )
  {
    fprintf(file_pointer, "%s \n", Prm::getCsvFile().c_str() );
    return 1;
  }
  return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Write the Years to .prm
 *
 * @return 1 - successfully written to file
 * @return 0 - file i/o issue
 *
 *****************************************************************************/
int Prm::writeYears()
{
  ///check if file pointer is valid, then write the years value with 
  ///appropriate comment style to the prm file

  if( file_pointer )
  {
    fprintf(file_pointer, "%d", Prm::getYears() );
    fprintf(file_pointer, "     # years of burned acreage\n");
    return 1;
  }
  return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Write the Months to .prm
 *
 * @return 1 - successfully written to file
 * @return 0 - file i/o issue
 *
 *****************************************************************************/
int Prm::writeMonths()
{
  ///check if file pointer is valid, then write the months value with 
  ///appropriate comment style to the prm file

  if( file_pointer )
  {
    fprintf(file_pointer, "%d", Prm::getMonths() );
    fprintf(file_pointer, "     # months of PDSI data\n");
    return 1;
  }
  return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Write the End Month to .prm
 *
 * @return 1 - successfully written to file
 * @return 0 - file i/o issue
 *
 *****************************************************************************/
int Prm::writeEndMonth()
{
  ///check if file pointer is valid, then write the end month value with 
  ///appropriate comment style to the prm file

  if( file_pointer )
  {
    fprintf(file_pointer, "%d", Prm::getEndMonth() );
    fprintf(file_pointer, "     # end month of current year");
    fprintf(file_pointer, " (1=Jan, 2=Feb, 3=Mar, etc.)\n");
    return 1;
  }
  return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Write the Number of classes to .prm
 *
 * @return 1 - successfully written to file
 * @return 0 - file i/o issue
 *
 *****************************************************************************/
int Prm::writeNumClasses()
{
  ///check if file pointer is valid, then write the number of classes with 
  ///appropriate comment style to the prm file

  if( file_pointer )
  {
    fprintf(file_pointer, "%d", Prm::getNumClasses() );
    fprintf(file_pointer, "     # number of classes\n");
    return 1;
  }
  return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Write the Low/Med to .prm
 *
 * @return 1 - successfully written to file
 * @return 0 - file i/o issue
 *
 *****************************************************************************/
int Prm::writeLowMed()
{
  ///check if file pointer is valid, then write the fire severity (low/med)
  /// value with appropriate comment style to the prm file

  if( file_pointer )
  {
    fprintf(file_pointer, "%d \n", Prm::getLowMed() );
    return 1;
  }
  return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Write the Med/High to .prm
 *
 * @return 1 - successfully written to file
 * @return 0 - file i/o issue
 *
 *****************************************************************************/
int Prm::writeMedHigh()
{
  ///check if file pointer is valid, then write the fire severity (med/high)
  /// value with appropriate comment style to the prm file

  if( file_pointer )
  {
    fprintf(file_pointer, "%d \n", Prm::getMedHigh() );
    return 1;
  }
  return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print Filename Parameter
 *
 * @returns none
 *
 *****************************************************************************/
void Prm::printFilename( )
{
  printf( "Prm File: %s \n", Prm::getFilename( false ).c_str() );
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print wts File Parameter
 *
 * @returns none
 *
 *****************************************************************************/
void Prm::printWtsFile( )
{
  printf( "Weights File: %s \n", Prm::getWtsFile().c_str() );
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print Epochs Parameter
 *
 * @returns none
 *
 *****************************************************************************/
void Prm::printEpochs( )
{
  printf( "Epochs: %d \n", Prm::getEpochs() );
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print Learning Rate Parameter
 *
 * @returns none
 *
 *****************************************************************************/
void Prm::printLearningRate( )
{
  printf( "Learning Rate: %lf \n", Prm::getLearningRate() );
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print Momentum Parameter
 *
 * @returns none
 *
 *****************************************************************************/
void Prm::printMomentum( )
{
  printf( "Momentum: %lf \n", Prm::getMomentum() );
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print Threshold Parameter
 *
 * @returns none
 *
 *****************************************************************************/
void Prm::printThreshold( )
{
  printf( "Threshold: %lf \n", Prm::getThreshold() );
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print Layers Parameter
 *
 * @returns none
 *
 *****************************************************************************/
void Prm::printLayers( )
{
  printf( "Layers: %d \n", Prm::getLayers() );
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print The whole NodeCount vector
 *
 * @returns none
 *
 *****************************************************************************/
void Prm::printAllNodes( )
{
  printf("Node Count: ");
  int sz = Prm::_node_count.size();
  for(int i = 0; i < sz; i++)
  {
    Prm::printNodeCount( i );
    printf(" ");
  }
  printf("\n");
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print Individual Node Count Parameter
 *
 * @param[in] index - index to specific node count in vector
 *
 * @returns none
 *
 *****************************************************************************/
void Prm::printNodeCount( int index )
{
  printf( "%d", Prm::getNodeCount(index) );
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print csv file Parameter
 *
 * @returns none
 *
 *****************************************************************************/
void Prm::printCsvFile( )
{
  printf( "CSV file: %s \n", Prm::getCsvFile().c_str() );
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print Years Parameter
 *
 * @returns none
 *
 *****************************************************************************/
void Prm::printYears( )
{
  printf( "Years: %d \n", Prm::getYears() );
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print Months Parameter
 *
 * @returns none
 *
 *****************************************************************************/
void Prm::printMonths( )
{
  printf( "Months: %d \n", Prm::getMonths() );
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print End Month Parameter
 *
 * @returns none
 *
 *****************************************************************************/
void Prm::printEndMonth( )
{
  printf( "End Month: %d \n", Prm::getEndMonth() );
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print Number of Classes Parameter
 *
 * @returns none
 *
 *****************************************************************************/
void Prm::printNumClasses( )
{
  printf( "Number of Classes: %d \n", Prm::getNumClasses() );
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print Low/Med Parameter
 *
 * @returns none
 *
 *****************************************************************************/
void Prm::printLowMed( )
{
  printf( "Low/Med: %d \n", Prm::getLowMed() );
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print Med/High Parameter
 *
 * @returns none
 *
 *****************************************************************************/
void Prm::printMedHigh( )
{
  printf( "Med/High: %d \n", Prm::getMedHigh() );
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print literally everything ever!
 *
 * @param[in] err - error code
 * 
 * @returns none
 *
 *****************************************************************************/
void Prm::printPrm()
{
  ///Print out everything that has been set for the prm file.
  Prm::printFilename();
  Prm::printWtsFile();
  Prm::printEpochs();
  Prm::printLearningRate();
  Prm::printMomentum();
  Prm::printThreshold();
  Prm::printLayers();
  Prm::printAllNodes();
  Prm::printCsvFile();
  Prm::printYears();
  Prm::printMonths();
  Prm::printEndMonth();
  Prm::printNumClasses();
  Prm::printLowMed();
  Prm::printMedHigh();
}


/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Error Handler that will let you know what you SCREWED UP. Specific to Prm
 *
 * @param[in] err - error code
 * 
 * @returns none
 *
 *****************************************************************************/
void Prm::printErrorCode( int err )
{
  ///Print out a corresponding error code based on what error arose when reading 
  ///in the parameter file.
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
  ///This method will remove the portion of a given input line that is denoted 
  ///as a comment based on the # symbol.
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
string  Prm::stripSpaces( string input )
{
  ///This method removes spaces in a given input line. Not PARTICULARLY important 
  ///but could potentially help with converting given string inputs to numerical
  ///data types.
  string output = input;
  output.erase(remove(output.begin(), output.end(), ' '), output.end());
  return output;
}
