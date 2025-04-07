#if !defined(__RMG_Field_Heights_Dialog__)
#define __RMG_Field_Heights_Dialog__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Resource.h"
#include "ResizeDialog.h"

class CRMGCreateFieldDialog;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CRMGFieldHeightsDialog : public CResizeDialog
{
	friend class CRMGCreateFieldDialog;

public:
	CRMGFieldHeightsDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CRMGFieldHeightsDialog)
	enum { IDD = IDD_RMG_CF_HEIGHTS };
	CEdit	m_SizeMinEdit;
	CEdit	m_SizeMaxEdit;
	CEdit	m_ProfileEdit;
	CEdit	m_PositiveRatioEdit;
	CEdit	m_HeightEdit;
	CSliderCtrl	m_PositiveRatioSlider;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CRMGFieldHeightsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CRMGFieldHeightsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnChangeHeightEdit();
	afx_msg void OnChangePositiveRatioEdit();
	afx_msg void OnChangeProfileEdit();
	afx_msg void OnChangeSizeMaxEdit();
	afx_msg void OnChangeSizeMinEdit();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnProfileBrowseButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	bool bCreateControls;
	class CRMGCreateFieldDialog *pRMGCreateFieldDialog;
	struct SRMFieldSet *pRMFieldSet;						//�������
	std::vector<struct SRMFieldSet*> fieldSets;	//���������� ( ��� ��������� ������ � ������ ����� ( ����� ������� ) )

	virtual std::string GetXMLOptionsLabel() { return "CRMGFieldHeightsDialog"; }

	void CreateControls();
	void UpdateControls();
	void LoadFieldToControls();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(__RMG_Field_Heights_Dialog__)
