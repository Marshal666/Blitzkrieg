#if !defined(__AUTO_RUN_APPLICATION__)
#define __AUTO_RUN_APPLICATION__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAutoRunApp : public CWinApp
{
public:
	CAutoRunApp();

	//{{AFX_VIRTUAL(CAutoRunApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAutoRunApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(__AUTO_RUN_APPLICATION__)
