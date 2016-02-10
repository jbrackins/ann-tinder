/*************************************************************************//**
 * @file Prm.h
 *
 * @author Julian Brackins, Samuel Carroll, Alex Nienhueser
 *
 * @brief HEADER - Class for reading and writing Parameter Files.
 *
 *****************************************************************************/

#ifndef _PRM_H_
#define _PRM_H_

/******************************************************************************
 *
 * INCLUDE
 *
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

/*************************************************************************//**
* @class Prm
*
* @author Julian Brackins
*
* @brief Parameter file class.
*
*****************************************************************************/
class Prm
{
public:
  // CONSTRUCTORS
  Prm(  );
  Prm( std::string filename );

  // DESTRUCTOR
  ~Prm();
  
  ///READ and WRITE to/from the .prm file
  int readPrm( );
  int writePrm();

  ///GETTERS - Get the values of each variable
  std::string getFilename();
  std::string getWtsFile();
  int getEpochs();
  double getLearningRate();
  double getMomentum();
  double getThreshold();
  int getLayers();
  int getNodeCount( int index );
  std::string getCsvFile();
  int getYears();
  int getMonths();
  int getEndMonth();
  int getNumClasses();
  int getLowMed();
  int getMedHigh();

  ///SETTERS - Set the values of each variable. Note that
  ///All non-string parameters have two different setters, 
  ///One for ubiquitous std::string types read in from file, 
  ///Another for the specific data type input
  //File name setter
  int setFilename( std::string input );
  //Weights file setter
  int setWtsFile( std::string input );
  //Epochs Setter
  int setEpochs( std::string input );
  int setEpochs( int input );
  //Learning Rate Setters
  int setLearningRate( std::string input );
  int setLearningRate( double input );
  //Momentum Setters
  int setMomentum( std::string input );
  int setMomentum( double input );
  //Threshold Setters
  int setThreshold( std::string input );
  int setThreshold( double input );
  //Layers Setters
  int setLayers( std::string input );
  int setLayers( int input );
  //NodeCount Setter and 'Pusher'
  int setNodeCount( std::string input );
  int addNodeCount( int input );
  //CSV file setter
  int setCsvFile( std::string input );
  //Years Setters
  int setYears( std::string input );
  int setYears( int input );
  //Months Setters
  int setMonths( std::string input );
  int setMonths( int input );
  //End Month Setters
  int setEndMonth( std::string input );
  int setEndMonth( int input );
  //Number of Classes Seters
  int setNumClasses( std::string input );
  int setNumClasses( int input );
  //Low-Medium Setters
  int setLowMed( std::string input );
  int setLowMed( int input );
  //Medium-High Setters
  int setMedHigh( std::string input );
  int setMedHigh( int input );

  ///WRITERS - Write the values of each variable to a file
  int writeFilename( );
  int writeWtsFile( );
  int writeEpochs(  );
  int writeLearningRate(  );
  int writeMomentum(  );
  int writeThreshold(  );
  int writeLayers(  );
  int writeAllNodes();
  int writeNodeCount( int index );
  int writeCsvFile(  );
  int writeYears(  );
  int writeMonths(  );
  int writeEndMonth(  );
  int writeNumClasses(  );
  int writeLowMed(  );
  int writeMedHigh(  );

  ///PRINTERS - Print the values of each variable to stdout
  void printFilename();
  void printWtsFile();
  void printEpochs();
  void printLearningRate();
  void printMomentum();
  void printThreshold();
  void printLayers();
  void printAllNodes();
  void printNodeCount( int index );
  void printCsvFile();
  void printYears();
  void printMonths();
  void printEndMonth();
  void printNumClasses();
  void printLowMed();
  void printMedHigh();
  //print the whole damn lot
  void printPrm();
  //print errors
  void printErrorCode( int err );

  ///STRIPPERS - Not that kind ;) .... Removes random junk
  std::string stripComment( std::string input );
  std::string stripSpaces( std::string input );

private:
  std::string      _filename;  

  ///ANN Parameters  
  std::string      _wts_file;       /// name of ANN weight file
  int              _epochs;         /// number of training epochs
  double           _learning_rate;  /// learning rate
  double           _momentum;       /// momentum
  double           _threshold;      /// threshold for ANN error
  int              _layers;         /// layers of adjustable weights
  std::vector<int> _node_count;     /// how many nodes in each layer 

  ///Training and Testing Data file
  std::string      _csv_file;       /// training and testing data file name
  
  ///Feature vector info:
  int              _years;          /// years of burned acreage, 
  int              _months;         /// months of PDSI data 
  int              _end_month;      /// end month of current year

  ///Output class info
  int              _num_classes;

  ///Fire severity parameter
  int              _low_med;  /// Corresponds to low/medium/high cutoffs
  int              _med_high;

  FILE * file_pointer; //File Pointer  
};

#endif
