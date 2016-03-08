/*************************************************************************//**
 * @file ANN.cpp
 *
 * @brief SOURCE - ANN Tinder Main Source file.
 *
 * @mainpage Program 1 - TINDER
 *
 * @section course_section CSC 447/547
 *
 * @author Julian Brackins, Samuel Carroll, Alex Nienhueser
 *
 * @date February 24, 2016
 *
 * @par Professor:
 *         Dr. John Weiss
 *
 * @par Course:
 *         CSC 447/547 - 9:00am
 *
 * @par Location:
 *         McLaury - 313
 *
 * @section program_section Program Information
 *
 * @details
 * <a href="http://julianbrackins.me/projects/tinder/">Project Webpage</a>
 *
 * TINDER stands for Tree Intelligence Network for Determining Ember Risk and
 * is, to our knowledge, probably the first software program to ever have this
 * name. Any other similarities in name are purely coincidental and are in no
 * relation to the TINDER project and its morals or values.
 *
 * TINDER is an artificial neural network that utilizes a back-propagation
 * network to determine a given year's fire severity risk based on PDSI
 * (Palmer Drought Severity Index) data. This program is strictly for
 * educational purposes for our academic understanding of how a neural network
 * is designed and how it operates. This program in no way ensures 100% accurate
 * fire predictions and should not be held to such a standard.
 *
 * This is the first programming assignment for CSC 447/547: Artificial
 * Intelligence. The objective of this project is to get a general
 * understanding of the architecture of a neural network, and how neural nets
 * can be used to assist with real-world scenarios.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      (Linux) - make
 *
 * @par Usage:
 @verbatim
 ./ANNtrain <parameterfile>
 ./ANNtest <parameterfile>
 ./CrossValidate <parameterfile>
 @endverbatim
 *
 * It should be noted that this project has a specific directory structure, so
 * all .prm parameter files are located in their own specified prm/ directory.
 *
 * @section directory_structure Directory Structure
 @verbatim
--------------------------------------------------------------------------------


  ann-tinder/
            Makefile
            Program_Writeup.pdf
            README.md
            ANNtrain
            ANNtest
            CrossValidate
            inc/
                ANN.h
                ANNtest.h
                ANNtrain.h
                CrossValidate.h
                Csv.h
                NeuralNet.h
                Perceptron.h
                Prm.h
                Wts.h
            src/
                ANN.cpp
                ANNtest.cpp
                ANNtrain.cpp
                CrossValidate.cpp
                Csv.cpp
                NeuralNet.cpp
                Perceptron.cpp
                Prm.cpp
                Wts.cpp
            tst/
                testPerceptron.cpp
                testPrm.cpp
            prm/
                bh.prm
                nw.prm
                Parameter.prm
            wts/
                weights.wts
            csv/
               PDSI_BH_1978-2015.csv
               PDSI_NW_1998_2015.csv
            doc/
                doxy.conf


--------------------------------------------------------------------------------
 @endverbatim
 *
 * @section neural_network_info Neural Network Information
 * For this project, a neural network was implemented to classify fire season
 * severity into low, medium, and high categories. This neural network has been
 * made by using a backprop net. This backprop net consists of units that
 * process the weighted sum of input values, applying an activation function to
 * produce a specific output. For this project, a three layer neural net has
 * been implemented, with two layers of adjustable weights.
 *
 * For this project, the neural net has been trained with PDSI measurement data
 * in order to adjust the weights in the net through learning rules. After
 * a training session, the various weights from the net are dumped out to a
 * .wts file for future training or testing. The RMS (Root Mean Squared)
 * error value for each epoch of training is output for user feedback during
 * a training session.
 *
 * After training, the net can be tested to determine how viable the training
 * methods are in predicting fire severity.
 *
 * @section neural_network_questions Neural Network Questions
 * The following questions have been answered as a result of completing this
 * project:
 *
 * - <b>How well does your network train?</b>
 *    - The way that the back-propagation is implemented seems to be incorrect.
 * Additional work into how the weights are being set up in the neural net
 * in order to observe how these errors are occuring. It is believed that the
 * error gradients are being calculated incorrectly, which would lead to
 * the adjustments of weights being inaccurate.
 *
 * - <b>What is the impact of network topology (i.e., changing the number of
 * hidden layer nodes) on training?</b>
 *    - Decreasing the amount of hidden nodes tends to decrease the error rate,
 * whereas increasing the error rate would yield higher error rates.
 *
 * - <b>How well does the network generalize from training data to
 * testing data?</b>
 *    - Our network does not generalize training data to testing data well.
 * If the neural network is tested on the same data set that was used for
 * training, it naturally performs well. However, if tested on a different
 * set of data, the neural net fails to predict the fire severity. This is
 * likely due to an error with the calculations from the outputs of the
 * perceptron.
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @par Modifications and Development Timeline:
 @verbatim
 --------------------------------------------------------------------------------


 Date              Modification
 ----------------  --------------------------------------------------------------
 January  27, 2016  * Began project.
 January  30, 2016  * Set up project directory structure.
 February 03, 2016  * Prm Class started for reading/writing .prm parameter
                      files.
 February 06, 2016  * Finished basic setter methods for Prm Class.
 February 09, 2016  * Finished getter, writing and printing methods for Prm
                      Class.
 February 11, 2016  * Started work on perceptron class.
 February 21, 2016  * Set up executable outputs.
                    * Set up Perceptron class.
                    * Set up NeuralNet class.
                    * Added Prm class behaviour to validate whether or not a
                      .prm file was successfully read in.
                    * Added .csv file reading and .wts file reading.
 February 22, 2016  * Modified Perceptron behavior.
 February 23, 2016  * Documentation cleanup, Split code into .h and .cpp files.
                    * Modified readCSV to read entire csv file and return it as
                      a Linked list.
                    * Mild to moderate crying.
                    * Added readCSVEntry function to perform the
                      way readCSV previously did.
                    * Completed first stable build of neural net.
 February 24, 2016  * Error Gradiant calculations correct.
                    * Bug Fixes - Memory Leak Issues.
                    * Completed ANNtrain program.
                    * Moderate to severe crying.
                    * Completed ANNtest program.
                    * Completed CrossValidate program.


--------------------------------------------------------------------------------
 @endverbatim
 *
 *
 * @section outline Document Outline
 * The remainder of this document is the documentation of the various methods
 * and data structures used in developing this project. If for whatever reason
 * you are reading our documentation in the .pdf instead of online, PLEASE
 * go to <a href="http://julianbrackins.me/projects/tinder/">our project
 * webpage</a> because the formatting looks a thousand times better on there
 * than the crappy /LATEX-generated document...
 *
 ******************************************************************************/

#include "../inc/ANN.h"

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
 * @author Julian Brackins
 *
 * @par Description:
 * Print out training information
 *
 * @param[in] paramFile - Parameter file that has been read in.
 *
 * @returns nothing
 *
 *****************************************************************************/
void printInfo( Prm * paramFile )
{
    ///Print out the info for what file was read in.
    //Parameter File: <FILE.prm>
    //CSV Data  File: <FILE.csv>

    cout << "Parameter File: " << paramFile->getFilename( false ) << endl;
    cout << "CSV  Data File: " << paramFile->getCsvFile()         << endl;
    cout << endl;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print program Usage statements
 *
 * @returns nothing
 *
 *****************************************************************************/
void usage( char ** argv )
{
    ///Print out the usage statement for each executable.
    ///This is effectively identical in each instance, so one usage statement
    ///Will suffice.
    cout << "Usage: " << argv[0] << " <parameterfile>" << endl;
    cout << endl;
    cout << "<parameterfile> - Parameter file used for configuring net" << endl;
}
