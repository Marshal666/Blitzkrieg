#include "StdAfx.h"

#include "TemplateTree.h"
#include "editor.h"


CTemplateTreeCtrl::CTemplateTreeCtrl()
{
	m_pDragImageList = 0;
	m_bDragging = false;
}

CTemplateTreeCtrl::~CTemplateTreeCtrl()
{
}

BOOL CTemplateTreeCtrl::PreTranslateMessage( MSG* pMsg )
{
	return CWnd::PreTranslateMessage( pMsg );
}

CTemplateTreeProperty* CTemplateTreeCtrl::GetTemplateTreeProperty( HTREEITEM hti )
{
	TV_ITEM tvi;
	tvi.mask = TVIF_PARAM;
	tvi.hItem = hti;
	m_treeCtrl.GetItem(&tvi);
	
	NI_ASSERT( tvi.lParam != 0 );
	return (CTemplateTreeProperty *) tvi.lParam;
}

BEGIN_MESSAGE_MAP(CTemplateTreeCtrl, CWnd)
	//{{AFX_MSG_MAP(CTemplateTreeCtrl)
	ON_WM_CREATE()
  ON_NOTIFY(TVN_BEGINDRAG, IDC_TEMPLATE_TREE_CONTROL, OnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TEMPLATE_TREE_CONTROL, OnItemExpanding)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TEMPLATE_TREE_CONTROL, OnSelect)
	ON_NOTIFY(NM_RCLICK, IDC_TEMPLATE_TREE_CONTROL, OnRButtonClick)
	ON_NOTIFY(TVN_KEYDOWN, IDC_TEMPLATE_TREE_CONTROL, OnKeyDown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTemplateTreeCtrl message handlers

int CTemplateTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	// create a tree control
	DWORD dwStyle = TVS_SHOWSELALWAYS |
		TVS_HASBUTTONS |
		TVS_LINESATROOT |
		TVS_HASLINES |
//		TVS_EDITLABELS |
		TVS_SHOWSELALWAYS |
//		TVS_DISABLEDRAGDROP |
		WS_CHILD | WS_VISIBLE;
	
	DWORD dwStyleEx = /*TVXS_MULTISEL | */ TVXS_FLYBYTOOLTIPS | LVXS_HILIGHTSUBITEMS;
	
	bool bCreated = m_treeCtrl.Create( dwStyle, dwStyleEx, CRect(0, 0, 0, 0), this, IDC_TEMPLATE_TREE_CONTROL );
	NI_ASSERT(bCreated);
/*
  AddSomeItems();
	m_treeCtrl.SetImageList(&m_imlNormal, TVSIL_NORMAL);
*/
	m_treeCtrl.ShowWindow( SW_SHOW );  
  m_treeCtrl.SetNotifyWnd( this );
  m_treeCtrl.UpdateWindow();
	
	return 0;
}

void CTemplateTreeCtrl::LoadImageList( UINT nID )
{
	CBitmap bmp;
	// normal tree images
	m_imlNormal.Create(16,
		16,
		TRUE,
		8,	// number of initial images
		8);
	
	NI_ASSERT( m_imlNormal.m_hImageList != 0 );
	
	bmp.LoadBitmap(nID);
	m_imlNormal.Add( &bmp, RGB(255,255,255));
	bmp.DeleteObject();
	m_treeCtrl.SetImageList(&m_imlNormal, TVSIL_NORMAL);
}

void CTemplateTreeCtrl::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult)
{
//	TRACE(_T("Begin Drag\n"));
	NI_ASSERT(m_bDragging == FALSE);
	NI_ASSERT(m_pDragImageList == NULL);
	
	CPoint ptAction;
	UINT nFlags;
	
	GetCursorPos(&ptAction);
  ScreenToClient( &ptAction );
	
	HTREEITEM hTreeItem = m_treeCtrl.HitTest(ptAction, &nFlags);
  if ( !hTreeItem )
    return;
	
	m_bDragging = TRUE;
	m_hitemDrag = hTreeItem;
	m_pDragImageList = m_treeCtrl.CreateDragImage(hTreeItem);

	NI_ASSERT( m_pDragImageList != 0 );
	m_pDragImageList->DragShowNolock(TRUE);

	CRect rcItem;
	m_treeCtrl.GetItemRect(hTreeItem, &rcItem, TRUE);
	m_pDragImageList->BeginDrag(0, CPoint( ptAction.x - rcItem.left, ptAction.y - rcItem.top ) );

	CRect r;
  theApp.GetMainWnd()->GetWindowRect( &r );
	GetCursorPos(&ptAction);
  ptAction -= r.TopLeft();
  rcItem   -= r.TopLeft();

	m_pDragImageList->DragMove(ptAction);
	m_pDragImageList->DragEnter(theApp.GetMainWnd(), ptAction);
//	m_pDragImageList->DragEnter(this, ptAction);
	SetCapture();
	
  *pResult = 0;
}

void CTemplateTreeCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bDragging)
	{
		HTREEITEM		hitem;
		UINT				flags;
    CRect       r;
    CPoint      pt, ptTree;
		
		NI_ASSERT(m_pDragImageList != NULL);
		
    theApp.GetMainWnd()->GetWindowRect( &r );
		GetCursorPos( &pt );
    pt -= r.TopLeft();
		m_pDragImageList->DragMove( pt );
		
    GetCursorPos(&ptTree);
    ScreenToClient( &ptTree );

		hitem = m_treeCtrl.HitTest(ptTree, &flags);
		if ( hitem && (TVHT_ONITEM & flags) )
		{
/*
			//Проверяем типы item drag & item drop
			CTreeItem *pDrag = GetTreeItem( m_hitemDrag );
			CTreeItem *pDrop = GetTreeItem( hitem );

//			if ( pDrag->GetItemType() == pDrop->GetItemType() )
			if ( pDrag->IsCompatibleWith(pDrop) )
			{
				m_pDragImageList->DragLeave( theApp.GetMainWnd() );
				m_treeCtrl.SelectDropTarget( hitem );
				m_hitemDrop = hitem;
				m_pDragImageList->DragEnter( theApp.GetMainWnd(), pt );
			}
			else
			{
				m_pDragImageList->DragLeave( theApp.GetMainWnd() );
				m_treeCtrl.SelectDropTarget( 0 );
				m_pDragImageList->DragEnter( theApp.GetMainWnd(), pt );
			}
*/
		}
		else if ( !hitem )
		{
			m_pDragImageList->DragLeave(theApp.GetMainWnd());
			m_treeCtrl.SelectDropTarget( 0 );
			m_pDragImageList->DragEnter(theApp.GetMainWnd(), pt);
		}
/*
		else if ( m_hitemDrop && !(TVHT_ONITEM & flags) )
		{
			//m_treeCtrl.SelectDropTarget(0);
			m_treeCtrl.SelectItem(0);
			m_hitemDrop = 0;
		}
*/
	}
	
	CWnd::OnMouseMove(nFlags, point);
}

void CTemplateTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
  if(m_bDragging == TRUE)
  {
//		TRACE(_T("End Drag\n"));
		ReleaseCapture();
		NI_ASSERT(m_pDragImageList != NULL);
		m_pDragImageList->DragLeave(this);
		m_pDragImageList->EndDrag();
		delete m_pDragImageList;
		m_pDragImageList = NULL;
		m_bDragging = FALSE;
/*
		TV_ITEM tvidrag;
		memset( &tvidrag, 0, sizeof(tvidrag) );
		tvidrag.mask  = TVIF_PARAM;
		tvidrag.hItem = m_hitemDrag;
		m_treeCtrl.GetItem(&tvidrag);
*/

//		m_treeCtrl.SelectDropTarget( 0 );
/*
		CRect rect;
		GetClientRect( &rect );
		// если объект кинули мимо нашего окна, посылаем сообщение родительскому окну и выходим
		if ( !rect.PtInRect( point )
			//&& !IsFolder( tvidrag.lParam )
			)
		{
			m_treeCtrl.SelectDropTarget( 0 );
			GetParent()->PostMessage( WM_DROPITEM, nTreeID, tvidrag.lParam );
			CWnd::OnLButtonUp(nFlags, point);
			m_treeCtrl.SelectDropTarget( 0 );
			return;
		}
*/
		HTREEITEM hItemDrop = m_treeCtrl.GetDropHilightItem();
		m_treeCtrl.SelectDropTarget( 0 );
		if ( hItemDrop == NULL || hItemDrop == m_hitemDrag )
			return;

		//Проверяем типы item drag & item drop
/*
		CTreeItem *pDrag = GetTreeItem( m_hitemDrag );
		CTreeItem *pDrop = GetTreeItem( hItemDrop );

		pDrag->CopyItemTo( pDrop );
*/

  }
  
  CWnd::OnLButtonUp(nFlags, point);
}

