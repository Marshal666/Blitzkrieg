// OIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mapedit.h"
#include "OIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COIDlg dialog


COIDlg::COIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COIDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COIDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COIDlg, CDialog)
	//{{AFX_MSG_MAP(COIDlg)
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COIDlg message handlers

BOOL COIDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  
  // Init object inspector
  RECT rect;

  GetClientRect( &rect );
//  GetWindowRect( &rect );
//m_wndOI.CreateEx( WS_EX_STATICEDGE, 0, 0, WS_CHILD | WS_VISIBLE, rect, this, ID_OI );
  m_wndOI.Create( 0, "ObjectInspector", WS_CHILD | WS_VISIBLE, rect, this, ID_OI );
  m_wndOI.SetWindowPos( 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOSIZE );
  
  return TRUE;  // return TRUE  unless you set the focus to a control
}

void COIDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void COIDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
  RECT r;
  GetClientRect( &r );
  if ( ::IsWindow( m_wndOI.m_hWnd ) )
    m_wndOI.SetWindowPos( 0, 0, 0, r.right, r.bottom, SWP_NOZORDER );
}

void COIDlg::OnCancel()
{
  return;
}
