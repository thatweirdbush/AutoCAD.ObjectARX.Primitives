#pragma once
//-----------------------------------------------------------------------------
//----- Here you can include utility headers
#include "Constants.h"
#include "Helpers.h"

//-----------------------------------------------------------------------------
//----- Here you can define AutoCAD LineJig class
//-----------------------------------------------------------------------------
class LineJig : public AcEdJig
{
private:
	AcGePoint3d _startPoint;
	AcGePoint3d _endPoint;
	AcDbLine* _line;

public:
	LineJig(const AcGePoint3d& startPoint);
	~LineJig();
	virtual AcDbEntity* entity() const override;

protected:
	virtual DragStatus sampler() override;
	virtual Adesk::Boolean update() override;

public:
	static void jig();
};

//-----------------------------------------------------------------------------
//----- Here you can define AutoCAD CircleJig class
//-----------------------------------------------------------------------------
class CircleJig : public AcEdJig
{
private:
	AcGePoint3d _center;
	double _radius;
	AcDbCircle* _circle;

public:
	CircleJig(const AcGePoint3d& center);
	~CircleJig();
	virtual AcDbEntity* entity() const override;

protected:
	virtual DragStatus sampler() override;
	virtual Adesk::Boolean update() override;

public:
	static void jig();
};

//-----------------------------------------------------------------------------
//----- Here you can define AutoCAD PolylineJig class
//-----------------------------------------------------------------------------
class PolylineJig : public AcEdJig
{
private:
	AcGePoint3d _startPoint;
	AcGePoint3d _nextPoint;
	AcDbPolyline* _polyline;

public:
	PolylineJig(const AcGePoint3d& startPoint);
	~PolylineJig();
	virtual AcDbEntity* entity() const override;

protected:
	virtual DragStatus sampler() override;
	virtual Adesk::Boolean update() override;
	virtual void addDummyVertex();
	virtual void append();

public:
	static void jig();
};

//-----------------------------------------------------------------------------
//----- Here you can define AutoCAD Jiggers functions
//-----------------------------------------------------------------------------
class Jiggers
{
public:
	static void ADSK_TEST_CREATE_LINE_JIG() {
		LineJig::jig();
	};

	static void ADSK_TEST_CREATE_CIRCLE_JIG() {
		CircleJig::jig();
	};

	static void ADSK_TEST_CREATE_POLYLINE_JIG() {
		PolylineJig::jig();
	};
};

