#if !defined(__RMG_Graph_Node_Properties_Dialog__)
#define __RMG_Graph_Node_Properties_Dialog__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Resource.h"
#include "ResizeDialog.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CRMGGraphNodePropertiesDialog : public CResizeDialog
{
public:
	CRMGGraphNodePropertiesDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CRMGGraphNodePropertiesDialog)
	enum { IDD = IDD_RMG_GRAPH_NODE_PROPERTIES };
	CEdit	m_ContainerPathEdit;
	CString	m_strSize;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CRMGGraphNodePropertiesDialog)
	protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CRMGGraphNodePropertiesDialog)
	afx_msg void OnContainerBrowseButton();
	afx_msg void OnChangeContainerEdit();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	const static int vID[];

	virtual int GetMinimumXDimension() { return 300; }
	virtual int GetMinimumYDimension() { return 125; }
	virtual std::string GetXMLOptionsLabel() { return "CRMGGraphNodePropertiesDialog"; }
	virtual bool GetDrawGripper() { return true; }

public:
	std::string szContainerInitialFileName;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(__RMG_Graph_Node_Properties_Dialog__)
