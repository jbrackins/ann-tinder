/*************************************************************************//**
* @file Weights.h
*
* @author Julian Brackins, Samuel Carroll, Alex Nienhueser
*
* @brief HEADER - Methods for reading in and writing Wts File information
*
*****************************************************************************/

#ifndef _WTS_H_
#define _WTS_H_

/******************************************************************************
*
* INCLUDE
*
******************************************************************************/

#include <iostream>
#include <list>
#include <string>
#include <fstream>

/******************************************************************************
 *
 * PROTOTYPES
 *
 ******************************************************************************/

bool setWeights(  std::string fileName, double weights[], int arraySize );
bool readWeights( std::string fileName, double weights[], int arraySize );

#endif
