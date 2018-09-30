/*	SOMCellDouble Header
	Robert Kirk Delisle
	24 March 2004

	Purpose:	Defines a floating point SOMCell with the appropriate functions 
				declared.

	Modification History:

*/

#if !defined(SOMCellFloat_16March2004__INCLUDED)
#define SOMCellFloat_16March2004__INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include <vector>
using namespace std;

#include "ISOMCell.h"
#include "CExceptionRKD.h"

class CSOMCellDouble : public ISOMCell
{
private:

	vector<double> m_Weights;
		//	vector to contain the features or weights of this cell		

	CSOMCellDouble();
		//	No default public constructor to force users to supply parameters for construction.

public:
		
	CSOMCellDouble(const vector<double> *Weights);
		//Construct an SOMCell from the passed vector of Weights
	
	virtual bool AdjustWeights(const ISOMCell *TargetCell, double Influence);
		//	Returns true if successful
		//	false otherwise.  Adjusts the representation (weights) of this cell
		//	based upon the passed TargetCell considering the Influence factor.
		//	This allows for variable levels of adjustments - decaying radius of influence
		//	and decaying learning rate - combined in one variable.

	virtual double Similarity(const ISOMCell *TargetCell) const;
		//	Returns a value which
		//	is interpreted as a similarity measure between this cell and the 
		//	passed cell.  A higher value is interpreted as more similar. 
	
	bool GetCellWeights(vector<double> *Weights) const;
		//	Returns true if successful
		//	Put the weights of this cells representation into the vector.
	
	virtual ~CSOMCellDouble() { m_Weights.erase(m_Weights.begin(), m_Weights.end() ); }
		//	Destructor merely clears the weights as no memory allocation is occuring
		
};	

#endif