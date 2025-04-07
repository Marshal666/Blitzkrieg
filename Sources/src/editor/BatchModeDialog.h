#if !defined(AFX_BATCHMODEDIALOG_H__8A884632_0001_4426_9D69_70A7A4E2D825__INCLUDED_)
#define AFX_BATCHMODEDIALOG_H__8A884632_0001_4426_9D69_70A7A4E2D825__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BatchModeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBatchModeDialog dialog

class CBatchModeDialog : public CDialog
{
// Construction
public:
	CBatchModeDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBatchModeDialog)
	enum { IDD = IDD_RUN_BATCH_MODE_DIALOG };
	CString	m_szDestDir;
	CString	m_szSourceDir;
	BOOL	m_forceModeFlag;
	CString	m_szSearchMask;
	BOOL	m_openAndSaveFlag;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBatchModeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetSourceDir( const char *pszDir ) { m_szSourceDir = pszDir; }
	void SetDestDir( const char *pszDir ) { m_szDestDir = pszDir; }
	void SetSearchMask( const char *pszMask ) { m_szSearchMask = pszMask; }
	void SetForceModeFlag( bool bFlag ) { m_forceModeFlag = bFlag; }
	const char *GetSourceDir() { return m_szSourceDir; }
	const char *GetDestDir() { return m_szDestDir; }
	const char *GetSearchMask() { return m_szSearchMask; }
	bool GetForceModeFlag() { return m_forceModeFlag; }
	bool GetOpenAndSaveFlag() { return m_openAndSaveFlag; }

protected:
	// Generated message map functions
	//{{AFX_MSG(CBatchModeDialog)
	afx_msg void OnBrowseDestDir();
	afx_msg void OnBrowseSourceDir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BATCHMODEDIALOG_H__8A884632_0001_4426_9D69_70A7A4E2D825__INCLUDED_)
