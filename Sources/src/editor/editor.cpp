// editor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include <crtdbg.h>
#include <secsplsh.h>
#include <Shlwapi.h>

#include "editor.h"
#include "RefDlg.h"
#include "GUIFrame.h"
#include "AnimationFrm.h"
#include "SpriteFrm.h"
#include "EffectFrm.h"
#include "ObjectFrm.h"
#include "MeshFrm.h"
#include "WeaponFrm.h"
#include "BuildFrm.h"
#include "TileSetFrm.h"
#include "FenceFrm.h"
#include "ParticleFrm.h"
#include "TrenchFrm.h"
#include "SquadFrm.h"
#include "MineFrm.h"
#include "BridgeFrm.h"
#include "MissionFrm.h"
#include "ChapterFrm.h"
#include "CampaignFrm.h"
#include "3dRoadFrm.h"
#include "3dRiverFrm.h"

#include "MainFrm.h"
#include "frames.h"

#include "..\Main\iMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const char szVersion[] = "0.09";

/////////////////////////////////////////////////////////////////////////////
// CEditorApp

BEGIN_MESSAGE_MAP(CEditorApp, CWinApp)
	//{{AFX_MSG_MAP(CEditorApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND_RANGE(ID_FILE_RECENT_0, ID_FILE_RECENT_6, OnRecentFile)
	ON_UPDATE_COMMAND_UI(ID_FILE_RECENT_0, OnUpdateRecentFile)
	ON_UPDATE_COMMAND_UI_RANGE(ID_FILE_RECENT_0, ID_FILE_RECENT_6, OnUpdateRecentFileRange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 

/////////////////////////////////////////////////////////////////////////////
// CEditorApp construction

CEditorApp::CEditorApp()
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
//	_CrtSetBreakAlloc( 80 );

	int nBreakId = -1;
	_CrtSetBreakAlloc( nBreakId );

	m_pMainFrame = 0;

	char temp[255];
	GetCurrentDirectory( 255, temp );
	szEditorDir = temp;
	szEditorDir += '\\';
	NStr::ToLower( szEditorDir );			//��� ���� ����� ��������� � ������ ��������

	m_bInitFinished = false;
	m_bVersionIncreased = false;

	szSourceDir = "";
	szDestDir = "";
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEditorApp object

CEditorApp theApp;

void CEditorApp::WriteProfileFloat( const char *pszName, float f )
{
	int *pTemp = (int *) &f;
	WriteProfileInt( "", pszName, *pTemp );
}

float CEditorApp::GetProfileFloat( const char *pszName )
{
	int nTemp = GetProfileInt( "", pszName, 0 );
	float *pTemp = (float *) &nTemp;
	return *pTemp;
}

/////////////////////////////////////////////////////////////////////////////
// CEditorApp initialization

BOOL CEditorApp::InitInstance()
{
	// check for network drive
	if ( !NMain::CanLaunch() )
		return false;
	//
	
#ifndef _DEBUG
  SECSplashWnd *pSplashWnd = new SECSplashWnd( IDB_EDITOR_STARTUP );
  pSplashWnd->Create();
#endif		//! _DEBUG
	
#if defined( _DO_SEH ) && !defined( _DEBUG )
	// set StructuredExceptionHandler 
	SetCrashHandlerFilter( CrashHandlerFilter );
#endif // defined( _DO_SEH ) && !defined( _DEBUG )
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
//	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	SetRegistryKey( "Nival Interactive" );
	m_pRecentFileList = new CRecentFileList( 0, "MRU", "file%d", 7 );
	m_pRecentFileList->ReadList();

	LoadVersionNumber();
	if ( m_bVersionIncreased )
	{
		const string str = "Software\\Nival Interactive\\Blitzkreig Resource Editor\\";
		SHDeleteKey( HKEY_CURRENT_USER, (str + "Layout").c_str() );
	}
	
	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.
	m_pMainFrame = new CMainFrame;
	m_pMainWnd = m_pMainFrame;

	// create main MDI frame window
	m_nCmdShow = SW_HIDE;
	if (!m_pMainFrame->LoadFrame(IDR_EDITORTYPE))
		return FALSE;
	
	// try to load shared MDI menus and accelerator table
	//TODO: add additional member variables and load calls for
	//	additional menu types your application may need. 
	
	/*
  SECSplashWnd *pSplashWnd = new SECSplashWnd( IDB_EDITOR_STARTUP );
  pSplashWnd->Create();
	*/
	
	HINSTANCE hInst = AfxGetResourceHandle();
	m_hMDIMenu  = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_EDITORTYPE));
	m_hMDIAccel = ::LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_EDITORTYPE));
	m_nCmdShow = SW_SHOWMAXIMIZED;
	
	m_bInitFinished = false;
	CWnd *pActiveFrame = 0;
	//����� ������ ������������ � AnimationFrame ����� �� ������� ������
	pActiveFrame = g_frameManager.GetFrame( CFrameManager::E_ANIMATION_FRAME );
	pActiveFrame->SendMessage( WM_SETFOCUS, 0, 0 );
	
	// The main window has been initialized, so show and update it.
	m_pMainFrame->ShowWindow(m_nCmdShow);
	m_pMainFrame->UpdateWindow();
	
	//����� ��������������� ����� � ��������� �������� ������, ������ �������� ���������� � �������, �� �������
	int nActiveFrame = LoadLastActiveModuleID();
	pActiveFrame = g_frameManager.GetFrame( nActiveFrame );
	NI_ASSERT( pActiveFrame != 0 );
	pActiveFrame->PostMessage( WM_SETFOCUS, 0, 0 );
	m_bInitFinished = true;
	
	if ( RunBatchMode() )
	{
		//close the application
		return FALSE;
	}
	
	LoadRegisterData();
	
	return TRUE;
}

