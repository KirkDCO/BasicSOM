/*	CCoordinates declaration
	Robert Kirk DeLisle

	Purpose:	Enacapsulates the cooridinates of a plottable point in 3D space.

	Modification History:

*/

#if !defined(CCordinates_07April2004__INCLUDED)
#define CCordinates_07April2004__INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace Coordinates
{
	enum CCoordDimensions
	{
		CCoord_OneD,
		CCoord_TwoD,
		CCoord_ThreeD
	};
}

class CCoordinates
{
public:

	CCoordinates() { X=0; Y=0; Z=0; };

	double X;
	double Y;
	double Z;

	~CCoordinates() {};
};

#endif