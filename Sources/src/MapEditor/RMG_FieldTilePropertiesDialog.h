#if !defined(__RMG_Field_Tile_Properties_Dialog__)
#define __RMG_Field_Tile_Properties_Dialog__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Resource.h"
#include "ResizeDialog.h"

class CRMGFieldTilePropertiesDialog : public CResizeDialog
{
public:
	CRMGFieldTilePropertiesDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CRMGFieldTilePropertiesDialog)
	enum { IDD = IDD_RMG_CF_TS_TILE_PROPERTIES };
	CStatic	m_Icon;
	CString	m_szName;
	CString	m_szStats;
	CString	m_szVariants;
	CString	m_szWeight;
	//}}AFX_DATA

	bool bDisableEditWeight;
	HICON hIcon;
	//{{AFX_VIRTUAL(CRMGFieldTilePropertiesDialog)
	protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CRMGFieldTilePropertiesDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	virtual bool GetDrawGripper() { return false; }

public:
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(__RMG_Field_Tile_Properties_Dialog__)
