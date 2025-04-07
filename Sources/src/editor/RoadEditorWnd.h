#if !defined(AFX_RoadEditorWnd_H__B695C508_0D00_475E_8FF7_C9693CE02D39__INCLUDED_)
#define AFX_RoadEditorWnd_H__B695C508_0D00_475E_8FF7_C9693CE02D39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RoadEditorWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRoadEditorWnd window


class CRoadEditorWnd : public CWnd
{
	
// Construction
public:
	CRoadEditorWnd(); 

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoadEditorWnd)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRoadEditorWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRoadEditorWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RoadEditorWnd_H__B695C508_0D00_475E_8FF7_C9693CE02D39__INCLUDED_)
