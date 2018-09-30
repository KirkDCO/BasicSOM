/*	CSOMLatticeSettings Header and Implementation
	Robert Kirk Delisle
	6 April 2004

	Purpose:	A settings object defines the structure of the SOM.
				Users MUST supply a Cell Factory which is used to acquire cells for the SOM,
				and a Topology which is used to define the topological arrangement of the network.

	Modification History:

*/

#if !defined(SOMLatticeSettings_06April2004__INCLUDED)
#define SOMLatticeSettings_06April2004__INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ISOMCellFactory.h"
#include "ISOMLatticeTopology.h"

namespace SOMLatticeSettings
{
	//LatticeInitMethod enumeration allows users to select the method by which lattice cells
	//are constructed.
	enum LatticeInitMethod
	{
		SOMInit_Random,				//set the weights of the cell at random
		SOMInit_DataRandom,		//pick a random training observation to set the weights
		SOMInit_DataSequential	//construct the Cells from the sequential list of observations
	};	
}
	
class CSOMLatticeSettings
{
public:

	CSOMLatticeSettings()
	{
		m_InitMethod					=	SOMLatticeSettings::SOMInit_DataRandom;
		m_CellFactory					=	0;			//user MUST supply

		m_TotalIterations				=	40000;
		m_TrainingStepSize				=	1000;
		m_InitialLearningRate			=	0.1;
		m_FinalLearningRate				=	0.005;
		m_InitialNeighborInfluence		=	5.0;
		m_FinalNeighborInfluence		=	0.2;
		m_LatticeTopology				=	0;		//user MUST supply
	};

	//get/set for all variables
	SOMLatticeSettings::LatticeInitMethod InitMethod() const
		{ return m_InitMethod; };
	void InitMethod(const SOMLatticeSettings::LatticeInitMethod Method) 
		{ m_InitMethod = Method; };

	const ISOMCellFactory * CellFactory() const
		{ return m_CellFactory; };
	void CellFactory(const ISOMCellFactory * Factory)
		{ m_CellFactory = Factory;};

	unsigned long TotalIterations() const
		{ return m_TotalIterations; };
	void TotalIterations(unsigned long Iterations)
		{ m_TotalIterations = Iterations; };

	unsigned long TrainingStepSize() const
		{ return m_TrainingStepSize; };	
	void TrainingStepSize( unsigned long StepSize )
		{ m_TrainingStepSize = StepSize; };

	double InitialLearningRate() const
		{ return m_InitialLearningRate; };
	void InitialLearningRate( double Rate )
		{ m_InitialLearningRate = Rate; };

	double FinalLearningRate() const
		{ return m_FinalLearningRate; };
	void FinalLearningRate(double Rate)
		{ m_FinalLearningRate = Rate; };

	double InitialNeighborInfluence() const
		{ return m_InitialNeighborInfluence; };
	void InitialNeighborInfluence(double Influence)
		{ m_InitialNeighborInfluence = Influence; };

	double FinalNeighborInfluence() const
		{ return m_FinalNeighborInfluence; };
	void FinalNeighborInfluence(double Influence)
		{ m_FinalNeighborInfluence = Influence; };

	const ISOMLatticeTopology * LatticeTopology() const
		{ return m_LatticeTopology; };
	void LatticeTopology(ISOMLatticeTopology * Topology)
		{ m_LatticeTopology = Topology; };

private:

	SOMLatticeSettings::LatticeInitMethod	m_InitMethod;
	const ISOMCellFactory		*m_CellFactory;				//MUST be supplied by user

	unsigned long				m_TotalIterations;			//the total number of samples for training
	unsigned long				m_TrainingStepSize;			//how many step to take per call to Train()
	double						m_InitialLearningRate;	
	double						m_FinalLearningRate;	
	double						m_InitialNeighborInfluence;
	double						m_FinalNeighborInfluence;	
	const ISOMLatticeTopology	*m_LatticeTopology;			//MUST be supplied by user - allows arbitrary topology

};

#endif