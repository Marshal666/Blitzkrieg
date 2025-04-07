// ObjectView.cpp : implementation file
//

#include "StdAfx.h"
#include "ObjectView.h"
#include "ObjectFrm.h"
#include "frames.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjectView

CObjectView::CObjectView()
{
}

CObjectView::~CObjectView()
{
}


BEGIN_MESSAGE_MAP(CObjectView, CWnd)
//{{AFX_MSG_MAP(CObjectView)
ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CObjectView message handlers

BOOL CObjectView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;
	
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);
	
	return TRUE;
}


void CObjectView::OnPaint() 
{

//	if ( g_frameManager.GetFrame( CFrameManager::E_OBJECT_FRAME )->IsRunning() )
	{
		RECT valRC;
		((CWnd *) g_frameManager.GetGameWnd())->GetWindowRect( &valRC );
		ScreenToClient( &valRC );
		ValidateRect( &valRC );
		
		CWnd::OnPaint();
		g_frameManager.GetFrame( CFrameManager::E_OBJECT_FRAME )->GFXDraw();
	}
/*	else
	{
		CWnd::OnPaint();
		ValidateRect( 0 );
	}
*/
}
