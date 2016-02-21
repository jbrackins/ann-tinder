/*************************************************************************//**
 * @file Perceptron.h
 *
 * @author Julian Brackins, Samuel Carroll, Alex Nienhueser
 *
 * @brief HEADER - Implementation of a basic perceptron
 *
 *****************************************************************************/

#ifndef _PERCEPTRON_H_
#define _PERCEPTRON_H_

/******************************************************************************
 *
 * INCLUDE
 *
 ******************************************************************************/

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <math.h>

/*************************************************************************//**
* @class Perceptron
*
* @author Samuel Carroll
*
* @brief Perceptron class.
*
*****************************************************************************/
class Perceptron
{
   public:
      Perceptron();
      
      void add_input ( );
      double* get_output ( );
      void update_output ( );
   private:
      vector <double*> input;
      vector <double> weights;
      double output;
      double theta;
};

 #endif
