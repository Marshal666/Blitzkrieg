#ifndef __3DRIVER_VIEW_H__
#define __3DRIVER_VIEW_H__

/////////////////////////////////////////////////////////////////////////////
// C3DRiverView window

class C3DRiverView : public CWnd
{
	// Construction
public:
	C3DRiverView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DRiverView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~C3DRiverView();
	
private:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(C3DRiverView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__3DRIVER_VIEW_H__
