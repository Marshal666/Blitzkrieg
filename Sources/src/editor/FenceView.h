#ifndef __FENCEVIEW_H__
#define __FENCEVIEW_H__

/////////////////////////////////////////////////////////////////////////////
// CFenceView window

class CFenceView : public CWnd
{
	// Construction
public:
	CFenceView();
	virtual ~CFenceView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFenceView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	
	// Implementation
private:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CFenceView)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__FENCEVIEW_H__
