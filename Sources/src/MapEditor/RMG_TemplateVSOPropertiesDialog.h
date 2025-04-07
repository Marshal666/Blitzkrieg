#if !defined(__RMG_Template_VSO_Properties_Dialog__)
#define __RMG_Template_VSO_Properties_Dialog__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Resource.h"
#include "ResizeDialog.h"

class CRMGTemplateVSOPropertiesDialog : public CResizeDialog
{
public:
	CRMGTemplateVSOPropertiesDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CRMGTemplateVSOPropertiesDialog)
	enum { IDD = IDD_RMG_TEMPLATE_VSO_PROPERTIES };
	CString	m_strWidth;
	CString	m_strWeight;
	CString	m_strStats;
	CString	m_strPath;
	CString	m_strOpacity;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CRMGTemplateVSOPropertiesDialog)
	protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CRMGTemplateVSOPropertiesDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	const static int vID[];

	virtual int GetMinimumXDimension() { return 300; }
	virtual int GetMinimumYDimension() { return 200; }
	virtual std::string GetXMLOptionsLabel() { return "CRMGTemplateVSOPropertiesDialog"; }
	virtual bool GetDrawGripper() { return true; }

public:
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(__RMG_Template_VSO_Properties_Dialog__)
