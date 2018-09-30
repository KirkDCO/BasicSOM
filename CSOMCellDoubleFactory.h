/*	CSOMCellDoubleFactory  Definition
	Robert Kirk Delisle
	6 April 2004

	Purpose:	The factory will be used by an SOMLattice from which 
				to acquire SOMCells.  
				This derived class provides construction of CSOMCellDouble cells.

	Modification History:

*/

#if !defined(SOMCellDoubleFactory_06April2004__INCLUDED)
#define SOMCellDoubleFactory_06April2004__INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdlib.h>

#include "ISOMCellFactory.h"
#include "CSOMCellDouble.h"
#include "Dataset.h"
#include "CExceptionRKD.h"

class CSOMCellDoubleFactory : public ISOMCellFactory
{
private:

	const DataSet * m_pDataset;	//pointer to a DataSet object
	
	CSOMCellDoubleFactory() {};  //empty default constructor - privatized to force proper construction

public:	

	CSOMCellDoubleFactory( const DataSet *pData );
		//	Conversion from DataSet (and Observation) objects to SOMCellDouble

	virtual ISOMCell * GetRandomCell() const;
		//	Returns an SOMCell which has been constructed randomly.

	virtual ISOMCell * GetRandomDataCell() const;
		//	Returns an SOMCell which has been constructed based upon a random
		//	training observation.

	virtual ISOMCell * GetDataCellByIndex(long index) const;
		//	Returns a specific cell constructed from a training set
		//	corresponding to the passed index.

	virtual ~CSOMCellDoubleFactory() {};
		
};

#endif

