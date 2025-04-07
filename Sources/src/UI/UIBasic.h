#ifndef __UIBASIC_H__
#define __UIBASIC_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "UIInternal.h"
#include "..\lualib\script.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSimpleWindow;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef std::list< CObj<IUIElement> > CWindowList;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSimpleWindow
{
	DECLARE_SERIALIZE;
	
	//
	CTRect<float> wndRect;							//���������� ������ ������������ ������
	int nPositionFlag;									//������ ����� ��������
	CVec2 vPos;													//���������� ����� ������� ����� ������ ������������ ��������� ����� ��������
	CVec2 vSize;												//������� ������
	typedef std::vector<CWindowState> CStateVector;
	
	int nID;														//���������� ������������� ������
	CPtr<IUIContainer> pParent;					//��������
	bool bWindowActive;									//������� �� ����				//??
	int nCmdShow;												//������ ����������� ����
	
	CStateVector states;								//��� ��������� ��������� ���� ������, �������� � CheckButton ��� ���������
	int nCurrentState;									//������� ���������
	int nCurrentSubState;								//������� ������������ ������: NORMAL, HIGHLIGHTED, PUSHED
	bool bShowBackground;								//���������� ��� ��� �������� ( ����� ����� ��� ������ ������ � ������� )
	
	CObj<IManipulator> pManipulator;
	std::string szHighSound;						//����, ������������� ����� ����� ��������� �� �������, �������� ��� ������ ���� ������ ��� ������ state, ��
	
	//��� ������
	int nTextAlign;
	DWORD dwTextColor;
	CVec2 vShiftText;
	int nFontSize;
	CVec2 vTextPos;
	bool bRedLine;
	bool bSingleLine;

	//��� ����
	DWORD dwShadowColor;
	CVec2 vShadowShift;
	std::string szToolKey;
	
	//bound rect
	CTRect<float> rcBound;
	bool bBounded;
	
	//��� ������� �������� ��� ������� ������ (�������� ������, ����� nBlink == 1 � � ��� ���� state)
	//���� � ��� nBlink == 2 �� �������� ������ ���������� �� ���������� state
	//���� 0, �� ��� ������� ������ �� ������
	int nBlink;
	DWORD dwLastBlinkTime;
	DWORD dwCurrentBlinkColor;
	bool bBlinking;											//���� true �� ������ �������� ������
	DWORD dwBlinkTime;
	int nBlinkColorIndex;								// color number (for blinking)

	void InitDependentInfo();

protected:
	//��������� ����� �������� ��������� ���������, ��������� ����������� ������������ � pParent
	void UpdateLocalCoordinates();
	void SetShowBackgroundFlag( bool bFlag ) { bShowBackground = bFlag; }

	void DrawBackground( IGFX *pGFX );
	void DrawText( IGFX *pGFX );
	void VisitBackground( ISceneVisitor *pVisitor );
	void VisitText( ISceneVisitor *pVisitor );
	void BlinkMe( const int nBlinkTime = 0, const int nBlinkColorIndex = 0 );

	friend class CUIWindowManipulator;
	friend class CUIEditBox;
	friend class CUIScrollTextBox;
	friend class CUIStatic;
	friend class CUIMiniMap;
	friend class CUINumberIndicator;
	friend class CMultipleWindow;
	friend class CUIMedals;
	friend class CUIShortcutBar;
	friend class CUIComboBox;
	friend class CUIStatusBar;
	friend class CUICreditsScroller;
	friend class CUIConsole;

	void GetWindowRect( CTRect<float> *pWndRect ) const { *pWndRect = wndRect; }
	int GetCmdShow() const { return nCmdShow; }
public:
	CSimpleWindow() : nID( -1 ), nCurrentSubState( 0 ), bShowBackground( true ), nTextAlign( 0x0011 ), vShiftText( 0, 0 ), nBlink( 0 ), dwLastBlinkTime( 0 ), dwCurrentBlinkColor( 0xff000000 ),
		bWindowActive( true ), nCmdShow( UI_SW_SHOW ), states( 1 ), nCurrentState( 0 ), nPositionFlag( 0x0011 ), vPos(0, 0), vSize(0, 0), bBlinking( false ), bSingleLine( false ),
		dwTextColor( 0xff9aceb7 ), nFontSize( 1 ), bBounded( false ), vTextPos( 0, 0 ), bRedLine( false ), vShadowShift( 0, 0 ), dwShadowColor( 0xff000000 ), nBlinkColorIndex( 0 ) {}
	virtual ~CSimpleWindow() {}
	
	// serializing...
	virtual int STDCALL operator&( IDataTree &ss );
	
	// update
	virtual bool STDCALL Update( const NTimer::STime &currTime );
	virtual void STDCALL Reposition( const CTRect<float> &rcParent );
	
	// text
	virtual void STDCALL SetWindowText( int nState, const WORD *pszText );
	virtual const WORD* STDCALL GetWindowText( int nState );
	virtual void STDCALL SetTextColor( DWORD dwColor );
	
	// tool tip functions
	virtual IText* STDCALL GetHelpContext( const CVec2 &vPos, CTRect<float> *pRect );
	virtual void STDCALL SetHelpContext( int nState, const WORD *pszToolTipText );
	
	//CRAP set texture
	virtual void STDCALL SetWindowTexture( IGFXTexture *pTexture );
	virtual IGFXTexture* STDCALL GetWindowTexture();
	virtual void STDCALL SetWindowMap( const CTRect<float> &maps );
	virtual void STDCALL SetWindowPlacement( const CVec2 *_vPos, const CVec2 *_vSize );		//require to call Reposition() next
	virtual void STDCALL SetWindowID( int _nID );
	virtual void STDCALL SetBoundRect( const CTRect<float> &rc ) { bBounded = true; rcBound = rc; }
	
	// drawing
	virtual void STDCALL Draw( IGFX *pGFX );
	virtual void STDCALL Visit( interface ISceneVisitor *pVisitor );
	
	// cursor and actions
	virtual bool STDCALL OnLButtonDblClk( const CVec2 &vPos );
	virtual bool STDCALL OnMouseMove( const CVec2 &vPos, EMouseState mouseState );
	virtual bool STDCALL OnLButtonDown( const CVec2 &vPos, EMouseState mouseState );
	virtual bool STDCALL OnLButtonUp( const CVec2 &vPos, EMouseState mouseState );
	virtual bool STDCALL OnRButtonDown( const CVec2 &vPos, EMouseState mouseState );
	virtual bool STDCALL OnRButtonUp( const CVec2 &vPos, EMouseState mouseState );
	virtual bool STDCALL OnMouseWheel( const CVec2 &vPos, EMouseState mouseState, float fDelta );
	virtual bool STDCALL IsInside( const CVec2 &vPos );
	virtual bool STDCALL OnChar( int nAsciiCode, int nVirtualKey, bool bPressed, DWORD keyState ) { return false; }
	virtual bool STDCALL IsModal() const { return false; }
	
	virtual int STDCALL  GetWindowID() { return nID; }
	virtual int STDCALL GetWindowPlacement( CVec2 *pPos, CVec2 *pSize, CTRect<float> *pScreenRect );
	virtual int STDCALL GetPositionFlag() { return nPositionFlag; }
	virtual void STDCALL SetParent( interface IUIContainer *pPapa ) { pParent = pPapa; }
	virtual IUIContainer* STDCALL GetParent() { return pParent; }
	// state
	virtual void STDCALL SetFocus( bool bFocus );
	virtual void STDCALL EnableWindow( bool bEnable );
	virtual bool STDCALL IsWindowEnabled() { return bWindowActive; }
	virtual void STDCALL SetState( int nState, bool bNotify );		//if bNotify flag is false, then button will not send notification message
	virtual int  STDCALL GetState() { return nCurrentState; }
	virtual bool STDCALL IsVisible() { return nCmdShow != UI_SW_HIDE && nCmdShow != UI_SW_MINIMIZE; }
	virtual int  STDCALL GetVisibleState() { return nCmdShow; }
	virtual void STDCALL ShowWindow( int _nCmdShow );

	virtual bool STDCALL ProcessMessage( const SUIMessage &msg ) { if ( IsProcessedMessage( msg ) ) return pParent->ProcessMessage( msg ); return false; }
	
	virtual IUIElement* STDCALL PickElement( const CVec2 &vPos, int nRecursion );
	virtual IManipulator* STDCALL GetManipulator();
	virtual void STDCALL GetTextSize( const int nState, int *pSizeX, int *pSizeY ) const;


	// ������ ��� ����������� ����������
	const CTRect<float>& GetScreenRect() { return wndRect; }
	void SetScreenRect( const CTRect<float> &rc ) { wndRect = rc; }
	void UpdateSubRects();
	CVec2 GetSize() { return vSize; }
	void SetPos( const CVec2 &pos ) { vPos = pos; }
	void SetSize( const CVec2 &size ) { vSize = size; }
	void SetPositionFlag( int nFlag ) { nPositionFlag = nFlag; }
	void DestroyWindow();
	int GetCurrentSubState() { return nCurrentSubState; }
	
	void InitText();
	
	float GetWidth() const { return wndRect.Width(); }
	// duplicate
	void CopyInternals( CSimpleWindow * pWnd );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CMultipleWindow : public CSimpleWindow
{
	DECLARE_SERIALIZE;
	//
	//
	CWindowList childList;							//child windows
	//����� ������ ������ � ���� ������ ����� �����, ��� �������� ��������� �� ����������.
	//������ �������������� � ����� ������ � ������

	CPtr<IUIElement> pHighlighted;			//������������ ����
	CPtr<IUIElement> pPushed;						//������� ���� (����� ������)
	CPtr<IUIElement> pRPushed;					//���� � ������� ������ ������� ����
	CPtr<IUIElement> pFocused;					//���� � �������, ��� ������ ������ ��� edit box �������� ��������� TEXT_MODE
	
	typedef std::list< SUIMessage > CMessageList;
	CMessageList messageList;

	//���������� ��� mouse wheel support
	float fMouseWheelMultiplyer;

	//��������� LUA
	std::string szLuaFileName;
	bool bLua;																	//��������������������� �� LUA
	Script luaScript;
	static CMessageList staticMessageList;			//��� ��� ���������� ������ � ������� �� ����� ������ LUA �������
	
	struct SLuaValue
	{
		int nID;
		int nVal;
	};
	typedef std::vector< SLuaValue > CLuaValues;
	static CLuaValues staticLuaValues;

	//��� ���������� ����
	bool bAnimation;						//���� ���������� ����, �� ������ � ���������
	bool bAnimationRunning;			//���� ����, ��� ���������� ��������, ������� ��� ��������
	DWORD dwLastOpenTime;				//����� ����� �������� �������� ��������
	DWORD dwLastCloseTime;			//����� ����� �������� �������� ��������
	DWORD dwAnimationTime;			//����� �������� �������� ��� ��������
	CVec2 vMinPos;
	CVec2 vMaxPos;
	CVec2 vBeginPos;
	int nAnimationCmdShow;
	
	//CRAP
	bool bModal;			//������������ ��� ����, ����� ��� ��������� ������������ ������ ������� �������
	friend class CUIScrollTextBox;
	friend class CUIObjective;
	friend class CUIList;
	friend class CUIMedals;
	friend class CUIShortcutBar;
	friend class CUIObjMap;
	friend class CUIConsole;
	
	void InitDependentInfoMW();
	IUIElement * GetFirstModal();
protected:
	bool IsInsideChild( const CVec2 &_vPos );
	bool IsEmpty() { return childList.empty(); }

	CWindowList & GetChildList() { return childList; }

public:
	CMultipleWindow() : bLua( false ), bModal( false ), dwAnimationTime( 200 ), dwLastOpenTime( 0 ), fMouseWheelMultiplyer( 4.375f ),
		dwLastCloseTime( 0 ), bAnimation( false ), bAnimationRunning( false ), nAnimationCmdShow( 0 ) {}
	
	// serializing...
	virtual int STDCALL operator&( IDataTree &ss );
	
	// update
	virtual bool STDCALL Update( const NTimer::STime &currTime );
	virtual void STDCALL SetFocus( bool bFocus );
	virtual void STDCALL SetFocusedWindow( IUIElement *pNewFocusWindow );
	virtual void STDCALL Reposition( const CTRect<float> &rcParent );
	virtual void STDCALL EnableWindow( bool bEnable );
	
	// tool tip functions
	virtual IText* STDCALL GetHelpContext( const CVec2 &vPos, CTRect<float> *pRect );

	// drawing
	virtual void STDCALL Draw( IGFX *pGFX );
	virtual void STDCALL Visit( interface ISceneVisitor *pVisitor );
	
	// cursor and actions
	virtual bool STDCALL OnLButtonDblClk( const CVec2 &vPos );
	virtual bool STDCALL OnMouseMove( const CVec2 &vPos, EMouseState mouseState );
	virtual bool STDCALL OnLButtonDown( const CVec2 &vPos, EMouseState mouseState );
	virtual bool STDCALL OnLButtonUp( const CVec2 &vPos, EMouseState mouseState );
	virtual bool STDCALL OnRButtonDown( const CVec2 &vPos, EMouseState mouseState );
	virtual bool STDCALL OnRButtonUp( const CVec2 &vPos, EMouseState mouseState );
	virtual bool STDCALL OnMouseWheel( const CVec2 &vPos, EMouseState mouseState, float fDelta );
	virtual bool STDCALL OnChar( int nAsciiCode, int nVirtualKey, bool bPressed, DWORD keyState );
	
	virtual void STDCALL AddChild( IUIElement *pSimple ) { childList.push_front( pSimple ); IUIContainer *pContainer = dynamic_cast<IUIContainer*> ( this ); pSimple->SetParent( pContainer ); }
	virtual void STDCALL RemoveChild( IUIElement *pSimple ) { childList.remove( pSimple ); }
	virtual void STDCALL RemoveAllChildren() { childList.clear(); }
	virtual IUIElement* STDCALL GetChildByID( int nChildID );
	IUIElement* GetChildByIndex( int nIndex );
	virtual bool STDCALL IsModal() const { return bModal; }

	virtual void STDCALL MoveWindowUp( IUIElement *pWnd );
	virtual void STDCALL MoveWindowDown( IUIElement *pWnd );
	virtual bool STDCALL ProcessMessage( const SUIMessage &msg );
	virtual void STDCALL ShowWindow( int _nCmdShow );
	virtual void STDCALL SetBoundRect( const CTRect<float> &rc );

	virtual IUIElement* STDCALL PickElement( const CVec2 &vPos, int nRecursion );

	//��� ������ LUA
	static int AddMessage( lua_State *pLuaState );			//���������� �� �������
	static int SaveLuaValue( lua_State *pLuaState );		//���������� �� �������
	static int IsGameButtonProcessing( lua_State *pLuaState ); //���������� �� �������
	
	//��� ����������� ����������
	void SetModalFlag( bool bFlag ) { bModal = bFlag; }
	bool GetModalFlag() { return bModal; }
	void SetMouseWheelMultiplyer( float fVal ) { fMouseWheelMultiplyer = fVal; }
	float GetMouseWheelMultiplyer() { return fMouseWheelMultiplyer; }
	
	// duplication 
	void CopyInternals( CMultipleWindow * pWnd );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __UIBASIC_H__
