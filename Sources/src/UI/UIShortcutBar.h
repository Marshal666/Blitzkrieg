#ifndef __UI_SHORTCUT_BAR_H__
#define __UI_SHORTCUT_BAR_H__
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "UIBasic.h"
#include "UISlider.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CUIShortcutBar : public CMultipleWindow
{
	DECLARE_SERIALIZE;
	//
	CObj<IUIScrollBar> pScrollBar;				//���������������� �� ����� �������� � ������������ ��� ��������� ������� � �����������

	int nLeftSpace;
	int nRightSpace;
	int nTopSpace;
	int nBottomSpace;
	int nBarHeight;
	int nVSubSpace;
	int nItemLeftSpace;
	bool bScrollBarAlwaysVisible;
	int nScrollBarWidth;

	struct SBar
	{
		DECLARE_SERIALIZE;
	public:
		CPtr<IUIElement> pElement;
		CWindowList items;
		bool bExpandState;

		SBar() : bExpandState( false ) {}
	};
	typedef std::vector<SBar> CBarsVector;
	CBarsVector bars;

	//��� ��������� Selection
	int nSelBar;										//���������� bar
	int nSelItem;										//���������� item
	std::vector<SWindowSubRect> selSubRects;
	CPtr<IGFXTexture> pSelectionTexture;				// ������� ��� - ��������

	//��� �������� Bar, Item, Text
	std::string szBarFileName, szItemFileName, szTextFileName;

	void InitSBWidth();
	void UpdateItemsCoordinates();				//��������� ���������� ���� ���������� item
	void UpdateScrollBarStatus();					//��������� ��� ���� � ��������� SB

public:
	CUIShortcutBar();
	
	//mouse wheel
	virtual bool STDCALL OnMouseWheel( const CVec2 &vPos, EMouseState mouseState, float fDelta ) = 0;

	virtual bool STDCALL ProcessMessage( const SUIMessage &msg );
	virtual void STDCALL Reposition( const CTRect<float> &rcParent );
	
	// serializing...
	virtual int STDCALL operator&( IDataTree &ss );
	
	// drawing
	virtual void STDCALL Draw( IGFX *pGFX );
	virtual void STDCALL Visit( interface ISceneVisitor *pVisitor );
	
	virtual bool STDCALL OnLButtonDown( const CVec2 &vPos, EMouseState mouseState );
	virtual bool STDCALL OnLButtonUp( const CVec2 &vPos, EMouseState mouseState );
	
	//Public interface
	//add bar
	virtual IUIElement* STDCALL AddBar();
	//add item to the current bar (last added bar). If no bars are added then an error will occured.
	virtual IUIElement* STDCALL AddItem();
	virtual void STDCALL AddMultyItems( int nNum );
	virtual IUIElement* STDCALL AddTextItem( const WORD *pszText );
	//initial update, call this function after all bars and items are added
	virtual void STDCALL InitialUpdate();
	virtual void STDCALL GetSelectionItem( int *pBar, int *pItem );
	virtual void STDCALL SetSelectionItem( int nBar, int nItem );
	virtual bool STDCALL GetBarExpandState( int nBar ) { return bars.size() > nBar ? bars[nBar].bExpandState : false; }
	virtual void STDCALL SetBarExpandState( int nBar, bool bExpand, const bool bNotify = false );
	virtual IUIElement* STDCALL GetBar( int nBar );
	virtual int STDCALL GetNumberOfBars() { return bars.size(); }
	virtual int STDCALL GetNumberOfItems( int nBar );
	virtual IUIElement* STDCALL GetItem( int nBar, int nItem );
	virtual void STDCALL Clear();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CUIShortcutBarBridge : public IUIShortcutBar, public CUIShortcutBar
{
	OBJECT_NORMAL_METHODS( CUIShortcutBarBridge );
	DECLARE_SUPER( CUIShortcutBar );
	DEFINE_UICONTAINER_BRIDGE;
	
	virtual IUIElement* STDCALL AddBar() { return CSuper::AddBar(); }
	virtual IUIElement* STDCALL AddItem() { return CSuper::AddItem(); }
	virtual void STDCALL AddMultyItems( int nNum ) { CSuper::AddMultyItems( nNum ); }
	virtual IUIElement* STDCALL AddTextItem( const WORD *pszText ) { return CSuper::AddTextItem( pszText ); }
	virtual void STDCALL InitialUpdate() { CSuper::InitialUpdate(); }
	virtual void STDCALL GetSelectionItem( int *pBar, int *pItem ) { CSuper::GetSelectionItem( pBar, pItem ); }
	virtual void STDCALL SetSelectionItem( int nBar, int nItem ) { CSuper::SetSelectionItem( nBar, nItem ); }
	virtual bool STDCALL GetBarExpandState( int nBar ) { return CSuper::GetBarExpandState( nBar ); }
	virtual void STDCALL SetBarExpandState( int nBar, bool bExpand, const bool bNotify = false ) { CSuper::SetBarExpandState( nBar, bExpand, bNotify ); }
	virtual IUIElement* STDCALL GetBar( int nBar ) { return CSuper::GetBar( nBar ); }
	virtual int STDCALL GetNumberOfBars() { return CSuper::GetNumberOfBars(); }
	virtual int STDCALL GetNumberOfItems( int nBar ) { return CSuper::GetNumberOfItems( nBar ); }
	virtual IUIElement* STDCALL GetItem( int nBar, int nItem ) { return CSuper::GetItem( nBar, nItem ); }
	virtual void STDCALL Clear() { CSuper::Clear(); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif //__UI_SHORTCUT_BAR_H__
