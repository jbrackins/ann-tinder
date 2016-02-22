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
#include <string>
#include "Perceptron.h"
#include "Prm.h"
#include "CSVHeader.h"

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
      NeuralNet ( std::string param_file );
      void add_layer ( int nodes );
      void add_first_layer ( records *input_records );
      void connect_layers ( );
      void update_weights ( );
      void update_grads ( );
      void update_error_grad (Perceptron curr_node, bool inside_node,
                              double new_error_grad );

   private:
      std::vector <std::vector <Perceptron>> percep_net;
      Prm* ANN_params;
};

  #endif
