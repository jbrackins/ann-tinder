/*************************************************************************//**
 * @file CrossValidate.cpp
 *
 * @brief SOURCE - Artificial Neural Network - CrossValidate program file.
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
 ./CrossValidate <parameterfile>
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

#include "../inc/CrossValidate.h"

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
 * @returns 0 - Program Ends.
 *
 *****************************************************************************/
int main(int argc, char ** argv)
{
    if ( argc != 2 )
    {
        usage( argv );
        return -1;
    }

    int num_records;
    vector <bool> left_out;
    int years;
    int fin_out;
    int act_out;
    int curr_year;
    int leave_out = 0;
    int sample;
    int epoch;

    NeuralNet ANN = NeuralNet(argv[1]);

    records *head_record = new records;

    readCSV( ANN.ANN_params.getCsvFile( ), head_record );
    records *temp = head_record;
    num_records = getRecordsSize( temp );

    years = ceil (ANN.ANN_params.getMonths ( ) / 12.0 );

    for (int i = 0; i < num_records - years; i++)
        left_out.push_back(false);

    printHeader( );

    while (hasFalse (left_out ) )
    {
        ANN.connect_layers ( );

        while ( epoch < ANN.ANN_params.getEpochs ( ) )
        {
            for (curr_year = 0; curr_year < num_records - years; curr_year++ )
            {
                temp = head_record;
                if ( leave_out != curr_year )
                {
                    for ( int i = 0; i < curr_year; i++)
                        temp = temp->next;
                    ANN.set_first_layer ( temp );
                    for ( int i = 0; i < years; i++)
                        temp = temp->next;

                    ANN.set_desired_output ( temp );

                    ANN.update_output ( ); // need this
                    ANN.update_grads ( ); // update error gradiants
                    ANN.update_weights ( ); // update the weights for the neural net
                    // loop through and train
                }
            }
            epoch++;
        }

        temp = head_record;
        for ( int i = 0; i < leave_out; i++)
            temp = temp->next;

        ANN.set_first_layer ( temp );
        for (int i = 0; i < years; i++ )
            temp = temp->next;
        ANN.update_output ( );

        sample = temp -> dates; // get the year we tested

        fin_out = ANN.get_fin_out ( );
        act_out = get_actual_output ( (int)temp -> iAcres, ANN.ANN_params.getMedHigh( ),
                                      ANN.ANN_params.getLowMed ( ) );

        printCrossValidate ( sample, (int)temp -> iAcres, act_out, fin_out, 3.14);

        left_out[leave_out] = true;
        leave_out++;
        ANN.resetANN( );
        // reset ANN
    }

    //printInfo( p );

    //testPrintout();

}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print out the cross validation header.
 *
 * @returns nothing
 *
 *****************************************************************************/
