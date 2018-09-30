/*	SOMLattice Implementation
	Robert Kirk Delisle
	24 March 2004

	Purpose:	Implements the SOM Lattice containing the SOMCell nodes.
				Responsible for creation and management of SOMCells
				and training of the network

	Modification History:

*/

#include "stdafx.h"
#include <cmath>

#include "CSOMLattice.h"
#include "CExceptionRKD.h"

bool CSOMLattice::Initialize(const CSOMLatticeSettings *InitSettings)
{
	/*	Robert Kirk DeLisle
		24 March 2004
		
		Purpose:	Constructs the SOM lattice based upon the passed settings structure.

		Parameters:	Settings	-	Pointer to a LatticeSettings structure which contains all the 
									details of the lattice necessary for construction and training.

		Return:		true if successful
					false otherwise
	*/
	
	bool bSuccess=true;  //optimistic return
	long i;	//loop index
	
	//get rid of any old cells - this allows initialization to be conducted more than once on the same object
	for (i=0; i<m_SOMCells.size(); i++)
	{
		if (m_SOMCells[i] != 0)
		{
			delete m_SOMCells[i];
		}
	}
	m_SOMCells.erase(m_SOMCells.begin(), m_SOMCells.end());

	//set current iterations to 0
	m_lCurrentIterations = 0;

	//copy the settings
	m_Settings = (*InitSettings);

	try
	{	//put cells into the lattice
		for (i=0; i<(m_Settings.LatticeTopology())->NumberOfCells(); i++)
		{
			switch (m_Settings.InitMethod())
			{
				case SOMLatticeSettings::SOMInit_Random:
					m_SOMCells.push_back( (m_Settings.CellFactory())->GetRandomCell() );
					break;

				case SOMLatticeSettings::SOMInit_DataRandom:
					m_SOMCells.push_back( (m_Settings.CellFactory())->GetRandomDataCell() );
					break;

				case SOMLatticeSettings::SOMInit_DataSequential:
					m_SOMCells.push_back( (m_Settings.CellFactory())->GetDataCellByIndex(i) );
					break;

				default :
					m_SOMCells.push_back( (m_Settings.CellFactory())->GetRandomCell() );
			}
		}
	}
	catch(CExceptionRKD &ex)
	{
		bSuccess=false;
		throw ex;
	}
	catch(...)
	{
		bSuccess=false;
		throw ( CExceptionRKD(101,"CSOMLattice:Initialize","An unknown error occured during lattice cell construction.") );
	}

	m_bInitialized=bSuccess;
	return bSuccess;
}

bool CSOMLattice::Train()
{
	/*	Robert Kirk DeLisle
		24 March 2004
		
		Purpose:	Trains the SOM for the desired number of iterations.
					One iteration is defined as comparison of one observation
					and adjustment of weights.  <This may be modified to an epoch.>

		Parameters:	none

		Return:		true if more iterations are required to meet the target number
					false if we've hit the total number of iterations
	*/

	long i=0;					//index to loop
	long TargetIterations;		//the iteration number we're shooting for on this training process

	ISOMCell * CurrentTrainingCell;	//holds the current SOMCell for training
	
	double CellDistance;	
	vector<long> ClosestIndex;
	long WinningNodeIndex;

	//training variables
	double EpsilonT, Hrs, SigmaT;

	//are we ready to go?
	if (!m_bInitialized) 
	{
		throw CExceptionRKD(105,"CSOMLattice::Train","Lattice not initialized.");
		return false;	//no! fail
	}

	TargetIterations = m_lCurrentIterations + m_Settings.TrainingStepSize();	//set the target
	if (TargetIterations > m_Settings.TotalIterations())
		TargetIterations = m_Settings.TotalIterations();			//make sure we don't go over

	while (m_lCurrentIterations < TargetIterations)
	{
		//pick a random observation from the data set
		try 
		{
			CurrentTrainingCell = (m_Settings.CellFactory())->GetRandomDataCell();
		}
		catch ( CExceptionRKD &ex )
		{
			throw ex;
		}
		catch (...)
		{
			throw CExceptionRKD(102,"CSOMLattice::Train","Unknown error retrieving random data cell for training.");
		}

		//find the closest cell in the lattice
		//in case of a tie, pick a winner at random from the possible winners
		ClosestCellIndex(CurrentTrainingCell, &ClosestIndex);
		WinningNodeIndex = ClosestIndex[static_cast<long>(
											static_cast<double>(ClosestIndex.size())*
											static_cast<double>(rand())/static_cast<double>(RAND_MAX)
											)];

		//http://www.neuroinformatik.ruhr-uni-bochum.de/ini/VDM/research/gsn/DemoGNG/SOM_2.html 
		EpsilonT = 0.1 * pow( (.005/.1), (static_cast<double>(m_lCurrentIterations)/static_cast<double>(m_Settings.TotalIterations())) );
		SigmaT =   5.0 * pow( (0.2/5.0), (static_cast<double>(m_lCurrentIterations)/static_cast<double>(m_Settings.TotalIterations())) );
		
		for (i=0; i<m_SOMCells.size(); i++)
		{
			//get the distance between lattice cells defined by the LatticeTopology object
			CellDistance = (m_Settings.LatticeTopology())->LatticeDistance(WinningNodeIndex, i);
			
			Hrs = exp( -(CellDistance*CellDistance)/(2.0*SigmaT*SigmaT));

			try
			{
				m_SOMCells[i]->AdjustWeights(CurrentTrainingCell, EpsilonT*Hrs);
			}
			catch ( CExceptionRKD &ex )
			{
				throw ex;
			}
			catch (...)
			{
				throw CExceptionRKD(103, "CSOMLattice::Train","Unknown error adjusting cell weights.");
			}
		}
		
		delete CurrentTrainingCell;	//done with this one
		m_lCurrentIterations++;
	}
	
	if (m_lCurrentIterations < m_Settings.TotalIterations())
		return true;
	else
		return false;

}

