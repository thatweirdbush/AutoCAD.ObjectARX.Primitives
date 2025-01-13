//-----------------------------------------------------------------------------
//----- UserInteractions.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "UserInteractions.h"

//-----------------------------------------------------------------------------
//----- This will define the static members of the UserInteractions class
//-----------------------------------------------------------------------------
void UserInteractions::ADSK_TEST_GET_NAME_USING_GET_STRING()
{
	// Get a string from the user
    wchar_t pName[50];
	if (acedGetString(Adesk::kTrue, L"Enter your name: ", pName) == RTNORM)
	{
		// Create a formatted string
		wchar_t message[100];
        swprintf_s(message, 100, L"Your name is: %ls", pName);

		// Display the formatted string
		acedAlert(message);
		acutPrintf(L"Hello there: %s\n", pName);
	}
	else
	{
		// Display an error message
		acedAlert(L"Error getting name.");
	}
}

void UserInteractions::ADSK_TEST_CREATE_LINE_USING_GET_POINT()
{
    // Get the start point of the line
    ads_point ptStart;
    if (acedGetPoint(NULL, L"\nSpecify the start point: ", ptStart) != RTNORM)
    {
        acedAlert(L"\nError getting start point.");
        return;
    }
    Helpers::printAcGePoint3d(ptStart);

    // Get the end point of the line
    ads_point ptEnd;
    if (acedGetPoint(ptStart, L"\nSpecify the end point: ", ptEnd) != RTNORM)
    {
        acedAlert(L"\nError getting end point.");
        return;
    }
	Helpers::printAcGePoint3d(ptEnd);

    // Create a line
    AcDbLine* pLine = new AcDbLine(asPnt3d(ptStart), asPnt3d(ptEnd));

    // Get the current space
    AcDbBlockTable* pBlockTable;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);

    AcDbBlockTableRecord* pBlockTableRecord;
    pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
        AcDb::kForWrite);

    pBlockTable->close();
    AcDbObjectId lineId;
    pBlockTableRecord->appendAcDbEntity(lineId, pLine);
    pBlockTableRecord->close();
    pLine->close();
}

void UserInteractions::ADSK_TEST_GET_DISTANCE_BETWEEN_TWO_POINTS()
{
	// Get the first point
	ads_point ptStart;
	if (acedGetPoint(NULL, L"\nSpecify the first point: ", ptStart) != RTNORM)
	{
		acedAlert(L"\nError getting first point.");
		return;
	}
	Helpers::printAcGePoint3d(ptStart);

	// Get the second point
	ads_point ptEnd;
	if (acedGetPoint(ptStart, L"\nSpecify the second point: ", ptEnd) != RTNORM)
	{
		acedAlert(L"\nError getting second point.");
		return;
	}
	Helpers::printAcGePoint3d(ptEnd);

	// Calculate the distance between the two points
	double distance = Helpers::calcDistance(ptStart, ptEnd);

	// Display the formatted string
	acutPrintf(L"The distance between the two points is: %f", distance);
}

void UserInteractions::ADSK_TEST_GET_KEYWORDS()
{
	// Define the keywords
	wchar_t keywords[] = { L"Circle Line Text" };

	// Get the keyword from the user
	int keywordIndex;
	if (acedInitGet(RSG_NONULL, L"Circle Line Text") == RTNORM)
	{
		keywordIndex = acedGetKword(L"\nSpecify the entity type [Circle/Line/Text]: ", keywords);
	}
	else
	{
		acedAlert(L"\nError getting keyword.");
		return;
	}
	// Display the selected keyword
	acutPrintf(L"\nThe selected keyword is: %s", keywords);
}

