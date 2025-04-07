#include "stdafx.h"
#include "editor.h"
#include "TabAIGeneralSetPositionTypeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CTabAIGeneralSetPositionTypeDialog::CTabAIGeneralSetPositionTypeDialog( CWnd* pParent )
	: CDialog( CTabAIGeneralSetPositionTypeDialog::IDD, pParent )
{
	//{{AFX_DATA_INIT(CTabAIGeneralSetPositionTypeDialog)
	m_Type = 0;
	//}}AFX_DATA_INIT
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTabAIGeneralSetPositionTypeDialog::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabAIGeneralSetPositionTypeDialog)
	DDX_Radio(pDX, IDC_TAB_AI_GENERAL_SPT_TYPE0, m_Type);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CTabAIGeneralSetPositionTypeDialog, CDialog)
	//{{AFX_MSG_MAP(CTabAIGeneralSetPositionTypeDialog)
	ON_BN_CLICKED(IDC_TAB_AI_GENERAL_SPT_TYPE0, OnTabAiGeneralSptType0)
	ON_BN_CLICKED(IDC_TAB_AI_GENERAL_SPT_TYPE1, OnTabAiGeneralSptType1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTabAIGeneralSetPositionTypeDialog::OnTabAiGeneralSptType0() 
{
	m_Type = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTabAIGeneralSetPositionTypeDialog::OnTabAiGeneralSptType1() 
{
	m_Type = 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
