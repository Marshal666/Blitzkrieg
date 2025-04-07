#if !defined(__ELK_IMPORT_FROM_PAK_DIALOG__)
#define __ELK_IMPORT_FROM_PAK_DIALOG__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ResizeDialog.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CImportFromPAKDialog : public CResizeDialog
{
public:
	CImportFromPAKDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CImportFromPAKDialog)
	enum { IDD = IDD_IMPORT_FROM_PAK };
	CEdit	m_PAKEdit;
	CEdit	m_FileEdit;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CImportFromPAKDialog)
	protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CImportFromPAKDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFileBrowseButton();
	afx_msg void OnPAKBrowseButton();
	afx_msg void OnChangeFileBrowseEdit();
	afx_msg void OnChangePAKBrowseEdit();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	const static int vID[];

	virtual int GetMinimumXDimension() { return 350; }
	virtual int GetMinimumYDimension() { return 125; }
	virtual bool SerializeToRegistry() { return true; }
	virtual std::string GetRegistryKey();
	virtual bool GetDrawGripper() { return true; }

	void UpdateControls();

public:
	void GetPAKPath( std::string *pszPAKPath );
	void GetFilePath( std::string *pszFilePath );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(__ELK_IMPORT_FROM_PAK_DIALOG__)
