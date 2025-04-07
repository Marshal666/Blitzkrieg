#ifndef __FENCEFRM_H__
#define __FENCEFRM_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Main\rpgstats.h"
#include "GridFrm.h"
#include "TreeDockWnd.h"
#include "FenceTreeItem.h"
#include "FenceView.h"
#include "ThumbList.h"
#include "SingleIcon.h"
#include "DirectionButton.h"

interface IObjVisObj;

class CFenceFrame : public CGridFrame
{
	DECLARE_DYNCREATE(CFenceFrame)
public:
	CFenceFrame();
	virtual ~CFenceFrame();

// Attributes
public:

// Operations
public:
	virtual void GFXDraw();
	virtual void ShowFrameWindows( int nCommand );

	bool IsEditMode() { return bEditPassabilityMode; }

	void ViewSizeChanged();
	void UpdateThumbWindows() { m_wndAllDirThumbItems.Invalidate(); m_wndSelectedThumbItems.Invalidate(); m_fenceTypeIcon.Invalidate(); }

	void ActiveDirNameChanged();
	void SelectItemInSelectedThumbList( DWORD dwData );
	void DeleteFrameInSelectedList( DWORD dwData );
	void SetActiveFenceInsertItem( CFenceInsertItem *pFenceItem );

	void EditFence( CFencePropsItem *pFencePropsItem );
	void FillSegmentProps( CFencePropsItem *pFrameProps, SFenceRPGStats::SSegmentRPGStats &segment );
	void SaveMyData( CFencePropsItem *pFrameProps, CTreeAccessor saver );
	void LoadMyData( CFencePropsItem *pFrameProps, CTreeAccessor saver );

	void SetTranseparenceCombo( CComboBox *pCombo ) { m_pTransparenceCombo = pCombo; }
	void RemoveFenceIndex( int nIndex );
	int GetFreeFenceIndex();
	int GetMaxFenceIndex();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFenceFrame)
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
private:
	CFenceCommonPropsItem *m_pActiveCommonPropsItem;
	CFenceInsertItem *m_pActiveInsertItem;
	
	CThumbList m_wndAllDirThumbItems;
	CThumbList m_wndSelectedThumbItems;
	CSingleIcon m_fenceTypeIcon;
	
	bool bEditPassabilityMode;
	CPtr<IObjVisObj> pSprite;
	CPtr<IGFXTexture> pKrestTexture;
	CVec2 objShift;
	int m_mode;
	CFencePropsItem *m_pFencePropsItem;
	
	CComboBox *m_pTransparenceCombo;
	int m_transValue;

	std::list<int> freeIndexes;			//��� �������� ������������� ��������
	
protected:
	void ClickOnThumbList( int nID );
	void DoubleClickOnThumbList( int nID );
	void DeleteFrameInTree( int nID );
	void InitActiveCommonPropsItem();

	void SwitchToEditMode( bool bFlag );
	void CenterSpriteAboutTile();
	
	virtual void LoadRPGStats( IDataTree *pDT, CTreeItem *pRootItem );
	virtual void SpecificInit();														//��� ������������� ���������� ������ ����� �������� ������� ��� �������� ������
	virtual void SpecificClearBeforeBatchMode();
	virtual BOOL SpecificTranslateMessage( MSG *pMsg );
	
	virtual bool ExportFrameData( IDataTree *pDT, const char *pszProjectName, const char *pszResultFileName, CTreeItem *pRootItem );
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CFenceFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMoveObject();
	afx_msg void OnUpdateMoveObject(CCmdUI* pCmdUI);
	afx_msg void OnDrawGrid();
	afx_msg void OnUpdateDrawGrid(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCenterFenceAboutTile();
	afx_msg void OnUpdateCenterFenceAboutTile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawTransparence(CCmdUI* pCmdUI);
	afx_msg void OnSetFocusTranseparence();
	afx_msg void OnChangeTranseparence();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif		//__FENCEFRM_H__
