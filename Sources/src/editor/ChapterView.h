#ifndef __CHAPTERVIEW_H__
#define __CHAPTERVIEW_H__

/////////////////////////////////////////////////////////////////////////////
// CChapterView window

class CChapterView : public CWnd
{
	// Construction
public:
	CChapterView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChapterView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CChapterView();
	
private:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CChapterView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__CHAPTERVIEW_H__