void UserInteractions::ADSK_TEST_GET_ANGLE()
{
    // Get the first point
    ads_point ptStart;
    if (acedGetPoint(NULL, L"\nSpecify the first point: ", ptStart) != RTNORM)
    {
        acedAlert(L"\nError getting first point.");
        return;
    }
    Helpers::printAcGePoint3d(ptStart);

    // Get the second point
    ads_point ptEnd;
    if (acedGetPoint(ptStart, L"\nSpecify the second point: ", ptEnd) != RTNORM)
    {
        acedAlert(L"\nError getting second point.");
        return;
    }
    Helpers::printAcGePoint3d(ptEnd);

    // Convert ads_point to AcGePoint3d
    AcGePoint3d startPoint(asPnt3d(ptStart));
    AcGePoint3d endPoint(asPnt3d(ptEnd));

    // Get the angle between the two points
    double angle = acutAngle(ptStart, ptEnd);

    // Display the angle
    acutPrintf(L"The angle between the two points is: %f", angle);
}

/// <summary>
/// Create a rectangle using getCorner
/// </summary>
void UserInteractions::ADSK_TEST_GET_CORNER()
{
	// Get the first point
	ads_point ptStart;
	if (acedGetPoint(NULL, L"\nSpecify the first point: ", ptStart) != RTNORM)
	{
		acedAlert(L"\nError getting first point.");
		return;
	}
	Helpers::printAcGePoint3d(ptStart);
	// Get the second point
	ads_point ptEnd;
	if (acedGetCorner(ptStart, L"\nSpecify the second point: ", ptEnd) != RTNORM)
	{
		acedAlert(L"\nError getting second point.");
		return;
	}
	Helpers::printAcGePoint3d(ptEnd);

	// Create a rectangle
	AcDbPolyline* pPoly = new AcDbPolyline(4);
	pPoly->addVertexAt(0, asPnt2d(ptStart));
	pPoly->addVertexAt(1, AcGePoint2d(ptEnd[X], ptStart[Y]));
	pPoly->addVertexAt(2, asPnt2d(ptEnd));
	pPoly->addVertexAt(3, AcGePoint2d(ptStart[X], ptEnd[Y]));
	pPoly->setClosed(Adesk::kTrue);

	// Add the rectangle to the model space
	AcDbBlockTable* pBlockTable;
	acdbHostApplicationServices()->workingDatabase()
		->getSymbolTable(pBlockTable, AcDb::kForRead);

	AcDbBlockTableRecord* pBlockTableRecord;
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
		AcDb::kForWrite);

	pBlockTable->close();
	AcDbObjectId polyId;
	pBlockTableRecord->appendAcDbEntity(polyId, pPoly);
	pBlockTableRecord->close();
	pPoly->close();
}

void UserInteractions::ADSK_TEST_CHANGE_COLOR_USING_GET_ENTITY_SELECTION()
{
	// Get the selected object
	ads_name en;
	ads_point pt;
	if (acedEntSel(L"\nSelect an object: ", en, pt) != RTNORM)
	{
		acedAlert(L"\nError getting object.");
		return;
	}
	// Open the selected object
	AcDbObjectId pObjId;
	acdbGetObjectId(pObjId, en);

	AcDbEntity* pEnt;
	acdbOpenObject(pEnt, pObjId, AcDb::kForWrite);
	acutPrintf(pEnt->isA()->name());

	// Change the color of the object randomly
	pEnt->setColorIndex(Helpers::getRandColor());
	acutPrintf(L"\nThe color of the %ls has been changed.", pEnt->isA()->name());

	// Close the object
	pEnt->close();
}

