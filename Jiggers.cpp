//-----------------------------------------------------------------------------
//----- Jiggers.cpp
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "Jiggers.h"

//-----------------------------------------------------------------------------
//----- This will define the methods of the LineJig class
//-----------------------------------------------------------------------------
LineJig::LineJig(const AcGePoint3d& startPoint) :
	_startPoint(startPoint), _endPoint(startPoint) {
	_line = new AcDbLine(_startPoint, _endPoint);  // Initialize the AcDbLine
}

LineJig::~LineJig() {
	if (_line != nullptr) {
		_line->close();  // Close the AcDbLine
	}
}

AcDbEntity* LineJig::entity() const {
	return _line;
}

AcEdJig::DragStatus LineJig::sampler() {
	AcGePoint3d newPoint;
	DragStatus status = acquirePoint(newPoint);

	if (status != kNormal) {
		return kCancel;
	}
	if (newPoint.isEqualTo(_endPoint)) {
		return kNoChange;
	}
	_endPoint = newPoint;
	return kNormal;
}

Adesk::Boolean LineJig::update() {
	if (_line) {
		_line->setEndPoint(_endPoint);
		return Adesk::kTrue;
	}
	return Adesk::kFalse;
}

void LineJig::jig() {
	AcGePoint3d startPoint;
	ads_point pt;

	if (acedGetPoint(NULL, L"\nSpecify start point: ", pt) != RTNORM) {
		acutPrintf(L"\nNo point selected.");
		return;
	}
	startPoint.set(pt[0], pt[1], pt[2]);

	LineJig jig(startPoint);
	if (jig.drag() == AcEdJig::kNormal) {
		AcDbBlockTable* pBlockTable;
		acdbHostApplicationServices()->workingDatabase()
			->getSymbolTable(pBlockTable, AcDb::kForRead);

		AcDbBlockTableRecord* pBlockTableRecord;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
			AcDb::kForWrite);

		pBlockTable->close();
		AcDbEntity* pEntity = jig.entity();
		pBlockTableRecord->appendAcDbEntity(pEntity);
		acutPrintf(L"\nLine created successfully.");
		pEntity->close();
		pBlockTableRecord->close();
	}
}

//-----------------------------------------------------------------------------
//----- This will define the methods of the CircleJig class
//-----------------------------------------------------------------------------














