#if !defined(__Tabs__AIGeneral_SetPositionType_Dialog__)
#define __Tabs__AIGeneral_SetPositionType_Dialog__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ResizeDialog.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CTabAIGeneralSetPositionTypeDialog : public CDialog
{
public:
	CTabAIGeneralSetPositionTypeDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CTabAIGeneralSetPositionTypeDialog)
	enum { IDD = IDD_TAB_AI_GENERAL_SET_POSITION_TYPE };
	int		m_Type;
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CTabAIGeneralSetPositionTypeDialog)
	protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CTabAIGeneralSetPositionTypeDialog)
	afx_msg void OnTabAiGeneralSptType0();
	afx_msg void OnTabAiGeneralSptType1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // !defined(__Tabs__AIGeneral_SetPositionType_Dialog__)
