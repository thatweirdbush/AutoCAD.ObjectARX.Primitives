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
	static void ADSK_TEST_GET_CORNER();
	static void ADSK_TEST_CHANGE_COLOR_USING_GET_ENTITY_SELECTION();
	static void ADSK_TEST_CHANGE_COLOR_USING_GET_SELECTION_SET();
	static void ADSK_TEST_CHANGE_COLOR_USING_GET_SELECTION_SET_EXTENDED();
	static void ADSK_TEST_MOVE_OBJECT_USING_GET_POINT();
	static void ADSK_TEST_MOVE_LINE_ONLY();
	static void ADSK_TEST_ROTATE_OBJECT();
	static void ADSK_TEST_MIRROR_OBJECT_USING_LINE();
	static void ADSK_TEST_SCALE_OBJECT();
	static void ADSK_TEST_CALCULATE_POLYGON_AREA();
};

