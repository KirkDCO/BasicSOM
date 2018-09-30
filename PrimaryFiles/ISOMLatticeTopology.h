/*	ISOMLatticeTopology Interface Definition
	Robert Kirk Delisle
	6 April 2004

	Purpose:	Defines the minimum requirements for the ISOMLatticeTopology interface.
				Derived classes are able to define an arbitrary topology (i.e., 1D, 2D,
				3D, non-euclidean).  

	Modification History:

*/

#if !defined(SOMLatticeTopology_06April2004__INCLUDED)
#define SOMLatticeTopology_06April2004__INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ISOMLatticeTopology
{
public:

	ISOMLatticeTopology() {};

	virtual double LatticeDistance(long CellIndex1, long CellIndex2) const =0;
		//	returns a value which represents the topological distance
		//	between the cells corresponding to passed indicies
		//	It is the user's responsibility to define the representation

	virtual unsigned long NumberOfCells() const =0;
		//	returns the number of cells necessary for the given 
		//	topology.

	virtual ~ISOMLatticeTopology() {};
};

#endif
