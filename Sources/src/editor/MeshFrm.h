// MeshFrm.h : interface of the CMeshFrame class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __MESHFRM_H__
#define __MESHFRM_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Main\rpgstats.h"
#include "ParentFrame.h"

interface IObjVisObj;
struct SProp;
class CMeshLocatorPropsItem;
class CDirectionButtonDockBar;

class CMeshFrame : public CParentFrame
{
	DECLARE_DYNCREATE(CMeshFrame)
public:
	CMeshFrame();
	virtual ~CMeshFrame();

// Operations
public:
	virtual void GFXDraw();
	virtual void ShowFrameWindows( int nCommand );
	
	void LoadGunPointPropsComboBox( SProp *pPointProp );
	void LoadGunPartPropsComboBox( SProp *pPointProp );
	void LoadPlatformPropsComboBox( SProp *pPointProp );
	void LoadGunCarriagePropsComboBox( SProp *pPointProp );
	
	void SetDirectionButtonDockBar( CDirectionButtonDockBar *pDock ) { pDirectionButtonDockBar = pDock; }
	void SetCombatMesh( const char *pszMeshName, const char *pszProjectName, CTreeItem *pRootItem = 0 );
	void SetInstallMesh( const char *pszMeshName, const char *pszProjectName, CTreeItem *pRootItem = 0 );
	void SetTransportableMesh( const char *pszMeshName, const char *pszProjectName, CTreeItem *pRootItem = 0 );

	void SelectLocator( CMeshLocatorPropsItem *pLoc );
//	void UpdateItemType();
	void UpdateLocatorVisibility();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeshFrame)
	protected:
	//}}AFX_VIRTUAL

// Implementation
private:
	CPtr<IObjVisObj> pCombatObject, pInstallObject, pTransObject;
	CMeshLocatorPropsItem *pActiveLocator;
	const SHMatrix *pModelMatrix;
	CDirectionButtonDockBar *pDirectionButtonDockBar;
	bool bShowLocators;
	
	void UpdateActiveLocatorLine();

protected:
	void UpdateLocators();

	virtual void SpecificInit();
	virtual void SpecificClearBeforeBatchMode();
	virtual BOOL SpecificTranslateMessage( MSG *pMsg );
	//загружает данные перед экспортом проекта
	virtual bool LoadFramePreExportData( const char *pszProjectFile, CTreeItem *pRootItem );
	
	virtual void SaveRPGStats( IDataTree *pDT, CTreeItem *pRootItem, const char *pszProjectName );
	virtual void LoadRPGStats( IDataTree *pDT, CTreeItem *pRootItem );
	void FillRPGStats( SMechUnitRPGStats &rpgStats, CTreeItem *pRootItem, const char *pszProjectName );
	void GetRPGStats( const SMechUnitRPGStats &rpgStats, CTreeItem *pRootItem );
	
	virtual bool ExportFrameData( IDataTree *pDT, const char *pszProjectName, const char *pszResultFileName, CTreeItem *pRootItem );
	virtual FILETIME FindMaximalSourceTime( const char *pszProjectName, CTreeItem *pRootItem );
	virtual FILETIME FindMinimalExportFileTime( const char *pszResultFileName, CTreeItem *pRootItem );

// Generated message map functions
protected:
	//{{AFX_MSG(CMeshFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowLocatorsInfo();
	afx_msg void OnUpdateShowLocatorsInfo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateImportAckFile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateExportAckFile(CCmdUI* pCmdUI);
	afx_msg void OnShowDirectionButton();	
	afx_msg void OnUpdateShowDirectionButton(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif		//__MESHFRM_H__
