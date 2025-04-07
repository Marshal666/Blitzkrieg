#include "stdafx.h"
#include "editor.h"
#include "EnterScriptIDDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEnterScriptIDDialog::CEnterScriptIDDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEnterScriptIDDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEnterScriptIDDialog)
	m_id = 0;
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEnterScriptIDDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnterScriptIDDialog)
	DDX_Text(pDX, IDC_SCRIPT_ID_EDIT, m_id);
	//}}AFX_DATA_MAP
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CEnterScriptIDDialog, CDialog)
	//{{AFX_MSG_MAP(CEnterScriptIDDialog)
	ON_EN_CHANGE(IDC_SCRIPT_ID_EDIT, OnChangeScriptIdEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEnterScriptIDDialog::UpdateControls()
{
	if ( CWnd *pWnd = GetDlgItem( IDC_SCRIPT_ID_EDIT ) )
	{
		CString strText;
		pWnd->GetWindowText( strText );
		if ( pWnd = GetDlgItem( IDOK ) )
		{
			pWnd->EnableWindow( !strText.IsEmpty() );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEnterScriptIDDialog::OnChangeScriptIdEdit() 
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CEnterScriptIDDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	UpdateControls();
	return TRUE;
}
