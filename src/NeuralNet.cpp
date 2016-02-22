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
void NeuralNet::add_layer ( int nodes )
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

   for ( int i = 0; i < ( layers - 1 ); i++ )
   {
      left_layer_nodes = percep_net [i].size ( );
      right_layer_nodes = percep_net [i + 1].size ( );

      for ( int rt = 0; rt < right_layer_nodes; rt++ )
         for ( int lft = 0; lft < left_layer_nodes; lft++ )
         {
            percep_net [i + 1][rt].add_input(percep_net [i][lft].get_output( ));
         }
   }
}
