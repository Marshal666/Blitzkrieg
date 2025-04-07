#ifndef __SQUADFRM_H__
#define __SQUADFRM_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridFrm.h"
#include "..\Main\rpgstats.h"

#include "TreeDockWnd.h"
#include "SquadTreeItem.h"

class CDirectionButtonDockBar;

class CSquadFrame : public CGridFrame
{
	DECLARE_DYNCREATE(CSquadFrame)
public:
	CSquadFrame();
	virtual ~CSquadFrame();

// Attributes
public:

// Operations
public:
	virtual void GFXDraw();
	virtual void ShowFrameWindows( int nCommand );
	virtual void Init( IGFX *_pGFX );

	void SetDirectionButtonDockBar( CDirectionButtonDockBar *pDock ) { pDirectionButtonDockBar = pDock; }
	void SetActiveFormation( CSquadFormationPropsItem *pFormProps );
	void UpdateActiveFormation() { if ( pActiveFormation == 0 ) return; CSquadFormationPropsItem *p = pActiveFormation; pActiveFormation = 0; SetActiveFormation( p ); }
	void DeleteUnitFromScene( CTreeItem *pUnit, CSquadFormationPropsItem *pFormation );
	void SelectActiveUnit( CTreeItem *pUnit );
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSquadFrame)
protected:
	//}}AFX_VIRTUAL
	
	// Implementation
private:
	CDirectionButtonDockBar *pDirectionButtonDockBar;
	CPtr<IGFXTexture> pKrestTexture;
	CPtr<IGFXVertices> pFormationDirVertices;
	CPtr<IGFXIndices> pLineIndices;
	
	enum E_MODE
	{
		E_FREE,
		E_DRAG,
		E_SET_ZERO,
	};
	int m_mode;
	CSquadFormationPropsItem *pActiveFormation;
	CSquadFormationPropsItem::SUnit *pDraggingUnit;
//	IObjVisObj *pDraggingUnit;
	CVec2 objShift;

protected:
	virtual void SpecificInit();														//��� ������������� ���������� ������ ����� �������� ������� ��� �������� ������
	virtual void SpecificClearBeforeBatchMode();
	virtual BOOL SpecificTranslateMessage( MSG *pMsg );
	
	virtual void SaveRPGStats( IDataTree *pDT, CTreeItem *pRootItem, const char *pszProjectName );
	virtual void LoadRPGStats( IDataTree *pDT, CTreeItem *pRootItem );
	virtual bool ExportFrameData( IDataTree *pDT, const char *pszProjectName, const char *pszResultFileName, CTreeItem *pRootItem );
	
	void CreateKrest();
	void SetZeroCoordinate( POINT point );
	void UpdateFormationDirection();
	void CalculateNewPositions( float fAlpha );

// Generated message map functions
protected:
	//{{AFX_MSG(CSquadFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSetZeroButton();
	afx_msg void OnUpdateSetZeroButton(CCmdUI* pCmdUI);
	afx_msg void OnShowDirectionButton();	
	afx_msg void OnUpdateShowDirectionButton(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif		//__SQUADFRM_H__
