#ifndef __PARENT_FRAME_H__
#define __PARENT_FRAME_H__

#include <SECWB.H>
#include "..\GFX\GFX.h"

using std::string;
using std::vector;
using std::list;

interface IGFX;
class CTreeDockWnd;
class CPropView;
class CTreeItem;
class CETreeCtrl;
class SECCustomToolBar;

struct SObjectInfo
{
	std::string szPath;
	std::string szType;
	std::string szName;
	std::string szVisType;
	int operator&( IDataTree &ss )
	{
		CTreeAccessor saver = &ss;
		saver.Add( "path", &szPath );
		saver.Add( "game_type", &szType );
		saver.Add( "name", &szName );
		saver.Add( "type", &szVisType );
		return 0;
	}
};

class CParentFrame : public SECWorksheet
{
	DECLARE_DYNCREATE(CParentFrame)
public:
	CParentFrame();
	virtual ~CParentFrame();
	
	virtual void Init( IGFX *_pGFX ) { pGFX = _pGFX; }			//ининциализация
	virtual void ShowFrameWindows( int nCommand );					//вызывается при изменении фокуса, параметр SW_SHOW или SW_HIDE
	virtual void GFXDraw() {}																//отрисовка

	void SetChangedFlag( bool bFlag );											//устанавливает флаг модификации, отображает * в имени проекта
	int DisplayInsertMenu();																//отображает меню с пунктом insert
	int DisplayDeleteMenu();
	
	//функции для сохранения и загрузки информации в реестре
	void SaveRegisterData();
	void LoadRegisterData();

	int GetFrameType() { return nFrameType; }
	float GetBrightness() { return m_fBrightness; }
	float GetContrast() { return m_fContrast; }
	float GetGamma() { return m_fGamma; }
	void SetBrightness( float fVal ) { m_fBrightness = fVal; }
	void SetContrast( float fVal ) { m_fContrast = fVal; }
	void SetGamma( float fVal ) { m_fGamma = fVal; }
	int GetCompressedFormat() { NI_ASSERT( m_nCompressedFormat != -1 ); return m_nCompressedFormat; }
	int GetLowFormat() { NI_ASSERT( m_nLowFormat != -1 ); return m_nLowFormat; }
	int GetHighFormat() { NI_ASSERT( m_nHighFormat != -1 ); return m_nHighFormat; }
	int GetCompressedShadowFormat() { NI_ASSERT( m_nCompressedShadowFormat != -1 ); return m_nCompressedShadowFormat; }
	int GetLowShadowFormat() { NI_ASSERT( m_nLowShadowFormat != -1 ); return m_nLowShadowFormat; }
	int GetHighShadowFormat() { NI_ASSERT( m_nHighShadowFormat != -1 ); return m_nHighShadowFormat; }
	
	//инициализация OI и дерева
	void SetTreeDockBar( CTreeDockWnd *pWnd ) { pTreeDockBar = pWnd; }
	void SetOIDockBar( CPropView *pWnd );
	void SetToolBar( SECCustomToolBar *pWnd ) { pToolBar = pWnd; }
	void ClearPropView();
	BOOL SaveFrame( bool bUnlock = false );					//для сохранения данных frame после завершения программы
	virtual void UpdatePropView( CTreeItem *pTreeItem );								//для отображения в OI новой информации
	string GetProjectFileName() { return szProjectFileName; }		//для вычисления относительной директории при изменении путей в дереве
	const char *GetModuleExtension() { return szExtension.c_str(); }
	void RunBatchExporter( const char *pszSourceDir, const char *pszDestDir, const char *pszMask, bool bForceFlag, bool bOpenSave );
	
protected:
	CWnd *pWndView;											//view окошко для отображения
	CPtr<IGFX> pGFX;										//для ускорения доступа к GFX, старый остаток
	CTreeDockWnd *pTreeDockBar;					//дерево для выбора редактируемого item
	CPropView *pOIDockBar;							//object inspector, окно редактирования
	SECCustomToolBar *pToolBar;					//toolbar для данного фрейма

	string szProjectFileName;						//имя открытого проекта
	string szPrevExportFileName;				//ранее экспортированное имя для проекта, относительно szSourceDir
	bool bChanged;											//изменился ли проект после загрузки / создания
	bool bNewProjectJustCreated;				//если true, то только что создан новый проект, надо прогрузить данные из RPG stats

	int m_nCompressedFormat;
	int m_nLowFormat;
	int m_nHighFormat;

	int m_nCompressedShadowFormat;
	int m_nLowShadowFormat;
	int m_nHighShadowFormat;

	//для транзакций
	struct STransaction
	{
		string szSourceName;
		string szSourceDate;
		string szSourceTime;
		string szSourceOwner;
		string szAction;
		string szDestName;
		string szDestDate;
		string szDestTime;
		string szDestOwner;

