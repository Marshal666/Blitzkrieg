#ifndef __MISSIONVIEW_H__
#define __MISSIONVIEW_H__

/////////////////////////////////////////////////////////////////////////////
// CMissionView window

class CMissionView : public CWnd
{
	// Construction
public:
	CMissionView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMissionView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CMissionView();
	
private:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CMissionView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__MISSIONVIEW_H__
