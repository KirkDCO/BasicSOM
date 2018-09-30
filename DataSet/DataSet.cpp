// DataSet.cpp: implementation of the DataSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DataSet.h"

#include <fstream>
using namespace std;

#include <time.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DataSet::DataSet()
{
	numberOfDescriptors=0;
	numberOfObservations=0;
}

DataSet::~DataSet()
{
	//reclaim the observation vectors
	while ( !data.empty() )
	{		
		delete data.back();
		data.pop_back();
	}
}

long DataSet::GetNumberOfDescriptors() const
{
	/*	Robert Kirk DeLisle
		November 27 2001
		Purpose:	Retrieve the total number of descriptors

		Parameters:	none

		Return:		The number of descriptors (columns minus the endpoint) in the dataset.
	*/

	return numberOfDescriptors;

}

bool DataSet::LoadDataSet(const char *fileName)
{
	/*	Robert Kirk DeLisle
		November 27 2001
		Purpose:	Load data into the dataset from the specified file.  
					This function assumes CLEAN!! data files in CSV format.
					Any number of descriptors and observations are allowed, 
					but the first column is treated as the endpoint
					The first line is considered to be the column headers.

		Parameters:	fileName:	Pointer to a null-terminated string containing the
								complete filename of the data file.
					numOfObservations:	Reference variable which is changed by this
										function to contain the number of observations
					numOfDescriptors:	Reference variable which is changed by this
										function to contain the number of descriptors

		Return:		TRUE if successful, FALSE if unsuccessful
	*/

	fstream datafile;
	char ptrDataLine[10000];
	unsigned int counter; //loop counter
	
	datafile.open(fileName,ios::in);	//open the data file

	datafile.getline(ptrDataLine,10000); //get the first line - the column headers

	//count the number of commas - commas - 1 = number of columns(descriptors + endpoint + name)
	for (counter=0; counter<strlen(ptrDataLine); counter++)
	{
		if ( ptrDataLine[counter] == ',' )
			numberOfDescriptors++;
	}
	numberOfDescriptors++;

	//now save the actual values of the endpoints and the descriptors
	Observation * currentObservation;
	
	while ( !datafile.eof() )
	{
		datafile.getline(ptrDataLine,10000);
		
		//make a new observation to hold the data
		currentObservation = new Observation;
		currentObservation->SetIndex(numberOfObservations-1);
		
		if (strlen(ptrDataLine) != 0)
		{
			numberOfObservations++;

			//get the first value
			currentObservation->AddDescriptor(atof(&(ptrDataLine[0])));

			for (counter=0; counter<strlen(ptrDataLine); counter++)
			{			
				if ( ptrDataLine[counter] == 44 )
				{
					currentObservation->AddDescriptor(atof(&(ptrDataLine[counter+1])));
				}
			}			
			data.push_back(currentObservation);
		}
	}
			
	datafile.close();

	return true;
}

long DataSet::GetNumberOfObservations() const
{
	return numberOfObservations;
}

float DataSet::GetDescriptorValue(long observationIndex, long descriptorIndex) const
{
	/*	Robert Kirk DeLisle
		November 27 2001
		Purpose:	Return the value of the descriptor specified for the observation specified

		Parameters:	observationIndex:	The zero-based index of the observation of interest

					descriptorIndex:	The zero-based index of the descriptor of interest

		Return:		the value of the specified descriptor-observation pair
	*/

	return data.at(observationIndex)->GetDescriptorValue(descriptorIndex);

}

