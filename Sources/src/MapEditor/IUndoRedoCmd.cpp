// IUndoRedoCmd.cpp: implementation of the IUndoRedoCmd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "editor.h"
#include "IUndoRedoCmd.h"
#include "..\GFX\GFX.h"
#include "..\Scene\Scene.h"
#include "MapEditorBarWnd.h"
#include "TemplateEditorFrame1.h"

#include <Mmsystem.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//-===================== для постановки тайлов ===========================-
void CTileRedoCmd::Undo()
{
	m_ptr->AddTileCmd( m_data, false );
}
//-===================== для удаления объектов ===========================-
void CDellObjRedoCmd::Undo()
{
	// temp == true т.к при Undo
	CVec3 v( position.x, position.y, 0 );
	SMapObjectInfo info;
	info.szName = desc.szKey;
	info.vPos = v;
	Vis2AI( &info.vPos );
	info.nDir = m_dir ;
	info.nPlayer = player;
	info.nScriptID = scriptId;
	info.fHP = 1.0f;
	info.nFrameIndex = frameIndex;
	//info.szLogic = szBehavior;
	m_ptr->AddObjectByAI( info, player, true );
}
//-===================== для постановки объектов ===========================-
void CAddObjRedoCmd::Undo()
{
	m_ptr->RemoveObject( m_obj );
}
//==================================================================================================
void CAddMultiObjRedoCmd::Undo()
{
	for( std::vector<SMapObject*>::iterator it = m_objs.begin(); it != m_objs.end(); ++it )
	{
		m_ptr->RemoveObject( *it );
	}
}
//-===================== для движения объектов ===========================-
void CMoveObjRedoCmd::Undo()
{
	CVec3 vAI;
	Vis2AI( &vAI, CVec3( m_oldPos.x, m_oldPos.y, 0 ) );	
	if( m_ptr->ifObjectExist(m_obj) )
	{
		///GetSingleton<IAIEditor>()->MoveObject( m_obj->pAIObj, vAI.x, vAI.y );
		m_ptr->MoveObject( m_obj->pAIObj, vAI.x, vAI.y );
		IGameTimer *pTimer = GetSingleton<IGameTimer>();
		pTimer->Update( timeGetTime() );
		m_ptr->Update( pTimer->GetGameTime() );
	}
}
//-===================== для постановки дороги ===========================-
void CPutRoadRedoCmd::Undo()
{
	//m_ptr->DeleteRoad( m_item );
	//m_ptr->CalculateRoads();
}
//-===================== для удаления дороги ===========================-
void CDellRoadRedoCmd::Undo()
{
	//m_ptr->AddRoad( m_item );
	//m_ptr->CalculateRoads();
}
//-===================== для удаления при мультселекте ======================-
void CDellMultiObjRedoCmd::Undo()
{
	// temp == true т.к при Undo
	for ( std::vector<SObjectDellDisciption>::iterator it = m_objects.begin(); it != m_objects.end(); ++it )
	{
		CVec3 v( it->m_position );
		SMapObjectInfo info;
		info.szName = it->m_desc.szKey;
		info.vPos = v;
		Vis2AI( &info.vPos );
		info.nDir = it->m_dir ;
		info.nPlayer = it->m_player;
		info.nScriptID = it->m_scriptID;
		info.fHP = 1.0f;
		info.nFrameIndex = it->m_frameIndex;
		//info.szLogic = it->szBehavior;
		SMapObject *pObj = m_ptr->AddObjectByAI( info, it->m_player, true, it->m_bScenarioUnit );	
	}
}