#ifndef __3DROAD_VIEW_H__
#define __3DROAD_VIEW_H__

/////////////////////////////////////////////////////////////////////////////
// C3DRoadView window

class C3DRoadView : public CWnd
{
	// Construction
public:
	C3DRoadView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DRoadView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~C3DRoadView();
	
private:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(C3DRoadView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__3DROAD_VIEW_H__