CSOMLattice::~CSOMLattice()
{
	/*	Robert Kirk DeLisle
		25 March 2004

		Purpose:	Release references as needed.
	
		Parameters:	none

		Return:		none
	*/

	int i;	//loop index

	for (i=0; i<m_SOMCells.size(); i++)
	{
		if (m_SOMCells[i] != 0)
		{
			delete m_SOMCells[i];
		}
	}

	m_SOMCells.erase(m_SOMCells.begin(), m_SOMCells.end());

}

bool CSOMLattice::GetCellMembership(const ISOMCellFactory *TargetFactory, vector< vector<long> > *CellMembers) const
{
	/*	Robert Kirk DeLisle
		20 April 2004

		Purpose:	Each observation in the attached DataSet is assessed for which 
					node in the SOM is closest, ie, holds its membership.  Indices 
					are stored in the vector or vectors.
					The data set used is determined by the attached ISOMCellFactory in
					the settings object.  This allows users to change the data set being
					assessed on the fly and keeps this portion general.  Customization of 
					the factory allows usage of different data representations, topologies, etc.

		Parameters:	CellMembers	-	pointer to a vector of vectors of longs.  The outer 
									vector will contain as many vectors as there are nodes
									in the lattice.  They are maintained in the same order as
									they occur sequentially.  (Use the topology object to
									determined their specialized topological relationships.)  
									The inner vector of longs contains indicies to those
									observations that belong to this node.

		Return:		true if successful
					false otherwise
	*/

	bool bSuccess=true; //optimistic return value
	ISOMCell *currentDataCell;	//the current cell being evaluated

	long currentDataIndex=0;	//current index into the dataset
	vector<long> ClosestIndices; //holds all closest cells
	long i; //loop counter

	//reserve an appropriate amount of vectors 
	for (i=0; i<(m_Settings.LatticeTopology())->NumberOfCells(); i++)
	{
		CellMembers->push_back( vector <long>() );
	}
	
	try
	{
		currentDataCell = TargetFactory->GetDataCellByIndex(currentDataIndex);
		
		while (currentDataCell != 0 )
		{
			ClosestCellIndex(currentDataCell, &ClosestIndices);

			//push the current data index(indicies) into the correct vector(s)
			for (i=0; i<ClosestIndices.size(); i++)
			{
				(*CellMembers)[ClosestIndices[i]].push_back(currentDataIndex);					
			}

			//get the next observation
			delete currentDataCell;
			currentDataCell = TargetFactory->GetDataCellByIndex(++currentDataIndex);
		}

		delete currentDataCell;
	}
	catch (CExceptionRKD &ex)
	{
		throw ex;
	}
	catch(...)
	{
		bSuccess=false;
		throw CExceptionRKD(104,"CSOMLattice::GetCellMembership","Unknown error retrieving data cell or evaluating membership.");
	}

	return bSuccess;
}

bool CSOMLattice::ClosestCellIndex(const ISOMCell * const TargetCell, vector<long> *Indicies) const
{
	/*	Robert Kirk DeLisle
		20 April 2004

		Purpose:	Return the index of the closest cell in the lattice with respect
					to the passed cell.

		Parameters:	TargetCell	-	Reference to find the closest SOMCell.
					Indicies	-	vector of longs to store the indicies.  A vector is used
									due to the fact that there might be a tie.  In such a case,
									all cell indicies are included in the vector.  If there is an error,
									the vector will be empty.

		Return:		Lattice index (sequential numbering) of the closest lattice SOMCell.
	*/

	bool bSuccess=true;  //optimistic return outlook
	double CellSimilarity, currentClosestSim;	
	long i;	//loop counter

	//clear out the indicies
	Indicies->erase(Indicies->begin(), Indicies->end());
	Indicies->resize(0);

	//find the closest cell
	//in case of a tie, pick a winner at random from the possible winners
	Indicies->push_back(0);
	currentClosestSim = m_SOMCells[0]->Similarity(TargetCell);

	for ( i=1; i<m_SOMCells.size(); i++ )
	{
		CellSimilarity = m_SOMCells[i]->Similarity(TargetCell);
		if ( CellSimilarity < currentClosestSim ) 
		{
			Indicies->erase(Indicies->begin(),Indicies->end());
			Indicies->push_back(i);
			currentClosestSim=CellSimilarity;
		}
		else if ( CellSimilarity == currentClosestSim )
			Indicies->push_back(i);
	}
	
	//if we have a tie...
	return bSuccess;
}

const ISOMCell * CSOMLattice::GetCell(long Index) const
{
	/*	Robert Kirk DeLisle
		3 May 2004
		
		Purpose:	Provide a reference to cells by their indicies.

		Parameters:	Index	-	The index referring to a specific cell.	

		Return:		Pointer to the cell referred to by Index.
					If an error occurs, the returned pointer will be 0.
	*/
	
	if ( Index >= m_SOMCells.size() )
	{
		return 0;
	}

	return m_SOMCells[Index];
}