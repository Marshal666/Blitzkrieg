#if !defined(__RMG_Template_Graph_Properties_Dialog__)
#define __RMG_Template_Graph_Properties_Dialog__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Resource.h"
#include "ResizeDialog.h"

class CRMGTemplateGraphPropertiesDialog : public CResizeDialog
{
public:
	CRMGTemplateGraphPropertiesDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CRMGTemplateGraphPropertiesDialog)
	enum { IDD = IDD_RMG_TEMPLATE_GRAPH_PROPERTIES };
	CString	m_strWeight;
	CString	m_strStats;
	CString	m_strPath;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CRMGTemplateGraphPropertiesDialog)
	protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CRMGTemplateGraphPropertiesDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	const static int vID[];

	virtual int GetMinimumXDimension() { return 300; }
	virtual int GetMinimumYDimension() { return 120; }
	virtual std::string GetXMLOptionsLabel() { return "CRMGTemplateGraphPropertiesDialog"; }
	virtual bool GetDrawGripper() { return true; }

public:
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(__RMG_Template_Graph_Properties_Dialog__)
