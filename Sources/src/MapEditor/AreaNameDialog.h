#if !defined(AFX_AREANAMEDIALOG_H__8AF4FFB0_25B9_4FC4_A933_8CE87B12D6B5__INCLUDED_)
#define AFX_AREANAMEDIALOG_H__8AF4FFB0_25B9_4FC4_A933_8CE87B12D6B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAreaNameDialog : public CDialog
{
public:
	CAreaNameDialog(CWnd* pParent = NULL);
	//{{AFX_DATA(CAreaNameDialog)
	enum { IDD = IDD_TAB_TOOLS_AREAD_NAME };
	CString	m_name;
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CAreaNameDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	void UpdateControls();

	//{{AFX_MSG(CAreaNameDialog)
	afx_msg void OnChangeAreaNameEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_AREANAMEDIALOG_H__8AF4FFB0_25B9_4FC4_A933_8CE87B12D6B5__INCLUDED_)
