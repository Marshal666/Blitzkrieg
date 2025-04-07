#if !defined(__CREATE_FILTER_NAME_DIALOG__)
#define __CREATE_FILTER_NAME_DIALOG__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Resource.h"
#include "ResizeDialog.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCreateFilterNameDialog : public CResizeDialog
{
public:
	CCreateFilterNameDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CCreateFilterNameDialog)
	enum { IDD = IDD_CREATE_FILTER_NAME };
	CString	m_Name;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CCreateFilterNameDialog)
	protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CCreateFilterNameDialog)
	afx_msg void OnChangeFilterNameEdit();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	const static int vID[];

	virtual int GetMinimumXDimension() { return 200; }
	virtual int GetMinimumYDimension() { return 60; }
	virtual std::string GetXMLOptionsLabel() { return "CCreateFilterNameDialog"; }
	virtual bool GetDrawGripper() { return true; }
	
	void UpdateControls();
public:
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
#endif // !defined(__CREATE_FILTER_NAME_DIALOG__)
