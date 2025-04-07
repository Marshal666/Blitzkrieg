#ifndef __WEAPONVIEW_H__
#define __WEAPONVIEW_H__

// WeaponView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWeaponView window

class CWeaponView : public CWnd
{
	// Construction
public:
	CWeaponView();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWeaponView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CWeaponView();
	
private:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CWeaponView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//__WEAPONVIEW_H__
