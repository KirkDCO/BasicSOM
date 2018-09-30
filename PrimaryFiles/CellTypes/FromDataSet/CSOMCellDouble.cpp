/*	SOMCelDouble Implementation 
	Robert Kirk Delisle
	24 March 2004

	Purpose:	Implementation for the CSOMCellFloat class.

	Modification History:

*/

#include "stdafx.h"

#include "CSOMCellDouble.h"

CSOMCellDouble::CSOMCellDouble(const vector<double> *Weights)
{
	/*	Robert Kirk DeLisle
		6 April 2004
		
		Purpose:	Construct a CSOMCellDouble using the passed vector of weights.

		Parameters:	Weights		-	vector of double values to use in SOMCell construction

		Return:		none
	*/

	long i;	//loop counter

	for (i=0; i<Weights->size(); i++)
	{
		m_Weights.push_back( (*Weights)[i] );
	}

	return;
}

double CSOMCellDouble::Similarity(const ISOMCell *TargetCell)  const
{	
	/*	Robert Kirk DeLisle
		24 March 2004

		Purpose:	Return the similarity between this cell and the passed Cell.
					For the Double type, similarity is the Euclidean distance between
					cell descriptors.

		Parameters:	TargetCell	-	Cell used for comparison with this cell.

		Return:		Double representing the similarity between cells.
					If negative, an error occured.
	*/
	
	const CSOMCellDouble *CastTargetCell;	//used to contain a dynamic cast of the TargetCell
											//and makes certain the correct type came in
	double distance=0;						//accumulator for calculations
	int i;									//index for loop
	
	//verify that the target cell is a CSOMCellDouble
	if ( !(CastTargetCell = dynamic_cast<const CSOMCellDouble*>(TargetCell)) )
	{
		distance=-1;
	}
	else
	{
		for (i=0; i<m_Weights.size(); i++)
		{
			distance += (CastTargetCell->m_Weights[i] - m_Weights[i]) * (CastTargetCell->m_Weights[i] - m_Weights[i]);
		}
	}

	//distance=sqrt(distance);	avoiding the sqrt will save computation time
	return distance;
}
	
bool CSOMCellDouble::AdjustWeights(const ISOMCell *TargetCell, double Influence)
{
	/*	Robert Kirk DeLisle
		24 March 2004

		Purpose:	Alter the weights of this cell to become more like those
					of the passed target cell.  
					Calculate the difference between each of the weights and 

		Parameters:	TargetCell	-	Contains the target weights.
					Influence	-	Defines the amount by which to adjust the weights.
									Assumed to be [0,1].

		Return:		true if successful
					false otherwise
	*/
	
	const CSOMCellDouble *CastTargetCell;	//used to contain a dynamic cast of the TargetCell
											//and makes certain the correct type came in
	long i;									//loop index
	bool bSuccess = true;					//return argument - optimistic outlook
	
	//verify that the target cell is a CSOMCellFloat
	if ( !(CastTargetCell = dynamic_cast<const CSOMCellDouble*>(TargetCell)) )
	{
		bSuccess=false;
	}
	else
	{
		for (i=0; i<m_Weights.size(); i++)
		{	
			m_Weights[i] += (CastTargetCell->m_Weights[i] - m_Weights[i]) * Influence;
		}
	}

	return bSuccess;
}

bool CSOMCellDouble::GetCellWeights(vector<double> *Weights) const
{
	/*	Robert Kirk DeLisle
		
		Purpose:	Put the weights of this cells representation into the vector.

		Parameters:	Weights	-	Pointer to the target vector.

		Return:		true if successful
					false otherwise
	*/

	bool bSuccess=true;	//optimistic return outlook
	int i;	//loop index

	//make sure the return vector is empty
	Weights->erase(Weights->begin(), Weights->end());

	try
	{
		for (i=0; i<m_Weights.size(); i++)
		{
			Weights->push_back(m_Weights[i]);
		}
	}
	catch(...)
	{
		bSuccess=false;
		throw CExceptionRKD(301,"CSOMCellDouble::GetCellWeights", "Unknown error retrieving cell weights.");
	}

	return bSuccess;	
}
	

