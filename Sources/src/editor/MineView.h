#ifndef __MINEVIEW_H__
#define __MINEVIEW_H__

/////////////////////////////////////////////////////////////////////////////
// CMineView window

class CMineView : public CWnd
{
	// Construction
public:
	CMineView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMineView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CMineView();
	
private:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CMineView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__MINEVIEW_H__
