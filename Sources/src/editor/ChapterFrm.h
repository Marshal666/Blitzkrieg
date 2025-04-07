#ifndef __CHAPTERFRM_H__
#define __CHAPTERFRM_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Main\gamestats.h"
#include "ImageFrm.h"
class CChapterMissionPropsItem;
class CChapterPlacePropsItem;

class CChapterFrame : public CImageFrame
{
	DECLARE_DYNCREATE(CChapterFrame)
public:
	CChapterFrame();
	virtual ~CChapterFrame();

	void SetActiveMission( CChapterMissionPropsItem *pMission );
	void SetActivePlaceHolder( CChapterPlacePropsItem *pPlace );
	
	virtual void GFXDraw();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChapterFrame)
protected:
	//}}AFX_VIRTUAL
	
	// Implementation
private:
	std::string szPrefix;		//эта переменная используется для передачи параметра в функцию FillRpgStats, чтобы не было необходимости изменять интерфейс
	CChapterMissionPropsItem *pActiveMission;
	CChapterPlacePropsItem *pActivePlaceHolder;
	bool bEditCrosses;
	CVec2 vCrossShift;
	
protected:
	virtual void SaveRPGStats( IDataTree *pDT, CTreeItem *pRootItem, const char *pszProjectName );
	virtual void LoadRPGStats( IDataTree *pDT, CTreeItem *pRootItem );
	void FillRPGStats( SChapterStats &rpgStats, CTreeItem *pRootItem, const char *pszProjectName );
	void GetRPGStats( const SChapterStats &rpgStats, CTreeItem *pRootItem );
	
	virtual bool ExportFrameData( IDataTree *pDT, const char *pszProjectName, const char *pszResultFileName, CTreeItem *pRootItem );
	virtual FILETIME FindMaximalSourceTime( const char *pszProjectName, CTreeItem *pRootItem );
	virtual FILETIME FindMinimalExportFileTime( const char *pszResultFileName, CTreeItem *pRootItem );
	virtual void SpecificInit();
	virtual void SpecificClearBeforeBatchMode();

	void FindActiveCross( const CPoint &point );
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CChapterFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnShowCrosses();
	afx_msg void OnUpdateShowCrosses(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif		//__CHAPTERFRM_H__
