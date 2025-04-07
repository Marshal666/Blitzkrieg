#if !defined(AFX_MULTITREESLIDER_H__005E6039_7E8F_4DDC_A728_67E22F4F2608__INCLUDED_)
#define AFX_MULTITREESLIDER_H__005E6039_7E8F_4DDC_A728_67E22F4F2608__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MultiTreeSlider.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMultiTreeSlider window

class CMultiTreeSlider : public CSliderCtrl
{
// Construction
public:
	CMultiTreeSlider();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiTreeSlider)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMultiTreeSlider();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMultiTreeSlider)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTITREESLIDER_H__005E6039_7E8F_4DDC_A728_67E22F4F2608__INCLUDED_)
