// SECShortcutBarWithNotify.cpp : implementation file
//

#include "stdafx.h"
#include "editor.h"
#include "SECShortcutBarWithNotify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SECShortcutBarWithNotify

SECShortcutBarWithNotify::SECShortcutBarWithNotify()
{
}

SECShortcutBarWithNotify::~SECShortcutBarWithNotify()
{
}


BEGIN_MESSAGE_MAP(SECShortcutBarWithNotify, SECShortcutBar)
	//{{AFX_MSG_MAP(SECShortcutBarWithNotify)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// SECShortcutBarWithNotify message handlers

BOOL SECShortcutBarWithNotify::OnChangeBar( int Index)
{

	SShortcutBarNotify_NMHDR       nmhdr;
	CWnd *pParent = GetParent();
	if( pParent )
	{
		memset( &nmhdr, 0, sizeof(SShortcutBarNotify_NMHDR) );
		nmhdr.hdr.hwndFrom = GetSafeHwnd();
		nmhdr.hdr.idFrom   = IDC_SHORTCUTBAR;
		nmhdr.hdr.code	   = NM_CHANGEPAGE;
		nmhdr.nIndex = Index;
		pParent->SendMessage( WM_NOTIFY,
			IDC_SHORTCUTBAR, 
			(LPARAM)&nmhdr );
	}
	return true;
}