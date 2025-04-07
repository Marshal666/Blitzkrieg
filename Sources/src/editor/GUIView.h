#ifndef __GUIVIEW_H__
#define __GUIVIEW_H__

class CGUIView : public CWnd
{
	// Construction
public:
	CGUIView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGUIView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CGUIView();
	
private:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CGUIView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__GUIVIEW_H__
