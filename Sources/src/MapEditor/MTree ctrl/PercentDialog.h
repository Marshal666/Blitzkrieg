#if !defined(AFX_PERCENTDIALOG_H__3809B33A_7D0D_4885_A6E4_D06D7CB356FC__INCLUDED_)
#define AFX_PERCENTDIALOG_H__3809B33A_7D0D_4885_A6E4_D06D7CB356FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PercentDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPercentDialog dialog

#include "..\\Resource.h"

class CPercentDialog : public CDialog
{
// Construction
public:
	CPercentDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPercentDialog)
	enum { IDD = IDD_DIALOG1 };
	CSliderCtrl	m_slider;
	int		m_value;
	int		m_variable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPercentDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPercentDialog)
	virtual void OnOK();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERCENTDIALOG_H__3809B33A_7D0D_4885_A6E4_D06D7CB356FC__INCLUDED_)
