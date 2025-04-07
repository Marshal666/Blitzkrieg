#ifndef __CAMPAIGNVIEW_H__
#define __CAMPAIGNVIEW_H__

/////////////////////////////////////////////////////////////////////////////
// CImageView window

class CImageView : public CWnd
{
	// Construction
public:
	CImageView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CImageView();
	
private:
	void UpdateScrolls( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CImageView)
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__CAMPAIGNVIEW_H__
