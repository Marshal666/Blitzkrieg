// MapOptionsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "editor.h"
#include "MapOptionsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int CMapOptionsDialog::vID[] = 
{
	IDC_SCRIPT_FILE_LABEL,								//0
	IDC_SCRIPT_FILE_EDIT,									//1
	IDC_SCRIPT_FILE_BROWSE_BUTTON,				//2
	IDOK,																	//2
	IDCANCEL,															//3
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CMapOptionsDialog::CMapOptionsDialog(CWnd* pParent )
	: CResizeDialog(CMapOptionsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMapOptionsDialog)
	m_name = _T("");
	//}}AFX_DATA_INIT

	SetControlStyle( IDC_SCRIPT_FILE_LABEL, ANCHORE_LEFT_TOP );
	SetControlStyle( IDC_SCRIPT_FILE_EDIT, ANCHORE_LEFT_TOP | RESIZE_HOR );
	SetControlStyle( IDC_SCRIPT_FILE_BROWSE_BUTTON, ANCHORE_RIGHT_TOP );
	SetControlStyle( IDOK, ANCHORE_BOTTOM | ANCHORE_HOR_CENTER );
	SetControlStyle( IDCANCEL, ANCHORE_BOTTOM | ANCHORE_HOR_CENTER );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CMapOptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapOptionsDialog)
	DDX_Text(pDX, IDC_SCRIPT_FILE_EDIT, m_name);
	//}}AFX_DATA_MAP
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CMapOptionsDialog, CResizeDialog)
	//{{AFX_MSG_MAP(CMapOptionsDialog)
	ON_BN_CLICKED(IDC_SCRIPT_FILE_BROWSE_BUTTON, OnGetFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CMapOptionsDialog::OnGetFile() 
{
	CFileDialog dlg( true, ".lua", "", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Lua files (*.lua)|*.lua" );
	if ( dlg.DoModal() == IDOK )
	{
		m_name = dlg.GetPathName();	
		std::string tmp = m_name;
		tmp = std::string( tmp, tmp.rfind("\\") + 1 );
		tmp = std::string( tmp, 0, tmp.length() - 4 );
		tmp = tmp;
		m_name = tmp.c_str();
		UpdateData( false );
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
