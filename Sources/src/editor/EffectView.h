#ifndef __EFFECTVIEW_H__
#define __EFFECTVIEW_H__

// EffectView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEffectView window

class CEffectView : public CWnd
{
	// Construction
public:
	CEffectView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEffectView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CEffectView();
	
private:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CEffectView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__EFFECTVIEW_H__
