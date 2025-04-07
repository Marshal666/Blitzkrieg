#ifndef __PROPVIEW_H__
#define __PROPVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CtrlObjectInspector.h"
class CTreeItem;

//Это сообщения из Object Inspector через дерево идут во frame
const UINT WM_USERCHANGEPARAM = WM_USER + 10;		// пользователь поменял значение в OI

/////////////////////////////////////////////////////////////////////////////
// CPropView window

class CPropView : public SECControlBar
{
public:
  
  // Operations
public:
	void SetItemProperty( const char *szItemName, CTreeItem *pProp );
	void ClearControl() { pActiveTreeItem = 0; m_wndOI.ClearAll(); }

/*
  void SetPropMap( const CPropMap *_pPropMap );
  int  GetActiveProp( int nGroupID );
	void SetActiveProp( int nPropID );
  void UpdatePropList();
  void UpdateProperty( int nPropID );
*/
  // Implementation
  BOOL PreTranslateMessage( MSG* pMsg );
  //  BOOL OnInitDialog();
  
public:
  CPropView();  
  virtual ~CPropView();
	void UpdateValue( PropID nID );
  
  // Generated message map functions
protected:
	CCtrlObjectInspector m_wndOI;
	CTreeItem *pActiveTreeItem;

  
  //{{AFX_MSG(CPropView)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnChangeProp( WPARAM wParam, LPARAM lParam );
	//}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

#endif // __PROPVIEW_H__
