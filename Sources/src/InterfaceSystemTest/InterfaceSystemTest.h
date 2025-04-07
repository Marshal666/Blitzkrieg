// InterfaceSystemTest.h : main header file for the INTERFACESYSTEMTEST application
//

#if !defined(AFX_INTERFACESYSTEMTEST_H__BF2F8ED6_8A9F_4FCD_94CC_9733E732D5B8__INCLUDED_)
#define AFX_INTERFACESYSTEMTEST_H__BF2F8ED6_8A9F_4FCD_94CC_9733E732D5B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CInterfaceSystemTestApp:
// See InterfaceSystemTest.cpp for the implementation of this class
//

class CInterfaceSystemTestApp : public CWinApp
{
public:
	CInterfaceSystemTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterfaceSystemTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CInterfaceSystemTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERFACESYSTEMTEST_H__BF2F8ED6_8A9F_4FCD_94CC_9733E732D5B8__INCLUDED_)
