#ifndef __MEDALVIEW_H__
#define __MEDALVIEW_H__

/////////////////////////////////////////////////////////////////////////////
// CMedalView window

class CMedalView : public CWnd
{
	// Construction
public:
	CMedalView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMedalView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CMedalView();
	
private:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CMedalView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__MEDALVIEW_H__
