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
   {*/
      // add all the layers to the ANN and connect them
      int layers = ANN_params -> getLayers ( );
      for ( int i = 0; i < layers; i++ )
      {
         add_layer( ANN_params -> getNodeCount ( i ) );
      }

      connect_layers ( );
   /*}
   else
   {
      cout << "Error opening parameter file: " + param_file << endl;
      cout << "Program terminating" << endl;
      exit ( -1 );
   }*/
}

//should add a deconstructor 

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

   // if the node count is not viable quit the program
   if (nodes == -100)
   {
      cout << "Could not get layer node count, program ending" << endl;

      exit ( -1 );
   }

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
* Add first perceptron layer to the neural network
*
* @param[in] input_records - the input parameters for the ANN
*
* @todo - add the first n months of the current year
*
*****************************************************************************/
void NeuralNet::set_first_layer ( records * input_records )
{
   vector <Perceptron> input_layer;
   int i = 0;
   int input_nodes = ANN_params -> getNodeCount( 0 );

   // need to add n months of current year

   while ( input_records->next != NULL && i < input_nodes)
   {
      input_layer[i].set_output ( input_records->burnedAcres );
      i++;

      for(int indexY = 0; indexY < 12 && i < input_nodes; indexY++)
      {
         input_layer[i].set_output ( input_records->months[indexY] );
         i++;
      }

      input_records = input_records->next;
   }

   percep_net.push_back ( input_layer );
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

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Set the weights for the ANN
*
* @param weights - an array holding the set of weights of the ANN
*
******************************************************************************/
void NeuralNet::set_weights ( double weights [ ] )
{
   int layers = percep_net.size ( );
   int lft_nodes = 0;
   int nodes = 0;
   int weights_loc = 0;

   for ( int i = 1; i < layers; i++ )
   {
      lft_nodes = percep_net [ i - 1].size ( );
      nodes = percep_net [ i ].size ( );

      for (int j = 0; j < nodes; j++ )
         for (int k = 0; k < lft_nodes; k++)
         {
            percep_net[i][j].set_weight ( weights[ weights_loc ], k );
            weights_loc++;
         }
   }
}

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Set the weights for the ANN
*
* @param weights - an array holding the set of weights of the ANN
*
******************************************************************************/
double NeuralNet::get_error ( )
{
   int layers = percep_net.size ( );
   int nodes = percep_net [ layers - 1 ].size ( );
   double error = 0.0;
   double sum = 0.0;

   for ( int i = 0; i < nodes; i++ )
   {
      sum = percep_net [ layers - 1 ][ i ].get_desired_output( ) -
               *(percep_net [ layers - 1 ][ i ].get_output ( ));
      error += sum * sum;
   }

   return error;
}

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Returns the number of nodes in the layer specified in index
*
* @params [in] index - which layer that we want to get the number of nodes of
*
* @returns layer_nodes - number of nodes in the specified layer
*
******************************************************************************/
int NeuralNet::get_layer_nodes ( int index )
{
   return ANN_params -> getLayers ( );
}

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Returns the weights file name
*
* @returns string - name of the weights file
*
******************************************************************************/
string NeuralNet::get_weights_file ( )
{
   return ANN_params -> getWtsFile ( );
}

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Returns the CSV file to use for input
*
* @returns string - returns a string that is the CSV file name
*
*****************************************************************************/
string NeuralNet::getCsvFile ( )
{
   string CsvFileName = ANN_params -> getCsvFile ( );

   return ( CsvFileName );
}
