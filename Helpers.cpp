//-----------------------------------------------------------------------------
//----- Helpers.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "Helpers.h"

//-----------------------------------------------------------------------------
//----- This will define the static members of the Helpers class
//-----------------------------------------------------------------------------
uint16_t Helpers::mPreviousColor = -1;

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

uint16_t Helpers::getRandColor()
{
	if (mPreviousColor == -1)
	{
		mPreviousColor = rand() % 256;
		return mPreviousColor;
	}
	while (true)
	{
		uint16_t color = rand() % 256;

		// Check if the color is different from the previous color
		if (color != mPreviousColor)
		{
			mPreviousColor = color;
			return color;
		}
	}
}

double Helpers::CalculateAreaOfPolygon(AcDbPolyline* pPolyline) {
	if (pPolyline == nullptr || pPolyline->numVerts() < 3) {
		acutPrintf(L"Object is not a polygon or has less than 3 vertices.\n");
		return 0.0;
	}

	double area = 0.0;
	int numVerts = pPolyline->numVerts();

	AcGePoint3d prevPoint, currPoint;
	pPolyline->getPointAt(0, prevPoint); // Get the first point

	// Iterate through all points of the Polyline and apply the Shoelace formula
	for (int i = 1; i < numVerts; i++) {
		pPolyline->getPointAt(i, currPoint);
		area += prevPoint.x * currPoint.y - prevPoint.y * currPoint.x;
		prevPoint = currPoint;
	}

	// Close the polygon by calculating the area between the end point and the start point
	pPolyline->getPointAt(0, prevPoint);
	pPolyline->getPointAt(numVerts - 1, currPoint);
	area += currPoint.x * prevPoint.y - currPoint.y * prevPoint.x;

	return fabs(area) / 2.0;
}
