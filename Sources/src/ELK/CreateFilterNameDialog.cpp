#include "stdafx.h"

#include "CreateFilterNameDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int CCreateFilterNameDialog::vID[] = 
{
	IDC_CF_FILTER_NAME_LABEL,	//0
	IDC_CF_FILTER_NAME_EDIT,	//1
	IDOK,											//2
	IDCANCEL,									//3
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CCreateFilterNameDialog::CCreateFilterNameDialog( CWnd* pParent )
	: CResizeDialog( CCreateFilterNameDialog::IDD, pParent )
{
	//{{AFX_DATA_INIT(CCreateFilterNameDialog)
	m_Name = _T( "" );
	//}}AFX_DATA_INIT

	SetControlStyle( IDC_CF_FILTER_NAME_LABEL, ANCHORE_LEFT_TOP );
	SetControlStyle( IDC_CF_FILTER_NAME_EDIT, ANCHORE_LEFT_TOP | RESIZE_HOR );

	SetControlStyle( IDOK, ANCHORE_HOR_CENTER | ANCHORE_BOTTOM );
	SetControlStyle( IDCANCEL, ANCHORE_HOR_CENTER | ANCHORE_BOTTOM );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string CCreateFilterNameDialog::GetRegistryKey()
{
	CString strPath;
	CString strProgramKey;
	CString strKey;
	strPath.LoadString( IDS_REGISTRY_PATH );
	strProgramKey.LoadString( AFX_IDS_APP_TITLE );
	strKey.LoadString( IDS_CFN_REGISTRY_KEY );
	std::string szRegistryKey = NStr::Format( _T( "Software\\%s\\%s\\%s" ), LPCTSTR( strPath ), LPCTSTR( strProgramKey ), LPCTSTR( strKey ) );
	return szRegistryKey;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterNameDialog::DoDataExchange(CDataExchange* pDX)
{
	CResizeDialog::DoDataExchange( pDX );
	//{{AFX_DATA_MAP( CCreateFilterNameDialog )
	DDX_Text(pDX, IDC_CF_FILTER_NAME_EDIT, m_Name);
	//}}AFX_DATA_MAP
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CCreateFilterNameDialog, CResizeDialog)
	//{{AFX_MSG_MAP(CCreateFilterNameDialog)
	ON_EN_CHANGE(IDC_CF_FILTER_NAME_EDIT, OnChangeFilterNameEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterNameDialog::OnChangeFilterNameEdit() 
{
	UpdateControls();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CCreateFilterNameDialog::OnInitDialog() 
{
	CResizeDialog::OnInitDialog();

	UpdateControls();
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterNameDialog::UpdateControls()
{
	if ( CWnd *pWnd = GetDlgItem( IDC_CF_FILTER_NAME_EDIT ) )
	{
		CString strText;
		pWnd->GetWindowText( strText );
		
		if ( pWnd = GetDlgItem( IDOK ) )
		{
			pWnd->EnableWindow( !strText.IsEmpty() );
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// basement storage  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

