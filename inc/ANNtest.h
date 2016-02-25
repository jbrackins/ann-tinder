/*************************************************************************//**
 * @file ANNtest.h
 *
 * @author Julian Brackins, Samuel Carroll, Alex Nienhueser
 *
 * @brief HEADER - Neural Network Testing Header File
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
#include "NeuralNet.h"
#include "Wts.h"

/******************************************************************************
 *
 * PROTOTYPES
 *
 ******************************************************************************/

void printHeader( );
int printTesting( int sample, int actual, int predicted );
void printSummary( double lowAcc, double medAcc, double hiAcc );
std::string formatResult( int result );
void testPrintout(  );
int get_actual_output ( double burnAcre, int high, int low );

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
