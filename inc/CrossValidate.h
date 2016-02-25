/*************************************************************************//**
 * @file CrossValidate.h
 *
 * @author Julian Brackins, Samuel Carroll, Alex Nienhueser
 *
 * @brief HEADER - Neural Network Cross Validation Header File
 *
 *****************************************************************************/

#ifndef _CROSSVALIDATE_H_
#define _CROSSVALIDATE_H_

/******************************************************************************
 *
 * INCLUDE
 *
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Prm.h"
#include "ANN.h"
#include "NeuralNet.h"
#include "Wts.h"


/******************************************************************************
 *
 * NAMESPACES
 *
 ******************************************************************************/

using namespace std;


/******************************************************************************
 *
 * PROTOTYPES
 *
 ******************************************************************************/

void printHeader( );
void printCrossValidate( int year, int burned, int severity, int predicted, double error );
void printSummary( double accuracy );
std::string formatResult( int result );
void testPrintout( );
int get_actual_output ( double burnAcre, int high, int low );
bool hasFalse ( std::vector<bool> chk_vector );

/******************************************************************************
 *
 * ENUMS
 *
 ******************************************************************************/


/******************************************************************************
 *
 * GLOBALS
 *
 ******************************************************************************/


#endif
