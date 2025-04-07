#if !defined(AFX_BROWSEDIALOG_H__840A0428_5CE0_474A_A7D0_E4D42738147D__INCLUDED_)
#define AFX_BROWSEDIALOG_H__840A0428_5CE0_474A_A7D0_E4D42738147D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BrowseDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBrowseDialog dialog

class CBrowseDialog : public CDialog
{
// Construction
public:
	CBrowseDialog(CWnd* pParent = NULL);   // standard constructor

	void SetFileName( const char *pszName ) { m_szFileName = pszName; }
	const char *GetFileName() { return (const char *) m_szFileName; }
	void SetExtension( const char *pszExt ) { m_szExtension = pszExt; }
	void SetFilter( const char *pszFilter ) { m_szFilter = pszFilter; }
	void SetTitle( const char *pszTitle ) { m_szTitle = pszTitle; }
	
// Dialog Data
	//{{AFX_DATA(CBrowseDialog)
	enum { IDD = IDD_BROWSE_DIALOG };
	CString	m_szFileName;
	//}}AFX_DATA

	CString	m_szExtension;
	CString	m_szFilter;
	CString	m_szTitle;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrowseDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBrowseDialog)
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BROWSEDIALOG_H__840A0428_5CE0_474A_A7D0_E4D42738147D__INCLUDED_)
