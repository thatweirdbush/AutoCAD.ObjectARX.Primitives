#pragma once
//-----------------------------------------------------------------------------
//----- Here you can include utility headers
#include "Constants.h"

//-----------------------------------------------------------------------------
//----- Here you can define AutoCAD primitive entities drawing functions
//-----------------------------------------------------------------------------
class PrimitiveEntities : public AcRxArxApp
{
public:
	static void ADSK_TEST_CREATE_LINE();
	static void ADSK_TEST_CREATE_CIRCLE();
	static void ADSK_TEST_CREATE_MTEXT();
	static void ADSK_TEST_CREATE_ARC();
	static void ADSK_TEST_CREATE_POLYLINE();
	static void ADSK_TEST_CREATE_NEW_LAYER();
	static void ADSK_TEST_CREATE_NEW_BLOCK();
	static void ADSK_TEST_PRINT_ALL_FROM_BLOCK();
	static void ADSK_TEST_PRINT_LINETYPES();
};
