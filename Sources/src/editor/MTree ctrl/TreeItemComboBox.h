#if !defined(AFX_TREEITEMCOMBOBOX_H__06310D0F_1286_49F6_8EE2_F65ED36E3FC1__INCLUDED_)
#define AFX_TREEITEMCOMBOBOX_H__06310D0F_1286_49F6_8EE2_F65ED36E3FC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeItemComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTreeItemComboBox window

class CTreeItemComboBox : public CComboBox
{
// Construction
public:
	CTreeItemComboBox();

// Attributes
public:

// Operations 
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeItemComboBox)
		virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeItemComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTreeItemComboBox)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEITEMCOMBOBOX_H__06310D0F_1286_49F6_8EE2_F65ED36E3FC1__INCLUDED_)
