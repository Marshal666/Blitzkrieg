#if !defined(__Tabs__Tools_Dialog__)
#define __Tabs__Tools_Dialog__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ResizeDialog.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CTabToolsDialog : public CResizeDialog
{
public:
	CTabToolsDialog( CWnd* pParent = NULL );
	void UpdateControls();
// Dialog Data
	//{{AFX_DATA(CTabToolsDialog)
	enum { IDD = IDD_TAB_TOOLS };
	CListBox	m_areas;
	//CSpinButtonCtrl	m_spin;
	CString m_hp; 
	int		m_mode;
	int		m_drawType;
	//}}AFX_DATA

 
	//{{AFX_VIRTUAL(CTabToolsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	const static int vID[];
	virtual std::string GetXMLOptionsLabel() { return "CTabToolsDialog"; }
	bool bCreateControls;

	//{{AFX_MSG(CTabToolsDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit1();
	afx_msg void OnRadioChanged0();
	afx_msg void OnRadioChanged1();
	afx_msg void OnRadio1Changed0();
	afx_msg void OnRadio1Changed1();
	afx_msg void OnButtonDelArea();
	afx_msg void OnSelchangeToolsSaList();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(__Tabs__Tools_Dialog__)
