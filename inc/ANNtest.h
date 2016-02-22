/*************************************************************************//**
 * @file ANNtest.h
 *
 * @author Julian Brackins, Samuel Carroll, Alex Nienhueser
 *
 * @brief HEADER - Neural Network Header File
 *
 *****************************************************************************/

#ifndef _ANNTEST_H_
#define _ANNTEST_H_

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

/******************************************************************************
 *
 * PROTOTYPES
 *
 ******************************************************************************/

void printHeader( );
void printTesting( int epoch, std::string equation, double error );
void printSummary( std::string equation, double error, double accuracy );
std::string formatResult( int result );
void testPrintout(  );

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
