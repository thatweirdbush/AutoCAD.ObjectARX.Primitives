// (C) Copyright 2002-2012 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "PrimitiveEntities.h"
#include "UserInteractions.h"
#include "Jiggers.h"

//-----------------------------------------------------------------------------
#define szRDS _RXST("DD")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CFirstArxProjectApp : public AcRxArxApp {

public:
	CFirstArxProjectApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}
	
	//// The ACED_ARXCOMMAND_ENTRY_AUTO macro can be applied to any static member 
	//// function of the CFirstArxProjectApp class.
	//// The function should take no arguments and return nothing.
	////
	//// NOTE: ACED_ARXCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid and
	//// have arguments to define context and command mechanism.
	//
	//// ACED_ARXCOMMAND_ENTRY_AUTO(classname, group, globCmd, locCmd, cmdFlags, UIContext)
	//// ACED_ARXCOMMAND_ENTRYBYID_AUTO(classname, group, globCmd, locCmdId, cmdFlags, UIContext)
	//// only differs that it creates a localized name using a string in the resource file
	////   locCmdId - resource ID for localized command

	//// Modal Command with localized name
	//// ACED_ARXCOMMAND_ENTRY_AUTO(CFirstArxProjectApp, DDMyGroup, MyCommand, MyCommandLocal, ACRX_CMD_MODAL)
	//static void DDMyGroupMyCommand () {
	//	// Put your command code here

	//}

	//// Modal Command with pickfirst selection
	//// ACED_ARXCOMMAND_ENTRY_AUTO(CFirstArxProjectApp, DDMyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET)
	//static void DDMyGroupMyPickFirst () {
	//	ads_name result ;
	//	int iRet =acedSSGet (ACRX_T("_I"), NULL, NULL, NULL, result) ;
	//	if ( iRet == RTNORM )
	//	{
	//		// There are selected entities
	//		// Put your command using pickfirst set code here
	//	}
	//	else
	//	{
	//		// There are no selected entities
	//		// Put your command code here
	//	}
	//}

	//// Application Session Command with localized name
	//// ACED_ARXCOMMAND_ENTRY_AUTO(CFirstArxProjectApp, DDMyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION)
	//static void DDMyGroupMySessionCmd () {
	//	// Put your command code here
	//}

	//// The ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO macros can be applied to any static member 
	//// function of the CFirstArxProjectApp class.
	//// The function may or may not take arguments and have to return RTNORM, RTERROR, RTCAN, RTFAIL, RTREJ to AutoCAD, but use
	//// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal to return
	//// a value to the Lisp interpreter.
	////
	//// NOTE: ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid.
	//
	////- ACED_ADSFUNCTION_ENTRY_AUTO(classname, name, regFunc) - this example
	////- ACED_ADSSYMBOL_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file
	////- ACED_ADSCOMMAND_ENTRY_AUTO(classname, name, regFunc) - a Lisp command (prefix C:)
	////- ACED_ADSCOMMAND_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file

	//// Lisp Function is similar to ARX Command but it creates a lisp 
	//// callable function. Many return types are supported not just string
	//// or integer.
	//// ACED_ADSFUNCTION_ENTRY_AUTO(CFirstArxProjectApp, MyLispFunction, false)
	//static int ads_MyLispFunction () {
	//	//struct resbuf *args =acedGetArgs () ;
	//	
	//	// Put your command code here

	//	//acutRelRb (args) ;
	//	
	//	// Return a value to the AutoCAD Lisp Interpreter
	//	// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal

	//	return (RTNORM) ;
	//}
} ;

//-----------------------------------------------------------------------------
//----- Implementation macro of main AutoCAD entry point
IMPLEMENT_ARX_ENTRYPOINT(CFirstArxProjectApp)

