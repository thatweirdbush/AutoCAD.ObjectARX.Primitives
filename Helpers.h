#pragma once
//-----------------------------------------------------------------------------
//----- Helper functions. Eg. string conversions, print functions, etc.
//-----------------------------------------------------------------------------
class Helpers
{
private:
	static uint16_t mPreviousColor;

public:
	static void printAcGePoint3d(const AcGePoint3d& pt);
	static void printAcGePoint3d(const ads_point& pt);
	static double calcDistance(const ads_point& pt1, const ads_point& pt2);
	static uint16_t getRandColor();
	static double CalculateAreaOfPolygon(AcDbPolyline* pPolyline);
	static bool IsPointEqual(const AcGePoint3d& pt1, const AcGePoint3d& pt2);
};

