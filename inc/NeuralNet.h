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
      void add_layer ( int nodes );
      void connect_layers ( );
      void update_weights ( );
      void update_error_grad (Perceptron curr_node, bool inside_node );

   private:
      std::vector <std::vector <Perceptron>> percep_net;
};

  #endif
