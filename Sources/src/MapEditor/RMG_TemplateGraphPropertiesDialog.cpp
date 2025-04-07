#include "stdafx.h"

#include "RMG_TemplateGraphPropertiesDialog.h"

//#include "editor.h"

//#include "MapEditorBarWnd.h"
//#include "TemplateEditorFrame1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int CRMGTemplateGraphPropertiesDialog::vID[] = 
{
	IDC_RMG_TGP_STATS_LABEL_LEFT,		//0
	IDC_RMG_TGP_STATS_LABEL_RIGHT,	//1
	IDC_RMG_TGP_DELIMITER_00,				//2
	IDC_RMG_TGP_PATH_LABEL_LEFT,		//3
	IDC_RMG_TGP_PATH_LABEL_RIGHT,		//4
	IDC_RMG_TGP_WEIGHT_LABEL,				//5
	IDC_RMG_TGP_WEIGHT_EDIT,				//6
	IDOK,														//7
	IDCANCEL,												//8
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CRMGTemplateGraphPropertiesDialog::CRMGTemplateGraphPropertiesDialog( CWnd* pParent )
	: CResizeDialog( CRMGTemplateGraphPropertiesDialog::IDD, pParent )
{
	//{{AFX_DATA_INIT(CRMGTemplateGraphPropertiesDialog)
	m_strWeight = _T("");
	m_strStats = _T("");
	m_strPath = _T("");
	//}}AFX_DATA_INIT

	SetControlStyle( vID[0], ANCHORE_LEFT_TOP );
	SetControlStyle( vID[1], ANCHORE_LEFT_TOP | RESIZE_HOR );
	
	SetControlStyle( vID[2], ANCHORE_LEFT_TOP | RESIZE_HOR );
	
	SetControlStyle( vID[3], ANCHORE_LEFT_TOP );
	SetControlStyle( vID[4], ANCHORE_LEFT_TOP | RESIZE_HOR );

	SetControlStyle( vID[5], ANCHORE_LEFT_TOP );
	SetControlStyle( vID[6], ANCHORE_LEFT_TOP | RESIZE_HOR );

	SetControlStyle( vID[7], ANCHORE_BOTTOM | ANCHORE_HOR_CENTER );
	SetControlStyle( vID[8], ANCHORE_BOTTOM | ANCHORE_HOR_CENTER );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CRMGTemplateGraphPropertiesDialog::DoDataExchange(CDataExchange* pDX)
{
	CResizeDialog::DoDataExchange( pDX );
	//{{AFX_DATA_MAP( CRMGTemplateGraphPropertiesDialog )
	DDX_Text(pDX, IDC_RMG_TGP_WEIGHT_EDIT, m_strWeight);
	DDX_Text(pDX, IDC_RMG_TGP_STATS_LABEL_RIGHT, m_strStats);
	DDX_Text(pDX, IDC_RMG_TGP_PATH_LABEL_RIGHT, m_strPath);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CRMGTemplateGraphPropertiesDialog, CResizeDialog)
	//{{AFX_MSG_MAP(CRMGTemplateGraphPropertiesDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// basement storage  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
