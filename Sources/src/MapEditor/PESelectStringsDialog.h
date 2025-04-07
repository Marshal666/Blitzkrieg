#if !defined(__Property_Editor_SelectStringsDialog__)
#define __Property_Editor_SelectStringsDialog__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ResizeDialog.h"
#include "UnitCreation.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CPESelectStringsDialog : public CResizeDialog
{
public:
	std::list<std::string> *pAvailiableStrings;
	std::vector<std::string> *pSelectedStrings;
	std::string szDialogName;

	CPESelectStringsDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CPESelectStringsDialog)
	enum { IDD = IDD_PE_SELECT_STRINGS };
	CCheckListBox	stringList;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPESelectStringsDialog)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL
protected:
	const static int vID[];

	//минимальные размеры клиентской части диалога
	virtual int GetMinimumXDimension() { return 200; }
	virtual int GetMinimumYDimension() { return 200; }
	virtual std::string GetXMLOptionsLabel() { return "CPESelectStringsDialog"; }
	virtual bool GetDrawGripper() { return true; }

  //static inline bool GetCheckState(UINT state) {int v = ( ( state & LVIS_STATEIMAGEMASK ) >> 12 ) - 1; return v <= 0 ? false : true; }
  //static inline UINT SetCheckState( UINT state, bool isChecked ) { return ( state & LVIS_STATEIMAGEMASK ) + ( ( isChecked ? 1 : 0 ) << 12 ); }

	void CreateList();
	//{{AFX_MSG(CPESelectStringsDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(#define __Property_Editor_SelectStringsDialog__)
