/*************************************************************************//**
 * @file Perceptron.cpp
 *
 * @author Julian Brackins, Samuel Carroll, Alex Nienhueser
 *
 * @brief SOURCE - Implementation of a basic Perceptron
 *
 ******************************************************************************/

/******************************************************************************
 *
 * INCLUDE
 *
 ******************************************************************************/

#include "../inc/Perceptron.h"

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
 * Perceptron Constructor
 *
 *****************************************************************************/
Perceptron::Perceptron ( void )
{
   // Randomly generate a theta thershold for each perceptron, in the range
   // of 0 to 1 (from Artificial Intelligence Illuminated page 303)
   double rand_greater = rand( ) % 100000000;
   double rand_smaller = rand( ) % ( (int) rand_greater - 1 );


   theta = rand_smaller / rand_greater;
}

/**************************************************************************//**
 * @author Samuel Carroll
 *
 * @par Description:
 * Perceptron Destructor
 *
 *****************************************************************************/
Perceptron::~Perceptron ( )
{
   // make sure that input and weight vectors are clear
}

/**************************************************************************//**
 * @author Samuel Carroll
 *
 * @par Description:
 * Add Input Function.
 *
 * @param[in] input - pointer to a double that is the new input for the node
 *
 *****************************************************************************/
void Perceptron::add_input ( double* new_input )
{
   double rand_greater = rand( ) % 100000000;
   double rand_smaller = rand( ) % ( (int) rand_greater );

   // Add a pointer to the output of another perceptron, a pointer is used so
   // we don't need to reconnect the all the perceptrons if one input is
   // updated
   input.push_back(new_input);
   weights.push_back( (rand_smaller / rand_greater) - 0.5);

   update_output ( );
}

/**************************************************************************//**
 * @author Samuel Carroll
 *
 * @par Description:
 * Sets the error gradiant
 *
 * @param[in] new_error_grad - the new error gradiant value
 *
 *****************************************************************************/
void Perceptron::set_error_grad ( double new_error_grad )
{
   error_grad = new_error_grad;
}

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Gets the error gradiant
*
*****************************************************************************/
double Perceptron::get_error_grad ( )
{
   return error_grad;
}

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Sets the desired output value
*
* @param[in] new_desired - the new desired output value 
*
*****************************************************************************/
void Perceptron::set_desired_output ( double new_desired )
{
   desired_output = new_desired;
}

double Perceptron::get_desired_output ( )
{
   return desired_output;
}

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Sets the output value for the input layer of perceptrons
*
* @param[in] new_output - the new output for the input layer of the ANN
*
*****************************************************************************/
void Perceptron::set_output ( double new_output )
{
   output = new_output;
}

/**************************************************************************//**
 * @author Samuel Carroll
 *
 * @par Description:
 * Get Output Function.
 *
 * @returns double* - return pointer to the output
 *****************************************************************************/
double* Perceptron::get_output ( )
{
   // Return a pointer to the output of a given perceptron, used for connecting
   // the ANN layers together
   return &output;
}

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Sets the weight for a specific input node
*
******************************************************************************/
void Perceptron::set_weight (double new_weight, int index)
{
   weights[index] = new_weight;
}

/**************************************************************************//**
* @author Samuel Carroll
*
* @par Description:
* Gets the weight for a specific input node
*
******************************************************************************/
double Perceptron::get_weight (int index)
{
   return weights[index];
}

/**************************************************************************//**
 * @author Samuel Carroll
 *
 * @par Description:
 * Update Output Function.
 *
 *****************************************************************************/
void Perceptron::update_output ( )
{
   // Get the number of inputs coming into a perceptron to feed into our
   // sigmoid function
   int num_input = input.size ( );
   double x_sub_j = 0;

   // For every input adjust the xj to calculate the sigmoid function of the
   // perceptron
   for ( int i = 0; i < num_input; i++)
   {
      x_sub_j += ((*(input[i])) * weights [ i ] - theta);
   }

   // actually find the output of the perceptron
   output = 1.0 / ( 1 + exp( x_sub_j ));

   // To get a true range of 0 to 1 as our output we will need to round up or
   // down if we are within a certain thershold of 0 or 1. See Artificial
   // Intelligence Illuminated page 303 for reasons why.
   if (output > 0.95)
      output = 1;
   else if (output < 0.05)
      output = 0;
}
