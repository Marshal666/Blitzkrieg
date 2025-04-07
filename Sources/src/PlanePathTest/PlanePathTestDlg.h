// PlanePathTestDlg.h : header file
//

#if !defined(AFX_PLANEPATHTESTDLG_H__5543AEAD_6CEF_4FEE_BFAE_FF0E28DAC14C__INCLUDED_)
#define AFX_PLANEPATHTESTDLG_H__5543AEAD_6CEF_4FEE_BFAE_FF0E28DAC14C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "src\ComplexPathFraction.h"
#include "..\Misc\Spline.h"

/////////////////////////////////////////////////////////////////////////////
// CPlanePathTestDlg dialog

class CPlanePathTestDlg : public CDialog
{
// Construction

	CVec3 x0;														// initial placement & direection
	CVec3 v0;

	CVec3 x1;														// final placement & direction
	CVec3 v1;

	
	CVec3 x2;														// final placement & direction
	CVec3 v2;

	CPtr<CPathFractionArcLine3D> pBest;

	CPtr<CPathFractionArcLine3D> pBest1;

	void Recalc();

	void Draw();
	void DrawPointValue( CPaintDC &dc, const CVec3 &point ) const; 
	void DrawCircle( const CDirectedCircle &pC, CPaintDC &dc ) const;

public:
	CPlanePathTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPlanePathTestDlg)
	enum { IDD = IDD_PLANEPATHTEST_DIALOG };
	int		m_StartSpeed;
	int		m_FinalSpeed;
	int		m_PathProgress;
	int		m_XAngle;
	int		m_YAngle;
	int		m_ZAngle;
	int		m_Zoom;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlanePathTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPlanePathTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRecalc();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLANEPATHTESTDLG_H__5543AEAD_6CEF_4FEE_BFAE_FF0E28DAC14C__INCLUDED_)
