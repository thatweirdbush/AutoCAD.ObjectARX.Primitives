#pragma once
//-----------------------------------------------------------------------------
//----- Here you can define some useful constants
const double Pi = 3.141592653589793;

//-----------------------------------------------------------------------------
//----- Here you can define AutoCAD primitive entities drawing functions
class ADSK_PrimitiveEntities : public AcRxArxApp
{
public:
	ADSK_PrimitiveEntities() : AcRxArxApp() {}

	virtual AcRx::AppRetCode On_kInitAppMsg(void* pkt) {
		AcRx::AppRetCode retCode = AcRxArxApp::On_kInitAppMsg(pkt);

		return (retCode);
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg(void* pkt) {
		AcRx::AppRetCode retCode = AcRxArxApp::On_kUnloadAppMsg(pkt);

		return (retCode);
	}

	virtual void RegisterServerComponents() {
	}

public:
	static void ADSK_TEST_DRAW_LINE();
	static void ADSK_TEST_DRAW_CIRCLE();
	static void ADSK_TEST_CREATE_MTEXT();
	static void ADSK_TEST_CREATE_ARC();
	static void ADSK_TEST_CREATE_POLYLINE();
	static void ADSK_TEST_CREATE_NEW_LAYER();
	static void ADSK_TEST_PRINT_ALL();
	static void ADSK_TEST_CREATE_NEW_BLOCK();
	static void ADSK_TEST_PRINT_LINETYPES();
};
