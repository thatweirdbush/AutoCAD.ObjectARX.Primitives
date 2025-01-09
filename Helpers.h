#pragma once
//-----------------------------------------------------------------------------
//----- Helper functions. Eg. string conversions, print functions, etc.
//-----------------------------------------------------------------------------
class Helpers
{
public:
	static void printAcGePoint3d(const AcGePoint3d& pt);
	static void printAcGePoint3d(const ads_point& pt);
	static double calcDistance(const ads_point& pt1, const ads_point& pt2);
};

