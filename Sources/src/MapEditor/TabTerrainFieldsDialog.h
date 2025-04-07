#if !defined(__Tabs__Terrain_Fields_Tab_Dialog__)
#define __Tabs__Terrain_Fields_Tab_Dialog__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ResizeDialog.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CTabTerrainFieldsDialog : public CResizeDialog
{
protected:
	//{{AFX_MSG(CTabTerrainFieldsDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeFieldFieldCombo();
	afx_msg void OnEditchangeFieldFieldCombo();
	afx_msg void OnFieldBrowse();
	afx_msg void OnChangeFieldMinLengthEdit();
	afx_msg void OnChangeFieldWidthEdit();
	afx_msg void OnChangeFieldDisturbanceEdit();
	afx_msg void OnFieldRandomizePolygonCheckBox();
	afx_msg void OnFieldRemoveObjectsCheckBox();
	afx_msg void OnFieldFillHeightsCheckBox();
	afx_msg void OnFieldFillObjectsCheckBox();
	afx_msg void OnFieldFillTerrainCheckBox();
	afx_msg void OnFieldUpdateMapCheckBox();
	afx_msg void OnFieldCheckPassabilityCheckBox();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
	//{{AFX_VIRTUAL(CTabTerrainFieldsDialog)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

	bool bCreateControls;
	virtual std::string GetXMLOptionsLabel() { return "CTabTerrainFieldsDialog"; }
	void CreateControls();

public:
	CTabTerrainFieldsDialog( CWnd* pParent = NULL );
	//{{AFX_DATA(CTabTerrainFieldsDialog)
	enum { IDD = IDD_TAB_TERRAIN_FIELDS };
	CComboBox	m_Fields;
	CEdit	m_MinLength;
	CEdit	m_Width;
	CEdit	m_Disturbance;
	CButton	m_RandomizePolygonButton;
	CButton	m_RemoveObjectsButton;
	CButton	m_FillTerrainButton;
	CButton	m_FillObjectsButton;
	CButton	m_FillHeightsButton;
	CButton	m_UpdateMapButton;
	CButton	m_CheckPassabilityButton;
	//}}AFX_DATA

	void SetControlsToActualValues();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(__Tabs__Terrain_Fields_Tab_Dialog__)
