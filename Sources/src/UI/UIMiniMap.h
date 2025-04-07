#if !defined(__UIMiniMap__)
#define __UIMiniMap__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "..\GFX\GFX.h"
#include "..\GFX\GFXHelper.h"
#include "UIBasic.h"
#include "..\AILogic\AIConsts.h"
#include "..\AILogic\AITypes.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct STextureMarker
{
	CTRect<float> textureRect; //0.0f ... 1.0f
	CTRect<int> screenRect;	//с учетом HotSpot
	CTPoint<int> size;

	//constructors
	STextureMarker()
		: textureRect( 0.0f, 0.0f, 0.0f, 0.0f ), screenRect( 0, 0, 0, 0 ), size( 0, 0 ) {}
	STextureMarker( const CTRect<float> &rTextureRect, const CTRect<int> &rScreenRect, const CTPoint<int> &rSize )
		: textureRect( rTextureRect ), screenRect( rScreenRect ), size( rSize ) {}
	STextureMarker( const STextureMarker &rTextureMarker )
		: textureRect( rTextureMarker.textureRect ), screenRect( rTextureMarker.screenRect ), size( rTextureMarker.size ) {}
	STextureMarker& operator=( const STextureMarker &rTextureMarker )
	{
		if( &rTextureMarker != this )
		{
			textureRect = rTextureMarker.textureRect;
			screenRect = rTextureMarker.screenRect;
			size = rTextureMarker.size;
		}
		return *this;
	}

	// serializing...
	virtual int STDCALL operator&( IDataTree &ss );
	virtual int STDCALL operator&( IStructureSaver &ss );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SMiniMapMarker : public STextureMarker
{
	std::string szName;	//для обратной связи с типом маркера
	CVec2 vPos;					////0.0f ... 1.0f
	bool bActive;				//активна ли данная точка сейчас
	int nID;						//ID маркера
	NTimer::STime timeStart;		//время показывания
	NTimer::STime timeDuration; //продолжительность показывания
	//constructors
	SMiniMapMarker()
		: vPos( VNULL2 ), bActive( false ), nID( -1 ), timeStart( 0 ), timeDuration( 0 ) {}
	SMiniMapMarker( const STextureMarker &rTextureMarker, const std::string &rszName, const CVec2 &vPos, bool _bActive, int _nID, const NTimer::STime &rTimeStart, const NTimer::STime &rTimeDuration )
		: STextureMarker( rTextureMarker ), szName( rszName ), vPos( vPos ), bActive( _bActive ), nID( _nID ), timeStart( rTimeStart ), timeDuration( rTimeDuration ) {}
	SMiniMapMarker( const SMiniMapMarker &rMiniMapMarker )
		: STextureMarker( rMiniMapMarker.textureRect, rMiniMapMarker.screenRect, rMiniMapMarker.size ), szName( rMiniMapMarker.szName ), vPos( rMiniMapMarker.vPos ), bActive( rMiniMapMarker.bActive ), nID( rMiniMapMarker.nID ), timeStart( rMiniMapMarker.timeStart ), timeDuration( rMiniMapMarker.timeDuration ) {}
	SMiniMapMarker& operator=( const SMiniMapMarker &rMiniMapMarker )
	{
		if( &rMiniMapMarker != this )
		{
			textureRect = rMiniMapMarker.textureRect;
			screenRect = rMiniMapMarker.screenRect;
			szName = rMiniMapMarker.szName;
			vPos = rMiniMapMarker.vPos;
			bActive = rMiniMapMarker.bActive;
			nID = rMiniMapMarker.nID;
			timeStart = rMiniMapMarker.timeStart;
			timeDuration = rMiniMapMarker.timeDuration;
		}
		return *this;
	}
	
	virtual int STDCALL operator&( IStructureSaver &ss );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SMiniMapCircle
{
	CVec2 vCenter;
	float fRadius;
	NTimer::STime timeStart;
	NTimer::STime timeDuration;
	int nStyle;
	WORD wColor;
	LPARAM lParam;

	SMiniMapCircle()
		: vCenter( VNULL2 ), fRadius( 0.0f ), timeStart( 0 ), timeDuration( 0 ), nStyle( 0 ), wColor( 0xFFFF ), lParam( 0 ) {}
	SMiniMapCircle( const CVec2 &rvCenter, float _fRadius, const NTimer::STime &rTimeStart, const NTimer::STime &rTimeDuration, int _nStyle, WORD _wColor, LPARAM _lParam )
		: vCenter( rvCenter ), fRadius ( _fRadius ), timeStart( rTimeStart ), timeDuration( rTimeDuration ), nStyle( _nStyle ), wColor( _wColor ), lParam( _lParam ) {}
	SMiniMapCircle(	const SMiniMapCircle &rCircle )
		: vCenter( rCircle.vCenter ), fRadius ( rCircle.fRadius ), timeStart( rCircle.timeStart ), timeDuration( rCircle.timeDuration ), nStyle( rCircle.nStyle ), wColor( rCircle.wColor ), lParam( rCircle.lParam ) {}
	SMiniMapCircle& operator=( const SMiniMapCircle &rCircle )
	{
		if( &rCircle != this )
		{
			vCenter = rCircle.vCenter;
			fRadius = rCircle.fRadius;
			timeStart = rCircle.timeStart;
			timeDuration = rCircle.timeDuration;
			nStyle = rCircle.nStyle;
			wColor = rCircle.wColor;
			lParam = rCircle.lParam;
		}
		return *this;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CMarkPixelFunctional
{
	CTextureLock<SGFXColor4444> *pTextureLock;
	SGFXColor4444 color;
	CTPoint<int> size;
public:
	CMarkPixelFunctional( CTextureLock<SGFXColor4444> *_pTextureLock, SGFXColor4444 _color , const CTPoint<int> &_size )
		: pTextureLock( _pTextureLock ), color( _color ), size( _size ) {}
	void operator()( int nXPos, int nYPos )
	{
		if ( ( nXPos >= 0 ) &&
			   ( nXPos < size.x )&&
			   ( nYPos >= 0 ) &&
			   ( nYPos < size.y ) )
		{
			( *pTextureLock )[size.y - 1 - nYPos][nXPos] = color;
		}
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Вертексы расположены следующим образом:
// в текстуре: ( в AI тайлах ось Y инвертирована)
//0 ---------------- 3
//  |  --------->   |
//  |  |      ось X |
//  |  |            |
//  |  |            |
//  |  V ось Y      |
//1 ---------------- 2
// на экране ( в контроле )
//         0
//        / \
//      /     \
//    /         \
//1 /             \ 3
//  \             /
//    \         /
//      \     /
//        \ /
//         2
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CUIMiniMap : public CSimpleWindow
{
	DECLARE_SERIALIZE;

  const static char MARKERS_TYPES_FILE_NAME[];
  const static char MARKERS_TEXTURE_NAME[];
	const static char MARKERS_TYPES_NAME[];

	//Значения текстуры pWarFog и pWarFogTexture (0 - тайл закрыт, 1 - тайл открыт)
	SGFXColor4444 pWarFogValues[SAIConsts::VIS_POWER + 1];
	//Света юнитов в зависимоста от игрока
	SGFXColor4444 pPartyColors[SAIConsts::MAX_NUM_OF_PLAYERS + 1];
	//Свет рамки экрана
	DWORD dwScreenFrameColor;
	DWORD dwScreenFrameColorShadow;
  //размер MiniMap по горизонтали ( считывается из XML файла )
  //размер MiniMap по вертикали равен nSize / 2
  int nSize;
	int nPlayersCount;
	//Размер крестика отмечающего юнит (0 - точка, 1 - крестик 3x3, 2 - крестик 5x5 ... )
  int nUnitCrossSize;

	//размер боевого поля в VIS тайлах ( берется из AITerrain при инициализации )
  CTPoint<int> terrainSize;
  //количество заполненных VIS тайлов на данный момент
  int nFiledVISTiles;

  //массив AI обьектов ( Заполняется по информации от AILogic )
  std::vector<SMiniMapUnitInfo> units;
  //массив радиусов стрельбы ( Заполняется по информации от AILogic )
  std::vector<SShootAreas> shootAreas;
	//список кругов артиллерии( Заполняется по информации от AILogic )
	std::list<SMiniMapCircle> circles;
	
	//список позиций, обозначаемых флажком
	std::hash_map<std::string, STextureMarker> markersTypes;
	std::list<SMiniMapMarker> markers;

	bool isWarFogNeedUpdate;
	bool isInstantObjectsNeedUpdate;

	//текстура Fog Of War ( Заполняется по информации от AILogic )
  CPtr<IGFXTexture> pWarFog;
	//текстура Fog Of War ( Она непосредственно расположена в видеопамяти и отрисовывается на экран )
  CPtr<IGFXTexture> pWarFogTexture;
	//текстура с юнитами, радиусами обстрелов  т.д. ( Заполняется по информации от AILogic )
  CPtr<IGFXTexture> pInstantObjects;
	//текстура с юнитами, радиусами обстрелов  т.д. ( Она непосредственно расположена в видеопамяти и отрисовывается на экран )
  CPtr<IGFXTexture> pInstantObjectsTexture;
	//текстура Mini Map ( Грузится из ресурсов )
  CPtr<IGFXTexture> pBackgroundTexture;
	//текстура Objective ( Грузится из ресурсов )
  CPtr<IGFXTexture> pMarkerTexture;

  // время предыдущего апдейта ( в единицах игроаого времени )
  //DWORD dwPreviousUpdateTime;
  // таймаут обновления информации об обьектах на MiniMap
  //DWORD dwRefreshTimeout;

	void CreateMiniMapTextures();
	//возврашает координаты нулевой точки в текстурных координатах ( isTopLeft == true - инвертирована ось Y )
  //возврашает координаты нулевой точки в координатах fog of war ( isTopLeft == false )
  void GetZeroPoint( float *pfXZeroPoint, float *pfYZeroPoint, bool isTopLeft = true );
  //возврашает координаты точки в текстурных координатах ( isTopLeft == true - инвертирована ось Y )
  //возврашает координаты точки в координатах fog of war ( isTopLeft == false )
  void PointToTextureMiniMap( float fXPos, float fYPos, float *pfXMiniMapPos, float *pfYMiniMapPos , bool isLeftTop = true );
  //возврашает координаты точки в мировых координатах ( isTopLeft == true - инвертирована ось Y )
  //возврашает координаты точки в мировых координатах ( isTopLeft == false )
	void TextureMiniMapToPoint( float fXMiniMapPos, float fYMiniMapPos, float *pfXPos, float *pfYPos , bool isLeftTop = true );
	//координата Y по точке Х, получаемая через уравнение прямой проходящей через две точки
	float GetYByX( float fX, float fX0, float fY0, float fX1, float fY1 )
	{
		NI_ASSERT_SLOW_T( ( fX1 - fX0 ) != 0,
											NStr::Format( "Devision by zero: (%f)", fX1 - fX0 ) );
		return ( fY1 * ( fX - fX0 ) - fY0 * ( fX - fX1 ) ) / ( fX1 - fX0 );

	}
	//точка X по координате Y, получаемая через уравнение прямой проходящей через две точки
	float GetXByY( float fY, float fX0, float fY0, float fX1, float fY1 )
	{
		NI_ASSERT_SLOW_T( ( fY1 - fY0 ) != 0,
											NStr::Format( "Devision by zero: (%f)", fY1 - fY0 ) );
		return ( fX1 * ( fY - fY0 ) - fX0 * ( fY - fY1 ) ) / ( fY1 - fY0 );
	}
	//Возвращает ребро рамки экрана на miniMap с отрезанными краями, в мировых координатах
	//Последовательность точек, как в ребре 0-1
	void GetVerticalClippedScreenEdge( const CTPoint<float> &v0, const CTPoint<float> &v1, std::vector<CTPoint<float> > *pvPoints );
	//Возвращает ребро рамки экрана на miniMap с отрезанными краями, в мировых координатах
	//Последовательность точек, как в ребре 1-2
	void GetHorizontalClippedScreenEdge( const CTPoint<float> &v1, const CTPoint<float> &v2, std::vector<CTPoint<float> > *pvPoints );
	//Возвращает рамку экрана на miniMap с отрезанными краями, в мировых координатах
	//Требуется перевод в локальные экранные координаты контрола с помошью метода PointToTextureMiniMap()
	void GetClippedScreenFrame( std::vector<CTPoint<float> > *pvPoints, IGFX *pGFX );

	//Условие вызова метода SetScreenSize() если его не вызвать, minimap не будкт отображен
	bool IsInitialized()
  {
    return ( ( terrainSize.x > 0 ) &&
             ( terrainSize.y > 0 ) );
  }

	//Проверка принадлежности точки прямоугольнику minimap
	bool InMiniMap( float fXPos, float fYPos )
	{
		return ( ( fXPos >= 0 ) &&
			       ( fXPos <= terrainSize.x ) &&
				     ( fYPos >=0 ) &&
				     ( fYPos <= terrainSize.y ) );
	}

	//
	void DrawFireRanges( CTextureLock<SGFXColor4444> *pTextureLock );
public:
	CUIMiniMap( )
		: nSize( 0 ), nUnitCrossSize( 1 ), terrainSize( 0, 0 ), nFiledVISTiles( 0 ),  dwScreenFrameColor( 0xFFAFAFAF ), dwScreenFrameColorShadow( 0xFF4F4F4F ), isWarFogNeedUpdate( false ), isInstantObjectsNeedUpdate( false ), nPlayersCount( 2 )
	{
		for ( int nFogValue = 0; nFogValue <= SAIConsts::VIS_POWER; ++nFogValue )
		{
			WORD a = 8 - 8 * nFogValue / SAIConsts::VIS_POWER;
			pWarFogValues[nFogValue] = a << 12;
		}

		//CRAP{ необходимо снаружи инициализировать цвета плееров
		pPartyColors[0] = 0xF0F0;
		pPartyColors[1] = 0xFF00;
		pPartyColors[2] = 0xF00F;
		pPartyColors[3] = 0xFFF0;
		pPartyColors[4] = 0xF0FF;
		pPartyColors[5] = 0xFF0F;
		pPartyColors[6] = 0xFFFF;
		pPartyColors[7] = 0xFF80;
		pPartyColors[8] = 0xFF08;
		pPartyColors[9] = 0xF8F0;
		pPartyColors[10] = 0xF0F8;
		pPartyColors[11] = 0xF80F;
		pPartyColors[12] = 0xF08F;
		pPartyColors[13] = 0xFF88;
		pPartyColors[14] = 0xF8F8;
		pPartyColors[15] = 0xF88F;
		pPartyColors[16] = 0x0000;
		/**
		for ( int index = 2; index <= SAIConsts::MAX_NUM_OF_PLAYERS; ++index )
		{
			pPartyColors[index] = 0x0000;
		}
		/**/
		//}CRAP
	}
	~CUIMiniMap()
	{
	}

	//установить размер поля для получения информации по fog of war, текстуры тумана будут созданы исходя из этих размеров
  //размер в VIS тайлах
  virtual void STDCALL SetTerrainSize( int nXTerrainSize, int nYTerrainSize, int _nPlayersCount );
	//установить текстуру карты
	virtual void STDCALL SetBackgroundTexture( IGFXTexture *_pBackgroundTexture )
	{
		pBackgroundTexture = _pBackgroundTexture;
	}

	//добавить информацию о fog of war, берется от AILogic вызовом метода:
	//если получена последняя порция информации - возвращается true
	//иначе - возвращается false
	virtual bool STDCALL AddWarFogData( const BYTE *pVizBuffer, int nLength );
	//добавить информацию о юнитах, берется от AILogic вызовом метода:
	virtual void STDCALL AddUnitsData( const struct SMiniMapUnitInfo *pUnitsBuffer, int nUnitsCount );
	//добавить информацию об отображаемых радиусах и углах стрельбы
	virtual void STDCALL AddFireRangeAreas( const struct SShootAreas *pShootAreasBuffer, int nShootAreasCount );
	//
	virtual void STDCALL AddCircle( const CVec2 &vCenter, const float fRadius, int nStyle, WORD wColor, const NTimer::STime &rStart, const NTimer::STime &rDuration, bool bRelative, LPARAM lParam );
	virtual int STDCALL AddMarker( const std::string &rszName, const CVec2 &vPos, bool _bActive, int _nID, const NTimer::STime &rStart, const NTimer::STime &rDuration, bool bRelative );
	virtual void STDCALL ActivateMarker( int _nID, bool _bActive );
	virtual void STDCALL ActivateMarker( const std::string &rszName, bool _bActive );
	virtual void STDCALL RemoveMarker( int _nID );
	virtual void STDCALL RemoveMarker( const std::string &rszName );
	
	//from UIControl interface
	// serializing...
	virtual int STDCALL operator&( IDataTree &ss );

//Mouse moving
	virtual bool STDCALL IsInside( const CVec2 &vPos );
	virtual bool STDCALL OnLButtonDown( const CVec2 &vPos, EMouseState mouseState );
	virtual bool STDCALL OnLButtonUp( const CVec2 &vPos, EMouseState mouseState );
	virtual bool STDCALL OnMouseMove( const CVec2 &vPos, EMouseState mouseState );
	virtual bool STDCALL OnRButtonUp( const CVec2 &vPos, EMouseState mouseState );
// update
  virtual bool STDCALL Update( const NTimer::STime &currTime );
// drawing
	virtual void STDCALL Draw( interface IGFX *_pGFX ) = 0;
	virtual void STDCALL Visit( interface ISceneVisitor *pVisitor );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CUIMiniMapBridge : public IUIMiniMap, public CUIMiniMap
{
	OBJECT_NORMAL_METHODS( CUIMiniMapBridge );
	DECLARE_SUPER( CUIMiniMap );
	DEFINE_UIELEMENT_BRIDGE;

  virtual void STDCALL SetTerrainSize( int nXTerrainSize, int nYTerrainSize, int _nPlayersCount ) { CSuper::SetTerrainSize( nXTerrainSize, nYTerrainSize, _nPlayersCount ); }
	virtual void STDCALL SetBackgroundTexture( IGFXTexture *_pBackgroundTexture )  { CSuper::SetBackgroundTexture( _pBackgroundTexture ); }
	virtual bool STDCALL AddWarFogData( const BYTE *pVizBuffer, int nLength ) { return CSuper::AddWarFogData( pVizBuffer, nLength ); }
	virtual void STDCALL AddUnitsData( const struct SMiniMapUnitInfo *pUnitsBuffer, int nUnitsCount )  { CSuper::AddUnitsData( pUnitsBuffer, nUnitsCount ); }
	virtual void STDCALL AddFireRangeAreas( const struct SShootAreas *pShootAreasBuffer, int nShootAreasCount )  { CSuper::AddFireRangeAreas( pShootAreasBuffer, nShootAreasCount ); }
	virtual void STDCALL AddCircle( const CVec2 &vCenter, const float fRadius, int nStyle, WORD wColor, const NTimer::STime &rStart, const NTimer::STime &rDuration, bool bRelative, LPARAM lParam ) { CSuper::AddCircle( vCenter, fRadius, nStyle, wColor, rStart, rDuration, bRelative, lParam ); }
	//
	virtual int STDCALL AddMarker( const std::string &rszName, const CVec2 &vPos, bool _bActive, int _nID, const NTimer::STime &rStart, const NTimer::STime &rDuration, bool bRelative ) { return CSuper::AddMarker( rszName, vPos, _bActive, _nID, rStart, rDuration, bRelative ); }
	virtual void STDCALL ActivateMarker( int _nID, bool _bActive ) { CSuper::ActivateMarker( _nID, _bActive ); }
	virtual void STDCALL ActivateMarker( const std::string &rszName, bool _bActive ) { CSuper::ActivateMarker( rszName, _bActive ); }
	virtual void STDCALL RemoveMarker( int _nID ) { CSuper::RemoveMarker( _nID ); }
	virtual void STDCALL RemoveMarker( const std::string &rszName )  { CSuper::RemoveMarker( rszName ); }
};
#endif //#if !defined(__UIMiniMap__)

