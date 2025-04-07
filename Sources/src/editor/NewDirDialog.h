#if !defined(AFX_NEWDIRDIALOG_H__D8FA628C_1C81_46CA_8150_377DFFEAC767__INCLUDED_)
#define AFX_NEWDIRDIALOG_H__D8FA628C_1C81_46CA_8150_377DFFEAC767__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewDirDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewDirDialog dialog

class CNewDirDialog : public CDialog
{
// Construction
public:
	CNewDirDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewDirDialog)
	enum { IDD = IDD_NEW_DIR_DIALOG };
	CString	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewDirDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewDirDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWDIRDIALOG_H__D8FA628C_1C81_46CA_8150_377DFFEAC767__INCLUDED_)
