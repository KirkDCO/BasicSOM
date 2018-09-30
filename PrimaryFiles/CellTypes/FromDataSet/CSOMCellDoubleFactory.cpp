/*	CSOMCellDoubleFactory Implementation
	Robert Kirk Delisle
	6 April 2004

	Purpose:	Defines a floating point SOMCell with the appropriate functions 
				declared.

	Modification History:

*/

#include "stdafx.h"

#include "CSOMCellDoubleFactory.h"

CSOMCellDoubleFactory::CSOMCellDoubleFactory( const DataSet *pData )
{
	/*	Robert Kirk DeLisle
		
		Purpose:

		Parameters:

		Return:
	*/

	m_pDataset = pData;	
}

ISOMCell * CSOMCellDoubleFactory::GetRandomCell() const
{
	/*	Robert Kirk DeLisle
		
		Purpose:	Returns a DoubleSOMCell which has been constructed by
					random assignment of weights.  Clamping of the weights
					between the max and min present in the dataset is done.
					The dataset doesn't supply this, so it is done crudely here.
					A better dataset object would help.

		Parameters:	none
	
		Return:		Base class pointer to the newly constructed CSOMCellDouble.
	*/

	long descr, obs; //loop indices
	static vector<float> max, min; //maxium and minimum values
	float currentDescrVal;
	vector<double> Weights;
	static bool MaxMinCalc = false;

	try
	{
		for (descr=0; descr<m_pDataset->GetNumberOfDescriptors(); descr++)
		{
			if ( !MaxMinCalc ) 
			{
				max.push_back(m_pDataset->GetDescriptorValue(0,descr));
				min.push_back(m_pDataset->GetDescriptorValue(0,descr));

				for (obs=1; obs<m_pDataset->GetNumberOfObservations(); obs++)
				{
					currentDescrVal = m_pDataset->GetDescriptorValue(obs,descr);

					if ( currentDescrVal < min[descr] )
						min[descr] = currentDescrVal;

					if ( currentDescrVal > max[descr] )
						max[descr] = currentDescrVal;
				}
			}

			Weights.push_back( (static_cast<double>(rand())/static_cast<double>(RAND_MAX)) *
								(max[descr] - min[descr]) + min[descr] );
		}
		MaxMinCalc = true;
	}
	catch(CExceptionRKD &ex)
	{
		throw ex;
	}
	catch(...)
	{
		throw CExceptionRKD(201,"CSOMCellDoubleFactory::GetRandomCell","Unknown error accessing DataSet.");
	}

	return new CSOMCellDouble( &Weights );
}	

ISOMCell * CSOMCellDoubleFactory::GetRandomDataCell() const
{
	/*	Robert Kirk DeLisle
	
		Purpose:	Returns a DoubleSOMCell which has been constructed based upon a random
					training observation.

		Parameters:	none

		Return:		Base class pointer to the newly constructed CSOMCellDouble.
	*/

	long selectedObsIndex; //index of the observation used
	long descr;	//loop counter for descriptors
	vector<double> Weights;

	try
	{
		selectedObsIndex = (static_cast<double>(rand())/static_cast<double>(RAND_MAX)) * (m_pDataset->GetNumberOfObservations()-1);
	}
	catch (CExceptionRKD &ex)
	{
		throw ex;
	}
	catch(...)
	{
		throw CExceptionRKD(202,"CSOMCellDoubleFactory::GetRandomDataCell","Unknown error accessing DataSet.");
	}

	for (descr=0; descr<m_pDataset->GetNumberOfDescriptors(); descr++)
	{
		Weights.push_back(m_pDataset->GetDescriptorValue(selectedObsIndex,descr));
	}

	return new CSOMCellDouble(&Weights);
}

ISOMCell * CSOMCellDoubleFactory::GetDataCellByIndex(long index) const
{
	/*	Robert Kirk DeLisle
		
		Purpose:	Returns a specific cell constructed from a training set
					corresponding to the passed index.

		Parameters:	index	-	Refers to the desired observation in the dataset of interest.

		Return:		Base class pointer to the newly constructed CSOMCellDouble.
	*/

	bool bSuccess=true;	//optimistic return status
	long descr; //loop counter
	vector<double> Weights; //used to construct the weights of the SOMCell

	//verify we're in bounds of the number of observations
	if ( index<0 || index >=m_pDataset->GetNumberOfObservations() )
	{
		bSuccess=false;
	}
	else
	{
		try
		{
			for (descr=0; descr<m_pDataset->GetNumberOfDescriptors(); descr++)
			{
				Weights.push_back( m_pDataset->GetDescriptorValue(index,descr) );
			}
		}
		catch(CExceptionRKD &ex)
		{
			throw ex;
		}
		catch(...)
		{
			throw CExceptionRKD(203,"CSOMCellDoubleFactory::GetDataCellByIndex","Unknown error accessing DataSet.");
		}
	}

	if (bSuccess)
		return new CSOMCellDouble( &Weights );
	else
		return 0;
}	
