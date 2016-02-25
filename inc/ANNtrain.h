/*************************************************************************//**
 * @file ANNtrain.h
 *
 * @author Julian Brackins, Samuel Carroll, Alex Nienhueser
 *
 * @brief HEADER - Neural Network Training Header File
 *
 *****************************************************************************/

#ifndef _ANNTRAIN_H_
#define _ANNTRAIN_H_

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
// don't include CSVHeader.h as it's included with NeuralNet.h

/******************************************************************************
 *
 * PROTOTYPES
 *
 ******************************************************************************/

void printTraining( int epoch, std::string equation, double error );
void testPrintout();
bool isTrue ( std::vector <bool> start_here, int vec_size );
int getStart ( std::vector <bool> start_here, int months, int num_recs );

/******************************************************************************
 *
 * STRUCTS
 *
 ******************************************************************************/

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
