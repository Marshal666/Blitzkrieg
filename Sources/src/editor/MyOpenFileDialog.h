#ifndef __MY_OPEN_FILE_DIALOG_H__
#define __MY_OPEN_FILE_DIALOG_H__

class CMyOpenFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CMyOpenFileDialog)

public:
	CMyOpenFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL) : CFileDialog( bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd ) {}
	virtual ~CMyOpenFileDialog() {}

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyOpenFileDialog)
protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CMyOpenFileDialog)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

void SaveFileDialogRegisterData();
void LoadFileDialogRegisterData();
bool GetDirectoryFromExtensionTable( std::string &szRes, const std::string &szExtension );

BOOL ShowFileDialog( std::string &szResult, LPCTSTR lpszInitDir, LPCTSTR lpszTitle, BOOL bOpen, LPCTSTR lpszDefExt = NULL,
										LPCTSTR lpszFileName = NULL, LPCTSTR lpszFilter = NULL );

#endif		//__MY_OPEN_FILE_DIALOG_H__
