/*	ISOMCellFactory Interface Definition
	Robert Kirk Delisle
	6 April 2004

	Purpose:	Defines the minimum requirements for an SOMCellFactory.
				The factory will be used by an SOMLattice from which 
				to acquire SOMCells.  Derived classes are required to implement
				the specific details necessary for construction and internal
				representation of SOMCells.  This includes how to acquire them
				from files, etc.

	Modification History:

*/

#if !defined(SOMCellFactory_06April2004__INCLUDED)
#define SOMCellFactory_06April2004__INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ISOMCell.h"

class ISOMCellFactory
{
public:

	ISOMCellFactory() {};  //empty default constructor

	virtual ISOMCell * GetRandomCell() const =0;
		//	Returns an SOMCell which has been constructed randomly.

	virtual ISOMCell * GetRandomDataCell() const =0;
		//	Returns an SOMCell which has been constructed based upon a random
		//	training observation.

	virtual ISOMCell * GetDataCellByIndex(long index) const =0;
		//	Returns a specific cell constructed from a training set
		//	corresponding to the passed index.

	virtual ~ISOMCellFactory() {};
		
};

#endif

