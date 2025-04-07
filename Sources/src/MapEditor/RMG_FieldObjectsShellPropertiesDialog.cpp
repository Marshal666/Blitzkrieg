#include "stdafx.h"

#include "RMG_FieldObjectsShellPropertiesDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CRMGFieldObjectsShellPropertiesDialog::CRMGFieldObjectsShellPropertiesDialog( CWnd* pParent )
	: CResizeDialog( CRMGFieldObjectsShellPropertiesDialog::IDD, pParent )
{
	//{{AFX_DATA_INIT(CRMGFieldObjectsShellPropertiesDialog)
	m_szWidth = _T("");
	m_szStep = _T("");
	m_szRatio = _T("");
	//}}AFX_DATA_INIT

	SetControlStyle( IDC_RMG_CF_TS_WIDTH_LABEL_LEFT, ANCHORE_LEFT_TOP );
	SetControlStyle( IDC_RMG_CF_TS_WIDTH_EDIT, ANCHORE_LEFT_TOP | RESIZE_HOR );
	SetControlStyle( IDC_RMG_CF_TS_WIDTH_LABEL_RIGHT, ANCHORE_RIGHT_TOP );
	
	SetControlStyle( IDOK, ANCHORE_BOTTOM | ANCHORE_HOR_CENTER );
	SetControlStyle( IDCANCEL, ANCHORE_BOTTOM | ANCHORE_HOR_CENTER );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CRMGFieldObjectsShellPropertiesDialog::DoDataExchange(CDataExchange* pDX)
{
	CResizeDialog::DoDataExchange( pDX );
	//{{AFX_DATA_MAP( CRMGFieldObjectsShellPropertiesDialog )
	DDX_Text(pDX, IDC_RMG_CF_OS_WIDTH_EDIT, m_szWidth);
	DDX_Text(pDX, IDC_RMG_CF_OS_STEP_EDIT, m_szStep);
	DDX_Text(pDX, IDC_RMG_CF_OS_PROBABILITY_EDIT, m_szRatio);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CRMGFieldObjectsShellPropertiesDialog, CResizeDialog)
	//{{AFX_MSG_MAP(CRMGFieldObjectsShellPropertiesDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// basement storage  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
