#ifndef __SQUADVIEW_H__
#define __SQUADVIEW_H__

// SquadView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSquadView window

class CSquadView : public CWnd
{
	// Construction
public:
	CSquadView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSquadView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CSquadView();
	
private:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CSquadView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__SQUADVIEW_H__
