#if !defined(AFX_MULTITREEEDITBOX_H__FC15D22B_F5FA_44C1_8140_39689B14A0B1__INCLUDED_)
#define AFX_MULTITREEEDITBOX_H__FC15D22B_F5FA_44C1_8140_39689B14A0B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MultiTreeEditBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMultiTreeEditBox window

class CMultiTreeEditBox : public CEdit
{
// Construction
public:
	CMultiTreeEditBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiTreeEditBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMultiTreeEditBox();

	// Generated message map functions
protected:
	//CFont	m_Font;
	//{{AFX_MSG(CMultiTreeEditBox)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTITREEEDITBOX_H__FC15D22B_F5FA_44C1_8140_39689B14A0B1__INCLUDED_)
