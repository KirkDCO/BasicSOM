/*	CSOMLattice Header
	Robert Kirk Delisle
	23 March 2004

	Purpose:	Defines the SOM Lattice containing the SOMCell nodes.
				Responsible for acquiring and managing SOMCells
				and training of the network

	Modification History:

*/

#if !defined(SOMLattice_23March2004__INCLUDED)
#define SOMLattice_23March2004__INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

#include "CSOMLatticeSettings.h"
#include "ISOMCell.h"
#include "CExceptionRKD.h"

class CSOMLattice
{
private:
	
	long					m_lCurrentIterations;	//keeps a tally of how many iterations we've done so far
	bool					m_bInitialized;
	CSOMLatticeSettings		m_Settings;	//keeps a copy of the settings passed in by the user.
	vector<ISOMCell *>		m_SOMCells;	//the nodes of the SOM - assumed to be derived from CSOMCell

	CSOMLattice() {};  //default constructor privatized to force parameter use

	bool ClosestCellIndex(const ISOMCell * const TargetCell, vector<long> *Indicies) const;
		//finds the cell(s) in the lattice that are closest to the TargetCell
		//if ties are found, all indices are stored in the vector out parameter.

public:
	
	CSOMLattice(const CSOMLatticeSettings *InitSettings) //parameterized constructor
	{ Initialize(InitSettings); }

	const ISOMCell * GetCell(long Index) const;
		//provide a reference to cells by their indicies

	long CellCount()
	{ return m_SOMCells.size(); }
		//return the number of cells in the lattice

	bool GetCellMembership(const ISOMCellFactory *TargetFactory, vector< vector<long> > *CellMembers) const;
		//determines the location of the data items in the SOM

	bool Initialize(const CSOMLatticeSettings *InitSettings);
		//primary lattice construction routine

	bool Train();	
		//function to start training the lattice

	~CSOMLattice();
};

#endif