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
void printInfo( Prm * paramFile );
void printHeader( );
void printTesting( int epoch, string equation, double error );
void printSummary( string equation, double error, double accuracy );
std::string formatResult( int result );
void testPrintout(  );
void usage( char ** argv );


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
