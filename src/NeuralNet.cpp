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
* Add perceptron layer to the neural network
*
*****************************************************************************/
void NeuralNet::add_layer ( int nodes )
{
   // Use i to count the perceptrons in the layer and a temporary vector of
   // perceptrons to add to the ANN
   int i;
   vector <Perceptron> perceptron_layer;

   // Add all the perceptrons for a given layer
   for ( i = 0; i < nodes; i++ )
   {
      perceptron_layer.push_back( Perceptron ( ) );
   }

   // Add the new layer of perceptrons to the ANN
   percep_net.push_back ( perceptron_layer );
}

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Connect all the layers in the Neural network to one another
*
******************************************************************************/
void NeuralNet::connect_layers( )
{
   int layers = percep_net.size( );
   int left_layer_nodes;
   int right_layer_nodes;

   // Connect all the perceptrons in the layers together
   for ( int i = 0; i < ( layers - 1 ); i++ )
   {
      // Get all the perceptrons in the left and right sides of the ANN so we
      // can connect them together
      left_layer_nodes = percep_net [i].size ( );
      right_layer_nodes = percep_net [i + 1].size ( );

      // For each perceptron on the right side attach all the perceptrons on
      // the left side
      for ( int rt = 0; rt < right_layer_nodes; rt++ )
         for ( int lft = 0; lft < left_layer_nodes; lft++ )
         {
            percep_net [i + 1][rt].add_input(percep_net [i][lft].get_output( ));
         }
   }
}
