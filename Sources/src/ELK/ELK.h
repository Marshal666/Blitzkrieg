#if !defined(__ELK_APPLICATION__)
#define __ELK_APPLICATION__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CELKApp : public CWinApp
{
public:
	CELKApp();

	//{{AFX_VIRTUAL(CELKApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

public:
	//{{AFX_MSG(CELKApp)
	afx_msg void OnAppAbout();
	afx_msg void OnHelpContents();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(__ELK_APPLICATION__)
