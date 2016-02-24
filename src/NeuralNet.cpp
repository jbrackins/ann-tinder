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

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* NeuralNet Constructor
*
*****************************************************************************/
using namespace std;

NeuralNet::NeuralNet ( string param_file )
{
   ANN_params = new Prm ( param_file );
   ANN_params -> readPrm ( );

   /*if (ANN_params -> valid ( ))
   {*/
      // add all the layers to the ANN and connect them
      int layers = ANN_params -> getLayers ( );
      for ( int i = 0; i <= layers; i++ )
      {
         add_layer( ANN_params -> getNodeCount ( i ) );
      }

   /*}
   else
   {
      cout << "Error opening parameter file: " + param_file << endl;
      cout << "Program terminating" << endl;
      exit ( -1 );
   }*/
}

/**************************************************************************//**
* @author Julian Brackins
*
* @par Description:
* NeuralNet Destructor
*
*****************************************************************************/
NeuralNet::~NeuralNet()
{
   if ( ANN_params != NULL)
      delete ANN_params;
}


/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Add perceptron layer to the neural network
*
* @param[in] nodes - number of nodes in perceptron layer
*
* @return none
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
   int i = 0;
   int input_nodes = ANN_params -> getNodeCount( 0 );

   // need to add n months of current year

   while ( input_records->next != NULL && i < input_nodes)
   {
      percep_net[0][i].set_output ( input_records->burnedAcres );
      i++;

      for(int indexY = 0; indexY < 12 && i < input_nodes; indexY++)
      {
         percep_net[0][i].set_output ( input_records->months[indexY] );
         i++;
      }

      input_records = input_records->next;
   }

}

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Updates the output of each of the perceptrons in the Neural Net
*
*****************************************************************************/
void NeuralNet::update_output ( )
{
   int layers = percep_net.size( );
   int nodes;

   for (int i = 1; i < layers; i++)
   {
      nodes = percep_net[i].size ( );

      for (int j = 0; j < nodes; j++)
      {
         percep_net[i][j].update_output ( );
      }
   }

}

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Add desired output for the neural net based on the burned acreage
*
* @param[in] input_records - the input parameters for the ANN
*
*****************************************************************************/
void NeuralNet::set_desired_output ( records *input_records )
{
   double burnage = input_records -> burnedAcres;
   int layers = percep_net.size ( );

   cout << burnage << endl;
   // set high if high burned acreage
   if ( burnage > 0.666666 )
   {
      percep_net [ layers - 1 ][ 0 ].set_desired_output ( 1.0 );
      percep_net [ layers - 1 ][ 1 ].set_desired_output ( 0.0 );
      percep_net [ layers - 1 ][ 2 ].set_desired_output ( 0.0 );
   }
   // set low if low burned acreage
   else if ( burnage < 0.333333 )
   {
      percep_net [ layers - 1 ][ 0 ].set_desired_output ( 0.0 );
      percep_net [ layers - 1 ][ 1 ].set_desired_output ( 0.0 );
      percep_net [ layers - 1 ][ 2 ].set_desired_output ( 1.0 );
   }
   // set mild if mild burned acreage
   else
   {
      percep_net [ layers - 1 ][ 0 ].set_desired_output ( 0.0 );
      percep_net [ layers - 1 ][ 1 ].set_desired_output ( 1.0 );
      percep_net [ layers - 1 ][ 2 ].set_desired_output ( 0.0 );
   }
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
*
******************************************************************************/
void NeuralNet::update_weights( )
{
   int layers = percep_net.size ( );
   int curr_layer;
   int next_layer_size;
   int nodes;
   double new_weight;

   cout << "updating the weights function" << endl;

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
      new_error_grad = percep_net[curr_layer][i].get_desired_output ( ) -
                       *(percep_net[curr_layer][i].get_output ( ));
      update_error_grad ( curr_layer, i, false, new_error_grad );
      cout << "set EG of node [" << curr_layer << "]["<<i<<"] to " << percep_net[curr_layer][i].get_error_grad ( ) << endl;
   }

   for (curr_layer = layers - 2; curr_layer > 0; curr_layer--)
   {
      sum = 0;
      nodes = percep_net[curr_layer].size( );
      next_layer_size = percep_net[curr_layer + 1].size( );
      for (int j = 0; j < nodes; j++)
      {
         for ( int k = 0; k < next_layer_size; k++ )
         {
            cout << "Curr weight is " << percep_net[curr_layer + 1][k].get_weight ( j )
                 << "\tcurr EG is " << percep_net[curr_layer + 1][k].get_error_grad ( ) << endl;
            sum += percep_net[curr_layer + 1][k].get_weight ( j ) *
                   percep_net[curr_layer + 1][k].get_error_grad ( );
         }

         cout << "sum = " << sum << endl;
         new_error_grad = *(percep_net[curr_layer][j].get_output( )) *
                          (1 - *(percep_net[curr_layer][j].get_output ( ))) *
                          sum;

         update_error_grad (curr_layer, j, true, new_error_grad);
      }
   }

}

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Update the error gradiant for a given perceptron in the ANN
*
* @param[in] layer          - current node layer
* @param[in] node           - node position in layer
* @param[in] inside_node    - inside node
* @param[in] new_error_grad - new error gradiant to be updated.
*
******************************************************************************/
void NeuralNet::update_error_grad (int layer, int node, bool inside_node,
                                   double new_error_grad )
{
   double error_grad;
   double output;

   if ( inside_node == true )
   {
      percep_net[layer][node].set_error_grad(new_error_grad);
   }
   else
   {
      output = *(percep_net[layer][node].get_output( ));

      error_grad = output * (1 - output) * new_error_grad;
      percep_net[layer][node].set_error_grad( error_grad );
      cout << percep_net[layer][node].get_error_grad ( )<< endl;
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
      {
         for (int k = 0; k < lft_nodes; k++)
         {
            if ( weights_loc < 10000 )
            {
               percep_net[i][j].set_weight ( weights[ weights_loc ], k );
               weights_loc++;
            }
         }
         //percep_net[i][j].set_theta ( weights [ weights_loc ] );
         //weights_loc++;
      }
   }
}

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Get the weights for the ANN
*
* @param weights - an array to hold the set of weights of the ANN
* @param size - the size of the weights array
*
******************************************************************************/
void NeuralNet::get_weights ( double weights [ ], int size )
{
   int layers = percep_net.size ( );
   int lft_nodes;
   int nodes;
   int weights_loc = 0;

   //cout << "HI" << endl;

   for ( int i = 1; i < layers; i++ )
   {
      lft_nodes = percep_net [ i - 1].size ( );
      nodes = percep_net [ i ].size ( );

      for (int j = 0; j < nodes; j++ )
      {
         for ( int k = 0; k < lft_nodes; k++ )
         {
            if ( weights_loc < size )
               weights[weights_loc] = percep_net[i][j].get_weight ( k );
            else
            {
               cout << "Weights array too small make it larger" << endl;
               cout << "Program ending!";
               exit ( -1 );
            }
            weights_loc++;
         }
         //weights[weights_loc] = percep_net[i][j].get_theta ( );
         //cout << "Theta from " << i << " " <<  j << " has theta " << weights[weights_loc] << endl;
         //weights_loc++;
      }
   }
}

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Get the error value
*
* @return error - error value
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
   return ( ANN_params -> getCsvFile ( ) );
}

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Returns the CSV file to use for input
*
* @returns nodeCount - integer with the number of weights in the ANN 
*
*****************************************************************************/
int NeuralNet::getNetSize ( )
{
   int weightCount = 0;
   int lft_nodes;
   int rght_nodes;
   int layers = percep_net.size( );

   for ( int i = 0; i < layers - 1; i++ )
   {
      lft_nodes = percep_net [ i ].size ( );
      rght_nodes = percep_net [ i + 1 ].size ( );
      weightCount += lft_nodes * rght_nodes;
   }

   return weightCount;
}
