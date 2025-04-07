#if !defined(AFX_GETGROUPID_H__F1E869B2_25A8_40CB_BB77_CFE65772EA33__INCLUDED_)
#define AFX_GETGROUPID_H__F1E869B2_25A8_40CB_BB77_CFE65772EA33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CGetGroupID : public CDialog
{
public:
	CGetGroupID(CWnd* pParent = NULL);

	//{{AFX_DATA(CGetGroupID)
	enum { IDD = IDD_TAB_GROUPS_GET_GROUP_ID };
	UINT	m_id;
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CGetGroupID)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	void UpdateControls();

	//{{AFX_MSG(CGetGroupID)
	afx_msg void OnChangeGroupIdEdit();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GETGROUPID_H__F1E869B2_25A8_40CB_BB77_CFE65772EA33__INCLUDED_)
