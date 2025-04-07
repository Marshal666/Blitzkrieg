#if !defined(AFX_MODDIALOG_H__A108E742_4E72_46D3_B97F_F6C20D43E0DA__INCLUDED_)
#define AFX_MODDIALOG_H__A108E742_4E72_46D3_B97F_F6C20D43E0DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MODDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMODDialog dialog

class CMODDialog : public CDialog
{
// Construction
public:
	CMODDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMODDialog)
	enum { IDD = IDD_MOD_SETTINGS_DIALOG };
	CString	mExportDir;
	CString	mName;
	CString	mVersion;
	CString	mDesc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMODDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMODDialog)
	afx_msg void OnModExportBtn();
	afx_msg void OnModDefaultsBtn();
	afx_msg void OnButtonNewMod();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODDIALOG_H__A108E742_4E72_46D3_B97F_F6C20D43E0DA__INCLUDED_)
