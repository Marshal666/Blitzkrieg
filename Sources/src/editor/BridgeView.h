#ifndef __BRIDGEVIEW_H__
#define __BRIDGEVIEW_H__

/////////////////////////////////////////////////////////////////////////////
// CBridgeView window

class CBridgeView : public CWnd
{
	// Construction
public:
	CBridgeView();
	virtual ~CBridgeView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBridgeView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
	// Implementation
private:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CBridgeView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__BRIDGEVIEW_H__
