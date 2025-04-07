// BatchModeDialog.cpp : implementation file
//

#include "stdafx.h"
#include <browedit.h>

#include "editor.h"
#include "BatchModeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBatchModeDialog dialog


CBatchModeDialog::CBatchModeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBatchModeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBatchModeDialog)
	m_szDestDir = _T("");
	m_szSourceDir = _T("");
	m_forceModeFlag = FALSE;
	m_szSearchMask = _T("");
	m_openAndSaveFlag = FALSE;
	//}}AFX_DATA_INIT
}


void CBatchModeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBatchModeDialog)
	DDX_Text(pDX, IDC_EDIT_DEST_DIR, m_szDestDir);
	DDX_Text(pDX, IDC_EDIT_SOURCE_DIR, m_szSourceDir);
	DDX_Check(pDX, IDC_FORCE_MODE_CHECK, m_forceModeFlag);
	DDX_Text(pDX, IDC_EDIT_SEARCH_MASK, m_szSearchMask);
	DDX_Check(pDX, IDC_OPEN_AND_SAVE, m_openAndSaveFlag);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBatchModeDialog, CDialog)
	//{{AFX_MSG_MAP(CBatchModeDialog)
	ON_BN_CLICKED(IDC_BROWSE_DEST_DIR, OnBrowseDestDir)
	ON_BN_CLICKED(IDC_BROWSE_SOURCE_DIR, OnBrowseSourceDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBatchModeDialog message handlers

void CBatchModeDialog::OnBrowseDestDir() 
{
	SECDirSelectDlg dlg( "Select Destination Directory" );
	dlg.SetInitialDir( m_szDestDir );
	if ( dlg.DoModal() == IDOK )
	{
		UpdateData( TRUE );
		dlg.GetPath( m_szDestDir );
		m_szDestDir.MakeLower();
		UpdateData( FALSE );
	}
}

void CBatchModeDialog::OnBrowseSourceDir() 
{
	SECDirSelectDlg dlg( "Select Source Directory" );
	dlg.SetInitialDir( m_szSourceDir );
	if ( dlg.DoModal() == IDOK )
	{
		UpdateData( TRUE );
		dlg.GetPath( m_szSourceDir );
		m_szSourceDir.MakeLower();
		UpdateData( FALSE );
	}
}
