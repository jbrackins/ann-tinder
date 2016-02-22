/*************************************************************************//**
* @file NeuralNet.h
*
* @author Julian Brackins, Samuel Carroll, Alex Nienhueser
*
* @brief HEADER - Implementation of a Neural Network
*
*****************************************************************************/

#ifndef _NEURALNET_H_
#define _NEURALNET_H_

/******************************************************************************
*
* INCLUDE
*
******************************************************************************/
#include <vector>
#include <iostream>
#include "Perceptron.h"

/*************************************************************************//**
* @class Neural Net
*
* @author Samuel Carroll
*
* @brief Neural Net class.
*
*****************************************************************************/
class NeuralNet
{
   public:
      void add_perceptron ( );

   private:
      vector <vector <perceptron>> percep_net;
};

  #endif
