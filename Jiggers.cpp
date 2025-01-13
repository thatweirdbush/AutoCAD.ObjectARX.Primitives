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
	_line->close();  // Close the AcDbLine
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
	if (Helpers::IsPointEqual(newPoint, _endPoint)) {
		return kNoChange;
	}
	_endPoint = newPoint;
	return kNormal;
}

Adesk::Boolean LineJig::update() {
	if (!_line) {
		return Adesk::kFalse;
	}
	if (Helpers::IsPointEqual(_startPoint, _endPoint)) {
		return Adesk::kFalse;
	}
	_line->setEndPoint(_endPoint);
	return Adesk::kTrue;
}

void LineJig::jig() {
	AcGePoint3d startPoint;
	ads_point pt;

	if (acedGetPoint(NULL, L"\nSpecify start point: ", pt) != RTNORM) {
		acutPrintf(L"\nNo point selected.");
		return;
	}
	startPoint.set(pt[0], pt[1], pt[2]);
	Helpers::printAcGePoint3d(startPoint);
	acutPrintf(L"\nSpecify end point: ");

	while (true)
	{
		LineJig jig(startPoint);
		DragStatus status = jig.drag();

		if (status == AcEdJig::kNormal) {
			AcDbBlockTable* pBlockTable;
			acdbHostApplicationServices()->workingDatabase()
				->getSymbolTable(pBlockTable, AcDb::kForRead);

			AcDbBlockTableRecord* pBlockTableRecord;
			pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
				AcDb::kForWrite);

			pBlockTable->close();
			AcDbEntity* pEntity = jig.entity();
			pBlockTableRecord->appendAcDbEntity(pEntity);

			Helpers::printAcGePoint3d(jig._endPoint);
			acutPrintf(L"\nLine created successfully.");

			pEntity->close();
			pBlockTableRecord->close();
			break;
		}
		else if (status == AcEdJig::kCancel) {
			acutPrintf(L"\nCommand canceled.");
			break;
		}
		else
			acutPrintf(L"\nStart point and end point must be different. Specify end point: ");
	}
}

//-----------------------------------------------------------------------------
//----- This will define the methods of the CircleJig class
//-----------------------------------------------------------------------------
CircleJig::CircleJig(const AcGePoint3d& center) :
	_center(center) {
	_radius = AcGeContext::gTol.equalPoint(); // Initialize the radius, do not use 0.0
	_circle = new AcDbCircle(_center, AcGeVector3d::kZAxis, _radius);  // Initialize the AcDbCircle
}

CircleJig::~CircleJig() {
	_circle->close();  // Close the AcDbCircle
}

AcDbEntity* CircleJig::entity() const {
	return _circle;
}

AcEdJig::DragStatus CircleJig::sampler() {
	double dist;
	DragStatus status = acquireDist(dist, _center);

	if (status != kNormal) {
		return kCancel;
	}
	if (dist == _radius) {
		return kNoChange;
	}
	_radius = dist;
	return kNormal;
}

Adesk::Boolean CircleJig::update() {
	if (!_circle) {
		return Adesk::kFalse;
	}
	if (_radius <= AcGeContext::gTol.equalPoint()) {
		return Adesk::kFalse;
	}
	_circle->setRadius(_radius);
	return Adesk::kTrue;
}

void CircleJig::jig() {
	AcGePoint3d center;
	ads_point pt;

	if (acedGetPoint(NULL, L"\nSpecify center point: ", pt) != RTNORM) {
		acutPrintf(L"\nNo point selected.");
		return;
	}
	center.set(pt[0], pt[1], pt[2]);
	Helpers::printAcGePoint3d(center);
	acutPrintf(L"\nSpecify radius: ");

	while (true)
	{
		CircleJig jig(center);

		DragStatus status = jig.drag();
		if (status == AcEdJig::kNormal) {
			AcDbBlockTable* pBlockTable;
			acdbHostApplicationServices()->workingDatabase()
				->getSymbolTable(pBlockTable, AcDb::kForRead);

			AcDbBlockTableRecord* pBlockTableRecord;
			pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
				AcDb::kForWrite);

			pBlockTable->close();
			AcDbEntity* pEntity = jig.entity();
			pBlockTableRecord->appendAcDbEntity(pEntity);

			acutPrintf(L"%f", jig._radius);
			acutPrintf(L"\nCircle created successfully.");

			pEntity->close();
			pBlockTableRecord->close();
			break;
		}
		else if (status == AcEdJig::kCancel) {
			acutPrintf(L"\nCommand canceled.");
			break;
		}
		else
			acutPrintf(L"\nRadius must be greater than 0. Specify radius: ");
	}
}














