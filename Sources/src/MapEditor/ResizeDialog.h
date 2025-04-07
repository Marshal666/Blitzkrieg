#if !defined(__CommonControls__Resizee_Dialog__)
#define __CommonControls__Resizee_Dialog__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CResizeDialog : public CDialog
{
	struct SControlStyle
	{
		CTRect<int> position;
		DWORD dwStyle;
		float fHorCenterAnchorRatio;
		float fVerCenterAnchorRatio;
		float fHorResizeRatio;
		float fVerResizeRatio;
	};

	struct SOptions
	{
		CTRect<int> rect;
		std::vector<int> nParameters;
		std::vector<std::string> szParameters;
		std::vector<float> fParameters;

		SOptions() : rect( 0, 0, 0, 0 ) {}
		virtual int STDCALL operator&( IStructureSaver &ss );
		virtual int STDCALL operator&( IDataTree &ss );
	};

	std::hash_map<UINT, SControlStyle> resizeDialogControlStyles;
	CTPoint<int> resizeDialogOriginalSize;

	public:
	SOptions resizeDialogOptions;
	//ANCHORE_LEFT				resize - относительно левого края ( центральная линия - 0.0f )
	//ANCHORE_RIGHT				resize - относительно правого края ( центральная линия - 1.0f )
	//ANCHORE_HOR_CENTER	resize - относительно центральной линии ( центральная линия - fHorCenterAnchorRatio)
	//RESIZE_HOR					дополнительно меняем размер на fHorResizeRatio
	
	static const DWORD ANCHORE_LEFT;
	static const DWORD ANCHORE_TOP;
	static const DWORD ANCHORE_RIGHT;
	static const DWORD ANCHORE_BOTTOM;
	static const DWORD ANCHORE_HOR_CENTER;
	static const DWORD ANCHORE_VER_CENTER;
	static const DWORD RESIZE_HOR;
	static const DWORD RESIZE_VER;
	
	static const DWORD ANCHORE_LEFT_TOP;
	static const DWORD ANCHORE_RIGHT_TOP;
	static const DWORD ANCHORE_LEFT_BOTTOM;
	static const DWORD ANCHORE_RIGHT_BOTTOM;
	static const DWORD ANCHORE_HOR_VER_CENTER;
	static const DWORD RESIZE_HOR_VER;

	static const DWORD DEFAULT_STYLE;
	static const std::string szOptionsFileName;

	CResizeDialog( UINT nIDTemplate, CWnd* pParent = 0 );
	
	//{{AFX_DATA(CResizeDialog)
	//}}AFX_DATA
	void SetControlStyle( UINT nControlID, DWORD dwStyle = DEFAULT_STYLE, float fHorCenterAnchorRatio = 0.5f, float fVerCenterAnchorRatio = 0.5f, float fHorResizeRatio = 1.0f, float fVerResizeRatio = 1.0f ); //Add and style control to inner structure
	void LoadResizeDialogOptions();
	void SaveResizeDialogOptions();
	
	void UpdateControlPositions();

protected:
	//минимальные размеры клиентской части диалога
	virtual int GetMinimumXDimension() { return 0; }
	virtual int GetMinimumYDimension() { return 0; }

	//способ сохранения
	virtual bool SerializeToRegistry() { return false; }
	
	//файл XML относительно текущего IDataStorage
	virtual std::string GetXMLOptionsLabel() { return ""; }
	virtual int GetXMLOptionsNumber() { return 0; }					//not used
	
	//ключ REGISTRY относительно HKEY_CURRENT_USER
	virtual std::string GetRegistryKey() { return ""; }

	//Рисовать или не рисовать гриппер
	virtual bool GetDrawGripper() { return false; }
	
	//{{AFX_VIRTUAL(CResizeDialog)
	virtual void DoDataExchange( CDataExchange* pDX );
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CResizeDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnSizing( UINT fwSide, LPRECT pRect );
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(__CommonControls__Resizee_Dialog__)
