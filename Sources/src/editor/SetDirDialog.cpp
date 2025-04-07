// SetDirDialog.cpp : implementation file
//

#include "stdafx.h"
#include <browedit.h>

#include "editor.h"
#include "SetDirDialog.h"
//#include "frames.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetDirDialog dialog


CSetDirDialog::CSetDirDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDirDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetDirDialog)
	m_szSourceDir = _T("");
	m_szExecDir = _T("");
	m_szExecArgs = _T("");
	//}}AFX_DATA_INIT
}


void CSetDirDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetDirDialog)
	DDX_Text(pDX, IDC_EDIT_SOURCE_DIR, m_szSourceDir);
	DDX_Text(pDX, IDC_EDIT_EXEC_DIR, m_szExecDir);
	DDX_Text(pDX, IDC_EDIT_COMMAND, m_szExecArgs);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetDirDialog, CDialog)
	//{{AFX_MSG_MAP(CSetDirDialog)
	ON_BN_CLICKED(IDC_BROWSE_SOURCE_DIR, OnBrowseSourceDir)
	ON_BN_CLICKED(IDC_BROWSE_EXEC_DIR, OnBrowseExecDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetDirDialog message handlers

void CSetDirDialog::OnBrowseSourceDir() 
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CSetDirDialog::OnBrowseExecDir() 
{
	SECDirSelectDlg dlg( "Select Executable Directory" );
	dlg.SetInitialDir( m_szExecDir );
	if ( dlg.DoModal() == IDOK )
	{
		UpdateData( TRUE );
		dlg.GetPath( m_szExecDir );
		m_szExecDir.MakeLower();
		UpdateData( FALSE );
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
