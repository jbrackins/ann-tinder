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

NeuralNet::NeuralNet ( string param_file )
{
   ANN_params = new Prm ( param_file );
   ANN_params -> readPrm ( );

   /*if (ANN_params -> valid ( ))
   {
      
   }
   else
   {
      cout << "Error opening parameter file: " + param_file << endl;
      cout << "Program terminating" << endl;
      exit ( 2 );
   }*/
}

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

/**************************************************************************//**
* @author Samuel Carroll & Alex Nienhueser
*
* @par Description:
* Update the weights in the ANN
******************************************************************************/
void NeuralNet::update_weights( )
{
   int layers = percep_net.size ( );
   int curr_layer;
   int next_layer_size;
   int nodes;
   double new_weight;

   curr_layer = layers - 2;

   for( int i = curr_layer; i >= 0; i-- )
   {
      nodes = percep_net[curr_layer].size( );
      next_layer_size = percep_net[curr_layer + 1].size ( );
      for ( int j = 0; j < nodes; j++ )
      {
         for ( int k = 0; k < next_layer_size; k++ )
         {
            new_weight = percep_net[i + 1][k].get_weight ( j );
            new_weight += ANN_params -> getLearningRate() *
                          *(percep_net[i][j].get_output ( )) * 
                          percep_net[i][k].get_error_grad ( );
            percep_net[i + 1][k].set_weight(new_weight, j);
         }
      }
   }
}

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Update all the error gradiants in the ANN
*
******************************************************************************/
void NeuralNet::update_grads ( )
{
   int layers = percep_net.size ( );
   int next_layer_size;
   int curr_layer;
   int nodes;
   double new_error_grad;
   double sum;

   curr_layer = layers - 1;
   nodes = percep_net[curr_layer].size( );
   for (int i = 0; i < nodes; i++)
   {
      update_error_grad ( percep_net[curr_layer][i], false, 0 );
   }

   for (curr_layer = layers - 2; curr_layer > 0; curr_layer--)
   {
      sum = 0;
      nodes = percep_net[curr_layer].size( );
      next_layer_size = percep_net[curr_layer + 1].size( );
      for (int j = 0; j < nodes; j++)
      {
         for ( int k = 0; k < next_layer_size; k++ )
            sum += percep_net[curr_layer + 1][k].get_weight ( j ) *
                   percep_net[curr_layer + 1][k].get_error_grad ( );

         new_error_grad = *(percep_net[curr_layer][j].get_output( )) *
                          (1 - *(percep_net[curr_layer][j].get_output ( ))) *
                          sum;

         update_error_grad (percep_net[curr_layer][j], true, new_error_grad);
      }
   }

}

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Update the error gradiant for a given perceptron in the ANN
*
******************************************************************************/
void NeuralNet::update_error_grad (Perceptron curr_node, bool inside_node,
                                   double new_error_grad )
{
   double difference;

   if ( inside_node == true )
   {
      curr_node.set_error_grad(new_error_grad);
   }
   else
   {
      difference = curr_node.get_desired_output( ) - *(curr_node.get_output( ));
      new_error_grad = *(curr_node.get_output( ));
      new_error_grad *= (1 - *(curr_node.get_output( ))) * difference;
      curr_node.set_error_grad( new_error_grad );
   }

}
