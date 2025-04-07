#if !defined(__ELK_ABOUT_DIALOG__)
#define __ELK_ABOUT_DIALOG__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAboutDialog : public CDialog
{
public:
	CAboutDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CAboutDialog)
	enum { IDD = IDD_ABOUT };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CAboutDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAboutDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(__ELK_ABOUT_DIALOG__)

