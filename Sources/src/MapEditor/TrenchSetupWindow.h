#if !defined(__Tabs__VO_Entrenchments_Dialog__)
#define __Tabs__VO_Entrenchments_Dialog__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ResizeDialog.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CTrenchSetupWindow : public CResizeDialog
{
public:
	CTrenchSetupWindow(CWnd* pParent = NULL);

	//{{AFX_DATA(CTrenchSetupWindow)
	enum { IDD = IDD_TAB_VO_ENTRENCHMENTS };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTrenchSetupWindow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CTrenchSetupWindow)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(__Tabs__VO_Entrenchments_Dialog__)
