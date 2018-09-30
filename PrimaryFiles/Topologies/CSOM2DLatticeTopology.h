/*	CSOM2DLatticeTopology Interface Definition
	Robert Kirk Delisle
	6 April 2004

	Purpose:	Defines a mapping between indices in the lattice
				and a 2D relationship.

	Modification History:

*/

#if !defined(SOM2DLatticeTopology_06April2004__INCLUDED)
#define SOM2DLatticeTopology_06April2004__INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ISOMLatticeTopology.h"

class CSOM2DLatticeTopology : public ISOMLatticeTopology
{
private:

	long	m_lHeight;	//Height of the 2D lattice
	long	m_lWidth;	//Width of the 2D lattice

	CSOM2DLatticeTopology() {};	//privatized to force proper construction

public:

	CSOM2DLatticeTopology(long Height, long Width)
	{
		m_lHeight = Height;
		m_lWidth  = Width;
	};

	virtual double LatticeDistance(long CellIndex1, long CellIndex2) const;
		//	returns a value which represents the topological distance
		//	between the cells corresponding to passed indicies
		//	It is the user's responsibility to define the representation

	virtual unsigned long NumberOfCells() const { return (m_lHeight*m_lWidth); }
		//	returns the total number of cells required for this topology

	virtual ~CSOM2DLatticeTopology() {};
};

#endif
