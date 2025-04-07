#include "stdafx.h"
#include "editor.h"
#include "TabAIGeneralEnterScriptIDDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CTabAIGeneralEnterScriptIDDialog::CTabAIGeneralEnterScriptIDDialog( CWnd* pParent )
	: CDialog( CTabAIGeneralEnterScriptIDDialog::IDD, pParent )
{
	//{{AFX_DATA_INIT(CTabAIGeneralEnterScriptIDDialog)
	m_ScriptID = 0;
	//}}AFX_DATA_INIT
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTabAIGeneralEnterScriptIDDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabAIGeneralEnterScriptIDDialog)
	DDX_Text(pDX, IDC_TAB_AI_GENERAL_ENTER_SCRIPT_ID_EDIT, m_ScriptID);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CTabAIGeneralEnterScriptIDDialog, CDialog)
	//{{AFX_MSG_MAP(CTabAIGeneralEnterScriptIDDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
