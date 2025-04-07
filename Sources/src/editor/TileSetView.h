#ifndef __TILESETVIEW_H__
#define __TILESETVIEW_H__

// TileSetView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTileSetView window

class CTileSetView : public CWnd
{
	// Construction
public:
	CTileSetView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTileSetView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CTileSetView();
	
private:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CTileSetView)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__TILESETVIEW_H__