void CTemplateTreeCtrl::OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
/*
	NM_TREEVIEW* pInfo = (NM_TREEVIEW*)pNMHDR;
	TRACE( _T("expanding\n"));
	
	if ( (pInfo->itemNew.lParam == ON_DEMAND_NODE) && (pInfo->action == TVE_EXPAND) )
	{
		TRACE( _T("adding children on demand\n"));
		AddChildrenOnDemand( pInfo->itemNew.hItem );
	}
*/
	*pResult = 0;
}

void CTemplateTreeCtrl::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CWnd::OnShowWindow(bShow, nStatus);
	
	// для правильной работы QuickView окна, 
	// которое показывает текущий поселекченный объект
	if ( !bShow )
		m_treeCtrl.DeselectAllItems();
}

/////////////////////////////////////////////////////////////////////////////////////
// Без этой функции триконтрола мы не увидим
void CTemplateTreeCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);

	if ( ::IsWindow(m_treeCtrl) )
		m_treeCtrl.SetWindowPos( NULL, 0, 0, cx, cy,
		SWP_NOMOVE |
		SWP_NOACTIVATE |
		SWP_NOZORDER );
}

void CTemplateTreeCtrl::OnSelect(NMHDR* pNMHDR, LRESULT* pResult)
{
	HTREEITEM hti = m_treeCtrl.GetFirstSelectedItem();

	if ( hti )
	{
		LPARAM lParam = m_treeCtrl.GetItemData( hti );
		GetParent()->PostMessage( WM_USERTREESEL, 0, lParam );
	}
	*pResult = 0;
}

/*
void CTemplateTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if ( m_bDragging )
	{
		m_bDragging = false;
		m_hitemDrag = 0;
		m_hitemDrop = 0;
    ReleaseCapture();
    NI_ASSERT(m_pDragImageList != NULL);
    m_pDragImageList->DragLeave(this);
    m_pDragImageList->EndDrag();
    delete m_pDragImageList;
    m_pDragImageList = 0;
		m_treeCtrl.SelectDropTarget( 0 );
	}

	CWnd::OnRButtonDown(nFlags, point);
}

void CTemplateTreeCtrl::OnRButtonUp(UINT nFlags, CPoint point) 
{
	HTREEITEM hti = m_treeCtrl.GetFirstSelectedItem();
	if ( hti )
	{
		LPARAM lParam = m_treeCtrl.GetItemData( hti );
		GetParent()->PostMessage( WM_USERRBUTTONUP, 0, lParam );
	}

	CWnd::OnRButtonUp(nFlags, point);
}
*/

void CTemplateTreeCtrl::OnRButtonClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;

	HTREEITEM hti = m_treeCtrl.GetFirstSelectedItem();
	if ( hti )
	{
		LPARAM lParam = m_treeCtrl.GetItemData( hti );
		GetParent()->PostMessage( WM_USERRBUTTONCLICK, 0, lParam );
	}
}

void CTemplateTreeCtrl::OnKeyDown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMTVKEYDOWN ptvkd = (LPNMTVKEYDOWN)pNMHDR;
	HTREEITEM hti = m_treeCtrl.GetFirstSelectedItem();

	if ( hti )
	{
		LPARAM lParam = m_treeCtrl.GetItemData( hti );
		GetParent()->PostMessage( WM_USERKEYDOWN, ptvkd->wVKey, lParam );
	}
	*pResult = 0;
}

void CTemplateTreeCtrl::SaveTemplateTree( IDataTree *pDT )
{	
/*
	pRootItem->Serialize( pDT );
*/
}

void CTemplateTreeCtrl::LoadTemplateTree( IDataTree *pDT )
{
/*
	//Сперва убиваем все childs в дереве
	pRootItem->RemoveAllChilds();
	
	pRootItem->Serialize( pDT );
	//тут надо пройти по всем childs и удалить нулевые элементы
	pRootItem->DeleteNullChilds();
	pRootItem->CreateDefaultChilds();
	pRootItem->InsertChildItems();
*/
}