		int operator&( IDataTree &ss );
	};
	string m_szOldProjectName;					//имя предыдущего файла проекта
	vector<STransaction> transactions;

	//эти параметры должны инициализироваться в конструкторе для каждого композера
	string szComposerName;							//имя composer, отображается в title
	string szExtension;									//расширение для проектов композера
	string szExportExtension;						//расширение для экспорта файлов проекта
	string szComposerSaveName;					//используется при сохранении данных в XML
	string szAddDir;										//добавочная директория, добавляется к szSourceDir
	int nTreeRootItemID;								//ID root item для данного композера
	bool bDefaultExportName;						//если установлен флаг, то при экспорте будет предлагаться имя файла 1.xml по умолчанию
	int nFrameType;

	//параметры, сохраняемые в реестре
/*
	string szLocalSourceDir;						//директория исходников
	string szLocalDestDir;							//директория результатов
*/
	DWORD m_backgroundColor;						//цвет background для GFXDraw()
	float m_fBrightness;
	float m_fContrast;
	float m_fGamma;
	bool bTreeExpand;

protected:
	void ComputeCaption();							//обновляет title окошка
	void GenerateProjectName();					//генерит имя для нового проекта, используется при создании нового проекта

	//считывыет инфо из конфигурационного файла (ищет рекурсивно поднимаясь вверх ближайший gamma.cfg файл)
	//первый параметр - имя директории, относительно которой поднимаясь вверх компоновщик будет искать конфигурационный файл
	//второй параметр - флаг, находимся ли мы в режиме batch mode, чтобы не ругаться
	bool ReadConfigFile( const char *pszDirectory, bool bBatchMode );
	bool WriteConfigFile( bool bAsk, bool bCurrentProjectOnly );	//записывает инфо в конфиг файл

	void LoadTransactions( IDataTree *pDT );		//считывает инфу о предыдущих изменениях в проекте
	void SaveTransactions( FILETIME *pFT, IDataTree *pDT, const char *pszDest, int nAction );	//записывает инфу о произошедших изменениях
	bool ConvertAndSaveImage( const char *pszSrc, const char *pszDest );								//применяет преобразования и сохраняет картинку
	CETreeCtrl *CreateTrees();
	virtual string GetExportFileName();

	//специфичная обработка сообщений для модуля
	virtual BOOL SpecificTranslateMessage( MSG *pMsg ) { return FALSE; }
	virtual void SpecificInit() {}													//для инициализации внутренних данных после загрузки проекта или создании нового
	virtual void SpecificSave( IDataTree *pDT ) {}					//вызывается при записи проекта, нужно только в GUI composer
	virtual void SpecificClearBeforeBatchMode() {};					//для очистки перед запуском batch mode
	
	virtual void SaveFrameOwnData( IDataTree *pDT );				//для сохранения собственных данных проекта
	virtual void LoadFrameOwnData( IDataTree *pDT );				//для загрузки

	//сохраняет RPG stats композера в pDT, принимает параметр pRootItem для того чтобы функцию можно было вызывать из batch mode
	virtual void SaveRPGStats( IDataTree *pDT, CTreeItem *pRootItem, const char *pszProjectName ) {}
	//загружает RPG stats
	virtual void LoadRPGStats( IDataTree *pDT, CTreeItem *pRootItem ) {}

/*
	//заполняет rpgStats из дерева перед собственно записью в файл (или при создании нового проекта)
	void FillRPGStats( SCommonRPGStats *pCommonRpgStats, CTreeItem *pRootItem );
	//инициализирует данные в дереве при октрытии проекта
	void GetRPGStats( const SCommonRPGStats *pCommonRpgStats, CTreeItem *pRootItem );
*/

	//BATCH MODE
	//экспортирует один проект, если все ОК, возвращает 0, иначе код ошибки
	int ExportSingleFile( const char *pszFileName, const char *pszDestDir, bool bForceFlag, bool bOpenSave );
	//загружает данные перед экспортом проекта, используется в object, building, mesh фреймах
	virtual bool LoadFramePreExportData( const char *pszProjectFile, CTreeItem *pRootItem ) { return true; }
	//вычисляет максимальное время изменения для исходников проекта
	virtual FILETIME FindMaximalSourceTime( const char *pszProjectName, CTreeItem *pRootItem ) { FILETIME time; time.dwHighDateTime = 0xffffffff; time.dwLowDateTime = 0xffffffff; return time; }
	//вычисляет минимальное время для результатов экспорта
	virtual FILETIME FindMinimalExportFileTime( const char *pszResultFileName, CTreeItem *pRootItem ) { FILETIME time; time.dwHighDateTime = 0; time.dwLowDateTime = 0; return time; }
	//запускает экспортер
	//эта функция экспортирует все данные проекта, вызывается как из batch mode, так и при OnFileSave()
	//параметры: имя исходника проекта, имя файла результата, RootItem, дополнительный флаг
	virtual bool ExportFrameData( IDataTree *pDT, const char *pszProjectName, const char *pszResultFileName, CTreeItem *pRootItem ) { return true; }
	
