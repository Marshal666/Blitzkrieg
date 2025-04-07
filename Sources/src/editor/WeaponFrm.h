// WeaponFrm.h : interface of the CWeaponFrame class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __WEAPONFRM_H__
#define __WEAPONFRM_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Main\rpgstats.h"
#include "ParentFrame.h"

class CWeaponFrame : public CParentFrame
{
	DECLARE_DYNCREATE(CWeaponFrame)
public:
	CWeaponFrame();
	virtual ~CWeaponFrame();

// Attributes
public:

// Operations
public:
	virtual void GFXDraw();
//	virtual void ShowFrameWindows( int nCommand );
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWeaponFrame)
protected:
	//}}AFX_VIRTUAL

// Implementation
private:

protected:
	virtual void SaveRPGStats( IDataTree *pDT, CTreeItem *pRootItem, const char *pszProjectName );
	virtual void LoadRPGStats( IDataTree *pDT, CTreeItem *pRootItem );
	void FillRPGStats( SWeaponRPGStats &rpgStats, CTreeItem *pRootItem );
	void GetRPGStats( const SWeaponRPGStats &rpgStats, CTreeItem *pRootItem );

	virtual bool ExportFrameData( IDataTree *pDT, const char *pszProjectName, const char *pszResultFileName, CTreeItem *pRootItem );
//	virtual FILETIME FindMaximalSourceTime( const char *pszProjectName, CTreeItem *pRootItem );
	virtual FILETIME FindMinimalExportFileTime( const char *pszResultFileName, CTreeItem *pRootItem );
	
// Generated message map functions
protected:
	//{{AFX_MSG(CWeaponFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif		//__WEAPONFRM_H__
