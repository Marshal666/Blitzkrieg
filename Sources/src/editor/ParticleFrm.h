#ifndef __PARTICLE_FRAME_H__
#define __PARTICLE_FRAME_H__

#include "..\Scene\ParticleSourceData.h"
#include "..\Scene\SmokinParticleSourceData.h"

#include "ParentFrame.h"
#include "TreeDockWnd.h"

class CKeyFrameDockWnd;


class CParticleFrame : public CParentFrame
{
	DECLARE_DYNCREATE(CParticleFrame)
public:
	CParticleFrame();
	virtual ~CParticleFrame();

// Attributes
public:

// Operations
public:
	virtual void GFXDraw();
	virtual void ShowFrameWindows( int nCommand );

	BOOL Run();										//Вызывается из EditorApp OnIdle()
	bool IsRunning() { return bRunning; }

	void SetKeyFrameDockBar( CKeyFrameDockWnd *pWnd );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParticleFrame)
protected:
		//}}AFX_VIRTUAL

// Implementation
private:
	CKeyFrameDockWnd *pKeyFrameDockBar;
	
	bool bHorizontalCamera;
	bool bRunning;
	bool bComplexSource;

	//информация, отображаемая в status bar
	float m_fNumberOfParticles;
	float m_fMaxSize;
	float m_fAverageSize;
	float m_fAverageCount;
	CPtr<IEffectVisObj> pEffect;
protected:
	virtual void SpecificInit();
	virtual void SpecificClearBeforeBatchMode();
	virtual BOOL SpecificTranslateMessage( MSG *pMsg );

	virtual void SaveRPGStats( IDataTree *pDT, CTreeItem *pRootItem, const char *pszProjectName );
	virtual void LoadRPGStats( IDataTree *pDT, CTreeItem *pRootItem );
	void FillRPGStats( SParticleSourceData &particleSetup, CTreeItem *pRootItem );
	void GetRPGStats( const SParticleSourceData &particleSetup, CTreeItem *pRootItem );
	void FillRPGStats2( SSmokinParticleSourceData &particleSetup, CTreeItem *pRootItem );
	void GetRPGStats2( const SSmokinParticleSourceData &particleSetup, CTreeItem *pRootItem );
	virtual bool ExportFrameData( IDataTree *pDT, const char *pszProjectName, const char *pszResultFileName, CTreeItem *pRootItem );

	void GetParticleInfo();
	void CreateEffectDescriptionFile();
	void UpdateCamera();
	void UpdateSourceType( bool bOnlyDelete = false );
	void UpdateSourceTypeTB();
	
// Generated message map functions
protected:
	//{{AFX_MSG(CParticleFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRunButton();
	afx_msg void OnStopButton();
	afx_msg void OnUpdateStopButton(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRunButton(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStatusBar(CCmdUI* pCmdUI);
	afx_msg void OnGetParticleInfo();
	afx_msg void OnButtonCamera();
	afx_msg void OnSwitchParticleSourceType();
	afx_msg void OnUpdateParticleSource(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGetParticleInfo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonCamera(CCmdUI* pCmdUI);
	afx_msg void OnShowFunctionFrame();	
	afx_msg void OnUpdateShowFunctionFrame(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif		//__PARTICLE_FRAME_H__
