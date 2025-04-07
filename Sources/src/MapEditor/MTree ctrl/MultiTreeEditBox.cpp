// MultiTreeEditBox.cpp : implementation file
//

#include "stdafx.h"
#include "MultiTreeEditBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiTreeEditBox

CMultiTreeEditBox::CMultiTreeEditBox()
{
}

CMultiTreeEditBox::~CMultiTreeEditBox()
{
}


BEGIN_MESSAGE_MAP(CMultiTreeEditBox, CEdit)
	//{{AFX_MSG_MAP(CMultiTreeEditBox)
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CMultiTreeEditBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetFont( GetParent()->GetParent()->GetParent()->GetFont(), false );
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMultiTreeEditBox message handlers

void CMultiTreeEditBox::OnKillFocus(CWnd* pNewWnd) 
{
	//CEdit::OnKillFocus(pNewWnd);
	// TODO: Add your message handler code here
	GetParent()->SendMessage( WM_USER + 1);
}




BOOL CMultiTreeEditBox::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
		if (pMsg->message == WM_KEYDOWN &&
			pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			GetParent()->SendMessage( WM_USER + 1);
			return TRUE;
		}
		return CEdit::PreTranslateMessage(pMsg);
}
