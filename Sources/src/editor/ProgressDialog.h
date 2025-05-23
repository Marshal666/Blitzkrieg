#if !defined(AFX_PROGRESSDIALOG_H__F242B4EF_D0CD_4F69_8A36_27AADC3C6372__INCLUDED_)
#define AFX_PROGRESSDIALOG_H__F242B4EF_D0CD_4F69_8A36_27AADC3C6372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgressDialog dialog

class CProgressDialog : public CDialog
{
// Construction
public:
	CProgressDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProgressDialog)
	enum { IDD = IDD_PROGRESS_DIALOG };
	CProgressCtrl	m_batchProgress;
	CString	m_projectName;
	//}}AFX_DATA

	int m_nSize;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void Init( int nSize ) { m_nSize = nSize; }
	void SetPosition( int nPos ) { m_batchProgress.SetPos( nPos ); }
	void SetProjectName( const char *pszProjectName ) { m_projectName = pszProjectName; UpdateData( FALSE ); }

protected:

	// Generated message map functions
	//{{AFX_MSG(CProgressDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDIALOG_H__F242B4EF_D0CD_4F69_8A36_27AADC3C6372__INCLUDED_)
