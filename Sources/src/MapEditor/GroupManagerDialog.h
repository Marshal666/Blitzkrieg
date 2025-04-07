#if !defined(__Tabs__Groups_Dialog__)
#define __Tabs__Groups_Dialog__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ResizeDialog.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CGroupManagerDialog : public CResizeDialog
{

public:
	bool IfIDChecked( int id );
	CGroupManagerDialog( CWnd* pParent = NULL );
	//{{AFX_DATA(CGroupManagerDialog)
	enum { IDD = IDD_TAB_GROUPS };
	CListBox	m_groupInfo;
	CCheckListBox	m_groupList;
	//}}AFX_DATA

 
	//{{AFX_VIRTUAL(CGroupManagerDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	const static int vID[];

	//{{AFX_MSG(CGroupManagerDialog)
	afx_msg void OnSelchangeList1();
	afx_msg void OnNewGroup();
	afx_msg void OnDeleteGroup();
	afx_msg void OnAddIDGroupForCurrentRefGroup();
	afx_msg void OnDeleteScirptIDItem();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeGroupsPropertyList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void RedrawGroup();
	void UpdateControls();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(__Tabs__Groups_Dialog__)
