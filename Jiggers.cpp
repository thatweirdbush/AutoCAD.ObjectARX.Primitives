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

//-----------------------------------------------------------------------------
//----- This will define the methods of the PolylineJig class
//-----------------------------------------------------------------------------
PolylineJig::PolylineJig(const AcGePoint3d& startPoint)
{
	_startPoint = startPoint;
	_nextPoint = startPoint;
	_polyline = new AcDbPolyline();  // Initialize the AcDbPolyline
	_polyline->addVertexAt(0, AcGePoint2d(_startPoint.x, _startPoint.y));
	_polyline->setClosed(Adesk::kFalse);  // Open polyline
	addDummyVertex();
}

PolylineJig::~PolylineJig() {
	_polyline->close();  // Close the AcDbPolyline
}

AcDbEntity* PolylineJig::entity() const {
	return _polyline;
}

AcEdJig::DragStatus PolylineJig::sampler() {
	AcGePoint3d newPoint;
	DragStatus status = acquirePoint(newPoint);

	if (status != kNormal) {
		return kCancel;
	}
	_nextPoint = newPoint;
	return kNormal;
}

Adesk::Boolean PolylineJig::update() {
	if (!_polyline) {
		return Adesk::kFalse;
	}
	_polyline->setPointAt(
		_polyline->numVerts() - 1,
		AcGePoint2d(_nextPoint.x, _nextPoint.y)
	);
	return Adesk::kTrue;
}

void PolylineJig::addDummyVertex() {
	_polyline->addVertexAt(
		_polyline->numVerts(),
		AcGePoint2d(0.0, 0.0)
	);
}

void PolylineJig::append() {
	AcDbBlockTable* pBlockTable;
	acdbHostApplicationServices()->workingDatabase()
		->getSymbolTable(pBlockTable, AcDb::kForRead);

	AcDbBlockTableRecord* pBlockTableRecord;
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
		AcDb::kForWrite);

	pBlockTable->close();
	pBlockTableRecord->appendAcDbEntity(_polyline);

	acutPrintf(L"\nPolyline created successfully.");
	_polyline->close();
	pBlockTableRecord->close();
}

void PolylineJig::jig() {
	AcGePoint3d startPoint;
	ads_point pt;

	if (acedGetPoint(NULL, L"\nSpecify start point: ", pt) != RTNORM) {
		acutPrintf(L"\nNo point selected.");
		return;
	}
	startPoint.set(pt[0], pt[1], pt[2]);
	Helpers::printAcGePoint3d(startPoint);

	PolylineJig jig(startPoint);
	acutPrintf(L"\nSpecify next point: ");
	while (true)
	{
		DragStatus status = jig.drag();
		if (status == AcEdJig::kNormal) {
			jig.addDummyVertex();
		}
		else if (status == AcEdJig::kCancel) {
			Helpers::removeLastVertex(jig._polyline);
			if (jig._polyline->numVerts() > 1) {
				jig.append();
			}
			else {
				acutPrintf(L"\nCommand canceled.");
			}
			break;
		}
		else
			acutPrintf(L"\nNext point must be different. Specify next point: ");
	}
}

//-----------------------------------------------------------------------------
//----- This will define the methods of the ArcJig class
//-----------------------------------------------------------------------------
ArcJig::ArcJig(const AcGePoint3d& startPoint, const AcGePoint3d& secondPoint) :
	_startPoint(startPoint), _secondPoint(secondPoint)
{
	_center = startPoint;
	_endPoint = startPoint;
	_radius = AcGeContext::gTol.equalPoint(); // Do not use 0.0
	_startAngle = 0.0;
	_endAngle = 1.0;

	// Initialize the AcDbArc
	_arc = new AcDbArc();
	_arc->setCenter(_startPoint);
	_arc->setRadius(_radius);
	_arc->setStartAngle(_startAngle);
	_arc->setEndAngle(_endAngle);
}

ArcJig::~ArcJig() {
	_arc->close();  // Close the AcDbArc
}

AcDbEntity* ArcJig::entity() const {
	return _arc;
}

