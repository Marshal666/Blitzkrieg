// MultiTreeSlider.cpp : implementation file
//

#include "stdafx.h"
#include "MultiTreeSlider.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiTreeSlider

CMultiTreeSlider::CMultiTreeSlider()
{
}

CMultiTreeSlider::~CMultiTreeSlider()
{
}


BEGIN_MESSAGE_MAP(CMultiTreeSlider, CSliderCtrl)
	//{{AFX_MSG_MAP(CMultiTreeSlider)
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiTreeSlider message handlers

void CMultiTreeSlider::OnKillFocus(CWnd* pNewWnd) 
{
//	CSliderCtrl::OnKillFocus(pNewWnd);
		GetParent()->SendMessage( WM_USER + 1);

	// TODO: Add your message handler code here
	
}
