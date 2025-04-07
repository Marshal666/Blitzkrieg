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

	void ShowSECControlBar( SECControlBar *pControlBar, int nCommand );
	//void SetMainWindowTitle( const char *pszTitle );
	//void SetMainWindowText( const char *pszText );
	
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
/*	string GetEditorDir() const { return szEditorDir; }
	string GetEditorTempResourceDir() const;
	string GetEditorTempDir() const;
	string GetEditorDataDir() const;*/
//	string GetReferenceDir( int refType ) const;

// Implementation

protected:
	//string szEditorDir;
	HMENU m_hMDIMenu;
	HACCEL hMDIAccel;
	CMainFrame *m_pMainFrame;

public:
	//{{AFX_MSG(CEditorApp)
	afx_msg void OnAppAbout();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CEditorApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITOR_H__EF9ACF1F_0933_498C_B092_A3DED0F07F99__INCLUDED_)
