/*************************************************************************//**
* @file NeuralNet.cpp
*
* @author Julian Brackins, Samuel Carroll, Alex Nienhueser
*
* @brief SOURCE - Implementation of a Neural Network
*
******************************************************************************/

/******************************************************************************
*
* INCLUDE
*
******************************************************************************/

#include "../inc/NeuralNet.h"


/******************************************************************************
*
* NAMESPACES
*
******************************************************************************/

using namespace std;

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Add perceptron to the neural network
*
*****************************************************************************/
void NeuralNet::add_perceptron ( int nodes )
{
   int i;
   vector <Perceptron> perceptron_layer; // create a whole new layer

   for ( i = 0; i < nodes; i++ )
   {
      perceptron_layer.push_back( Perceptron ( ) ); // add all the nodes for
                                                    // that layer
   }

   percep_net.push_back ( perceptron_layer ); // add the layer to the network
}
