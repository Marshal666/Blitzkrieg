#include "StdAfx.h"
#include "WeaponView.h"
#include "frames.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWeaponView

CWeaponView::CWeaponView()
{
}

CWeaponView::~CWeaponView()
{
}


BEGIN_MESSAGE_MAP(CWeaponView, CWnd)
//{{AFX_MSG_MAP(CWeaponView)
ON_WM_PAINT()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWeaponView message handlers

BOOL CWeaponView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;
	
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);
	
	return TRUE;
}


void CWeaponView::OnPaint() 
{
	CWnd::OnPaint();
}
