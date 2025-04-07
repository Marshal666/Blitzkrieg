#include "StdAfx.h"

#include "LoadMission.h"

#include "..\Main\iMainCommands.h"
#include "SaveLoadCommon.h"
#include "CommonId.h"
#include "..\Main\ScenarioTracker.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const NInput::SRegisterCommandEntry loadmissionCommands[] = 
{
	{ "cancel_load"	,	IMC_CANCEL					},
	{ "load_mission", IMC_OK							},
	{ "key_up",				MESSAGE_KEY_UP			},
	{ "key_down",			MESSAGE_KEY_DOWN		},
	{ "key_left",			MESSAGE_KEY_LEFT		},
	{ "key_right",		MESSAGE_KEY_RIGHT		},
	{ 0							,	0										}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CICLoadMission::PostCreate( IMainLoop *pML, CInterfaceLoadMission *pILM )
{
	pML->PushInterface( pILM );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CInterfaceLoadMission::~CInterfaceLoadMission()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CInterfaceLoadMission::Init()
{
	NStr::SetCodePage( GetACP() );
	CInterfaceScreenBase::Init();
	SetBindSection( "loadmission" );
	loadmissionMsgs.Init( pInput, loadmissionCommands );
	
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CInterfaceLoadMission::StartInterface()
{
	CInterfaceScreenBase::StartInterface();
	// initialize UI saves list with available saves
	pUIScreen = CreateObject<IUIScreen>( UI_SCREEN );
	pUIScreen->Load( "ui\\LoadMission" );
	pUIScreen->Reposition( pGFX->GetScreenRect() );
	
	IUIElement *pElement = pUIScreen->GetChildByID( 1000 );		//should be List Control
	IUIListControl *pList = checked_cast<IUIListControl*>( pElement );
	if ( !pList )
		return;			//�� ������� list control
	
	// enumerate all available saves
	szSaves.clear();
	std::string szMask = "*.sav";
	std::string szBaseDir = std::string( GetSingleton<IDataStorage>()->GetName() );
	szBaseDir = szBaseDir.substr( 0, szBaseDir.rfind('\\') );
	szBaseDir = szBaseDir.substr( 0, szBaseDir.rfind('\\') );
	const std::string szModname = GetSingleton<IUserProfile>()->GetMOD();
	szBaseDir += "\\";
	if ( !szModname.empty() )
	{
		szBaseDir += "mods\\";
		szBaseDir += szModname;
	}
	szBaseDir += "saves\\";
	// collect files and sort it by last write time
	std::vector<SLoadFileDesc> files;
	NFile::EnumerateFiles( szBaseDir.c_str(), szMask.c_str(), CGetFiles2Load(files, szBaseDir), true );
	std::sort( files.begin(), files.end(), SLoadFileLessFunctional() );
	// add strings to list control
	const DWORD dwTextColor = GetGlobalVar( "Scene.Colors.Summer.Text.Default.Color", int(0xffd8bd3e) );
	for ( int i=0; i<files.size(); i++ )
	{
		pList->AddItem();
		IUIListRow *pRow = pList->GetItem( i );
		
		//��������� ��� save �����
		IUIStatic *pStatic = checked_cast<IUIStatic*> ( pRow->GetElement( 0 ) );
		szSaves.push_back( files[i].szFileName );
		//������� extension
		std::wstring wszTemp;
		NStr::ToUnicode( &wszTemp, files[i].szFileName.substr( 0, files[i].szFileName.rfind( '.' ) ) );
		pStatic->SetWindowText( pStatic->GetState(), wszTemp.c_str() );
		pStatic->SetTextColor( dwTextColor );
	}
	
	if ( szSaves.size() > 0 )
	{
		std::string szEdit = szSaves[0];
		szEdit = szEdit.substr( 0, szEdit.rfind( '.' ) );
		// ��������� ���� ������� � ����������� �����
		pElement = pUIScreen->GetChildByID( 2000 );
		pElement->SetWindowText( 0, NStr::ToUnicode(szEdit).c_str() );
		pList->SetSelectionItem( 0 );
	}
	
	pList->InitialUpdate();
	pUIScreen->Reposition( pGFX->GetScreenRect() );
	// add UI screen to scene
	pScene->AddUIScreen( pUIScreen );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CInterfaceLoadMission::ProcessMessage( const SGameMessage &msg )
{
	switch ( msg.nEventID )
	{
		case IMC_SELECTION_CHANGED:
			{
				//��������� ����� ������� selection �� list control
				IUIElement *pElement = pUIScreen->GetChildByID( 1000 );		//should be List Control
				IUIListControl *pList = checked_cast<IUIListControl*>( pElement );
				if ( !pList )
					return true;			//�� ������� list control
				int nSave = pList->GetSelectionItem();
				if ( nSave == -1 )
					return true;
				
				std::string szEdit = szSaves[nSave];
				szEdit = szEdit.substr( 0, szEdit.rfind( '.' ) );
				//��������� ���� ������� � ����������� �����
				pElement = pUIScreen->GetChildByID( 2000 );
				pElement->SetWindowText( 0, NStr::ToUnicode(szEdit).c_str() );
			}
			return true;
			
		case IMC_CANCEL:
			{
				IMainLoop *pML = GetSingleton<IMainLoop>();
				CloseInterface();
				pML->Command( MAIN_COMMAND_CMD, NStr::Format("%d", CMD_GAME_UNPAUSE_MENU) );	//������ �����
				//pML->Command( MAIN_COMMAND_CMD, NStr::Format("%d", MC_SHOW_ESCAPE_MENU) );	//������� escape menu
				return true;
			}

		case IMC_OK:
			{
				//��������� ����� ������� selection �� list control
				IUIElement *pElement = pUIScreen->GetChildByID( 1000 );		//should be List Control
				IUIListControl *pList = checked_cast<IUIListControl*>( pElement );
				if ( !pList )
					return true;			//�� ������� list control
				int nSave = pList->GetSelectionItem();
				if ( nSave == -1 )
					return true;

				std::string szEdit = szSaves[nSave];
				IMainLoop *pML = GetSingleton<IMainLoop>();
				CloseInterface();
				pML->Command( MAIN_COMMAND_LOAD, szEdit.c_str() );
				pML->Command( MAIN_COMMAND_CMD, NStr::Format("%d", CMD_GAME_UNPAUSE_MENU) );	//������ �����
				return true;
			}
	}
	//
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CInterfaceLoadMission::StepLocal( bool bAppActive )
{
	const CVec2 vPos = pCursor->GetPos();
	CInterfaceScreenBase::OnCursorMove( vPos );
	pUIScreen->Update( pTimer->GetAbsTime() );
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CInterfaceLoadMission::DrawAdd()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
