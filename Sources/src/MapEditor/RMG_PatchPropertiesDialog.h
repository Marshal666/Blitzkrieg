#if !defined(__RMG_Patch_Properties_Dialog__)
#define __RMG_Patch_Properties_Dialog__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Resource.h"
#include "ResizeDialog.h"

class CRMGPatchPropertiesDialog : public CResizeDialog
{
public:
	CRMGPatchPropertiesDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CRMGPatchPropertiesDialog)
	enum { IDD = IDD_RMG_PATCH_PROPERTIES };
	CComboBox	m_Places;
	CString	m_strPath;
	CString	m_strSize;
	int		m_n0;
	int		m_n180;
	int		m_n270;
	int		m_n90;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CRMGPatchPropertiesDialog)
	protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CRMGPatchPropertiesDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeRmgPpPlaceComboBox();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	const static int vID[];

	virtual int GetMinimumXDimension() { return 300; }
	virtual int GetMinimumYDimension() { return 180; }
	virtual std::string GetXMLOptionsLabel() { return "CRMGPatchPropertiesDialog"; }
	virtual bool GetDrawGripper() { return true; }

public:
	std::vector<std::string> szPlaces;
	std::string szPlace;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(__RMG_Patch_Properties_Dialog__)
