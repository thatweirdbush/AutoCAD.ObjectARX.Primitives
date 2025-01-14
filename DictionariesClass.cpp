//-----------------------------------------------------------------------------
//----- DictionariesClass.cpp
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "DictionariesClass.h"

//-----------------------------------------------------------------------------
//----- This will define the static members of the Dictionaries class
//-----------------------------------------------------------------------------
void DictionariesClass::ADSK_TEST_LIST_NOD()
{
	// Get the current database
	AcDbDatabase* pDb =
		acdbHostApplicationServices()->workingDatabase();

	// Get the named object dictionary
	AcDbDictionary* pNOD = nullptr;
	int numEntries = 0;

	if (acdbOpenObject(pNOD, pDb->namedObjectsDictionaryId(), AcDb::kForRead) == Acad::eOk)
	{
		acutPrintf(L"\nDictionaries in Named Object Dictionary:");
		AcDbDictionaryIterator* iter = pNOD->newIterator();

		for (; !iter->done(); iter->next())
		{
			acutPrintf(L"\n - %s", iter->name());
			numEntries++;
		}
		delete iter;
		iter = nullptr;
		pNOD->close();
		acutPrintf(L"\nNumber of dictionaries in Named Object Dictionary: %d", numEntries);
	}
	else
	{
		acutPrintf(L"\nError getting named object dictionary.");
	}	
}

void DictionariesClass::ADSK_TEST_ADD_NOD()
{
	// Get the current database
	AcDbDatabase* pDb =
		acdbHostApplicationServices()->workingDatabase();

	// Get the named object dictionary
	AcDbDictionary* pNOD = nullptr;
	if (acdbOpenObject(pNOD, pDb->namedObjectsDictionaryId(), AcDb::kForWrite) == Acad::eOk)
	{
		const wchar_t* customDictName = L"MyCustomDictionary";
		if (!pNOD->has(customDictName))
		{
			// Create a new dictionary
			AcDbDictionary* pDict = new AcDbDictionary();
			AcDbObjectId dictId;
			pNOD->setAt(customDictName, pDict, dictId);
			pDict->close();
			acutPrintf(L"\nCustom dictionary %s created successfully!", customDictName);
		}
		else
		{
			acutPrintf(L"\nDictionary already exists.");
		}
		pNOD->close();
	}
	else
	{
		acutPrintf(L"\nError getting named object dictionary.");
	}	
}

void DictionariesClass::ADSK_TEST_ADD_NOD_DATA()
{
	// Get the current database
	AcDbDatabase* pDb =
		acdbHostApplicationServices()->workingDatabase();

	// Get the named object dictionary
	AcDbDictionary* pNOD = nullptr;
	if (acdbOpenObject(pNOD, pDb->namedObjectsDictionaryId(), AcDb::kForWrite) == Acad::eOk)
	{
		const wchar_t* customDictName = L"MyCustomDictionary";
		AcDbDictionary* pDict = nullptr;

		if (pNOD->has(customDictName))
		{
			pNOD->getAt(customDictName, pDict, AcDb::kForWrite);
			pNOD->close();
		}
		else
		{
			pNOD->close();
			acutPrintf(L"\nCustom dictionary does not exist.");
			return;
		}

		// Create a new Xrecord
		AcDbXrecord* pXRec = new AcDbXrecord();
		AcDbObjectId xRecId = AcDbObjectId::kNull;

		// Create a resbuf list
		resbuf* pResBuf = acutBuildList(
			AcDb::kDxfText, L"Custom data string",
			AcDb::kDxfReal, 3.14,
			AcDb::kDxfInt32, (Adesk::Int32)42,
			RTNONE);

		// Set the resbuf list to the Xrecord
		pXRec->setFromRbChain(*pResBuf);
		acutRelRb(pResBuf);

		// Add the Xrecord to the dictionary
		const wchar_t* customXRecName = L"MyCustomXRecord";
		pDict->setAt(customXRecName, pXRec, xRecId);
		pDict->close();
		pXRec->close();
		acutPrintf(L"\nNew Xrecord named \"%s\" added to \"%s\" dictionary.", customXRecName, customDictName);
	}
	else
	{
		acutPrintf(L"\nError getting named object dictionary.");
	}	
}

