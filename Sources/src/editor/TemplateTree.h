#ifndef __TEMPLATE_TREE_H__
#define __TEMPLATE_TREE_H__

#include <TrCtlX.h>

#define IDC_TEMPLATE_TREE_CONTROL 2000

// ��� ��������� �� ������
const UINT WM_USERTREESEL				= WM_USER + 1;				// ���������� ������ �������
const UINT WM_USERDROPITEM			= WM_USER + 2;				// Drop ��� �������� ������
const UINT WM_USERKEYDOWN				= WM_USER + 3;				// ������ �������
const UINT WM_USERRBUTTONCLICK	= WM_USER + 4;				// ���� ������ �����

class CTemplateTreeProperty;

/////////////////////////////////////////////////////////////////////////////
// CTemplateTreeCtrl window

class CTemplateTreeCtrl : public CWnd
{
// Construction
public:
	CTemplateTreeCtrl();
	virtual ~CTemplateTreeCtrl();

// Attributes
private:
  SECTreeCtrl m_treeCtrl;
	CImageList *m_pDragImageList;
	CImageList m_imlNormal;
	HTREEITEM m_hitemDrop;
	HTREEITEM m_hitemDrag;
	bool m_bDragging;

public:
	SECTreeCtrl* GetTreeCtrl() { return &m_treeCtrl; }
	void LoadImageList( UINT nID );
	CTemplateTreeProperty* GetTemplateTreeProperty( HTREEITEM hti );

	void SaveTemplateTree( IDataTree *pDT );
	void LoadTemplateTree( IDataTree *pDT );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CETreeCtrl)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
		//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CETreeCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelect(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeyDown(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif	//__TEMPLATE_TREE_H__