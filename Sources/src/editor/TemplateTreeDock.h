#ifndef __TEMPLATE_TREE_DOCK_H__
#define __TEMPLATE_TREE_DOCK_H__

using namespace std;
#include "TemplateTree.h"

class CTemplateTreeCtrl;

/////////////////////////////////////////////////////////////////////////////
// CTemplateTreeDockBar window

class CTemplateTreeDockBar : public SECControlBar
{
	// Construction
public:
	CTemplateTreeDockBar();
	virtual ~CTemplateTreeDockBar();
	
	// Attributes
public:
	
	// Operations
public:
	void SaveTemplateTree( IDataTree *pDT );
	void LoadTemplateTree( IDataTree *pDT );
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTemplateTreeDockBar)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	
	// Generated message map functions
protected:
	CTemplateTreeCtrl *pTemplateTree;
	
	//{{AFX_MSG(CTemplateTreeDockBar)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __TEMPLATE_TREE_DOCK_H__