void DictionariesClass::ADSK_TEST_READ_NOD()
{
	AcDbDatabase* pDb =
		acdbHostApplicationServices()->workingDatabase();

	AcDbDictionary* pNOD = nullptr;
	if (acdbOpenObject(pNOD, pDb->namedObjectsDictionaryId(), AcDb::kForRead) != Acad::eOk)
	{		
		acutPrintf(L"\nError getting named object dictionary.");
		return;
	}

	const wchar_t* customDictName = L"MyCustomDictionary";
	if (!pNOD->has(customDictName))
	{
		acutPrintf(L"\nThe dictionary \"%s\" doesn't exist!", customDictName);
		pNOD->close();		
		return;
	}

	AcDbDictionary* pDict = nullptr;
	if (pNOD->getAt(customDictName, pDict, AcDb::kForRead) != Acad::eOk)
	{
		acutPrintf(L"\nError getting \"%s\" dictionary.", customDictName);
		pNOD->close();		
		return;
	}
	pNOD->close();

	const wchar_t* customXRecName = L"MyCustomXRecord";
	if (!pDict->has(customXRecName))
	{
		acutPrintf(L"\nThe Xrecord \"%s\" doesn't exist!", customXRecName);
		pDict->close();		
		return;
	}

	AcDbXrecord* pXRec = nullptr;
	if (pDict->getAt(customXRecName, pXRec, AcDb::kForRead) != Acad::eOk)
	{
		acutPrintf(L"\nError getting \"%s\" Xrecord.", customXRecName);
		pDict->close();		
		return;
	}
	pDict->close();

	resbuf* pResBuf = nullptr;
	pXRec->rbChain(&pResBuf);
	pXRec->close();

	if (pResBuf)
	{
		acutPrintf(L"\nXrecord data:");
		for (resbuf* pTemp = pResBuf; pTemp; pTemp = pTemp->rbnext)
		{
			switch (pTemp->restype)
			{
			case AcDb::kDxfText:
				acutPrintf(L"\nType: %d, Value: %s", pTemp->restype, pTemp->resval.rstring);
				break;
			case AcDb::kDxfReal:
				acutPrintf(L"\nType: %d, Value: %f", pTemp->restype, pTemp->resval.rreal);
				break;
			case AcDb::kDxfInt32:
				acutPrintf(L"\nType: %d, Value: %d", pTemp->restype, pTemp->resval.rlong);
				break;
			default:
				acutPrintf(L"\nType: %d, Value: (unsupported type)", pTemp->restype);
				break;
			}
		}
		acutRelRb(pResBuf);
	}	
}

void DictionariesClass::ADSK_TEST_DEL_NOD()
{
	// Get the current database
	AcDbDatabase* pDb =
		acdbHostApplicationServices()->workingDatabase();

	// Get the named object dictionary
	AcDbDictionary* pNOD = nullptr;
	if (acdbOpenObject(pNOD, pDb->namedObjectsDictionaryId(), AcDb::kForWrite) != Acad::eOk)
	{
		acutPrintf(L"\nError getting named object dictionary.");
		return;
	}

	// Get the custom dictionary
	const wchar_t* customDictName = L"MyCustomDictionary";
	if (!pNOD->has(customDictName))
	{
		acutPrintf(L"\nCustom dictionary does not exist.");
		pNOD->close();
		return;
	}

	// Delete the custom dictionary
	AcDbDictionary* customDict = nullptr;
	if (pNOD->getAt(customDictName, customDict, AcDb::kForWrite) != Acad::eOk)
	{
		acutPrintf(L"\nError getting custom dictionary.");
		pNOD->close();
		return;
	}
	customDict->erase();
	customDict->close();
	pNOD->close();
	acutPrintf(L"\nCustom dictionary deleted successfully!");
}
