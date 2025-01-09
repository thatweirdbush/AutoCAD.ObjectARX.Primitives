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
    if (acedGetPoint(NULL, L"\Specify the start point: ", ptStart) != RTNORM)
    {
        acedAlert(L"\nError getting start point.");
        return;
    }

    // Convert the point to a string for printing
    wchar_t ptStartStr[100];
    swprintf_s(ptStartStr, 100, L"(%f, %f, %f)", ptStart[X], ptStart[Y], ptStart[Z]);
    acutPrintf(ptStartStr);

    // Get the end point of the line
    ads_point ptEnd;
    if (acedGetPoint(ptStart, L"\Specify the end point: ", ptEnd) != RTNORM)
    {
        acedAlert(L"\nError getting end point.");
        return;
    }

    // Convert the point to a string for printing
	wchar_t ptEndStr[100];
    swprintf_s(ptEndStr, 100, L"(%f, %f, %f)", ptEnd[X], ptEnd[Y], ptEnd[Z]);
	acutPrintf(ptEndStr);

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


