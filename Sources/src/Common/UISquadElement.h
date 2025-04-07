#ifndef __UISQUADELEMENT_H__
#define __UISQUADELEMENT_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "..\UI\UI.h"
#include "MapObject.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CUISquadElement;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** icon update subelement
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SIconDesc
{
	int nType;														// icon type
	CPtr<ISceneIcon> pIcon;								// icon itself
	//
	SIconDesc() {  }
	SIconDesc( const int _nType, ISceneIcon *_pIcon )
		: nType( _nType ), pIcon( _pIcon ) {  }
	//
	int operator&( IStructureSaver &ss )
	{
		CSaverAccessor saver = &ss;
		saver.Add( 1, &nType );
		saver.Add( 2, &pIcon );
		return 0;
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CUIUnitObserver : public CTRefCount<IUnitStateObserver>
{
	OBJECT_SERVICE_METHODS( CUIUnitObserver );
	DECLARE_SERIALIZE;
	//
	float fHP;														// HP of this passanger
	std::list<SIconDesc> icons;						// icons of this passanger
	CPtr<CUISquadElement> pSquad;					// squad to report about unit changes
	CPtr<IMOUnit> pMOUnit;                // corresponding map object
public:
	CUIUnitObserver() : fHP( 0 ) {  }
	CUIUnitObserver( IMOUnit *_pMOUnit ) : fHP( 0 ) { pMOUnit = _pMOUnit; }
	//
	virtual void STDCALL AddIcon( const int nType, interface ISceneIcon *pIcon );
	virtual void STDCALL RemoveIcon( const int nType );
	virtual void STDCALL UpdateHP( const float fValue );
	virtual void STDCALL RemoveUnit();
	virtual IMOUnit* STDCALL GetMOUnit() { return pMOUnit; }
	//
	void SetSquad( CUISquadElement *_pSquad ) { pSquad = _pSquad; }
	//
	const std::list<SIconDesc>& GetIcons() const { return icons; }
	const float GetHP() const { return fHP; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** squad UI element (who-in-container interface)
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CUISquadElement : public CTRefCount<IUIElement>
{
	OBJECT_SERVICE_METHODS( CUISquadElement );
	DECLARE_SERIALIZE;
	//
	CTRect<float> rcWindow;							// координаты окошка относительно экрана
	int nPositionFlag;									// задает точку привязки
	CVec2 vPos;													// координаты левой верхней точки окошка относительно выбранной точки привязки
	CVec2 vSize;												// размеры окошка

	int nID;														// уникальный идентификатор окошка
	CPtr<IUIContainer> pParent;					// родитель
	bool bWindowActive;									// активно ли окно				//??
	int nCmdShow;												// статус обображения окна
	bool bSelected;											// is this squad selected inside the container?
	//
	typedef std::list< CObj<CUIUnitObserver> > CPassangersList;
	CPassangersList passangers;					// container passangers
	CPtr<IGFXTexture> pSquadIcon;				// general squad icon
public:	
	CUISquadElement();
	// serializing...
	virtual int STDCALL operator&( IDataTree &ss );

	// update
	virtual bool STDCALL Update( const NTimer::STime &currTime );
	virtual void STDCALL Reposition( const CTRect<float> &rcParent );

	// drawing
	virtual void STDCALL Draw( interface IGFX *pGFX );
	virtual void STDCALL Visit( interface ISceneVisitor *pVisitor );

	// CRAP{
	virtual void STDCALL SetWindowTexture( IGFXTexture *pTexture );
	virtual IGFXTexture* STDCALL GetWindowTexture() { return 0; }
	virtual void STDCALL SetWindowMap( const CTRect<float> &maps );
	virtual void STDCALL SetWindowPlacement( const CVec2 *vPos, const CVec2 *vSize );
	virtual void STDCALL SetWindowID( int nID );
	virtual void STDCALL SetBoundRect( const CTRect<float> &rc );
	// CRAP}

	// cursor and actions
	virtual bool STDCALL OnLButtonDblClk( const CVec2 &vPos );
	virtual bool STDCALL OnMouseMove( const CVec2 &vPos, EMouseState mouseState );
	virtual bool STDCALL OnLButtonDown( const CVec2 &vPos, EMouseState mouseState );
	virtual bool STDCALL OnLButtonUp( const CVec2 &vPos, EMouseState mouseState );
	virtual bool STDCALL OnRButtonDown( const CVec2 &vPos, EMouseState mouseState );
	virtual bool STDCALL OnRButtonUp( const CVec2 &vPos, EMouseState mouseState );
	virtual bool STDCALL OnMouseWheel( const CVec2 &vPos, EMouseState mouseState, float fDelta );
	virtual bool STDCALL IsInside( const CVec2 &vPos );
	virtual bool STDCALL OnChar( int nAsciiCode, int nVirtualKey, bool bPressed, DWORD keyState );
	virtual void STDCALL SetParent( interface IUIContainer *pParent );
	virtual IUIContainer* STDCALL GetParent();
	virtual bool STDCALL IsModal() const { return false; }


	// text functions
	virtual void STDCALL SetWindowText( int nState, const WORD *pszText );
	virtual const WORD* STDCALL GetWindowText( int nState );
	virtual void STDCALL SetTextColor( DWORD dwColor );

	// tool tip functions
	virtual interface IText* STDCALL GetHelpContext( const CVec2 &vPos, CTRect<float> *pRect );
	virtual void STDCALL SetHelpContext( int nState, const WORD *pszToolTipText );
	
	// state
	virtual void STDCALL SetFocus( bool bFocus );
	virtual void STDCALL EnableWindow( bool bEnable );
	virtual bool STDCALL IsWindowEnabled();
	virtual void STDCALL SetState( int nState, bool bNotify );
	virtual int  STDCALL GetState();
	virtual bool STDCALL IsVisible();
	virtual int  STDCALL GetVisibleState();
	virtual void STDCALL ShowWindow( int nCmdShow );
	virtual int STDCALL  GetWindowID();

	//return position flags
	virtual int STDCALL GetWindowPlacement( CVec2 *pPos, CVec2 *pSize, CTRect<float> *pScreenRect );
	virtual int STDCALL GetPositionFlag();

	// msg processing
	virtual bool STDCALL ProcessMessage( const SUIMessage &msg );
	//pick the element over screen coordinates, nRecursion is a number of recursion function calls
	virtual IUIElement* STDCALL PickElement( const CVec2 &vPos, int nRecursion );
	//get manipulator for editor functionality
	virtual IManipulator* STDCALL GetManipulator();
	virtual void STDCALL GetTextSize( const int nState, int *pSizeX, int *pSizeY ) const {  }

	//
	//
	//
	virtual void STDCALL AddPassanger( IUnitStateObserver *pObserver );
	virtual void STDCALL RemovePassanger( IUnitStateObserver *pObserver );
	virtual int STDCALL GetPassangerCount();
	//
	virtual void STDCALL SetSquadIcon( IGFXTexture *pTexSquadIcon ) { pSquadIcon = pTexSquadIcon; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** icons visitor
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CIconsVisitor : public ISceneVisitor
{
	// refcounting
	virtual void STDCALL AddRef( int nRef = 1, int nMask = 0x7fffffff ) {  }
	virtual void STDCALL Release( int nRef = 1, int nMask = 0x7fffffff ) {  }
	virtual bool STDCALL IsValid() const { return true; }
public:
	const SSpriteInfo *pInfo;
	//
	CIconsVisitor() : pInfo( 0 ) {  }
	// billboard sprite object
	void STDCALL VisitSprite( const SBasicSpriteInfo *pObj, int nType, int nPriority )
	{
		pInfo = static_cast<const SSpriteInfo*>( pObj );
	}
	// mesh object
	void STDCALL VisitMeshObject( interface IMeshVisObj *pObj, int nType, int nPriority ) {  }
	// particles
	void STDCALL VisitParticles( interface IParticleSource *pObj ) {  }
	// unknown scene object
	void STDCALL VisitSceneObject( interface ISceneObject *pObj ) {  }
	// text object
	void STDCALL VisitText( const CVec3 &vPos, const char *pszText, interface IGFXFont *pFont, DWORD color ) {  }
	// bold line object
	void STDCALL VisitBoldLine( CVec3 *corners, float fWidth, DWORD color ) {  }
	//
	void Clear() { pInfo = 0; }
	// empty
	void STDCALL VisitMechTrace( const SMechTrace &trace ) {  };
	void STDCALL VisitGunTrace( const SGunTrace &trace ) {  };
	// UI elements visiting
	void STDCALL VisitUIRects( interface IGFXTexture *pTexture, const int nShadingEffect, struct SGFXRect2 *rects, const int nNumRects ) {  }
	void STDCALL VisitUIText( interface IGFXText *pText, const CTRect<float> &rcRect, const int nY, const DWORD dwColor, const DWORD dwFlags ) {  }
	void STDCALL VisitUICustom( interface IUIElement *pElement ) {  }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __UISQUADELEMENT_H__
