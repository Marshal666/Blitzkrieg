#if !defined(AFX_OIEDIT_H__257BD5B4_F0D5_4982_AB55_368BE38F3314__INCLUDED_)
#define AFX_OIEDIT_H__257BD5B4_F0D5_4982_AB55_368BE38F3314__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OIEdit.h : header file
//

const UINT WM_USER_LOST_FOCUS = WM_USER + 2;
/////////////////////////////////////////////////////////////////////////////
// COIEdit window

class COIEdit : public CEdit
{
// Construction
public:
	COIEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COIEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COIEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(COIEdit)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OIEDIT_H__257BD5B4_F0D5_4982_AB55_368BE38F3314__INCLUDED_)
