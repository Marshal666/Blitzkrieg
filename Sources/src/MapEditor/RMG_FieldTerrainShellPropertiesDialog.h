#if !defined(__RMG_Field_Terrain_Shell_Properties_Dialog__)
#define __RMG_Field_Terrain_Shell_Properties_Dialog__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Resource.h"
#include "ResizeDialog.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CRMGFieldTerrainShellPropertiesDialog : public CResizeDialog
{
public:
	CRMGFieldTerrainShellPropertiesDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CRMGFieldTerrainShellPropertiesDialog)
	enum { IDD = IDD_RMG_CF_TS_PROPERTIES };
	CString	m_szWidth;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CRMGFieldTerrainShellPropertiesDialog)
	protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CRMGFieldTerrainShellPropertiesDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	virtual bool GetDrawGripper() { return false; }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(__RMG_Field_Terrain_Shell_Properties_Dialog__)
