// InterfaceSystemTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InterfaceSystemTest.h"
#include "InterfaceSystemTestDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CInterfaceSystemTestDlg dialog

CInterfaceSystemTestDlg::CInterfaceSystemTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInterfaceSystemTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInterfaceSystemTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInterfaceSystemTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInterfaceSystemTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInterfaceSystemTestDlg, CDialog)
	//{{AFX_MSG_MAP(CInterfaceSystemTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterfaceSystemTestDlg message handlers

BOOL CInterfaceSystemTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	pScreen = new CScreen;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CInterfaceSystemTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		
		lines.clear();
		pScreen->Visit( this );
	
		CPaintDC dc(this); // device context for painting
		CPen pen( PS_SOLID, 2, 0x00ff8888 );
		dc.SelectObject( &pen );
		for ( std::list<SColorLine>::iterator it = lines.begin(); it != lines.end(); ++it )
		{
			dc.MoveTo( it->v.first.x, it->v.first.y );
			dc.LineTo( it->v.second.x, it->v.second.y );
		}
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CInterfaceSystemTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CInterfaceSystemTestDlg::VisitBoldLine( CVec3 *corners, float fWidth, DWORD color )
{
	lines.push_back( SColorLine( corners, color, fWidth ) );
}

