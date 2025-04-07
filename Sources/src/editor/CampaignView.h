#ifndef __CAMPAIGNVIEW_H__
#define __CAMPAIGNVIEW_H__

/////////////////////////////////////////////////////////////////////////////
// CCampaignView window

class CCampaignView : public CWnd
{
	// Construction
public:
	CCampaignView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCampaignView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CCampaignView();
	
private:
	void UpdateScrolls( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CCampaignView)
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__CAMPAIGNVIEW_H__
