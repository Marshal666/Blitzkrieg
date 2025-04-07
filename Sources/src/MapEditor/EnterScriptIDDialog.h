#if !defined(AFX_ENTERSCRIPTIDDIALOG_H__A20FCCF4_2814_43E9_9491_FBB61E8F622E__INCLUDED_)
#define AFX_ENTERSCRIPTIDDIALOG_H__A20FCCF4_2814_43E9_9491_FBB61E8F622E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CEnterScriptIDDialog : public CDialog
{
public:
	CEnterScriptIDDialog(CWnd* pParent = NULL);

	//{{AFX_DATA(CEnterScriptIDDialog)
	enum { IDD = IDD_TAB_GROUPS_GET_SCRIPT_ID };
	int		m_id;
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CEnterScriptIDDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
protected:
	void UpdateControls();

	//{{AFX_MSG(CEnterScriptIDDialog)
	afx_msg void OnChangeScriptIdEdit();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_ENTERSCRIPTIDDIALOG_H__A20FCCF4_2814_43E9_9491_FBB61E8F622E__INCLUDED_)
