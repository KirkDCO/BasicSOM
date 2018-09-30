// DataSet.h: interface for the DataSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATASET_H__E6F6D1CB_C06B_44DE_8CB3_72E50EB7350A__INCLUDED_)
#define AFX_DATASET_H__E6F6D1CB_C06B_44DE_8CB3_72E50EB7350A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Observation.h"
#include <fstream>
#include <vector>
using namespace std;

class DataSet  
{
public:
	float GetDescriptorValue(long observationIndex, long descriptorIndex) const;
	long GetNumberOfDescriptors() const;
	long GetNumberOfObservations() const;
	bool LoadDataSet(const char *fileName);
	DataSet();
	virtual ~DataSet();

private:
	long numberOfDescriptors;
	long numberOfObservations;
	vector<Observation *> data;
};

#endif // !defined(AFX_DATASET_H__E6F6D1CB_C06B_44DE_8CB3_72E50EB7350A__INCLUDED_)
