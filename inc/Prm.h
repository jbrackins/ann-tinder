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
  
  std::string getFilename();
  int ReadPrm( std::string filename );
  
  int setWtsFile( std::string input );
  int setEpochs( std:: string input );
  int setLearningRate( std:: string input );
  int setMomentum( std:: string input );
  int setThreshold( std:: string input );
  int setLayers( std:: string input );
  int setNodeCount( std:: string input );
  int setCsvFile( std:: string input );
  int setYears( std:: string input );
  int setMonths( std:: string input );
  int setEndMonth( std:: string input );
  int setNumClasses( std:: string input );
  int setLowMed( std:: string input );
  int setMedHigh( std:: string input );

  void printErrorCode( int err );


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
public:

  
  
};

#endif
