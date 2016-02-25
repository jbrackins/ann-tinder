/*************************************************************************//**
 * @file Csv.cpp
 *
 * @brief SOURCE - Methods for reading in Csv File information
 *
 ******************************************************************************/

/******************************************************************************
 *
 * INCLUDE
 *
 ******************************************************************************/

#include "../inc/Csv.h"

/******************************************************************************
 *
 * NAMESPACES
 *
 ******************************************************************************/

using namespace std;

/**************************************************************************//**
 * @author Alex Nienhueser
 *
 * @par Description:
 * Read in and parse the csv file for a specific entry.
 *
 * @param[in] filename - csv file name
 * @param[in] predictYear - predicted year
 * @param[in] prevYears - previous years to be predicted
 * @param[in] *data    - head pointer for records struct.
 *
 *****************************************************************************/

records *readCSVEntry(string filename, int predictYear, int prevYears, records *data)
{
  ifstream file ( "csv/"+filename ); // declare file stream
  string value; 
  list<string> values;

  //Skip first two lines
  getline ( file, value );
  getline ( file, value );
  
  //Fill list with string in csv
  while ( file.good() )
  {
		
    getline ( file, value, ',' ); // read a string until next comma
    if (value.find('\n') != string::npos) 
    {
      split_line(value, "\n", values);
    } 
    else
    {
      values.push_back(value);
    }
  }

  int indexX = 0;
 
  //Create list iterator
  list<string>::const_iterator it = values.begin();
  records *temp = data;
  records *prev = temp;
  
  //Loop through list
  for(indexX = 0; predictYear >= strtod(values.front().c_str(), NULL) &&
                !values.empty(); indexX++)
  {
    if(predictYear-(strtod(values.front().c_str(), NULL)) <= prevYears)
    {
        temp->dates = strtod(values.front().c_str(), NULL);
        values.pop_front();
        temp->burnedAcres = strtod(values.front().c_str(), NULL);
        values.pop_front();

        //Fill Months
        for(int indexY = 0; indexY < 12; indexY++)
        {
          temp->months[indexY] = strtod(values.front().c_str(), NULL);
          values.pop_front();
        }
        prev = temp;
        temp->next = new records;
        temp = temp->next;
	
        }
        else
        {

          for(int indexZ = 0; indexZ < 14; indexZ++)
            values.pop_front();
        }
    }
    delete prev->next;
    
    //Normalize the data read in from the file
    normalize(data);

    //Close the file
    file.close();

    return data;
}

/**************************************************************************//**
 * @author Alex Nienhueser
 *
 * @par Description:
 * Read In the CSV File
 *
 * @param[in] filename - csv file name
 * @param[in] *data    - head pointer for records struct.
 *
 * @returns pointer to the linked list of records read in from csv file.
 *
 *****************************************************************************/
records *readCSV(string filename, records *data)
{
  ifstream file ( "csv/"+filename ); // declare file stream: 
  string value;
  list<string> values;

  //Skip first two lines
  getline ( file, value );
  getline ( file, value );

  //Fill list with string in csv
  while ( file.good() )
  {
    getline ( file, value, ',' ); // read a string until next comma
    if (value.find('\n') != string::npos) 
    {
      split_line(value, "\n", values);
    } 
    else
    {
      values.push_back(value);
    }
  }
  int indexX = 0;

  //Create list iterator 
  list<string>::const_iterator it = values.begin();

  records *temp = data;
  records *prev = temp;

  //Loop through list
  for(indexX = 0; !values.empty(); indexX++)
  {
    temp->dates = strtod(values.front().c_str(), NULL);
    values.pop_front();
    temp->burnedAcres = strtod(values.front().c_str(), NULL);
    temp->iAcres = temp->burnedAcres;
    values.pop_front();

    //Fill Months		
    for(int indexY = 0; indexY < 12; indexY++)
    {
      temp->months[indexY] = strtod(values.front().c_str(), NULL);
      values.pop_front();
    }

    prev = temp;
    temp->next = new records;
    temp = temp->next;	

  }

  delete prev->next;
  prev->next = NULL;

  //Normalize the data read in from the file
  normalize(data);

  //Close the file
  file.close();
  
  return data;
}

/**************************************************************************//**
 * @author Alex Nienhueser
 *
 * @par Description:
 * Split a line read in from csv file by a specified delimeter.
 *
 * @param[in] line - line to be split
 * @param[in] delim - delimeter string
 * @param[in] values - list of values
 *
 *****************************************************************************/
void split_line(string& line, string delim, list<string>& values)
{
    size_t pos = 0;
    while ((pos = line.find(delim, (pos + 1))) != string::npos) {
        string p = line.substr(0, pos);
        values.push_back(p);
        line = line.substr(pos + 1);
    }

    if (!line.empty()) {
        values.push_back(line);
    }
}

/**************************************************************************//**
 * @author Alex Nienhueser
 *
 * @par Description:
 * Normalization Function.
 *
 * @param[in] *data - head pointer for records struct.
 *
 *****************************************************************************/
void normalize(records *data)
{
  records *temp = data;
  double minBurnedAcres = temp->burnedAcres;
  double minMonths = temp->months[0];
  double maxBurnedAcres = temp->burnedAcres;
  double maxMonths = temp->months[0];

  while(temp != NULL)
  {
    //Check for highest/lowest burnedAcres
    if(minBurnedAcres > temp->burnedAcres)
      minBurnedAcres = temp->burnedAcres;
    if(maxBurnedAcres < temp->burnedAcres)
      maxBurnedAcres = temp->burnedAcres;

    //Check for highest/lowest all monthes
    for(int indexX = 0; indexX < 12; indexX++)
    {
      if(minMonths > temp->months[indexX])
        minMonths = temp->months[indexX];
      if(maxMonths < temp->months[indexX])
         maxMonths = temp->months[indexX];
    }

    temp=temp->next;
  }
  temp = data;

  //Nomalize burned acres and months
  while(temp != NULL)
  {
    temp->burnedAcres=(temp->burnedAcres-minBurnedAcres)/(maxBurnedAcres-minBurnedAcres);

    for(int indexX = 0; indexX < 12; indexX++)
    {
      temp->months[indexX]=(temp->months[indexX]-minMonths)/(maxMonths-minMonths);
    }
    temp=temp->next;
  }
}


/**************************************************************************//**
 * @author Alex Nienhueser
 *
 * @par Description:
 * Get the record size
 *
 * @param[in] *data - head pointer for records struct.
 *
 *****************************************************************************/
int getRecordsSize( records *data )
{
  int recordSize = 0;
  records *temp = data;

  for( recordSize = 0; temp != NULL; recordSize++)
    temp = temp -> next;


  return recordSize;
}

/**************************************************************************//**
 * @author Alex Nienhueser
 *
 * @par Description:
 * Free up the records structure
 *
 * @param[in] *data - head pointer for records struct.
 *
 * @bug - This method which frees up the linked list of csv data records is 
 * performed recursively. Although this is less efficient than an iterative 
 * approach, for whatever reason every iterative approach to freeing the 
 * linked list just resulted in nasty seg faults. - Julian A. Brackins
 *
 *****************************************************************************/
void freeRecords(records *data)
{
  if(data->next == NULL)
  {
  	return;
  }
  freeRecords(data->next); 
  if(data !=NULL)
	  delete data;
}
