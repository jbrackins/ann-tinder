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
// don't include CSVHeader.h as it's included with NeuralNet.h

/******************************************************************************
 *
 * PROTOTYPES
 *
 ******************************************************************************/

void printTraining( int epoch, std::string equation, double error );
void testPrintout();

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
