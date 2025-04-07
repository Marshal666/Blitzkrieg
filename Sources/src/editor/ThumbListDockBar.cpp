// ThumbListDockBar.cpp : implementation file
//

#include "stdafx.h"
#include "ThumbListDockBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThumbListDockBar

CThumbListDockBar::CThumbListDockBar()
{
}

CThumbListDockBar::~CThumbListDockBar()
{
}


BEGIN_MESSAGE_MAP(CThumbListDockBar, SECControlBar)
//{{AFX_MSG_MAP(CThumbListDockBar)
ON_WM_CREATE()
ON_WM_SIZE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CThumbListDockBar message handlers

int CThumbListDockBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (SECControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create a list control
	DWORD dwStyle = LVS_SHOWSELALWAYS | LVS_SINGLESEL | LVS_ALIGNLEFT | LVS_ICON |
		WS_CHILD | WS_VISIBLE | WS_BORDER;
	m_wndThumbList.Create( 0, "Thumbnail List", dwStyle,
		CRect(0, 0, 0, 0), this, 1005 );
	return 0;
}

void CThumbListDockBar::OnSize(UINT nType, int cx, int cy) 
{
	SECControlBar::OnSize(nType, cx, cy);

	if( m_wndThumbList.GetSafeHwnd() != NULL )
	{
		CRect r;
		GetInsideRect(r);
		m_wndThumbList.SetWindowPos( NULL, r.left, r.top, r.Width(), r.Height(), SWP_NOZORDER|SWP_NOACTIVATE );
	}
}