AcEdJig::DragStatus ArcJig::sampler() {
	AcGePoint3d endPoint;
	DragStatus status = acquirePoint(endPoint, _secondPoint);

	if (status != kNormal) {
		return kCancel;
	}
	if (Helpers::IsPointEqual(endPoint, _startPoint) ||
		Helpers::IsPointEqual(endPoint, _secondPoint)) {
		return kNoChange;
	}
	if (isAligned(_startPoint, _secondPoint, endPoint)) {
		_arc->setVisibility(AcDb::kInvisible);
		_endPoint = endPoint;
		return kNoChange;
	}
	// Calculate the center of the arc
	std::tuple<bool, AcGePoint3d> center =
		getArcCenter(_startPoint, _secondPoint, endPoint);

	if (!std::get<0>(center)) {
		return kNoChange; // Skip if points are collinear
	}
	_center = std::get<1>(center);
	_endPoint = endPoint;

	// Calculate the radius of the arc
	_radius = _center.distanceTo(_startPoint);

	// Calculate the start and end angles of the arc
	_startAngle = atan2(_startPoint.y - _center.y, _startPoint.x - _center.x);
	_endAngle = atan2(_endPoint.y - _center.y, _endPoint.x - _center.x);

	// Swap the angles to ensure the arc is drawn in the correct direction
	if (_endPoint.y <= _secondPoint.y) {
		double temp = _startAngle;
		_startAngle = _endAngle;
		_endAngle = temp + 2 * MathConstants::Pi;
	}

	// Re-display the arc when the three points are no longer collinear
	_arc->setVisibility(AcDb::kVisible);
	return kNormal;
}

Adesk::Boolean ArcJig::update() {
	if (!_arc) {
		return Adesk::kFalse;
	}
	if (_radius <= AcGeContext::gTol.equalPoint()) {
		return Adesk::kFalse;
	}
	_arc->setCenter(_center);
	_arc->setRadius(_radius);
	_arc->setStartAngle(_startAngle);
	_arc->setEndAngle(_endAngle);
	return Adesk::kTrue;
}

std::tuple<bool, AcGePoint3d> ArcJig::getArcCenter(
	const AcGePoint3d& startPoint,
	const AcGePoint3d& secondPoint,
	const AcGePoint3d& endPoint
) {
	// Midpoints between the points
	AcGePoint3d midAB = startPoint + (secondPoint - startPoint) / 2;
	AcGePoint3d midBC = secondPoint + (endPoint - secondPoint) / 2;

	// Perpendicular bisector of the line between start - second points (AB)
	AcGeVector3d dirAB = secondPoint - startPoint;
	AcGeVector3d perpAB = dirAB.rotateBy(MathConstants::Pi / 2, AcGeVector3d::kZAxis);

	// Perpendicular bisector of the line between second - end points (BC)
	AcGeVector3d dirBC = endPoint - secondPoint;
	AcGeVector3d perpBC = dirBC.rotateBy(MathConstants::Pi / 2, AcGeVector3d::kZAxis);

	// Calculate the intersection point of the two lines
	AcGeLine3d line1(midAB, midAB + perpAB);
	AcGeLine3d line2(midBC, midBC + perpBC);

	AcGePoint3d arcCenter;
	if (line1.intersectWith(line2, arcCenter) == Adesk::kTrue) {
		return std::make_tuple(true, arcCenter);
	}
	return std::make_tuple(false, AcGePoint3d());
}

bool ArcJig::isAligned(
	const AcGePoint3d& startPoint,
	const AcGePoint3d& secondPoint,
	const AcGePoint3d& endPoint
) {
	// The area of a triangle is calculated by the formula:
	// 0.5 * |x1(y2 - y3) + x2(y3 - y1) + x3(y1 - y2)|
	double area = abs(
		startPoint.x * (secondPoint.y - endPoint.y) +
		secondPoint.x * (endPoint.y - startPoint.y) +
		endPoint.x * (startPoint.y - secondPoint.y)
	) / 2;
	return area < AcGeContext::gTol.equalPoint();
}

void ArcJig::jig() {
	AcGePoint3d startPoint;
	AcGePoint3d secondPoint;
	ads_point ptStart;
	ads_point ptSecond;

	if (acedGetPoint(NULL, L"\nSpecify start point: ", ptStart) != RTNORM) {
		acutPrintf(L"\nNo start point selected.");
		return;
	}
	startPoint.set(ptStart[0], ptStart[1], ptStart[2]);
	Helpers::printAcGePoint3d(startPoint);

	if (acedGetPoint(ptStart, L"\nSpecify second point: ", ptSecond) != RTNORM) {
		acutPrintf(L"\nNo second point selected.");
		return;
	}
	secondPoint.set(ptSecond[0], ptSecond[1], ptSecond[2]);
	Helpers::printAcGePoint3d(secondPoint);

	ArcJig jig(startPoint, secondPoint);
	acutPrintf(L"\nSpecify end point: ");
	while (true)
	{
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

			acutPrintf(L"\nArc created successfully.");
			pEntity->close();
			pBlockTableRecord->close();
			break;
		}
		else if (status == AcEdJig::kCancel) {
			acutPrintf(L"\nCommand canceled.");
			break;
		}
		else
			acutPrintf(L"\nPoints are aligned. Please choose a different endpoint: ");
	}
}













