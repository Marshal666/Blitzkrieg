#ifndef __PARTICLE_VIEW_H__
#define __PARTICLE_VIEW_H__

/////////////////////////////////////////////////////////////////////////////
// CParticleView window

class CParticleView : public CWnd
{
	// Construction
public:
	CParticleView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParticleView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CParticleView();
	
private:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CParticleView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__PARTICLE_VIEW_H__
