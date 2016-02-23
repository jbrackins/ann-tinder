/*************************************************************************//**
 * @file ANNtrain.cpp
 *
 * @brief SOURCE - Artificial Neural Network - ANNtrain Tester program file. 
 *
 * @mainpage Program 1 - TINDER
 *
 * @section course_section CSC 447/547
 *
 * @author Julian Brackins, Samuel Carroll, Alex Nienhueser
 *
 * @date January 29, 2016
 *
 * @par Professor:
 *         Dr. John Weiss
 *
 * @par Course:
 *         CSC 447/546 - 9:00am
 *
 * @par Location:
 *         McLaury - 313
 *
 * @section program_section Program Information
 *
 * @details
 * Program Info
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      (Linux) - make
 *
 * @par Usage:
 @verbatim
 ./ANNtrain <parameterfile>
 @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 *
 ******************************************************************************/

/******************************************************************************
 *
 * INCLUDE
 *
 ******************************************************************************/

#include "../inc/ANNtrain.h"

/******************************************************************************
 *
 * NAMESPACES
 *
 ******************************************************************************/

using namespace std;

/******************************************************************************
 *
 * GLOBALS
 *
 ******************************************************************************/

/**************************************************************************//**
 * @author Julian Brackins, Samuel Carroll, Alex Nienhueser
 *
 * @par Description:
 * This is the starting point to the program.  
 *
 * @param[in] argc - the number of arguments from the command prompt.
 * @param[in] argv - a 2d array of characters containing the arguments.
 *
 * @returns 0 - Program Ends Gracefully.
 * @returns -1 - Program Ends because YOU GOOFED UP
 *
 *****************************************************************************/
int main(int argc, char ** argv)
{
  int num_samples = 0;
  double error_sum = 0;
  double rms = 0.0;

  if( argc != 2 )
  {
  	usage( argv );
  	return -1;
  }  

  //Prm * p = new Prm( argv[1] );
  // open the Neural Net with the given parameter file
  NeuralNet ANN(argv[1]);

  //Read in a .prm file  
  //p->readPrm();

  //create the records template so we can read in the CSV file
  records *head_record = new records( );

  // strat loop
  //open and read the specified records
  ///todo make sure we can read in an entire CSV file
  /*head_record = readCSV(ANN.getCsvFile(), 2015, 30);*/
  records *temp = head_record;
  
  // set the csv file input to the neural net input layer
  ANN.set_first_layer ( temp );

  // open and set weights values (if present)
  double weights [ 1000 ] = { -1000 }; // set value outside acceptable weight range
  // make sure we can read weights file from another cpp
  //readWeights (ANN.get_weights_file ( ), weights, 1000 );
  ANN.set_weights ( weights );

  // run the neural net
  ANN.connect_layers ( ); // connects and updates output of perceptrons
  // should add to neural net get output for output nodes;
  ANN.update_grads ( ); // update error gradiants
  ANN.update_weights ( ); // update the weights for the neural net

  // calculate the error every year based on the sum of the input expect vs input actual
  error_sum = ANN.get_error ( );

  // sum all error of the inputs together
  num_samples = ANN.get_layer_nodes ( 0 ); // get number of samples used

  // find the Root squared error from this sum
  rms = 1.0 / num_samples * error_sum;
  rms = sqrt(rms);

  // print the Training for the epoch and repeat for every year in the csv file

  // after we have all the training done, write the weights file
  // add a get weights function


  //printInfo( p );

  testPrintout();

}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print out a training iteration.
 *
 * @param[in] epoch     - Epoch of a given training iteration
 * @param[in] equation  - error equation used for training
 * @param[in] error     - error value
 *
 * @returns nothing
 *
 *****************************************************************************/
void printTraining( int epoch, string equation, double error )
{
  
  ///Print out a single iteration of the training execution. For each epoch, 
  ///The error value is out displayed. A successful neural network should have 
  ///a decreasing error value with each iteration.
  cout << "Epoch" << setw(7) << epoch;
  cout << ": " << equation << " error = ";
  cout << setiosflags(ios::fixed) << setprecision(3)  << error << endl; 

}


/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Test the output of our program
 *
 * @returns nothing
 *
 *****************************************************************************/
void testPrintout(  )
{
  int e;
  string eq = "RMS";
  double err;

  srand (time(NULL));


  for( e = 0; e < 1000; e+=10 )
  {
	err = (double)rand() / RAND_MAX;
    err = err * (1.00 - 0.00);
    printTraining( e, eq, err );
  }
}

