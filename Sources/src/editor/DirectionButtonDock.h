#ifndef __DIRECTION_BUTTON_DOCK_H__
#define __DIRECTION_BUTTON_DOCK_H__

#include "DirectionButton.h"

class CDirectionButtonDockBar : public SECControlBar
{
	// Construction
public:
	CDirectionButtonDockBar();
	virtual ~CDirectionButtonDockBar();
	
	// Attributes
public:
private:
	CDirectionButton m_DirectionButton;
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirectionButtonDockBar)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	float GetAngle();
	void SetAngle( float fVal );
	int GetIntAngle();
	void SetIntAngle( int nVal );

	// Generated message map functions
protected:
	//{{AFX_MSG(CDirectionButtonDockBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif		// __DIRECTION_BUTTON_DOCK_H__
