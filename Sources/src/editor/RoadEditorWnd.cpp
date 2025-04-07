// RoadEditorWnd.cpp : implementation file
//

#include "stdafx.h"

#include "RoadEditorWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoadEditorWnd

CRoadEditorWnd::CRoadEditorWnd()
{
}
 
CRoadEditorWnd::~CRoadEditorWnd()
{
}


BEGIN_MESSAGE_MAP(CRoadEditorWnd, CWnd)
	//{{AFX_MSG_MAP(CRoadEditorWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRoadEditorWnd message handlers

BOOL CRoadEditorWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CWnd::Create( lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext );
}

int CRoadEditorWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	return 0;
}

void CRoadEditorWnd::OnSize(UINT nType, int cx, int cy) 
{

	// TODO: Add your message handler code here
	CWnd::OnSize(nType, cx, cy);
}

void CRoadEditorWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	{
		RECT r;
		GetClientRect( &r) ;
		CBrush* pBrush =new CBrush( RGB(255, 255, 0));
		dc.FillRect( &r, pBrush );
		delete pBrush ;
	}
	// Do not call CWnd::OnPaint() for painting messages
}