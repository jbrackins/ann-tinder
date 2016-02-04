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
  int setFeatureVector( std:: string input );
  int setNumClasses( std:: string input );
  int setFireSeverity( std:: string input );

  void printErrorCode( int err );

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
  std::vector<int> _feature_vector; /// feature vector info:
                                    /// years of burned acreage, 
                                    /// months of PDSI data 
                                    /// end month of current year

  ///Output class info
  int              _num_classes;

  ///Fire severity parameter
  std::vector<int> _fire_severity;  /// Corresponds to low/medium/high cutoffs

public:

  
  
};

#endif
