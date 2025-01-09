//-----------------------------------------------------------------------------
//----- PrimitiveEntities.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "PrimitiveEntities.h"

//-----------------------------------------------------------------------------
//----- This will define the static members of the PrimitiveEntities class
//-----------------------------------------------------------------------------

void ADSK_PrimitiveEntities::ADSK_TEST_DRAW_LINE()
{
	AcGePoint3d startPt(10.0, 10.0, 0.0);
	AcGePoint3d endPt(30.0, 10.0, 0.0);

	AcDbLine* pLine = new AcDbLine(startPt, endPt);

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

void ADSK_PrimitiveEntities::ADSK_TEST_DRAW_CIRCLE()
{
	AcGePoint3d center(9.0, 3.0, 0.0);
	AcGeVector3d normal(0.0, 0.0, 1.0);
	double radius = 10.0;

	AcDbCircle* pCirc = new AcDbCircle(center, normal, radius);

	AcDbBlockTable* pBlockTable;
	acdbHostApplicationServices()->workingDatabase()
		->getSymbolTable(pBlockTable, AcDb::kForRead);

	AcDbBlockTableRecord* pBlockTableRecord;
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
		AcDb::kForWrite);

	pBlockTable->close();
	AcDbObjectId circleId;
	pBlockTableRecord->appendAcDbEntity(circleId, pCirc);
	pBlockTableRecord->close();
	pCirc->close();
}

void ADSK_PrimitiveEntities::ADSK_TEST_CREATE_MTEXT()
{
	AcDbMText* pMText = new AcDbMText();
	pMText->setLocation(AcGePoint3d(10.0, 10.0, 0.0));
	pMText->setContents(L"Hello, World!");
	pMText->setTextHeight(100.0);

	AcDbBlockTable* pBlockTable;
	acdbHostApplicationServices()->workingDatabase()
		->getSymbolTable(pBlockTable, AcDb::kForRead);

	AcDbBlockTableRecord* pBlockTableRecord;
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
		AcDb::kForWrite);

	pBlockTable->close();
	AcDbObjectId mTextId;
	pBlockTableRecord->appendAcDbEntity(mTextId, pMText);
	pBlockTableRecord->close();
	pMText->close();
}

void ADSK_PrimitiveEntities::ADSK_TEST_CREATE_ARC()
{
	AcGePoint3d center(10.0, 10.0, 0.0);
	double radius = 10.0;
	double startAngle = 0.0;
	double endAngle = Pi / 2.0;

	AcDbArc* pArc = new AcDbArc(center, radius, startAngle, endAngle);

	AcDbBlockTable* pBlockTable;
	acdbHostApplicationServices()->workingDatabase()
		->getSymbolTable(pBlockTable, AcDb::kForRead);

	AcDbBlockTableRecord* pBlockTableRecord;
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
		AcDb::kForWrite);

	pBlockTable->close();
	AcDbObjectId arcId;
	pBlockTableRecord->appendAcDbEntity(arcId, pArc);
	pBlockTableRecord->close();
	pArc->close();
}

