#if !defined(__CHOOSE_FONTS_DIALOG__)
#define __CHOOSE_FONTS_DIALOG__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ELK_Types.h"
#include "ResizeDialog.h"
#include "..\RandomMapGen\Resource_Types.h"
#include "ELK_Types.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CChooseFontsDialog : public CResizeDialog
{
public:
	CChooseFontsDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CChooseFontsDialog)
	enum { IDD = IDD_CHOOSE_FONTS };
	CComboBox	wndNormalFontSizeComboBox;
	CComboBox	wndLargeFontSizeComboBox;
	CStatic	wndSample;
	CComboBox	wndFontComboBox;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CChooseFontsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CChooseFontsDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeFontComboBox();
	afx_msg void OnSelchangeSizeLargeComboBox();
	afx_msg void OnSelchangeSizeNormalComboBox();
	afx_msg void OnDefaultButton();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	virtual int GetMinimumXDimension() { return 320; }
	virtual int GetMinimumYDimension() { return 200; }
	virtual bool SerializeToRegistry() { return true; }
	virtual std::string GetRegistryKey();
	virtual bool GetDrawGripper() { return true; }

	bool bCreateControls;

	void CreateControls();
	void UpdateControls();
	
	CFont sampleFont;
public:
	CString strFontName;
	DWORD dwNormalFontSize;
	DWORD dwLargeFontSize;
	DWORD nCodePage;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(__CHOOSE_FONTS_DIALOG__)
