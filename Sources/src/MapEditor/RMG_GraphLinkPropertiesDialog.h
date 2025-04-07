#if !defined(__RMG_Graph_Link_Properties_Dialog__)
#define __RMG_Graph_Link_Properties_Dialog__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Resource.h"
#include "ResizeDialog.h"
#include "..\RandomMapGen\RMG_Types.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CALLBACK GraphLinksCompareFunc( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CRMGGraphLinkPropertiesDialog : public CResizeDialog
{
	friend int CALLBACK GraphLinksCompareFunc( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort );
public:
	CRMGGraphLinkPropertiesDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CRMGGraphLinkPropertiesDialog)
	enum { IDD = IDD_RMG_GRAPH_LINK_PROPERTIES };
	CEdit	m_DisturbanceEdit;
	CEdit	m_WidthEdit;
	CEdit	m_LengthEdit;
	CEdit	m_RadiusEdit;
	CEdit	m_PartsEdit;
	CEdit	m_DescEdit;
	CListCtrl	m_GraphLinksList;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CRMGGraphLinkPropertiesDialog)
	protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CRMGGraphLinkPropertiesDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnColumnclickLinksList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDeleteMenu();
	afx_msg void OnDeleteLinkButton();
	afx_msg void OnKeydownLinksList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedLinksList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeCornerPartsEdit();
	afx_msg void OnChangeCornerRadiusEdit();
	afx_msg void OnChangeDescEdit();
	afx_msg void OnChangeLineDisturbanceEdit();
	afx_msg void OnChangeLengthEdit();
	afx_msg void OnChangeWidthEdit();
	afx_msg void OnType00RadioButton();
	afx_msg void OnType01RadioButton();
	afx_msg void OnDescBrowseButton();
	afx_msg void OnRclickLinksList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	const static int vID[];
	bool bCreateControls;
	int nSortColumn;
	std::vector<bool> bGraphLinkSortParam;

	virtual int GetMinimumXDimension() { return 425; }
	virtual int GetMinimumYDimension() { return 300; }
	virtual std::string GetXMLOptionsLabel() { return "CRMGGraphLinkPropertiesDialog"; }
	virtual bool GetDrawGripper() { return true; }

	bool LoadGraphLinks();

	bool LoadGraphLinkToControls();
	bool SaveGraphLinkFromControls();
	void  SetGraphLinkItem( int nItem, int nSelectedLink );

	void CreateControls();
	void UpdateControls();
public:

	SRMGraph graph;
	std::vector<int> linkIndices;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
#endif // !defined(__RMG_Graph_Link_Properties_Dialog__)
