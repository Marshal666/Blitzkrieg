#if !defined(__RMG_Template_Field_Properties_Dialog__)
#define __RMG_Template_Field_Properties_Dialog__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Resource.h"
#include "ResizeDialog.h"

class CRMGTemplateFieldPropertiesDialog : public CResizeDialog
{
public:
	CRMGTemplateFieldPropertiesDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CRMGTemplateFieldPropertiesDialog)
	enum { IDD = IDD_RMG_TEMPLATE_FIELD_PROPERTIES };
	BOOL	m_bDefault;
	CString	m_strWeight;
	CString	m_strStats;
	CString	m_strPath;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CRMGTemplateFieldPropertiesDialog)
	protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CRMGTemplateFieldPropertiesDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	const static int vID[];

	virtual int GetMinimumXDimension() { return 300; }
	virtual int GetMinimumYDimension() { return 150; }
	virtual std::string GetXMLOptionsLabel() { return "CRMGTemplateFieldPropertiesDialog"; }
	virtual bool GetDrawGripper() { return false; }

public:
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(__RMG_Template_Field_Properties_Dialog__)
