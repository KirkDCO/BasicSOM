/*	CExceptionRKD
	Robert Kirk DeLisle
	
	Purpose:	Class to be used in exception handling.

	Modification History:
*/

#if !defined(CExceptionRKD_06May2004_INCLUDED)
#define CExceptionRKD_06May2004_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ostream>
using namespace std;

class CExceptionRKD
{
private:
	
	long m_lErrCode;	//contains an error code value
	char *m_cMessage;	//an error message
	char *m_cFunction;	//will contain the name of the function which generated the error

	CExceptionRKD();	//force a construction method

public:
	
	CExceptionRKD(long ErrCode, char *FunctionName, char *Message)
	{  m_lErrCode=ErrCode; m_cMessage=Message; m_cFunction=FunctionName; }

	~CExceptionRKD() {}

friend ostream& operator<<(ostream& s, const CExceptionRKD &ex);
};

#endif