bool CEditorApp::RunBatchMode()
{
	//read command line params
	int nArgsCount = 0;
	LPWSTR pCommandLine = GetCommandLineW();
	LPWSTR *pRes = CommandLineToArgvW( pCommandLine, &nArgsCount );
	
	if ( nArgsCount == 1 )
		return false;
	
	//��������, ������� �� batch mode
	if ( nArgsCount < 4 )
	{
		std::string szMessage = "ResEditor command line batch mode:\nreseditor.exe <*.project extensions> <folder with projects> <destination folder> [-f] [-os]\n"
			"where [-f] is forced flag and [-os] is flag to only open and save projects";
		AfxMessageBox( szMessage.c_str() );
		return false;
	}
	
	std::string szMask = NStr::ToAscii( pRes[1] );
	CParentFrame *pFrame = g_frameManager.ActivateFrameByExtension( szMask.c_str() );
	if ( !pFrame )
	{
		std::string szErr = NStr::Format( "Error: The file extension %s for batch mode is not supported", szMask.c_str() );
		AfxMessageBox( szErr.c_str() );
		return false;
	}
	
	bool bForced = false;
	bool bOpenSave = false;
	std::string szSourceDir = NStr::ToAscii( pRes[2] );
	std::string szDestDir = NStr::ToAscii( pRes[3] );
	for ( int i=4; i<nArgsCount; i++ )
	{
		std::string szParam = NStr::ToAscii( pRes[i] );
		if ( szParam == "-f" )
			bForced = true;
		if ( szParam == "-os" )
			bOpenSave = true;
	}
	
	pFrame->RunBatchExporter( szSourceDir.c_str(), szDestDir.c_str(), szMask.c_str(), bForced, bOpenSave );
	return true;
}

void CEditorApp::LoadRegisterData()
{
	LoadDirs();
	LoadFileDialogRegisterData();

	// ��������� source & destination directory ��� ���� �������
	for ( int i=0; i<g_frameManager.frames.size(); i++ )
		g_frameManager.frames[i]->LoadRegisterData();
}

int CEditorApp::LoadLastActiveModuleID()
{
	return GetProfileInt( "", "Active Frame", CFrameManager::E_ANIMATION_FRAME );
}

void CEditorApp::LoadVersionNumber()
{
	m_bVersionIncreased = false;
	std::string szV = GetProfileString( "", "Version", "" );
	if ( szV.size() == 0 || strcmp( szVersion, szV.c_str() ) > 0 )
		m_bVersionIncreased = true;
}

void CEditorApp::LoadDirs()
{
	szSourceDir = GetProfileString( "", "Composer Source Directory", szSourceDir.c_str() );
	szDestDir = GetProfileString( "", "Composer Destination Directory", szDestDir.c_str() );
	szExecDir = GetProfileString( "", "Composer Executive Directory", GetEditorDir().c_str() );
	szExecArgs = GetProfileString( "", "Composer Executive Arguments", "" );
	if ( szSourceDir.empty() )
		szSourceDir = GetEditorDir() + "complete\\";
	if ( szDestDir.empty() )
		szDestDir = GetEditorDir() + "mods\\mymod\\";
	ReadMODFile( szDestDir + "data\\", szMODName, szMODVersion, szMODDesc );
}

void CEditorApp::SaveRegisterData()
{
	SaveVersionNumber();
	SaveDirs();
	SaveNewFrameTypeToRegister();
	SaveFileDialogRegisterData();
	m_pRecentFileList->WriteList();

	for ( int i=0; i<g_frameManager.frames.size(); i++ )
		g_frameManager.frames[i]->SaveRegisterData();
}

