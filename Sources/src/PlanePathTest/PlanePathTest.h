// PlanePathTest.h : main header file for the PLANEPATHTEST application
//

#if !defined(AFX_PLANEPATHTEST_H__F369AA91_6A0D_46E3_9D79_98905A3FF8CC__INCLUDED_)
#define AFX_PLANEPATHTEST_H__F369AA91_6A0D_46E3_9D79_98905A3FF8CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPlanePathTestApp:
// See PlanePathTest.cpp for the implementation of this class
//

class CPlanePathTestApp : public CWinApp
{
public:
	CPlanePathTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlanePathTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPlanePathTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLANEPATHTEST_H__F369AA91_6A0D_46E3_9D79_98905A3FF8CC__INCLUDED_)
