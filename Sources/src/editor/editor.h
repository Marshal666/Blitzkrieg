// editor.h : main header file for the EDITOR application
//

#if !defined(AFX_EDITOR_H__EF9ACF1F_0933_498C_B092_A3DED0F07F99__INCLUDED_)
#define AFX_EDITOR_H__EF9ACF1F_0933_498C_B092_A3DED0F07F99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

using std::string;

#include "resource.h"       // main symbols
class CSimpleWindow;
class CMainFrame;

/////////////////////////////////////////////////////////////////////////////
// CEditorApp:
// See editor.cpp for the implementation of this class
//

class CEditorApp : public CWinApp
{
public:
	CEditorApp();
	~CEditorApp() {}

	void SaveRegisterData();
	void LoadRegisterData();

	void SaveVersionNumber();
	void LoadVersionNumber();
	void SaveDirs();
	void LoadDirs();
	void SaveNewFrameTypeToRegister();
	int LoadLastActiveModuleID();
	
	//if this function returns true, then application will be closed
	bool RunBatchMode();

	void UpdateStatusBarIndicators();
	void UpdateStatusBarCoordsIndicator(const POINT &pt);
	void UpdateStatusBarControlIndicator(const RECT &rc);
	void UpdateStatusBarControlIndicator(const CTRect<float> &rc);
	void ClearStatusBarControlIndicator();
	void ShowSECControlBar( SECControlBar *pControlBar, int nCommand );
	void ShowSECToolBar( SECControlBar *pToolBar, int nCommand );
	void SetMainWindowTitle( const char *pszTitle );
	void SetMainWindowText( const char *pszText );

	void WriteProfileFloat( const char *pszName, float f );
	float GetProfileFloat( const char *pszName );

	BOOL MyWriteProfileString( LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszValue );
	CString MyGetProfileString( LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault = NULL );
	BOOL MyWriteProfileInt( LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue );
	UINT MyGetProfileInt( LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault );

	bool IsInitFinished() { return m_bInitFinished; }
	bool IsVersionIncreased() { return m_bVersionIncreased; }
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditorApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
//	virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);
	virtual BOOL OnIdle(LONG lCount);
	virtual BOOL SaveAllModified();
	//}}AFX_VIRTUAL

	CMainFrame *GetMainFrame() { return m_pMainFrame; }
	string GetEditorDir() const { return szEditorDir; }
	string GetEditorTempResourceDir() const;
	string GetEditorTempDir() const;
	string GetEditorDataDir() const;

	const string& GetSourceDir() { return szSourceDir; }
	const string GetDestDir() { return szDestDir + "data\\"; }
	const string& GetCleanDestDir() { return szDestDir; }
	const string& GetExecDir() { return szExecDir; }
	const string& GetExecArgs() { return szExecArgs; }
	const string& GetMODName() { return szMODName; }
	const string& GetMODVersion() { return szMODVersion; }
	const string& GetMODDesc() { return szMODDesc; }
	void SetSourceDir( const char *pszName ) { szSourceDir = pszName; }
	void SetDestDir( const char *pszName ) { szDestDir = pszName; }
	void SetExecDir( const char *pszName ) { szExecDir = pszName; }
	void SetExecArgs( const char *pszArgs ) { szExecArgs = pszArgs; }
	void SetMODName( const char *pszName ) { szMODName = pszName; }
	void SetMODVersion( const char *pszVersion ) { szMODVersion = pszVersion; }
	void SetMODDesc( const char *pszDesc ) { szMODDesc = pszDesc; }
	void ReadMODFile( const std::string &szPath, std::string &szName, std::string &szVersion, std::string &szDesc );
	void WriteMODFile( const std::string &szPath, const std::string &szName, const std::string &szVersion, const std::string &szDesc );

// Implementation

protected:
	string szEditorDir;					//содержит директорию исполняемого файла компоновщика (reseditor.exe)
	string szExecDir;           //dir с game.exe
	string szMODName;           //название текущего мода
	string szMODVersion;        //версия текущего мода
	string szMODDesc;           //MOD description string
	string szExecArgs;          //game.exe args
	string szSourceDir;					//общая директория к исходникам для всех модулей
	string szDestDir;						//общая экспортируемая директория для всех модулей
	HMENU m_hMDIMenu;
	HACCEL m_hMDIAccel;
	CMainFrame *m_pMainFrame;
	bool m_bInitFinished;
	bool m_bVersionIncreased;

public:
	//{{AFX_MSG(CEditorApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg void OnUpdateRecentFile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecentFileRange(CCmdUI* pCmdUI);
	afx_msg void OnRecentFile( UINT nID );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CEditorApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITOR_H__EF9ACF1F_0933_498C_B092_A3DED0F07F99__INCLUDED_)
