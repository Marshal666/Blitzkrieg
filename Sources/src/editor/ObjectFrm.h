// ObjectFrm.h : interface of the CObjectFrame class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __OBJECTFRM_H__
#define __OBJECTFRM_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridFrm.h"

interface IObjVisObj;

class CObjectFrame : public CGridFrame
{
	DECLARE_DYNCREATE(CObjectFrame)
public:
	CObjectFrame();
	virtual ~CObjectFrame();

// Attributes
public:
	typedef vector< CPtr<IGFXVertices> > CVectorOfVertices;

// Operations
public:
	virtual void GFXDraw();
	virtual void ShowFrameWindows( int nCommand );
	virtual void Init( IGFX *_pGFX );
	
	void SetActiveGraphicPropsItem( CTreeItem *pGraphicProps );
	void UpdateActiveSprite();
	void SetTranseparenceCombo( CComboBox *pCombo ) { m_pTransparenceCombo = pCombo; }
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectFrame)
	protected:
	//}}AFX_VIRTUAL

// Implementation
private:
	int m_mode;
	CVec2 objShift, zeroShift;
	CVec3 m_zeroPos;
	CVec3 m_SpriteLoadPos;
	
	CPtr<IObjVisObj> pSprite;
	CPtr<IGFXTexture> pKrestTexture;
	
	CListOfTiles lockedTiles;
	CListOfTiles transeparences;
	CListOfTiles bonuses;
	
	CComboBox *m_pTransparenceCombo;
	int m_transValue;
	
	//one way transeparence
	bool bDragging;
	struct STransLine
	{
		CVec2 p1, p2;
		CPtr<IGFXVertices> pVertices;
		CPtr<IGFXVertices> pNormalVertices;

		int operator&( IDataTree &ss );
	};
	typedef list<STransLine> CTransLineList;
	STransLine currentLine;			//��� ����������� ������� ��������������� �����
	CTransLineList transLines;
	bool bDrawRect;
	CPtr<IGFXVertices> pRectVertices;
	int m_nSelected;
	CListOfNormalTiles dirTiles;

	// ��� ����������� ������� �������
	CTreeItem *pActiveGraphicProps;
	
protected:
	void LoadSprite( const char *pszSpriteFullName );

	void CreateKrest();
	int UpdateNormalForSelectedLine();
	virtual void SpecificInit();														//��� ������������� ���������� ������ ����� �������� ������� ��� �������� ������
	virtual void SpecificClearBeforeBatchMode();
	virtual BOOL SpecificTranslateMessage( MSG *pMsg );
		
	virtual void SaveFrameOwnData( IDataTree *pDT );				//��� ���������� ����������� ������ �������
	virtual void LoadFrameOwnData( IDataTree *pDT );				//��� ��������
	virtual void SaveRPGStats( IDataTree *pDT, CTreeItem *pRootItem, const char *pszProjectName );
	virtual void LoadRPGStats( IDataTree *pDT, CTreeItem *pRootItem );
	
	virtual bool LoadFramePreExportData( const char *pszProjectFile, CTreeItem *pRootItem );
	virtual bool ExportFrameData( IDataTree *pDT, const char *pszProjectName, const char *pszResultFileName, CTreeItem *pRootItem );
	virtual FILETIME FindMaximalSourceTime( const char *pszProjectName, CTreeItem *pRootItem );
	virtual FILETIME FindMinimalExportFileTime( const char *pszResultFileName, CTreeItem *pRootItem );
	
// Generated message map functions
protected:
	//{{AFX_MSG(CObjectFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawGrid();
	afx_msg void OnMoveObject();
	afx_msg void OnUpdateMoveObject(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawGrid(CCmdUI* pCmdUI);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetZeroButton();
	afx_msg void OnUpdateSetZeroButton(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawTransparence(CCmdUI* pCmdUI);
	afx_msg void OnSetFocusTranseparence();
	afx_msg void OnChangeTranseparence();
	afx_msg void OnDrawOneWayTranseparence();
	afx_msg void OnUpdateDrawOneWayTranseparence(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif		//__OBJECTFRM_H__
