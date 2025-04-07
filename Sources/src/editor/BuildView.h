#ifndef __BUILDVIEW_H__
#define __BUILDVIEW_H__

// BuildView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBuildingView window

class CBuildingView : public CWnd
{
	// Construction
public:
	CBuildingView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuildingView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CBuildingView();
	
private:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CBuildingView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__BUILDVIEW_H__
