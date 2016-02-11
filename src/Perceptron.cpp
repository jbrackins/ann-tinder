#include <vector>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

class perceptron
{
   public:
      perceptron();
      void add_input ( );
      double* get_output ( );
      void update_output ( );
   private:
      vector <double*> input;
      vector <double> weights;
      double* output;
      double theata;
};

perceptron::perceptron ( void )
{
   double rand_greater = rand( ) % 100000000;
   double rand_smaller = rand( ) % ( (int) rand_greater - 1 );


   theata = rand_smaller / rand_greater;
}

void perceptron::add_input (/*input type here?*/ )
{
   input.push_back(&(3.14)/* add the pointer to the input layer's output*/);

   

   update_output ( );
}

double* perceptron::get_output ( )
{
   return output;
}

void perceptron::update_output ( )
{
   int num_input = input.size ( );
   double x_sub_j = 0;

   for ( int i = 0; i < num_input; i++)
   {
      x_sub_j += ((*(input[i])) * weights [ i ] - theata);
   }

   *output = 1.0 / ( 1 + exp( x_sub_j );
}
