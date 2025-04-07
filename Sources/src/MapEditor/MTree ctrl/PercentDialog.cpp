// PercentDialog.cpp : implementation file
//

#include "stdafx.h"
#include "PercentDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPercentDialog dialog


CPercentDialog::CPercentDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPercentDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPercentDialog)
	m_value = 0;
	m_variable = 0;
	//}}AFX_DATA_INIT
}


void CPercentDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPercentDialog)
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Slider(pDX, IDC_SLIDER1, m_value);
	DDX_Text(pDX, IDC_EDIT1, m_variable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPercentDialog, CDialog)
	//{{AFX_MSG_MAP(CPercentDialog)
	ON_WM_HSCROLL()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, OnReleasedcaptureSlider1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPercentDialog message handlers

void CPercentDialog::OnOK() 
{
	// TODO: Add extra validation here
	GetParent()->SendMessage( WM_USER + 1);	
//	CDialog::OnOK();
}

void CPercentDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	UpdateData(true);
	m_variable = m_value;
	UpdateData(  false );
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CPercentDialog::OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	GetParent()->SendMessage( WM_USER + 1);	
	*pResult = 0;
}


