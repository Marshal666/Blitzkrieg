#if !defined(AFX_FRAMETREE_H__C3164C06_6784_4F26_A565_BCA2A98A0600__INCLUDED_)
#define AFX_FRAMETREE_H__C3164C06_6784_4F26_A565_BCA2A98A0600__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FrameTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFrameTree window
#include "MultiTree.h"

class CFrameTree : public CWnd
{
// Construction
public:
	static const int SCROLL_BAR_SIZE;
	CFrameTree();

// Attributes
public:
	CMultiTree m_tree;
	bool ifInit;
	bool bCreateControls;
// Operations
public:

	// Overrides
	BOOL SetItemData(HTREEITEM hItem, DWORD dwData);
	DWORD GetItemData(HTREEITEM hItem) const;

	HTREEITEM InsertItem( LPCTSTR lpszItem, int nImage, int nSelectedImage, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
	HTREEITEM InsertItem(LPCTSTR lpszItem, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST );
	HTREEITEM InsertItem(UINT nMask, LPCTSTR lpszItem, int nImage, int nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam, HTREEITEM hParent, HTREEITEM hInsertAfter );

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameTree)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	void Init();
	virtual ~CFrameTree();

	// Generated message map functions
protected:

	CBrush* m_pEditBkBrush;

	//{{AFX_MSG(CFrameTree)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor );

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMETREE_H__C3164C06_6784_4F26_A565_BCA2A98A0600__INCLUDED_)