void CEditorApp::SaveNewFrameTypeToRegister()
{
	WriteProfileInt( "", "Active Frame", g_frameManager.GetActiveFrameType() );
}

void CEditorApp::SaveVersionNumber()
{
	WriteProfileString( "", "Version", szVersion );
}

void CEditorApp::SaveDirs()
{
	WriteProfileString( "", "Composer Source Directory", szSourceDir.c_str() );
	WriteProfileString( "", "Composer Destination Directory", szDestDir.c_str() );
	WriteProfileString( "", "Composer Executive Directory", szExecDir.c_str() );
	WriteProfileString( "", "Composer Executive Arguments", szExecArgs.c_str() );
}

BOOL CEditorApp::MyWriteProfileString( LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszValue )
{
	return WriteProfileString( lpszSection, lpszEntry, lpszValue );
}

CString CEditorApp::MyGetProfileString( LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault )
{
	return GetProfileString( lpszSection, lpszEntry, lpszDefault );
}

BOOL CEditorApp::MyWriteProfileInt( LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue )
{
	return WriteProfileInt( lpszSection, lpszEntry, nValue );
}

UINT CEditorApp::MyGetProfileInt( LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault )
{
	return GetProfileInt( lpszSection, lpszEntry, nDefault );
}

/////////////////////////////////////////////////////////////////////////////
// CEditorApp message handlers

int CEditorApp::ExitInstance() 
{
#if defined( _DO_SEH ) && !defined( _DEBUG )
	// set StructuredExceptionHandler 
	SetCrashHandlerFilter( 0 );
#endif // defined( _DO_SEH ) && !defined( _DEBUG )
	//TODO: handle additional resources you may have added
	if (m_hMDIMenu != NULL)
		FreeResource(m_hMDIMenu);
	if (m_hMDIAccel != NULL)
		FreeResource(m_hMDIAccel);

	return CWinApp::ExitInstance();
}

string CEditorApp::GetEditorTempResourceDir() const
{
	return "editor\\temp";
}

string CEditorApp::GetEditorTempDir() const
{
	return GetEditorDir() + "data\\" + GetEditorTempResourceDir() + "\\";
}

string CEditorApp::GetEditorDataDir() const
{
	return GetEditorDir() + "data\\";
}

void CEditorApp::UpdateStatusBarIndicators()
{
	m_pMainFrame->UpdateStatusBarIndicators();
}

void CEditorApp::UpdateStatusBarCoordsIndicator(const POINT &pt)
{
	m_pMainFrame->UpdateStatusBarCoordsIndicator( pt );
}

void CEditorApp::UpdateStatusBarControlIndicator(const RECT &rc)
{
	m_pMainFrame->UpdateStatusBarControlIndicator( rc );
}

void CEditorApp::UpdateStatusBarControlIndicator(const CTRect<float> &rc)
{
	m_pMainFrame->UpdateStatusBarControlIndicator( rc );
}

void CEditorApp::ClearStatusBarControlIndicator()
{
	m_pMainFrame->ClearStatusBarControlIndicator();
}

void CEditorApp::ShowSECControlBar( SECControlBar *pControlBar, int nCommand )
{
	m_pMainFrame->ShowSECControlBar( pControlBar, nCommand );
}

void CEditorApp::ShowSECToolBar( SECControlBar *pControlBar, int nCommand )
{
	m_pMainFrame->ShowSECToolBar( pControlBar, nCommand );
}

void CEditorApp::SetMainWindowTitle( const char *pszTitle )
{
	m_pMainFrame->SetMainWindowTitle( pszTitle );
}

