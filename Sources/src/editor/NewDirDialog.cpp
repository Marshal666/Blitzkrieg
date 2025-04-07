// NewDirDialog.cpp : implementation file
//

#include "stdafx.h"
#include "editor.h"
#include "NewDirDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewDirDialog dialog


CNewDirDialog::CNewDirDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CNewDirDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewDirDialog)
	m_name = _T("MyMOD");
	//}}AFX_DATA_INIT
}


void CNewDirDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewDirDialog)
	DDX_Text(pDX, IDC_NAME_EDIT, m_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewDirDialog, CDialog)
	//{{AFX_MSG_MAP(CNewDirDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewDirDialog message handlers

void CNewDirDialog::OnOK() 
{
	UpdateData();
	if ( m_name.Find( "\\" ) != -1 || m_name.Find( "/" ) != -1 )
	{
		MessageBox( "Directory name shouldn't contain slash characters!", "Error" );
		return;
	}
	CDialog::OnOK();
}