void UserInteractions::ADSK_TEST_CHANGE_COLOR_USING_GET_SELECTION_SET()
{
	// Display a custom prompt to the user
	acutPrintf(L"\nSelect LINE objects on Layer 0 to change color to Green:");

	// Define the resbufs
	struct resbuf rbLine;
	struct resbuf rbLayer;

	// Initialize the Line and Layer resbufs
	rbLine.restype = 0;
	rbLine.resval.rstring = L"LINE";
	rbLine.rbnext = &rbLayer; // Link to the next resbuf

	rbLayer.restype = 8;
	rbLayer.resval.rstring = L"0";
	rbLayer.rbnext = NULL; // End of the resbufs

	// Get the selection set
	ads_name ss;
	ads_name ent;

	if (acedSSGet(NULL, NULL, NULL, &rbLine, ss) != RTNORM)
	{
		acedAlert(L"\nError getting selection set.");
		return;
	}

	// Get the length of the selection set
	int length;
	acedSSLength(ss, &length);

	// Change the color of the objects to Green
	AcDbObjectId objId = AcDbObjectId::kNull;
	AcDbEntity* pEnt = NULL;
	uint16_t color = Helpers::getRandColor();

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

void UserInteractions::ADSK_TEST_CHANGE_COLOR_USING_GET_SELECTION_SET_EXTENDED()
{
	// Define the keywords
	wchar_t keywords[] = { L"A I P W WP C CP F" };

	// Get the keyword from the user
	int keywordIndex;
	if (acedInitGet(NULL, L"A I P W WP C CP F") == RTNORM)
	{
		keywordIndex = acedGetKword(L"\nSpecify the selection mode [A/I/P/W/WP/C/CP/F]: ", keywords);
	}
	else
	{
		acedAlert(L"\nError getting keyword.");
		return;
	}

	ads_name ss;
	ads_name ent;

	// Options for point list when using modes like WP, CP, F
	ads_point pt1 = { 0.0, 0.0, 0.0 };
	ads_point pt2 = { 5'000.0, 5'000.0, 0.0 };
	ads_point pt3 = { 10'000.0, 5'000.0, 0.0 };
	ads_point pt4 = { 5'000.0, 0.0, 0.0 };
	struct resbuf* pointlist = acutBuildList(
		RTPOINT, pt1, RTPOINT, pt2, RTPOINT, pt3, RTPOINT, pt4, 0);

	int result;
	if (wcscmp(keywords, L"W") == 0) {
		result = acedSSGet(L"W", pt1, pt2, NULL, ss);
	}
	else if (wcscmp(keywords, L"WP") == 0) {
		result = acedSSGet(L"WP", pointlist, NULL, NULL, ss);
	}
	else if (wcscmp(keywords, L"C") == 0) {
		result = acedSSGet(L"C", pt1, pt2, NULL, ss);
	}
	else if (wcscmp(keywords, L"CP") == 0) {
		result = acedSSGet(L"CP", pointlist, NULL, NULL, ss);
	}
	else if (wcscmp(keywords, L"F") == 0) {
		result = acedSSGet(L"F", pointlist, NULL, NULL, ss);
	}
	else if (wcscmp(keywords, L"A") == 0) {
		result = acedSSGet(L"A", NULL, NULL, NULL, ss);
	}
	else if (wcscmp(keywords, L"I") == 0) {
		result = acedSSGet(L"I", NULL, NULL, NULL, ss);
	}
	else if (wcscmp(keywords, L"P") == 0) {
		result = acedSSGet(L"P", NULL, NULL, NULL, ss);
	}
	else if (wcscmp(keywords, L"") == 0) {
		result = acedSSGet(L"A", NULL, NULL, NULL, ss);
	}
	else {
		result = acedSSGet(L"A", NULL, NULL, NULL, ss);
	}
	// Free the point list
	acutRelRb(pointlist);

	if (result != RTNORM) {
		acedAlert(L"\nError getting selection set.");
		return;
	}

	// Get the length of the selection set
	int length;
	acedSSLength(ss, &length);

	// Change the color of the objects to Green
	AcDbObjectId objId = AcDbObjectId::kNull;
	AcDbEntity* pEnt = NULL;
	uint16_t color = Helpers::getRandColor();

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

void UserInteractions::ADSK_TEST_MOVE_OBJECT_USING_GET_POINT()
{
	// Get the selected object
	ads_name en;
	ads_point pt;
	if (acedEntSel(L"\nSelect an object: ", en, pt) != RTNORM)
	{
		acedAlert(L"\nError getting object.");
		return;
	}
	// Open the selected object
	AcDbObjectId pObjId;
	acdbGetObjectId(pObjId, en);

	AcDbEntity* pEnt;
	acdbOpenObject(pEnt, pObjId, AcDb::kForWrite);
	acutPrintf(pEnt->isA()->name());

	//  Get the base point
	ads_point ptBase;
	if (acedGetPoint(NULL, L"\nSpecify the base point: ", ptBase) != RTNORM)
	{
		acedAlert(L"\nError getting base point.");
		return;
	}
	Helpers::printAcGePoint3d(ptBase);

	// Get the new position of the object
	ads_point ptNew;
	if (acedGetPoint(NULL, L"\nSpecify the new position: ", ptNew) != RTNORM)
	{
		acedAlert(L"\nError getting new position.");
		return;
	}
	Helpers::printAcGePoint3d(ptNew);

	// Calculate the vector
	AcGeVector3d vecMove(asPnt3d(ptNew) - asPnt3d(ptBase));

	// Move the object to the new position
	pEnt->transformBy(AcGeMatrix3d::translation(vecMove));

	// Close the object
	pEnt->close();
}

void UserInteractions::ADSK_TEST_MOVE_LINE_ONLY()
{
	// Get the selected object
	ads_name en;
	ads_point pt;
	if (acedEntSel(L"\nSelect an object: ", en, pt) != RTNORM)
	{
		acedAlert(L"\nError getting object.");
		return;
	}
	// Open the selected object
	AcDbObjectId pObjId;
	acdbGetObjectId(pObjId, en);

	AcDbEntity* pEnt;
	acdbOpenObject(pEnt, pObjId, AcDb::kForWrite);
	acutPrintf(pEnt->isA()->name());

	// Check if the selected object is a line
	if (pEnt->isKindOf(AcDbLine::desc()))
	{
		// Get the base point
		ads_point ptBase;
		if (acedGetPoint(NULL, L"\nSpecify the base point: ", ptBase) != RTNORM)
		{
			acedAlert(L"\nError getting base point.");
			return;
		}
		Helpers::printAcGePoint3d(ptBase);

		// Get the new position of the object
		ads_point ptNew;
		if (acedGetPoint(NULL, L"\nSpecify the new position: ", ptNew) != RTNORM)
		{
			acedAlert(L"\nError getting new position.");
			return;
		}
		Helpers::printAcGePoint3d(ptNew);

		// Calculate the vector
		AcGeVector3d vecMove(asPnt3d(ptNew) - asPnt3d(ptBase));

		// Move the object to the new position
		pEnt->transformBy(AcGeMatrix3d::translation(vecMove));
	}
	else
	{
		acedAlert(L"\nSelected object is not a line.");
	}
	// Close the object
	pEnt->close();
}

void UserInteractions::ADSK_TEST_ROTATE_OBJECT()
{
	// Get the selected object
	ads_name en;
	ads_point pt;
	if (acedEntSel(L"\nSelect an object: ", en, pt) != RTNORM)
	{
		acedAlert(L"\nError getting object.");
		return;
	}
	// Open the selected object
	AcDbObjectId pObjId;
	acdbGetObjectId(pObjId, en);

	AcDbEntity* pEnt;
	acdbOpenObject(pEnt, pObjId, AcDb::kForWrite);
	acutPrintf(pEnt->isA()->name());

	// Get the base point
	ads_point ptBase;
	if (acedGetPoint(NULL, L"\nSpecify the base point: ", ptBase) != RTNORM)
	{
		acedAlert(L"\nError getting base point.");
		return;
	}
	Helpers::printAcGePoint3d(ptBase);

	// Get the angle
	ads_real angle;
	if (acedGetAngle(ptBase, L"\nSpecify the angle: ", &angle) != RTNORM)
	{
		acedAlert(L"\nError getting angle.");
		return;
	}
	// Rotate the object
	pEnt->transformBy(AcGeMatrix3d::rotation(angle, AcGeVector3d::kZAxis, asPnt3d(ptBase)));

	// Close the object
	pEnt->close();
}

void UserInteractions::ADSK_TEST_MIRROR_OBJECT_USING_LINE()
{
	// Get the selected object
	ads_name en;
	ads_point pt;
	if (acedEntSel(L"\nSelect an object: ", en, pt) != RTNORM)
	{
		acedAlert(L"\nError getting object.");
		return;
	}
	// Open the selected object
	AcDbObjectId pObjId;
	acdbGetObjectId(pObjId, en);

	AcDbEntity* pEnt;
	acdbOpenObject(pEnt, pObjId, AcDb::kForWrite);
	acutPrintf(pEnt->isA()->name());

	// Get the first point
	ads_point ptFirst;
	if (acedGetPoint(NULL, L"\nSpecify the first point: ", ptFirst) != RTNORM)
	{
		acedAlert(L"\nError getting first point.");
		return;
	}
	Helpers::printAcGePoint3d(ptFirst);

	// Get the second point
	ads_point ptSecond;
	if (acedGetPoint(ptFirst, L"\nSpecify the second point: ", ptSecond) != RTNORM)
	{
		acedAlert(L"\nError getting second point.");
		return;
	}
	Helpers::printAcGePoint3d(ptSecond);

	// Calculate the mirror line
	AcGeLine3d mirrorLine(asPnt3d(ptFirst), asPnt3d(ptSecond));

	// Mirror the object
	pEnt->transformBy(AcGeMatrix3d::mirroring(mirrorLine));
	
	// Close the object
	pEnt->close();
}

void UserInteractions::ADSK_TEST_SCALE_OBJECT()
{
	// Get the selected object
	ads_name en;
	ads_point pt;
	if (acedEntSel(L"\nSelect an object: ", en, pt) != RTNORM)
	{
		acedAlert(L"\nError getting object.");
		return;
	}
	// Open the selected object
	AcDbObjectId pObjId;
	acdbGetObjectId(pObjId, en);

	AcDbEntity* pEnt;
	acdbOpenObject(pEnt, pObjId, AcDb::kForWrite);
	acutPrintf(pEnt->isA()->name());

	// Get the base point
	ads_point ptBase;
	if (acedGetPoint(NULL, L"\nSpecify the base point: ", ptBase) != RTNORM)
	{
		acedAlert(L"\nError getting base point.");
		return;
	}
	Helpers::printAcGePoint3d(ptBase);

	// Get the scale factor
	ads_real scaleFactor;
	if (acedGetReal(L"\nSpecify the scale factor: ", &scaleFactor) != RTNORM)
	{
		acedAlert(L"\nError getting scale factor.");
		return;
	}
	// Scale the object
	pEnt->transformBy(AcGeMatrix3d::scaling(scaleFactor, asPnt3d(ptBase)));

	// Close the object
	pEnt->close();
}

void UserInteractions::ADSK_TEST_CALCULATE_POLYGON_AREA()
{
	// Get the number of sides
	int sides;
	if (acedGetInt(L"\nEnter the number of sides: ", &sides) != RTNORM)
	{
		acedAlert(L"\nError getting number of sides.");
		return;
	}

	// Create Polygon's points
	ads_point* points = new ads_point[sides];
	AcDbPolyline* pPoly = new AcDbPolyline(sides);

	// Get the points
	for (int i = 0; i < sides; i++)
	{
		if (acedGetPoint(NULL, L"\nSpecify a point: ", points[i]) != RTNORM)
		{
			acedAlert(L"\nError getting point.");
			return;
		}
		Helpers::printAcGePoint3d(points[i]);
		pPoly->addVertexAt(i, asPnt2d(points[i]));
	}
	pPoly->setClosed(Adesk::kTrue);

	// Add the polygon to the model space
	AcDbBlockTable* pBlockTable;
	acdbHostApplicationServices()->workingDatabase()
		->getSymbolTable(pBlockTable, AcDb::kForRead);

	AcDbBlockTableRecord* pBlockTableRecord;
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
		AcDb::kForWrite);

	pBlockTable->close();
	AcDbObjectId polyId;
	pBlockTableRecord->appendAcDbEntity(polyId, pPoly);
	pBlockTableRecord->close();

	// Calculate the area of the polygon
	double area = Helpers::CalculateAreaOfPolygon(pPoly);

	// Display the area
	acutPrintf(L"\nThe area of the polygon is: %f", area);

	// Free the memory
	delete[] points;
	pPoly->close();
}
