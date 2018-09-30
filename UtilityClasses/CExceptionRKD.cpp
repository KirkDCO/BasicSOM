/*	CExceptionRKD implementation
	Robert Kirk DeLisle
	
	Purpose:	Class to be used in exception handling.

	Modification History:
*/


#include "stdafx.h"

#include "CExceptionRKD.h"

ostream& operator<<(ostream &s, const CExceptionRKD &ex)
{
	/*	Robert Kirk DeLisle
		
		Purpose:	Allow streaming output of exception contents.

		Parameters:	s	-	reference to the ostream object
					ex	-	reference to the CExceptionRKD object

		Return:
	*/

	s << ex.m_lErrCode << " : " << ex.m_cFunction << " : " << ex.m_cMessage;

	return s;
}