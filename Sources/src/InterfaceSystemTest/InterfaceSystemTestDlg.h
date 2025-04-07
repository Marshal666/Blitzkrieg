// InterfaceSystemTestDlg.h : header file
//

#if !defined(AFX_INTERFACESYSTEMTESTDLG_H__927E1D5C_FCEB_442F_840D_5AB43D69CBE5__INCLUDED_)
#define AFX_INTERFACESYSTEMTESTDLG_H__927E1D5C_FCEB_442F_840D_5AB43D69CBE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CInterfaceSystemTestDlg dialog
#include "SceneVisitor.h"
#include "UIScreen.h"

class CInterfaceSystemTestDlg : public CDialog, public ISceneVisitor
{
	struct SColorLine
	{
		std::pair<CVec3,CVec3> v;
		DWORD color;
		int width;
		
		SColorLine( const CVec3 *_coord, const DWORD _color, const int _width )
			: v( _coord[0], _coord[1] ), color( _color ), width( _width )
		{
		}
	};
	std::list<SColorLine> lines;
	
	CPtr<CScreen> pScreen;

// Construction
public:
	CInterfaceSystemTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CInterfaceSystemTestDlg)
	enum { IDD = IDD_INTERFACESYSTEMTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterfaceSystemTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

	virtual void STDCALL VisitBoldLine( CVec3 *corners, float fWidth, DWORD color );

protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CInterfaceSystemTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERFACESYSTEMTESTDLG_H__927E1D5C_FCEB_442F_840D_5AB43D69CBE5__INCLUDED_)

