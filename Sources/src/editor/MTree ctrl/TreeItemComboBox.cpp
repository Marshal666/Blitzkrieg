// TreeItemComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "TreeItemComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeItemComboBox

CTreeItemComboBox::CTreeItemComboBox()
{
}

CTreeItemComboBox::~CTreeItemComboBox()
{
}


BEGIN_MESSAGE_MAP(CTreeItemComboBox, CComboBox)
	//{{AFX_MSG_MAP(CTreeItemComboBox)
	ON_WM_KILLFOCUS() 
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeItemComboBox message handlers

void CTreeItemComboBox::OnKillFocus(CWnd* pNewWnd) 
{
	//CComboBox::OnKillFocus(pNewWnd);
		GetParent()->SendMessage( WM_USER + 1);
	// TODO: Add your message handler code here
	
}

int CTreeItemComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	SetFont( GetParent()->GetParent()->GetParent()->GetFont(), false );
	return 0;
}


BOOL CTreeItemComboBox::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
		if (pMsg->message == WM_KEYDOWN &&
			pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			GetParent()->SendMessage( WM_USER + 1);
			return TRUE;
		}
		return CComboBox::PreTranslateMessage(pMsg);
}
