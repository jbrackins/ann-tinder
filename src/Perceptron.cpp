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

}

/**************************************************************************//**
 * @author Samuel Carroll
 *
 * @par Description:
 * Add Input Function.
 *
 * @param[in] input -
 *
 *****************************************************************************/
void Perceptron::add_input (/*input type here?*/ )
{
   input.push_back(&(3.14)/* add the pointer to the input layer's output*/);

   update_output ( );
}

/**************************************************************************//**
 * @author Samuel Carroll
 *
 * @par Description:
 * Get Output Function.
 *
 * @returns double - 
 *****************************************************************************/
double Perceptron::get_output ( )
{
   return output;
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
   int num_input = input.size ( );
   double x_sub_j = 0;

   for ( int i = 0; i < num_input; i++)
   {
      x_sub_j += ((*(input[i])) * weights [ i ] - theta);
   }

   output = 1.0 / ( 1 + exp( x_sub_j );
}
