/*	CSOM3DLatticeTopology Interface Definition
	Robert Kirk Delisle
	6 April 2004

	Purpose:	Defines a mapping between indices in the lattice
				and a 3D relationship.

	Modification History:

*/

#if !defined(SOM3DLatticeTopology_12August2004__INCLUDED)
#define SOM3DLatticeTopology_12August2004__INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ISOMLatticeTopology.h"

class CSOM3DLatticeTopology : public ISOMLatticeTopology
{
private:

	long	m_lHeight;	//Height of the 3D lattice
	long	m_lWidth;	//Width of the 3D lattice
	long	m_lDepth;	//Depth of the 3D lattice

	CSOM3DLatticeTopology() {};	//privatized to force proper construction

public:

	CSOM3DLatticeTopology(long Height, long Width, long Depth)
	{
		m_lHeight = Height;
		m_lWidth  = Width;
		m_lDepth  = Depth;
	};

	virtual double LatticeDistance(long CellIndex1, long CellIndex2) const;
		//	returns a value which represents the topological distance
		//	between the cells corresponding to passed indicies
		//	It is the user's responsibility to define the representation

	virtual unsigned long NumberOfCells() const { return (m_lHeight*m_lWidth*m_lDepth); }
		//	returns the total number of cells required for this topology

	virtual ~CSOM3DLatticeTopology() {};
};

#endif