	//для локировки редактора
	bool LockFile();				//возвращает false если не может залочить файл (уже залочен)
	bool UnLockFile();			//возвращает false если не может разлочить (ошибка удаления файла или еще какой кал)
	void SwitchDockerVisible( SECControlBar *pBar );
	void UpdateShowMenu( CCmdUI* pCmdUI, SECControlBar *pBar );

	void SwitchActiveFrame( int id );
	void UpdateFrameMenu( CCmdUI* pCmdUI, int id );

public:
	void LoadComposerFile( const char *pszFileName );

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimationFrame)
protected:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
//	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual void OnUpdateFrameTitle( BOOL bAddToTitle ) { /* эта шняга должна быть пустой */ }
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CAnimationFrame)
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnFileCreateNewProject();
	afx_msg void OnFileOpen();
	afx_msg void OnFileClose();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveProjectAs();
	afx_msg void OnExportPak();
	afx_msg void OnRunGame();
	afx_msg void OnHelp();
	afx_msg void OnFileExportFiles();
	afx_msg void OnUpdateFileExportFiles(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSaveProjectAs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCloseFile(CCmdUI* pCmdUI);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnFileSetdirectories();
	afx_msg void OnSetPictureOptions();
	afx_msg void OnFileBatchMode();
	afx_msg void OnEditSetbackgroundcolor();
	afx_msg void OnUpdateInsertTreeItem(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeleteTreeItem(CCmdUI* pCmdUI);
	afx_msg void OnViewAdvancedToolbar();
	afx_msg void OnUpdateViewAdvancedToolbar(CCmdUI* pCmdUI);
	afx_msg void OnShowTree();	
	afx_msg void OnUpdateShowTree(CCmdUI* pCmdUI);
	afx_msg void OnShowOI();	
	afx_msg void OnUpdateShowOI(CCmdUI* pCmdUI);
	afx_msg void OnMODSettings();	
	afx_msg void OnExpandTree();
	
	afx_msg void OnUnitEditor();	
	afx_msg void OnUpdateUnitEditor(CCmdUI* pCmdUI);
	afx_msg void OnInfantryEditor();	
	afx_msg void OnUpdateInfantryEditor(CCmdUI* pCmdUI);
	afx_msg void OnSquadEditor();	
	afx_msg void OnUpdateSquadEditor(CCmdUI* pCmdUI);
	afx_msg void OnWeaponEditor();	
	afx_msg void OnUpdateWeaponEditor(CCmdUI* pCmdUI);
	afx_msg void OnMineEditor();	
	afx_msg void OnUpdateMineEditor(CCmdUI* pCmdUI);

	afx_msg void OnParticleEditor();	
	afx_msg void OnUpdateParticleEditor(CCmdUI* pCmdUI);
	afx_msg void OnSpriteEditor();	
	afx_msg void OnUpdateSpriteEditor(CCmdUI* pCmdUI);
	afx_msg void OnEffectEditor();	
	afx_msg void OnUpdateEffectEditor(CCmdUI* pCmdUI);

	afx_msg void OnBuildingEditor();	
	afx_msg void OnUpdateBuildingEditor(CCmdUI* pCmdUI);
	afx_msg void OnObjectEditor();	
	afx_msg void OnUpdateObjectEditor(CCmdUI* pCmdUI);
	afx_msg void OnFenceEditor();	
	afx_msg void OnUpdateFenceEditor(CCmdUI* pCmdUI);
	afx_msg void OnBridgeEditor();	
	afx_msg void OnUpdateBridgeEditor(CCmdUI* pCmdUI);
	afx_msg void OnTrenchEditor();	
	afx_msg void OnUpdateTrenchEditor(CCmdUI* pCmdUI);

	afx_msg void OnMissionEditor();	
	afx_msg void OnUpdateMissionEditor(CCmdUI* pCmdUI);
	afx_msg void OnChapterEditor();	
	afx_msg void OnUpdateChapterEditor(CCmdUI* pCmdUI);
	afx_msg void OnCampaignEditor();	
	afx_msg void OnUpdateCampaignEditor(CCmdUI* pCmdUI);
	afx_msg void OnMedalEditor();	
	afx_msg void OnUpdateMedalEditor(CCmdUI* pCmdUI);

	afx_msg void OnTerrainEditor();	
	afx_msg void OnUpdateTerrainEditor(CCmdUI* pCmdUI);
	afx_msg void OnRoadEditor();	
	afx_msg void OnUpdateRoadEditor(CCmdUI* pCmdUI);
	afx_msg void OnRiverEditor();	
	afx_msg void OnUpdateRiverEditor(CCmdUI* pCmdUI);
	afx_msg void OnSaveObjects();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif		//__PARENT_FRAME_H__
