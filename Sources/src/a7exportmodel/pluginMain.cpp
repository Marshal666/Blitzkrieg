#include "StdAfx.h"
//
// Copyright (C) 2001 Nival Interactive 
// 
// File: pluginMain.cpp
//
// Author: Maya SDK Wizard
//

#include <maya/MFnPlugin.h>

#include "A7ExportModel.h"

#ifdef __MAYA4__
#define EXPORT __declspec(dllexport)
#define VERSION "4.0"
#else
#define EXPORT
#define VERSION "3.0"
#endif // __MAYA4__

EXPORT MStatus initializePlugin( MObject obj )
//
//	Description:
//		this method is called when the plug-in is loaded into Maya.  It 
//		registers all of the services that this plug-in provides with 
//		Maya.
//
//	Arguments:
//		obj - a handle to the plug-in object (use MFnPlugin to access it)
//
{ 
	MFnPlugin plugin( obj, "Nival Interactive", VERSION, "Any" );

	return plugin.registerFileTranslator( "A7ExportModel", "none", CA7ExportModel::creator, "", "skeleton=1;" );
}
// model=0;animation=0;ai_model=0;mesh=0;skeleton=1;ai_mesh=0;

EXPORT MStatus uninitializePlugin( MObject obj )
//
//	Description:
//		this method is called when the plug-in is unloaded from Maya. It 
//		deregisters all of the services that it was providing.
//
//	Arguments:
//		obj - a handle to the plug-in object (use MFnPlugin to access it)
//
{
	MFnPlugin plugin( obj );

	return plugin.deregisterFileTranslator( "A7ExportModel" );
}
