#ifndef __TRENCHVIEW_H__
#define __TRENCHVIEW_H__

/////////////////////////////////////////////////////////////////////////////
// CTrenchView window

class CTrenchView : public CWnd
{
	// Construction
public:
	CTrenchView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrenchView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CTrenchView();
	
private:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CTrenchView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__TRENCHVIEW_H__
