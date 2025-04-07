#if !defined(__ELK_TRANSLATE_EDIT__)
#define __ELK_TRANSLATE_EDIT__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CTranslateEdit : public CEdit
{
public:
	CTranslateEdit();

public:
	//{{AFX_VIRTUAL(CTranslateEdit)
	protected:
	//}}AFX_VIRTUAL
public:
	virtual ~CTranslateEdit();
protected:
	//{{AFX_MSG(CTranslateEdit)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	bool bIgnoreSymbol;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CTranslateButton : public CButton
{
public:
	CTranslateButton();

public:
	//{{AFX_VIRTUAL(CTranslateButton)
	protected:
	//}}AFX_VIRTUAL
public:
	virtual ~CTranslateButton();
protected:
	//{{AFX_MSG(CTranslateButton)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	bool bIgnoreSymbol;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(__ELK_TRANSLATE_EDIT__)
