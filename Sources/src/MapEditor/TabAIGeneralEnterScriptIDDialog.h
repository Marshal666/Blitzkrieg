#if !defined(__Tabs__AIGeneral_EnterScriptID_Dialog__)
#define __Tabs__AIGeneral_EnterScriptID_Dialog__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CTabAIGeneralEnterScriptIDDialog : public CDialog
{
public:
	CTabAIGeneralEnterScriptIDDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CTabAIGeneralEnterScriptIDDialog)
	enum { IDD = IDD_TAB_AI_GENERAL_ENTER_SCRIPT_ID };
	int		m_ScriptID;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTabAIGeneralEnterScriptIDDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CTabAIGeneralEnterScriptIDDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(__Tabs__AIGeneral_EnterScriptID_Dialog__)
