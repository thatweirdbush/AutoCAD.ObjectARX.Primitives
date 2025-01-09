#pragma once
//-----------------------------------------------------------------------------
//----- Here you can include utility headers
#include "Constants.h"
#include "Helpers.h"

//-----------------------------------------------------------------------------
//----- Here you can define AutoCAD user interactions functions
//-----------------------------------------------------------------------------
class UserInteractions : public AcRxArxApp
{
public:
	static void ADSK_TEST_GET_NAME_USING_GET_STRING();
	static void ADSK_TEST_CREATE_LINE_USING_GET_POINT();
	static void ADSK_TEST_GET_DISTANCE_BETWEEN_TWO_POINTS();
	static void ADSK_TEST_GET_KEYWORDS();
	static void ADSK_TEST_GET_ANGLE();
	static void ADSK_TEST_CHANGE_COLOR_USING_GET_SELECTION();
	static void ADSK_TEST_MOVE_OBJECT_USING_GET_POINT();

};

