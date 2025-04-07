// BrowseDialog.cpp : implementation file
//

#include "stdafx.h"
#include "editor.h"
#include "frames.h"
#include "BrowseDialog.h"
#include "MyOpenFileDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrowseDialog dialog


CBrowseDialog::CBrowseDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBrowseDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBrowseDialog)
	m_szFileName = _T("");
	//}}AFX_DATA_INIT
}


void CBrowseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBrowseDialog)
	DDX_Text(pDX, IDC_EDIT_FILE, m_szFileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBrowseDialog, CDialog)
	//{{AFX_MSG_MAP(CBrowseDialog)
	ON_BN_CLICKED(ID_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrowseDialog message handlers

void CBrowseDialog::OnBrowse() 
{
	std::string szRes;
	if ( !ShowFileDialog( szRes, GetDirectory(m_szFileName).c_str(), m_szTitle, FALSE, m_szExtension, m_szFileName, m_szFilter ) )
		return;

	UpdateData( TRUE );
	m_szFileName = szRes.c_str();
	UpdateData( FALSE );
}