void ADSK_PrimitiveEntities::ADSK_TEST_CREATE_POLYLINE()
{
	AcDbPolyline* pPoly = new AcDbPolyline(4);
	pPoly->addVertexAt(0, AcGePoint2d(0.0, 0.0));
	pPoly->addVertexAt(1, AcGePoint2d(10.0, 0.0));
	pPoly->addVertexAt(2, AcGePoint2d(10.0, 10.0));
	pPoly->addVertexAt(3, AcGePoint2d(0.0, 10.0));
	pPoly->setClosed(Adesk::kTrue);

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

void ADSK_PrimitiveEntities::ADSK_TEST_CREATE_NEW_LAYER()
{
	AcDbLayerTable* pLayerTable;

	acdbHostApplicationServices()->workingDatabase()
		->getSymbolTable(pLayerTable, AcDb::kForWrite);

	AcDbLayerTableRecord* pLayerTableRecord =
		new AcDbLayerTableRecord;

	pLayerTableRecord->setName(L"ADSK_MYLAYER");

	// Defaults are used for other properties of 
	// the layer if they are not otherwise specified.
	//
	pLayerTable->add(pLayerTableRecord);
	pLayerTable->close();
	pLayerTableRecord->close();
}

void ADSK_PrimitiveEntities::ADSK_TEST_PRINT_ALL()
{
	int rc;
	wchar_t blkName[50];
	rc = acedGetString(Adesk::kTrue,
		L"Enter Block Name <CR for current space>: ",
		blkName);

	if (rc != RTNORM)
		return;

	if (blkName[0] == '\0') {
		if (acdbHostApplicationServices()->workingDatabase()
			->tilemode() == Adesk::kFalse) {
			struct resbuf rb;
			acedGetVar(L"cvport", &rb);
			if (rb.resval.rint == 1) {
				wcscpy(blkName, ACDB_PAPER_SPACE);
			}
			else {
				wcscpy(blkName, ACDB_MODEL_SPACE);
			}
		}
		else {
			wcscpy(blkName, ACDB_MODEL_SPACE);
		}
	}
	AcDbBlockTable* pBlockTable;
	acdbHostApplicationServices()->workingDatabase()
		->getSymbolTable(pBlockTable, AcDb::kForRead);

	AcDbBlockTableRecord* pBlockTableRecord;
	pBlockTable->getAt(blkName, pBlockTableRecord,
		AcDb::kForRead);
	pBlockTable->close();

	AcDbBlockTableRecordIterator* pBlockIterator;
	pBlockTableRecord->newIterator(pBlockIterator);

	for (; !pBlockIterator->done();
		pBlockIterator->step())
	{
		AcDbEntity* pEntity;
		pBlockIterator->getEntity(pEntity, AcDb::kForRead);

		AcDbHandle objHandle;
		pEntity->getAcDbHandle(objHandle);

		wchar_t handleStr[20];
		objHandle.getIntoAsciiBuffer(handleStr);

		const wchar_t* pCname = pEntity->isA()->name();
		acutPrintf(L"Object Id %lx, handle %s, class %s.\n",
			pEntity->objectId(), handleStr, pCname);
		pEntity->close();
	}
	delete pBlockIterator;
	pBlockTableRecord->close();
	acutPrintf(L"\n");
}

void ADSK_PrimitiveEntities::ADSK_TEST_CREATE_NEW_BLOCK()
{
	// Create and name a new block table record.
	//
	AcDbBlockTableRecord* pBlockTableRec
		= new AcDbBlockTableRecord();
	pBlockTableRec->setName(L"ASDK-NO-ATTR");

	// Get the block table.
	//
	AcDbBlockTable* pBlockTable = NULL;
	acdbHostApplicationServices()->workingDatabase()
		->getSymbolTable(pBlockTable, AcDb::kForWrite);

	// Add the new block table record to the block table.
	//
	AcDbObjectId blockTableRecordId;
	pBlockTable->add(blockTableRecordId, pBlockTableRec);
	pBlockTable->close();

	// Create and add a line entity to the component's
	// block record.
	//
	AcDbLine* pLine = new AcDbLine();
	AcDbObjectId lineId;
	pLine->setStartPoint(AcGePoint3d(3, 3, 0));
	pLine->setEndPoint(AcGePoint3d(6, 6, 0));
	pLine->setColorIndex(3); // Green

	pBlockTableRec->appendAcDbEntity(lineId, pLine);
	pLine->close();
	pBlockTableRec->close();
}

void ADSK_PrimitiveEntities::ADSK_TEST_PRINT_LINETYPES()
{
	AcDbLinetypeTable* pLinetypeTbl;
	acdbHostApplicationServices()->workingDatabase()
		->getSymbolTable(pLinetypeTbl, AcDb::kForRead);

	// Create a new iterator that starts at table
	// beginning and skips deleted.
	//
	AcDbLinetypeTableIterator* pLtIterator;
	pLinetypeTbl->newIterator(pLtIterator);

	// Walk the table, getting every table record and
	// printing the linetype name.
	//
	AcDbLinetypeTableRecord* pLtTableRcd;
	wchar_t* pLtName;

	for (; !pLtIterator->done(); pLtIterator->step()) {
		pLtIterator->getRecord(pLtTableRcd, AcDb::kForRead);

		pLtTableRcd->getName(pLtName);
		pLtTableRcd->close();

		acutPrintf(L"\nLinetype name is:  %s", pLtName);
		free(pLtName);
	}
	delete pLtIterator;
	pLinetypeTbl->close();
}
