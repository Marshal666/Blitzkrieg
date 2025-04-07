#if !defined(AFX_MAPOPTIONSDIALOG_H__9C3B4443_6465_427B_97E9_CDF3F6A28762__INCLUDED_)
#define AFX_MAPOPTIONSDIALOG_H__9C3B4443_6465_427B_97E9_CDF3F6A28762__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "ResizeDialog.h"
class CMapOptionsDialog : public CResizeDialog
{

public:
	CMapOptionsDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CMapOptionsDialog)
	enum { IDD = IDD_SCRIPT_NAME };
	CString	m_name;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CMapOptionsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	const static int vID[];

	virtual int GetMinimumXDimension() { return 300; }
	virtual int GetMinimumYDimension() { return 80; }
	virtual std::string GetXMLOptionsLabel() { return "CMapOptionsDialog"; }
	virtual bool GetDrawGripper() { return true; }

	//{{AFX_MSG(CMapOptionsDialog)
	afx_msg void OnGetFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MAPOPTIONSDIALOG_H__9C3B4443_6465_427B_97E9_CDF3F6A28762__INCLUDED_)
