// FrameTree.cpp : implementation file
//

#include "stdafx.h"
#include "FrameTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define ID_TREE_LIST_HEADER 3
#define ID_TREE_LIST_CTRL   1
/////////////////////////////////////////////////////////////////////////////
// CFrameTree
const int CFrameTree::SCROLL_BAR_SIZE = 18;
CFrameTree::CFrameTree() : ifInit(false), bCreateControls( false )
{
	m_pEditBkBrush = new CBrush(RGB(100, 100, 100));
}

CFrameTree::~CFrameTree()
{
	if ( m_pEditBkBrush )
	{
		delete m_pEditBkBrush;
		m_pEditBkBrush = 0;
	}
}


BEGIN_MESSAGE_MAP(CFrameTree, CWnd)
	//{{AFX_MSG_MAP(CFrameTree)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFrameTree message handlers

void CFrameTree::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	// Do not call CWnd::OnPaint() for painting messages
/*	{
		RECT r;
		GetClientRect( &r) ;
		CBrush* pBrush =new CBrush( RGB(255, 255, 0));
		dc.FillRect( &r, pBrush );
		delete pBrush ;
	}*/
}

BOOL CFrameTree::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	bool res = CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
	Init();
	ifInit = true;
	return  res;
}

void CFrameTree::Init()
{
	RECT r;
	GetClientRect( &r) ;

	// create the header
	CRect m_headerRect;
	m_headerRect.left = m_headerRect.top = -1;
	m_headerRect.right = r.right;
	m_headerRect.bottom = SCROLL_BAR_SIZE;
	m_tree.m_wndHeader.Create(WS_CHILD | WS_VISIBLE | HDS_BUTTONS | HDS_HORZ | HDS_FULLDRAG, m_headerRect, this, ID_TREE_LIST_HEADER);
	r.top = m_headerRect.bottom;
	m_tree.Create( WS_CHILD | WS_VISIBLE | TVS_HASLINES | WS_HSCROLL | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS, r, this, ID_TREE_LIST_CTRL   );


}

BOOL CFrameTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	HD_NOTIFY *pHDN = (HD_NOTIFY*)lParam;
	if((wParam == ID_TREE_LIST_HEADER) && (pHDN->hdr.code == HDN_ITEMCHANGED))
	{
		if ( !bCreateControls )
		{
			m_tree.SendMessage( WM_USER + 1 );

			bCreateControls = true;
			CRect rect;
			GetClientRect( &rect );
			
			HDITEM hDItem;
			hDItem.mask = HDI_WIDTH;
			m_tree.m_wndHeader.GetItem( 0, &hDItem );
			hDItem.cxy = rect.Width() - hDItem.cxy;
			m_tree.m_wndHeader.SetItem( 1, &hDItem );
			
			m_tree.Invalidate( false );
			bCreateControls = false;
		}
	}
	return CWnd::OnNotify(wParam, lParam, pResult);
}

BOOL CFrameTree::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	return CWnd::PreTranslateMessage(pMsg);
}

void CFrameTree::OnSize(UINT nType, int cx, int cy) 
{
	if (ifInit )
	{
		CWnd::OnSize(nType, cx, cy);
		m_tree.MoveWindow(0, SCROLL_BAR_SIZE, cx, cy - SCROLL_BAR_SIZE );
		
		HDITEM hDItem;
		hDItem.mask = HDI_WIDTH;
		m_tree.m_wndHeader.GetItem( 0, &hDItem );
		hDItem.cxy = cx - hDItem.cxy;
		m_tree.m_wndHeader.SetItem( 1, &hDItem );
		
		m_tree.m_wndHeader.MoveWindow( 0, 0, cx, SCROLL_BAR_SIZE );
	}
	// TODO: Add your message handler code here
	
}
HBRUSH CFrameTree::OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor )
{
//		pDC->SetBkColor( 0x00323232 );
//		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());    
	return CWnd::OnCtlColor( pDC, pWnd, nCtlColor );
}