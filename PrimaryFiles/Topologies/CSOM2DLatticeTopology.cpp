/*	CSOM2DLatticeTopology Implementation
	Robert Kirk Delisle
	6 April 2004

	Purpose:	Defines a mapping between indices in the lattice
				and a 2D relationship.

	Modification History:

*/

#include "stdafx.h"

#include "CSOM2DLatticeTopology.h"

double CSOM2DLatticeTopology::LatticeDistance(long CellIndex1, long CellIndex2) const
{
	/*	Robert Kirk DeLisle
		6 April 2004

		Purpose:	Returns the lattice distance between two SOM cells 
					based upon their indices.

		Parameters:	CellIndex1	-	Index of the first cell of interest.
					CellIncdex2	-	Index of the second cell of interest.

		Return:		The Manhattan distance between the two cells of interest
	*/

	long Row1, Col1, Row2, Col2;	//the mapped row and index of the passed cells

	Row1 = CellIndex1/m_lWidth;
	Col1 = CellIndex1 - (Row1*m_lWidth);

	Row2 = CellIndex2/m_lWidth;
	Col2 = CellIndex2 - (Row2*m_lWidth);

	return static_cast<double>(abs(Row1-Row2)+abs(Col1-Col2));
}