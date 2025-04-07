#ifndef __OBJECTVIEW_H__
#define __OBJECTVIEW_H__

// ObjectView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CObjectView window

class CObjectView : public CWnd
{
	// Construction
public:
	CObjectView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CObjectView();
	
private:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CObjectView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__OBJECTVIEW_H__
