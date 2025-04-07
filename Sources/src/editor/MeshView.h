#ifndef __MESHVIEW_H__
#define __MESHVIEW_H__

// MeshView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMeshView window

class CMeshView : public CWnd
{
	// Construction
public:
	CMeshView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeshView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CMeshView();
	
private:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CMeshView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__MESHVIEW_H__
