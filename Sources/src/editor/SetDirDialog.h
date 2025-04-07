#if !defined(AFX_SETDIRDIALOG_H__7B2C3F7C_861D_46D7_B240_BAE5ABD38E92__INCLUDED_)
#define AFX_SETDIRDIALOG_H__7B2C3F7C_861D_46D7_B240_BAE5ABD38E92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetDirDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetDirDialog dialog

class CSetDirDialog : public CDialog
{
// Construction
public:
	CSetDirDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetDirDialog)
	enum { IDD = IDD_SET_DIRECTORIES_DIALOG };
	CString	m_szSourceDir;
	CString	m_szExecDir;
	CString	m_szExecArgs;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetDirDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetSourceDir( const char *pszDir ) { m_szSourceDir = pszDir; }
	void SetExecDir( const char *pszDir ) { m_szExecDir = pszDir; }
	void SetExecArgs( const char *pszArgs ) { m_szExecArgs = pszArgs; }
	const char *GetSourceDir() { return m_szSourceDir; }
	const char *GetExecDir() { return m_szExecDir; }
	const char *GetExecArgs() { return m_szExecArgs; }
	
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetDirDialog)
	afx_msg void OnBrowseSourceDir();
	afx_msg void OnBrowseExecDir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETDIRDIALOG_H__7B2C3F7C_861D_46D7_B240_BAE5ABD38E92__INCLUDED_)