void printHeader( )
{
    cout << "*-----------------------------------------------------------------*" << endl;
    cout << "| YEAR | BURNED | SEVERITY | PREDICTED | RESULT  | TRAINING ERROR |" << endl;
    cout << "*-----------------------------------------------------------------*" << endl;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print out a cross validation iteration.
 *
 * @param[in] year      - year
 * @param[in] burned    - number of acres burned in a given year
 * @param[in] severity  - actual PDSI severity based on data
 * @param[in] predicted - predicted PDSI severity based on neural network
 * @param[in] error     - training error
 *
 * @returns nothing
 *
 *****************************************************************************/
void printCrossValidate( int year, int burned, int severity, int predicted, double error )
{
    string str_severity    = formatResult(severity);
    string str_predicted   = formatResult(predicted);
    string str_result;

    ///Prints out a single line of output. This line is a given year's
    ///total number of burned acreage, the actual and predicted  PDSI severity
    ///rating, which can each be low (LOW), medium (MED),
    ///or high (HI ) fire severity. If the actual and predicted values are
    ///identical, this means that the neural net was successful in predicting
    ///a given sample. If these values do not match, then the neural network
    ///did not predict the given sample properly. The training error for the
    ///year is also output.

    //If the actual and predicted are identical,
    //This prediction was successful.
    if ( severity == predicted && predicted != 000 )
        str_result = "SUCCESS";
    else
        str_result = "FAILURE";

    //print the year's statistics
    cout << "|" << " " << setw(4) << year << " ";
    cout << "|" << " " << setw(6) << burned << " ";
    cout << "|" << "   " << str_severity    << "    ";
    cout << "|" << "   " << str_predicted   << "     ";
    cout << "|" << " " << str_result    << " ";
    cout << "|" << "    (" << setiosflags(ios::fixed) << setprecision(3)  << error;
    cout << ")     " << "|" << endl;
    cout << "*-----------------------------------------------------------------*" << endl;;

}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print out the testing summary.
 *
 * @param[in] accuracy  - percentage of samples correctly predicted
 *
 * @returns nothing
 *
 *****************************************************************************/
void printSummary( double accuracy )
{

    ///This function will print out the summary statistics of how well the
    ///neural network performed in the tests.
    cout << endl;
    cout << "Overall Accuracy: " << setprecision(1) << accuracy * 100 << "%%" << endl;

}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Format the Actual and Predicted strings so they're pretty!
 *
 * @param[in] result - A given value, either actual or predicted
 *
 * @returns "LOW" - value passed in was 100
 * @returns "MED" - value passed in was 010
 * @returns "Hi " - value passed in was 001
 * @returns "ERR" - value passed in was invalid (anything other than above)
 *
 *****************************************************************************/
string formatResult( int result )
{

    ///This function rewrites each integer value of a given result, either
    ///actual or predicted, and displays it in a readable manner.
    ///The conversions are as follows:


    ///100 = LOW
    if (result == 100 )
        return "LOW";
    ///010 = MED
    else if (result == 10 )
        return "MED";
    ///001 = HI
    else if (result == 1 )
        return "HI ";
    ///Invalid otherwise
    else
        return "ERR";

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

    double acc = .91332;
    int yr;
    double burn;
    int sev;
    int pred;
    double err;

    printHeader( );

    //verify matches work
    yr = 1999;
    burn = 123485;
    sev = 010;
    pred = 010;
    err = 0.2348239743;
    printCrossValidate( yr, burn, sev, pred, err );

    //verify non match doesn't...
    yr = 1999;
    burn = 0;
    sev = 001;
    pred = 100;
    err = 0.2348239743;
    printCrossValidate( yr, burn, sev, pred, err );

    //verify invalid...
    yr = 0;
    burn = 1000;
    sev = 000;
    pred = 000;
    err = 0.2348239743;
    printCrossValidate( yr, burn, sev, pred, err );

    printSummary( acc );
}

/**************************************************************************//**
 * @author Samuel Carroll
 *
 * @par Description:
 * Checks if we have a high, medium or low range of burned acreage
 *
 * @param burnAcre - the number of acres burned
 * @param high - the high threshold
 * @param low - the low threshold
 *
 * @returns 100 - if we have a burn acreage in the high range
 * @returns 10 - if we have a burn acreage in the medium range
 * @returns 1 - if we have a burn acreage in the low range
 *
 *****************************************************************************/
int get_actual_output ( double burnAcre, int high, int low )
{
    // set high if high burned acreage
    if ( burnAcre > high )
    {
        return 100;
    }
    // set low if low burned acreage
    else if ( burnAcre < low )
    {
        return 1;
    }
    // set mild if mild burned acreage
    else
    {
        return 10;
    }
}

/**************************************************************************//**
 * @author Samuel Carroll
 *
 * @par Description:
 * Tests if a vector has any false values in it
 *
 * @param vector<bool> chk_vector - the vector to check
 *
 * @returns true - the vector had at least one false value
 * @returns false - the vector had been set to all true
 *
 *****************************************************************************/
bool hasFalse ( std::vector<bool> chk_vector )
{
    int size = chk_vector.size ( );

    for (int i = 0; i < size; i++)
    {
        if (chk_vector[i] == false)
            return true;
    }

    return false;
}
