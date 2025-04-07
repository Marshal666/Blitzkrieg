#if !defined(__ELK_INPUT_VIEW_DIALOG__)
#define __ELK_INPUT_VIEW_DIALOG__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ResizeDialog.h"
#include "TranslateEdit.h"
//#include "ot_sectga.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CInputViewDialog : public CResizeDialog
{
public:
	friend class CInputViewWindow;
	
	CInputViewDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CInputViewDialog)
	enum { IDD = IDD_INPUT_VIEW };
	CTranslateEdit	m_TranslateEdit;
	CTranslateEdit	m_OriginalEdit;
	CTranslateEdit	m_DescriptionEdit;
	CTranslateButton	m_NotTranslatedButton;
	CTranslateButton	m_OutdatedButton;
	CTranslateButton	m_TranslatedButton;
	CTranslateButton	m_ApprovedButton;
	CTranslateButton	m_NextButton;
	CTranslateButton	m_BackButton;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CInputViewDialog)
	protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CInputViewDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnNotTranslatedRadioButton();
	afx_msg void OnTranslatedRadioButton();
	afx_msg void OnApprovedRadioButton();
	afx_msg void OnChangeTranslateEdit();
	afx_msg void OnBackButton();
	afx_msg void OnNextButton();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	const static int vID[];

	CBitmap gameImageBitmap;
	CTPoint<int> gameImageSize;
	std::string szGameImagePath;

	HICON hNextIcon;
	HICON hBackIcon;
	CWnd *pwndMainFrame;
	bool bTranslatedTextChanged;
	bool bManualState;
	CString strInitialTranslatedText;
	int nInitialState;

	void LoadGameImage( const std::string &rszGameImagePath );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(__ELK_INPUT_VIEW_DIALOG__)
