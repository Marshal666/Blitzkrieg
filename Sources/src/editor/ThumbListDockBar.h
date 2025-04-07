#ifndef __THUMB_LIST_DOCK_BAR_H__
#define __THUMB_LIST_DOCK_BAR_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThumbListDockBar.h : header file
//

#include "ThumbList.h"
class CTemplateTree;

/////////////////////////////////////////////////////////////////////////////
// CThumbListDockBar window

class CThumbListDockBar : public SECControlBar
{
	// Construction
public:
	CThumbListDockBar();
	
	// Attributes
public:
private:
	CThumbList m_wndThumbList;
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThumbListDockBar)
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CThumbListDockBar();
	CThumbList *GetThumbListCtrl() { return &m_wndThumbList; }

	// Generated message map functions
protected:
	//{{AFX_MSG(CThumbListDockBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif		// __THUMB_LIST_DOCK_BAR_H__
