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

void UserInteractions::ADSK_TEST_CHANGE_COLOR_USING_GET_SELECTION()
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

	// Change the color of the object to Green
	pEnt->setColorIndex(3);
	acutPrintf(L"\nThe color of the %ls has been changed to Green.", pEnt->isA()->name());

	// Close the object
	pEnt->close();
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


