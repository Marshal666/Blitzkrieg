#ifndef __SPRITEVIEW_H__
#define __SPRITEVIEW_H__

// SpriteView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpriteView window

class CSpriteView : public CWnd
{
	// Construction
public:
	CSpriteView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpriteView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CSpriteView();
	
private:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CSpriteView)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__SPRITEVIEW_H__
