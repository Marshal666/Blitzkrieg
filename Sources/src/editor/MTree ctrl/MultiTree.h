#if !defined(AFX_MULTITREE_H__C215D318_F9F4_40AD_B30F_81CADE81DAA5__INCLUDED_)
#define AFX_MULTITREE_H__C215D318_F9F4_40AD_B30F_81CADE81DAA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MultiTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMultiTree window

#include "CTreeItem.h"
#include "MultiTreeEditBox.h"
enum TREEITEMTYPES
{
	simpleTreeItem,
	truefalseTreeItem,
	procentTreeItem,
	numComboBoxItem,
	emptyItem,
	propertieItem,
	propertieItemCombo,
	propertieItemDir,
	propertieItemFile,
	propertieItemUnits,
};
class CMultiTree : public CTreeCtrl
{
// Construction
public:
	CMultiTree();
	CHeaderCtrl m_wndHeader;
// Attributes 
public:
	//  using with usual types
	HTREEITEM InsertItem( LPCTSTR lpszItem, int nImage, int nSelectedImage, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
	HTREEITEM InsertItem(LPCTSTR lpszItem, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST );
	HTREEITEM InsertItem(UINT nMask, LPCTSTR lpszItem, int nImage, int nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam, HTREEITEM hParent, HTREEITEM hInsertAfter );
	//
	
	BOOL SetItemData(HTREEITEM hItem, DWORD dwData);
	DWORD GetItemData(HTREEITEM hItem) const;

	ITreeItem* GetTreeItemPtr(HTREEITEM hItem);

	int GetColumnWidth(int nCol);

	HTREEITEM InsertItemEx(LPCTSTR lpszItem, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST ,TREEITEMTYPES type = truefalseTreeItem );

	void DrawItemText (CDC* pDC, CString &text, CRect &rect, int nWidth, int nFormat);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiTree)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetFullWidth();
	virtual ~CMultiTree();
	void SafeDeleteItem( HTREEITEM item );
	void SafeDeleteAllItems();
	
private:
	CMultiTreeEditBox *m_editCtl;
	HTREEITEM m_editedItem;

	// Generated message map functions
protected:
	//{{AFX_MSG(CMultiTree)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTITREE_H__C215D318_F9F4_40AD_B30F_81CADE81DAA5__INCLUDED_)