//----- Here you can declare AutoCAD commands from PrimitiveEntities class
ACED_ARXCOMMAND_ENTRY_AUTO(PrimitiveEntities, ADSK, _TEST_CREATE_LINE, TEST_CREATE_LINE, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(PrimitiveEntities, ADSK, _TEST_CREATE_CIRCLE, TEST_CREATE_CIRCLE, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(PrimitiveEntities, ADSK, _TEST_CREATE_MTEXT, TEST_CREATE_MTEXT, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(PrimitiveEntities, ADSK, _TEST_CREATE_ARC, TEST_CREATE_ARC, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(PrimitiveEntities, ADSK, _TEST_CREATE_POLYLINE, TEST_CREATE_POLYLINE, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(PrimitiveEntities, ADSK, _TEST_CREATE_NEW_LAYER, TEST_CREATE_NEW_LAYER, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(PrimitiveEntities, ADSK, _TEST_CREATE_NEW_BLOCK, TEST_CREATE_NEW_BLOCK, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(PrimitiveEntities, ADSK, _TEST_PRINT_ALL_FROM_BLOCK, TEST_PRINT_ALL_FROM_BLOCK, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(PrimitiveEntities, ADSK, _TEST_PRINT_LINETYPES, TEST_PRINT_LINETYPES, ACRX_CMD_MODAL, NULL)

//----- Here you can declare AutoCAD commands from UserInteractions class
ACED_ARXCOMMAND_ENTRY_AUTO(UserInteractions, ADSK, _TEST_GET_NAME_USING_GET_STRING, TEST_GET_NAME_USING_GET_STRING, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(UserInteractions, ADSK, _TEST_CREATE_LINE_USING_GET_POINT, TEST_CREATE_LINE_USING_GET_POINT, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(UserInteractions, ADSK, _TEST_GET_DISTANCE_BETWEEN_TWO_POINTS, TEST_GET_DISTANCE_BETWEEN_TWO_POINTS, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(UserInteractions, ADSK, _TEST_GET_KEYWORDS, TEST_GET_KEYWORDS, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(UserInteractions, ADSK, _TEST_GET_ANGLE, TEST_GET_ANGLE, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(UserInteractions, ADSK, _TEST_GET_CORNER, TEST_GET_CORNER, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(UserInteractions, ADSK, _TEST_CHANGE_COLOR_USING_GET_ENTITY_SELECTION, TEST_CHANGE_COLOR_USING_GET_ENTITY_SELECTION, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(UserInteractions, ADSK, _TEST_CHANGE_COLOR_USING_GET_SELECTION_SET, TEST_CHANGE_COLOR_USING_GET_SELECTION_SET, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(UserInteractions, ADSK, _TEST_CHANGE_COLOR_USING_GET_SELECTION_SET_EXTENDED, TEST_CHANGE_COLOR_USING_GET_SELECTION_SET_EXTENDED, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(UserInteractions, ADSK, _TEST_MOVE_OBJECT_USING_GET_POINT, TEST_MOVE_OBJECT_USING_GET_POINT, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(UserInteractions, ADSK, _TEST_MOVE_LINE_ONLY, TEST_MOVE_LINE_ONLY, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(UserInteractions, ADSK, _TEST_ROTATE_OBJECT, TEST_ROTATE_OBJECT, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(UserInteractions, ADSK, _TEST_MIRROR_OBJECT_USING_LINE, TEST_MIRROR_OBJECT_USING_LINE, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(UserInteractions, ADSK, _TEST_SCALE_OBJECT, TEST_SCALE_OBJECT, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(UserInteractions, ADSK, _TEST_CALCULATE_POLYGON_AREA, TEST_CALCULATE_POLYGON_AREA, ACRX_CMD_MODAL, NULL)

//----- Here you can declare AutoCAD commands from Jiggers class
ACED_ARXCOMMAND_ENTRY_AUTO(Jiggers, ADSK, _TEST_CREATE_LINE_JIG, TEST_CREATE_LINE_JIG, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(Jiggers, ADSK, _TEST_CREATE_CIRCLE_JIG, TEST_CREATE_CIRCLE_JIG, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(Jiggers, ADSK, _TEST_CREATE_POLYLINE_JIG, TEST_CREATE_POLYLINE_JIG, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(Jiggers, ADSK, _TEST_CREATE_ARC_JIG, TEST_CREATE_ARC_JIG, ACRX_CMD_MODAL, NULL)


//ACED_ARXCOMMAND_ENTRY_AUTO(CFirstArxProjectApp, DDMyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//ACED_ARXCOMMAND_ENTRY_AUTO(CFirstArxProjectApp, DDMyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION, NULL)
//ACED_ADSSYMBOL_ENTRY_AUTO(CFirstArxProjectApp, MyLispFunction, false)

