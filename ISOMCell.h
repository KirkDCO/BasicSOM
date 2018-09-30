/*	ISOMCell Interface Definition
	Robert Kirk Delisle
	16 March 2004

	Purpose:	Defines the minimum requirements for an SOMCell
				within the SOM application.  Users are required to 
				implement various features in order to ensure functionality
				within the larger scope application.

				Any derived class must define its own internal representation and 
				implement the functions necessary to manipulate that representation
				given the requirments of the this base class.

	Modification History:

*/

#if !defined(SOMCell_16March2004__INCLUDED)
#define SOMCell_16March2004__INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream>
#include <fstream>
using namespace std;

class ISOMCell
{
public:

	ISOMCell() {};

	virtual bool AdjustWeights(const ISOMCell *TargetCell, double Influence)=0;
		//	Returns true if successful
		//  false otherwise.  Adjusts the representation (weights) of this cell
		//	based upon the passed TargetCell considering the Influence factor.
		//  This allows for variable levels of adjustments - decaying radius of influence
		//  and decaying learning rate - combined in one variable.

	virtual double Similarity(const ISOMCell *TargetCell) const =0;
		//	Returns a value which
		//	is interpreted as a similarity measure between this cell and the 
		//	passed cell.  A higher value is interpreted as more similar.

	virtual ~ISOMCell() {};
		//	virtual destructor in order to force call of derived destructor on delete
		
};	

#endif