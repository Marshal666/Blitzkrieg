#if !defined(AFX_MULTYSELDIALOG_H__72F92FDC_23D0_4F60_804D_5E21317C1884__INCLUDED_)
#define AFX_MULTYSELDIALOG_H__72F92FDC_23D0_4F60_804D_5E21317C1884__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MultySelDialog.h : header file
//

#include "RefDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CMultySelDialog dialog

class CMultySelDialog : public CDialog
{
// Construction
public:
	CMultySelDialog(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(CMultySelDialog)
	enum { IDD = IDD_MULTY_SEL_DIALOG };
	CCheckListBox	m_multyList;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultySelDialog)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	EReferenceType nReferenceType;
	std::string szResult;
	int64 nValue;
	
	void LoadActions();
	
public:
	void Init( int nRefId, int64 nVal );
	std::string GetValue();

	// Generated message map functions
	//{{AFX_MSG(CMultySelDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTYSELDIALOG_H__72F92FDC_23D0_4F60_804D_5E21317C1884__INCLUDED_)
