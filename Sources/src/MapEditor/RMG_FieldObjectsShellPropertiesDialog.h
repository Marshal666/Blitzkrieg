#if !defined(__RMG_Field_Objects_Shell_Properties_Dialog__)
#define __RMG_Field_Objects_Shell_Properties_Dialog__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Resource.h"
#include "ResizeDialog.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CRMGFieldObjectsShellPropertiesDialog : public CResizeDialog
{
public:
	CRMGFieldObjectsShellPropertiesDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CRMGFieldObjectsShellPropertiesDialog)
	enum { IDD = IDD_RMG_CF_OS_PROPERTIES };
	CString	m_szWidth;
	CString	m_szStep;
	CString	m_szRatio;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CRMGFieldObjectsShellPropertiesDialog)
	protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CRMGFieldObjectsShellPropertiesDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	virtual bool GetDrawGripper() { return false; }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
#endif // !defined(__RMG_Field_Objects_Shell_Properties_Dialog__)
