/*************************************************************************//**
 * @file Csv.h
 *
 * @author Julian Brackins, Samuel Carroll, Alex Nienhueser
 *
 *
 * @brief HEADER - Methods for reading in Csv File information
 *
 *****************************************************************************/

#ifndef _CSV_H_
#define _CSV_H_

/******************************************************************************
 *
 * INCLUDE
 *
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <list>
#include "../inc/Csv.h"

/******************************************************************************
 *
 * STRUCTS
 *
 ******************************************************************************/

/**************************************************************************//**
 * @brief Data structure for csv information.
 *
 * <DESCRIPTION GOES HERE>
 *
 *****************************************************************************/

struct records
{
	double dates;
	double burnedAcres;
	double months[12];
	records *next;
};

/******************************************************************************
 *
 * PROTOTYPES
 *
 ******************************************************************************/

records *readCSV(std::string filename);
records *readCSVEntry( std::string filename, int predictYear, int prevYears );
void split_line( std::string& line, std::string delim, std::list<std::string>& values );
void normalize( records *data );

#endif
