#ifndef __CAMPAIGNFRM_H__
#define __CAMPAIGNFRM_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Main\gamestats.h"
#include "ImageFrm.h"
class CCampaignChapterPropsItem;

class CCampaignFrame : public CImageFrame
{
	DECLARE_DYNCREATE(CCampaignFrame)
public:
	CCampaignFrame();
	virtual ~CCampaignFrame();

	void SetActiveChapter( CCampaignChapterPropsItem *pChapter );

	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCampaignFrame)
protected:
	//}}AFX_VIRTUAL
	
	// Implementation
private:
	std::string szPrefix;		//эта переменная используется для передачи параметра в функцию FillRpgStats, чтобы не было необходимости изменять интерфейс
	CCampaignChapterPropsItem *pActiveChapter;

protected:
	virtual void SaveRPGStats( IDataTree *pDT, CTreeItem *pRootItem, const char *pszProjectName );
	virtual void LoadRPGStats( IDataTree *pDT, CTreeItem *pRootItem );
	void FillRPGStats( SCampaignStats &rpgStats, CTreeItem *pRootItem, const char *pszProjectName );
	void GetRPGStats( const SCampaignStats &rpgStats, CTreeItem *pRootItem );
	
	virtual bool ExportFrameData( IDataTree *pDT, const char *pszProjectName, const char *pszResultFileName, CTreeItem *pRootItem );
	virtual FILETIME FindMinimalExportFileTime( const char *pszResultFileName, CTreeItem *pRootItem );
	virtual void SpecificInit();
	virtual void SpecificClearBeforeBatchMode();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CCampaignFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif		//__CAMPAIGNFRM_H__
