#ifndef __MINEFRM_H__
#define __MINEFRM_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Main\rpgstats.h"
#include "ParentFrame.h"
#include "MineTreeItem.h"


class CMineFrame : public CParentFrame
{
	DECLARE_DYNCREATE(CMineFrame)
public:
	CMineFrame();
	virtual ~CMineFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMineFrame)
protected:
	//}}AFX_VIRTUAL

// Implementation
private:

protected:
	virtual void SaveRPGStats( IDataTree *pDT, CTreeItem *pRootItem, const char *pszProjectName );
	virtual void LoadRPGStats( IDataTree *pDT, CTreeItem *pRootItem );
	void FillRPGStats( SMineRPGStats &rpgStats, CTreeItem *pRootItem );
	void GetRPGStats( const SMineRPGStats &rpgStats, CTreeItem *pRootItem );

	virtual bool ExportFrameData( IDataTree *pDT, const char *pszProjectName, const char *pszResultFileName, CTreeItem *pRootItem );
	virtual FILETIME FindMinimalExportFileTime( const char *pszResultFileName, CTreeItem *pRootItem );

// Generated message map functions
protected:
	//{{AFX_MSG(CMineFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif		//__MINEFRM_H__
