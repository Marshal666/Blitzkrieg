#if !defined(AFX_GAMEWND_H__2486EA35_E371_4C29_9C16_DDC5367C837E__INCLUDED_)
#define AFX_GAMEWND_H__2486EA35_E371_4C29_9C16_DDC5367C837E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GameWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGameWnd window

class CMainFrame;
class CGameWnd : public CWnd
{
	
// Construction
public:
	CGameWnd();

// Attributes
public:
	//=========================
	CMainFrame *m_mainFramePtr;
	//=========================
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameWnd)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGameWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGameWnd)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMEWND_H__2486EA35_E371_4C29_9C16_DDC5367C837E__INCLUDED_)