void CEditorApp::SetMainWindowText( const char *pszText )
{
	m_pMainFrame->SetMainWindowText( pszText );
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CEditorApp message handlers


#ifdef OLD
BOOL CEditorApp::ProcessMessageFilter(int code, LPMSG lpMsg) 
{
/*
	//���� � ������ �������� ESC � �� ���� ����� �� ����������
	if ( (lpMsg->hwnd == pPropertyWindow->GetSafeHwnd() ) ||
		::IsChild( pPropertyWindow->GetSafeHwnd(), lpMsg->hwnd ) )
    // Use ::IsChild to get messages that may be going
		// to the dialog's controls.  In the case of
		// WM_KEYDOWN this is required.
	{
		if ( lpMsg->message == WM_KEYDOWN && lpMsg->wParam == VK_ESCAPE )
		{
			if ( ::IsChild( pPropertyWindow->GetSafeHwnd(), lpMsg->hwnd ) )
			{
				::SendMessage( lpMsg->hwnd, WM_KEYDOWN, lpMsg->wParam, lpMsg->lParam );
				return TRUE;
			}
			else
				return TRUE;
		}
	}
	if ( lpMsg->message == WM_KEYDOWN && lpMsg->wParam == VK_DELETE )
	{
		if ( ::IsChild( pPropertyWindow->GetSafeHwnd(), lpMsg->hwnd ) )
		{
			::SendMessage( lpMsg->hwnd, WM_KEYDOWN, lpMsg->wParam, lpMsg->lParam );
			return TRUE;
		}
		else
			return TRUE;
	}
*/

	if ( lpMsg->message == WM_KEYDOWN && lpMsg->wParam == VK_ESCAPE || lpMsg->wParam == VK_DELETE )
	{
		::PostMessage( lpMsg->hwnd, WM_KEYDOWN, lpMsg->wParam, lpMsg->lParam );
		return TRUE;
/*		if ( ::IsChild( pPropertyWindow->GetSafeHwnd(), lpMsg->hwnd ) )
		{
			::SendMessage( lpMsg->hwnd, WM_KEYDOWN, lpMsg->wParam, lpMsg->lParam );
			return TRUE;
		}
		else
			return TRUE;
*/
	}

	return CWinApp::ProcessMessageFilter(code, lpMsg);
}
#endif		//OLD

BOOL CEditorApp::OnIdle(LONG lCount) 
{
	static nMyCount = 0;
	nMyCount++;

//	OutputDebugString( NStr::Format( "%d", nMyCount ) );
//	GetSingleton( (IGameTimer*)0 )->Update( timeGetTime() );
	
	if ( nMyCount == 1024 )
	{
		nMyCount = 0;

		if ( g_frameManager.GetActiveFrameType() == CFrameManager::E_GUI_FRAME )
		{
			CGUIFrame *pFrame = static_cast<CGUIFrame *> ( g_frameManager.GetFrame( CFrameManager::E_GUI_FRAME ) );
			return pFrame->Run();
		}
		else if ( g_frameManager.GetActiveFrameType() == CFrameManager::E_ANIMATION_FRAME )
		{
			CAnimationFrame *pFrame = static_cast<CAnimationFrame *> ( g_frameManager.GetFrame( CFrameManager::E_ANIMATION_FRAME ) );
			return pFrame->Run();
		}
		else if ( g_frameManager.GetActiveFrameType() == CFrameManager::E_SPRITE_FRAME )
		{
			CSpriteFrame *pFrame = static_cast<CSpriteFrame *> ( g_frameManager.GetFrame( CFrameManager::E_SPRITE_FRAME ) );
			return pFrame->Run();
		}
		else if ( g_frameManager.GetActiveFrameType() == CFrameManager::E_EFFECT_FRAME )
		{
			CEffectFrame *pFrame = static_cast<CEffectFrame *> ( g_frameManager.GetFrame( CFrameManager::E_EFFECT_FRAME ) );
			return pFrame->Run();
		}
		else if ( g_frameManager.GetActiveFrameType() == CFrameManager::E_PARTICLE_FRAME )
		{
			CParticleFrame *pFrame = static_cast<CParticleFrame *> ( g_frameManager.GetFrame( CFrameManager::E_PARTICLE_FRAME ) );
			return pFrame->Run();
		}
		else if ( g_frameManager.GetActiveFrameType() == CFrameManager::E_3DRIVER_FRAME )
		{
			C3DRiverFrame *pFrame = static_cast<C3DRiverFrame *> ( g_frameManager.GetFrame( CFrameManager::E_3DRIVER_FRAME ) );
			return pFrame->Run();
		}
	}
	CWinApp::OnIdle(lCount);
	return TRUE;
}

BOOL CEditorApp::SaveAllModified() 
{
	BOOL bCancelExit = FALSE;

	for ( int i=0; i<g_frameManager.frames.size(); i++ )
		bCancelExit |= g_frameManager.frames[i]->SaveFrame( true );
	
	if ( bCancelExit )
		return FALSE;
	else
		return TRUE;
}

void CEditorApp::OnFileNew() 
{
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);
	
	// create a new MDI child window
	CMDIChildWnd* pChildWnd = pFrame->CreateNewChild(
		RUNTIME_CLASS(CParentFrame), IDR_EDITORTYPE, NULL, m_hMDIAccel);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEditorApp::ReadMODFile( const std::string &szPath, std::string &szName, std::string &szVersion, std::string &szDesc )
{
	CPtr<IDataStream> pXMLStream = OpenFileStream( (szPath + "mod.xml").c_str(), STREAM_ACCESS_READ );
	szName = "";
	szVersion = "";
	if ( !pXMLStream )
		return;
	CPtr<IDataTree> pDT = CreateDataTreeSaver( pXMLStream, IDataTree::READ );
	CTreeAccessor saver = pDT;
	saver.Add( "MODName", &szName );
	saver.Add( "MODVersion", &szVersion );
	saver.Add( "MODDesc", &szDesc );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEditorApp::WriteMODFile( const std::string &szPath, const std::string &szName, const std::string &szVersion, const std::string &szDesc )
{
	CPtr<IDataStream> pXMLStream = CreateFileStream( (szPath + "mod.xml").c_str(), STREAM_ACCESS_WRITE );
	if ( pXMLStream )
	{
		CPtr<IDataTree> pDT = CreateDataTreeSaver( pXMLStream, IDataTree::WRITE );
		if ( pDT )
		{
			std::string szNameTemp = szName;
			std::string szVersionTemp = szVersion;
			std::string szDescTemp = szDesc;
			CTreeAccessor saver = pDT;
			saver.Add( "MODName", &szNameTemp );
			saver.Add( "MODVersion", &szVersionTemp );
			saver.Add( "MODDesc", &szDescTemp );
		}
	}
	CPtr<IDataStream> pResultStream = OpenFileStream( szPath + "modobjects.xml", STREAM_ACCESS_READ );
	if ( pResultStream == 0 )
	{
		pResultStream = CreateFileStream( szPath + "modobjects.xml", STREAM_ACCESS_WRITE );
		CPtr<IDataStorage> pStorage = GetSingleton<IDataStorage>();
		CPtr<IDataStream> pStream = pStorage->OpenStream( "editor\\modobjects.xml", STREAM_ACCESS_READ );
		pStream->CopyTo( pResultStream, pStream->GetSize() );
		//CopyFile( (GetEditorDataDir() + "editor\\modobjects.xml").c_str(), (szPath + "modobjects.xml").c_str(), TRUE );
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEditorApp::OnUpdateRecentFile( CCmdUI *pCmdUI )
{
	std::list<std::string> files;
	for ( int i = 0; i < m_pRecentFileList->m_nSize; ++i )
	{
		const std::string szProjectFile = (LPCTSTR)((*m_pRecentFileList)[i]);
		if ( !szProjectFile.empty() )
		{
			files.push_back( szProjectFile );
		}
	}
	pCmdUI->Enable( !files.empty() );
	if ( CMenu *pFileMenu = pCmdUI->m_pMenu )
	{
		if ( CMenu *pRecentMenu = pFileMenu->GetSubMenu( 12 ) )
		{
			while( pRecentMenu->GetMenuItemCount() > 0 )
			{
				pRecentMenu->RemoveMenu( 0 , MF_BYPOSITION );
			}
			int nFile = 0;
			for ( std::list<std::string>::const_iterator it = files.begin(); it != files.end(); ++it, ++nFile )
			{
				pRecentMenu->InsertMenu( -1, MF_BYPOSITION, ID_FILE_RECENT_0 + nFile, it->c_str() );
			}
			if ( pRecentMenu->GetMenuItemCount() == 0 )
			{
				CString strMenuLabel = "No recent files";
				pRecentMenu->InsertMenu( -1, MF_BYPOSITION, ID_FILE_RECENT_0, strMenuLabel );
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEditorApp::OnUpdateRecentFileRange( CCmdUI *pCmdUI )
{
	pCmdUI->Enable( true );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEditorApp::OnRecentFile( UINT nID )
{
	std::list<std::string> files;
	for ( int i = 0; i < m_pRecentFileList->m_nSize; ++i )
	{
		const std::string szProjectFile = (LPCTSTR)((*m_pRecentFileList)[i]);
		if ( !szProjectFile.empty() )
		{
			files.push_back( szProjectFile );
		}
	}
	int nFile = 0;
	for ( std::list<std::string>::const_iterator it = files.begin(); it != files.end(); ++it, ++nFile )
	{
		if ( nFile == nID - ID_FILE_RECENT_0 )
		{
			CParentFrame *pFrame = g_frameManager.ActivateFrameByExtension( it->c_str() );
			if ( pFrame == 0 )
			{
				int nRes = AfxMessageBox( "Error: unknown file extension, do you want to try opening this file in current editor?", MB_YESNO );
				if ( nRes == IDYES )
					pFrame = g_frameManager.GetActiveFrame();
			}
			if ( pFrame )
				pFrame->LoadComposerFile( it->c_str() );
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

