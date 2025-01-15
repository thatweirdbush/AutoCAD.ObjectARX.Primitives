//-----------------------------------------------------------------------------
//----- SelectionSetUsages.cpp
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "SelectionSetUsages.h"

//-----------------------------------------------------------------------------
//----- This will define the static members of the SelectionSetUsages class
//-----------------------------------------------------------------------------
void SelectionSetUsages::ADSK_TEST_SSGET_CROSSING()
{
	ads_point pt1, pt2;

	// Get the first corner of the crossing window
	if (acedGetPoint(NULL, L"\nSpecify first corner: ", pt1) != RTNORM)
	{
		acutPrintf(L"\nError getting first corner of crossing window.");
		return;
	}

	// Get the second corner of the crossing window
	if (acedGetCorner(pt1, L"\nSpecify opposite corner: ", pt2) != RTNORM)
	{
		acutPrintf(L"\nError getting opposite corner of crossing window.");
		return;
	}

	// Create a crossing window
	ads_name ss;
	if (acedSSGet(L"C", pt1, pt2, NULL, ss) != RTNORM)
	{
		acutPrintf(L"\nError creating crossing window.");
		return;
	}

	// Get the length of the selection set
	int length;
	acedSSLength(ss, &length);

	// Change the color of the objects
	AcDbObjectId objId = AcDbObjectId::kNull;
	AcDbEntity* pEnt = nullptr;
	uint16_t color = Helpers::getRandColor();
	ads_name ent;

	for (int i = 0; i < length; i++)
	{
		acedSSName(ss, i, ent);
		acdbGetObjectId(objId, ent);
		acdbOpenObject(pEnt, objId, AcDb::kForWrite);

		// Change entity color randomly
		pEnt->setColorIndex(color);
		pEnt->close();
	}
	acedSSFree(ss);
	acutPrintf(L"\nThe color of %d selected objects has been changed.", length);
}

void SelectionSetUsages::ADSK_TEST_SSGET_FENCE()
{
	int numPoints;

	// Get the number of points
	if (acedGetInt(L"\nEnter the number of points: ", &numPoints) != RTNORM || numPoints < 2)
	{
		acutPrintf(L"\nInvalid number of points. Must be at least 2.");
		return;
	}

	// Create an array of points
	ads_point* points = new ads_point[numPoints];

	// Get the first point
	if (acedGetPoint(NULL, L"\nSpecify the first point: ", points[0]) != RTNORM)
	{
		acutPrintf(L"\nError getting point.");
		delete[] points;
		points = nullptr;
		return;
	}

	// Get the remaining points
	for (int i = 1; i < numPoints; i++)
	{
		if (acedGetPoint(points[i-1], L"\nSpecify next point: ", points[i]) != RTNORM)
		{
			acutPrintf(L"\nError getting point.");
			delete[] points;
			points = nullptr;
			return;
		}
	}

	// Build a resbuf list for the point list
	struct resbuf* pointlist = acutBuildList(RT3DPOINT, points[0], RTNONE);
	struct resbuf* current = pointlist;

	for (int i = 1; i < numPoints; i++)
	{
		// Add the next point to the list
		current->rbnext = acutNewRb(RT3DPOINT);
		current = current->rbnext;

		// Set the point values
        current->resval.rpoint[X] = points[i][X];
        current->resval.rpoint[Y] = points[i][Y];
        current->resval.rpoint[Z] = points[i][Z];
	}
	current->rbnext = nullptr; // Mark the end of the list

	// Create a fence
	ads_name ss;
	if (acedSSGet(L"F", pointlist, NULL, NULL, ss) != RTNORM)
	{
		acutRelRb(pointlist);
		delete[] points;
		points = nullptr;
		acutPrintf(L"\nError creating fence.");
		return;
	}

	acutRelRb(pointlist);
	delete[] points;
	points = nullptr;

	// Get the length of the selection set
	int length;
	acedSSLength(ss, &length);

	// Change the color of the objects
	AcDbObjectId objId = AcDbObjectId::kNull;
	AcDbEntity* pEnt = nullptr;
	uint16_t color = Helpers::getRandColor();
	ads_name ent;

	for (int i = 0; i < length; i++)
	{
		acedSSName(ss, i, ent);
		acdbGetObjectId(objId, ent);
		acdbOpenObject(pEnt, objId, AcDb::kForWrite);

		// Change entity color randomly
		pEnt->setColorIndex(color);
		pEnt->close();
	}
	acedSSFree(ss);
	acutPrintf(L"\nThe color of %d selected objects has been changed.", length);
}
