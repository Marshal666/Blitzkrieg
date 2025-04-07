#ifndef __OI_REFERENCE_EDIT_H__
#define __OI_REFERENCE_EDIT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OIEdit.h"

class COIReferenceEdit;

/////////////////////////////////////////////////////////////////////////////

class COIReferenceButton : public CButton
{
public:
  COIReferenceButton( COIReferenceEdit *pPrnt, CEdit* pEdtBrowse );
  
  ~COIReferenceButton();
  
  BOOL Create();
  
protected:
  //{{AFX_MSG(COIReferenceButton)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
    
protected:
  virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
  
  // Button width enumeration.
  enum { 
    BTN_WIDTH = 20		// emem Button width.
  } ;
  
  // Pointer to parent control.
  CEdit* m_pEdtBrowse;
  COIReferenceEdit *m_pParentWnd;
  
  // control ID for this button.
  UINT m_uiID;  
};

/////////////////////////////////////////////////////////////////////////////

class COIReferenceEdit : public CWnd
{
public:
  
  COIReferenceEdit();  
  virtual ~COIReferenceEdit();
  
protected:
	enum { 
		BTN_WIDTH = 17
	};
	CFont	m_fntDef;
	COIEdit m_Edit;
	COIReferenceButton m_BrowseBtn;
	int nRefType;
	int64 nValue;

public:
	COIReferenceButton* GetBrowseButton()
		{ return &m_BrowseBtn; }
	void SetWindowText( LPCTSTR lpszString );
	void GetWindowText( CString &rString ) const;
	void SetReferenceType( int nType ) { nRefType = nType; }
	void SetReferenceValue( int64 nVal ) { nValue = nVal; }
	
public:
	virtual void OnBrowse();
  
protected:

	virtual BOOL PreTranslateMessage( MSG* pMsg );

	//{{AFX_MSG(COIReferenceEdit)  
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __OI_REFERENCE_EDIT_H__
