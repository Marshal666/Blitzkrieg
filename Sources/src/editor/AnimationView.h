#if !defined(AFX_ANIMATIONVIEW_H__FD350F35_C8FF_499B_8B91_C590E4BDEEE0__INCLUDED_)
#define AFX_ANIMATIONVIEW_H__FD350F35_C8FF_499B_8B91_C590E4BDEEE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnimationView.h : header file
//

//#include "DirectionButton.h"

/////////////////////////////////////////////////////////////////////////////
// CAnimationView window

class CAnimationView : public CWnd
{
// Construction
public:
	CAnimationView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimationView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAnimationView();

private:

	// Generated message map functions
protected:
	//{{AFX_MSG(CAnimationView)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMATIONVIEW_H__FD350F35_C8FF_499B_8B91_C590E4BDEEE0__INCLUDED_)
