// Observation.h: interface for the Observation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBSERVATION_H__98D9F256_7393_414C_B682_BB993427176E__INCLUDED_)
#define AFX_OBSERVATION_H__98D9F256_7393_414C_B682_BB993427176E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

class Observation  
{
public:
	float GetDescriptorValue(long descriptorIndex) const;
	void AddDescriptor(float descriptorValue);
	void SetIndex(int i);
	long GetNumberOfDescriptors() const;

	Observation();
	virtual ~Observation();

private:
	vector<float> descriptors;
	long index;

	

};

#endif // !defined(AFX_OBSERVATION_H__98D9F256_7393_414C_B682_BB993427176E__INCLUDED_)
