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
#include "ANN.h"


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
