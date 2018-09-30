// Observation.cpp: implementation of the Observation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Observation.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Observation::Observation()
{

}

Observation::~Observation()
{
	
}

float Observation::GetDescriptorValue(long descriptorIndex) const	
{
	/*	Returns the descriptor value */

	return (descriptors.at(descriptorIndex));
}
void Observation::AddDescriptor(float descriptorValue)
{
	/*  Add the passed descriptor to the vector of descriptors  */
	
	descriptors.push_back(descriptorValue);

}


void Observation::SetIndex(int i)
{
	/*	Set the zero-based index of the current observation */
	index=i;
}


long Observation::GetNumberOfDescriptors() const
{
	return descriptors.size();
}



