// OICombo.cpp : implementation file
//

#include "stdafx.h"
#include "OICombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COICombo

COICombo::COICombo()
{
}

COICombo::~COICombo()
{
}


BEGIN_MESSAGE_MAP(COICombo, CComboBox)
	//{{AFX_MSG_MAP(COICombo)
	ON_WM_CREATE()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COICombo message handlers

int COICombo::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void COICombo::OnKillFocus(CWnd* pNewWnd) 
{
	CComboBox::OnKillFocus(pNewWnd);
	
	if ( pNewWnd && pNewWnd != GetParent() )
		GetParent()->PostMessage( WM_USER + 2, (WPARAM)pNewWnd->m_hWnd );
}
