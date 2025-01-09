//-----------------------------------------------------------------------------
//----- Helpers.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "Helpers.h"

//-----------------------------------------------------------------------------
//----- This will define the static members of the Helpers class
//-----------------------------------------------------------------------------
void Helpers::printAcGePoint3d(const AcGePoint3d& pt)
{
	// Create a formatted string
	wchar_t message[100];
	swprintf_s(message, 100, L"(%f, %f, %f)", pt.x, pt.y, pt.z);

	// Display the formatted string to the command line
	acutPrintf(L"Point: %s\n", message);
}

void Helpers::printAcGePoint3d(const ads_point& pt)
{
	// Create a formatted string
	wchar_t message[100];
	swprintf_s(message, 100, L"(%f, %f, %f)", pt[X], pt[Y], pt[Z]);

	// Display the formatted string to the command line
	acutPrintf(L"Point: %s\n", message);
}

double Helpers::calcDistance(const ads_point& pt1, const ads_point& pt2)
{
	// Calculate the distance between two points
	double dX = pt1[X] - pt2[X];
	double dY = pt1[Y] - pt2[Y];
	double dZ = pt1[Z] - pt2[Z];
	return sqrt(dX * dX + dY * dY + dZ * dZ);
}
