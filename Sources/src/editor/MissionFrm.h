#ifndef __MISSIONFRM_H__
#define __MISSIONFRM_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Main\gamestats.h"
#include "ImageFrm.h"
class CMissionObjectivePropsItem;

class CMissionFrame : public CImageFrame
{
	DECLARE_DYNCREATE(CMissionFrame)
public:
	CMissionFrame();
	virtual ~CMissionFrame();
	
	void SetActiveObjective( CMissionObjectivePropsItem *pObjective );

	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMissionFrame)
protected:
	//}}AFX_VIRTUAL
	
	// Implementation
private:
	std::string szPrefix;		//��� ���������� ������������ ��� �������� ��������� � ������� FillRpgStats, ����� �� ���� ������������� �������� ���������
	CMissionObjectivePropsItem *pActiveObjective;
	
protected:
	virtual void SaveRPGStats( IDataTree *pDT, CTreeItem *pRootItem, const char *pszProjectName );
	virtual void LoadRPGStats( IDataTree *pDT, CTreeItem *pRootItem );
	void FillRPGStats( SMissionStats &rpgStats, CTreeItem *pRootItem, const char *pszProjectName );
	void GetRPGStats( const SMissionStats &rpgStats, CTreeItem *pRootItem );
	
	virtual bool ExportFrameData( IDataTree *pDT, const char *pszProjectName, const char *pszResultFileName, CTreeItem *pRootItem );
	virtual FILETIME FindMaximalSourceTime( const char *pszProjectName, CTreeItem *pRootItem );
	virtual FILETIME FindMinimalExportFileTime( const char *pszResultFileName, CTreeItem *pRootItem );
	virtual void SpecificInit();
	virtual void SpecificClearBeforeBatchMode();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CMissionFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnGenerateImage();
	afx_msg void OnUpdateGenerateImage(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif		//__MISSIONFRM_H__
