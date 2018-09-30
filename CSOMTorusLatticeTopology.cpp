/*	CSOMTorusLatticeTopology Implementation
	Robert Kirk Delisle
	23 August 2004

	Purpose:	Defines a mapping between indices in the lattice
				and a torroidal relationship.

	Modification History:

*/

#include "stdafx.h"

#include "CSOMTorusLatticeTopology.h"

double CSOMTorusLatticeTopology::LatticeDistance(long CellIndex1, long CellIndex2) const
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
	long xDist, yDist;				//distances for 2D rectangle
	long xTorDist, yTorDist;		//distances on torus

	//determine the rows and columns of the sought cells
	Row1 = CellIndex1/m_lWidth;
	Col1 = CellIndex1 - (Row1*m_lWidth);

	Row2 = CellIndex2/m_lWidth;
	Col2 = CellIndex2 - (Row2*m_lWidth);

	xDist = abs(Row1-Row2);
	xTorDist = __min(xDist, abs(m_lWidth-xDist));
	
	yDist = abs(Col1-Col2); //standard 2D Manhattan distance
	yTorDist = __min(yDist, abs(m_lWidth-yDist));

	return static_cast<double>(xTorDist+yTorDist);
}