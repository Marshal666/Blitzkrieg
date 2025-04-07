#ifndef __RMG_TYPES_H__
#define __RMG_TYPES_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "..\Formats\FmtMap.h"
#include "WV_Types.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//строковые костанты используемые для работы с xml файлами
extern const char *RMGC_CONTAINER_XML_NAME;
extern const char *RMGC_GRAPH_XML_NAME;
extern const char *RMGC_OBJECTSET_XML_NAME;
extern const char *RMGC_TILESET_XML_NAME;
extern const char *RMGC_TEMPLATE_XML_NAME;
extern const char *RMGC_FIELDSET_XML_NAME;

extern const char *RMGC_ROAD_LEVEL_FILE_NAME;
extern const char *RMGC_RIVER_LEVEL_FILE_NAME;
extern const char *RMGC_RM_LEVEL_VSO_PARAMETER_NAME;
extern const char *RMGC_CONTEXT_NAME;
extern const char *RMGC_SETTING_NAME;
extern const char *RMGC_SETTING_DEFAULT_FOLDER;
extern const char *RMGC_ANY_SETTING_NAME;
extern const char *RMGC_NO_MOD_FOLDER;
extern const char *RMGC_CURRENT_MOD_FOLDER;
extern const char *RMGC_OWN_MOD_FOLDER;

extern const int RMGC_CREATE_RANDOM_MAP_STEP_COUNT;
extern const int RMGC_CREATE_MINIMAP_IMAGE_STEP_COUNT;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef std::set<int> CUsedLinkIDs;
typedef std::set<int> CUsedScriptIDs;
typedef std::set<std::string> CUsedScriptAreas;

struct SRMLevelVSOParameter
{
	std::string szProfileFileName;		//имя профиля ( если пустое, то не поднимаем и не опускаем ничего не делает т.е. )
	float fHeight;										//максимальная высота профиля ( если нулевая, то ничего не происходит ) 
	bool bAdd;												//поднимаем/опускаем
	int nMiddlePointsCount;						//поднимаем/опускаем
	bool bLevelEnds;									//выравниваем концы рек и дорог
	bool bLevelPatches;								//выравнивать патчи

	//constructors
	SRMLevelVSOParameter() : fHeight( 0.0f ), bAdd( true ), nMiddlePointsCount( 0 ), bLevelEnds( false ), bLevelPatches( true )  {}
	SRMLevelVSOParameter( const SRMLevelVSOParameter &rRMLevelVSOParameter ) : szProfileFileName( rRMLevelVSOParameter.szProfileFileName ), fHeight( rRMLevelVSOParameter.fHeight ), bAdd( rRMLevelVSOParameter.bAdd ), nMiddlePointsCount( rRMLevelVSOParameter.nMiddlePointsCount ), bLevelEnds( rRMLevelVSOParameter.bLevelEnds ), bLevelPatches( rRMLevelVSOParameter.bLevelPatches ) {}
	SRMLevelVSOParameter& operator=( const SRMLevelVSOParameter &rRMLevelVSOParameter )
	{
		if( &rRMLevelVSOParameter != this )
		{
			szProfileFileName = rRMLevelVSOParameter.szProfileFileName;
			fHeight = rRMLevelVSOParameter.fHeight;
			bAdd = rRMLevelVSOParameter.bAdd;
			nMiddlePointsCount = rRMLevelVSOParameter.nMiddlePointsCount;
			bLevelEnds = rRMLevelVSOParameter.bLevelEnds;
			bLevelPatches = rRMLevelVSOParameter.bLevelPatches;
		}
		return *this;
	}	

	// serializing...
	virtual int STDCALL operator&( IStructureSaver &ss );
	virtual int STDCALL operator&( IDataTree &ss );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SRMPatch
{
	CTPoint<int> size;														//размер патча в VIS патчах ( 16 на 16 VIS тайлов )
	std::string szFileName;												//имя карты
	std::string szPlace;													//имя местности

	//constructors
	SRMPatch() : size( 0, 0 ) {}
	SRMPatch( const CTPoint<int> &rSize, const std::string &rszFileName, const std::string &rszPlace ) : size( rSize ), szFileName( rszFileName ), szPlace( rszPlace ) {}
	SRMPatch( const SRMPatch &rPatch ) : size( rPatch.size ), szFileName( rPatch.szFileName ), szPlace( rPatch.szPlace ) {} 
	SRMPatch& operator=( const SRMPatch &rPatch )
	{
		if( &rPatch != this )
		{
			size = rPatch.size;
			szFileName = rPatch.szFileName;
			szPlace = rPatch.szPlace;
		}
		return *this;
	}	

	// serializing...
	virtual int STDCALL operator&( IStructureSaver &ss );
	virtual int STDCALL operator&( IDataTree &ss );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef	std::vector<SRMPatch> CRMPatchesList;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SRMContainer
{
	enum ANGLE
	{
		ANGLE_0 = 0,
		ANGLE_90 = 1,
		ANGLE_180 = 2,
		ANGLE_270 = 3,
	};

	enum DIRECTION
	{
		NORTH = 0,
		EAST = 1,
		SOUTH = 2,
		WEST = 3,
	};

	CRMPatchesList patches;												//набор патчей
	std::vector<int> indices[4];									//индексы патчей по каждому из поворотов в предыдущем векторе
	
	//check info
	CTPoint<int> size;														//размер в VIS патчах ( 16 на 16 VIS тайлов )
	int nSeason;																	//сезон
	std::string szSeasonFolder;										//каталог сезона
	CUsedScriptIDs usedScriptIDs;									//используемые scriptIDs
	CUsedScriptAreas usedScriptAreas;							//используемые scriptAreas

	//constructors
	SRMContainer() : size( 0, 0 ), nSeason ( 0 ) {}
	SRMContainer( const SRMContainer &rContainer )
		: patches( rContainer.patches ),
			size( rContainer.size ),
			nSeason( rContainer.nSeason ),
			szSeasonFolder( rContainer.szSeasonFolder),
			usedScriptIDs( rContainer.usedScriptIDs ),
			usedScriptAreas( rContainer.usedScriptAreas )
	{
		for ( int index = 0; index < 4; ++index )
		{
			indices[index] = rContainer.indices[index];
		}
	}
	SRMContainer& operator=( const SRMContainer &rContainer )
	{
		if( &rContainer != this )
		{
			patches = rContainer.patches;
			size = rContainer.size;
			nSeason = rContainer.nSeason;
			szSeasonFolder = rContainer.szSeasonFolder;
			usedScriptIDs = rContainer.usedScriptIDs;
			usedScriptAreas = rContainer.usedScriptAreas;
			
			for ( int index = 0; index < 4; ++index )
			{
				indices[index] = rContainer.indices[index];
			}
		}
		return *this;
	}
	
	// serializing...
	virtual int STDCALL operator&( IStructureSaver &ss );
	virtual int STDCALL operator&( IDataTree &ss );

	int GetIndices( int nDirection, const std::string &rszPlace, std::vector<int> *pIndices ) const;
	int GetSupportedSettings( std::list<std::string> *pSupportedSettingsList ) const;
	bool IsSupportedSetting( const std::string &rszSettingName ) const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef std::hash_map<std::string, SRMContainer > CRMContainersHashMap;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SRMGraphNode
{
	CTRect<int> rect;															//положение в VIS тайлах в AI кординатах (инвертировано относительно terrainY )
	std::string	szContainerFileName;							//путь к контейнеру

	//constructors
	SRMGraphNode() : rect( 0, 0, 0, 0 ) {}
	SRMGraphNode( const SRMGraphNode &rGraphNode ) : rect( rGraphNode.rect ), szContainerFileName( rGraphNode.szContainerFileName ) {}
	SRMGraphNode& operator=( const SRMGraphNode &rGraphNode )
	{
		if( &rGraphNode != this )
		{
			rect = rGraphNode.rect;
			szContainerFileName = rGraphNode.szContainerFileName;
		}
		return *this;
	}

	// serializing...
	virtual int STDCALL operator&( IStructureSaver &ss );
	virtual int STDCALL operator&( IDataTree &ss );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SRMGraphLink
{
	static const int INVALID_LINK_VALUE;
	static const float DEFAULT_RADIUS;
	static const int DEFAULT_PARTS;
	static const float DEFAULT_MIN_LENGTH;
	static const float DEFAULT_DISTANCE;
	static const float DEFAULT_DISTURBANCE;

	enum TYPE
	{
		TYPE_ROAD			= 0,
		TYPE_RIVER		= 1,
	};

	CTPoint<int> link;														//номера нодов (задаются в темплейте)
	int nType;																		//тип VSO (река, дорога)
	std::string szDescFileName;										//имя VSO
	
	float fRadius;																//радиус закругления
	int nParts;																		//число элементов на окрухности
	float fMinLength;															//минимальная дистанция между точками, которая не подвергается дроблению
	float fDistance;															//расстояние от краев до возможного отклонения ( 0...1 )
	float fDisturbance;														//отклонение ( 0...1 )

	//constructors
	SRMGraphLink() : link( INVALID_LINK_VALUE, INVALID_LINK_VALUE ), nType( TYPE_ROAD ), fRadius( DEFAULT_RADIUS ), nParts( DEFAULT_PARTS ), fMinLength( DEFAULT_MIN_LENGTH ), fDistance( DEFAULT_DISTANCE ), fDisturbance( DEFAULT_DISTURBANCE ) {}
	SRMGraphLink( const SRMGraphLink &rGraphLink )
		: link( rGraphLink.link ),
			nType( rGraphLink.nType ),
			szDescFileName( rGraphLink.szDescFileName ),
			fRadius( rGraphLink.fRadius ),
			nParts( rGraphLink.nParts ),
			fMinLength( rGraphLink.fMinLength ),
			fDistance( rGraphLink.fDistance ),
			fDisturbance( rGraphLink.fDisturbance ) {}
	SRMGraphLink& operator=( const SRMGraphLink &rGraphLink )
	{
		if( &rGraphLink != this )
		{
			link = rGraphLink.link;
			nType = rGraphLink.nType;
			szDescFileName = rGraphLink.szDescFileName;
			fRadius = rGraphLink.fRadius;
			nParts = rGraphLink.nParts;
			fMinLength = rGraphLink.fMinLength;
			fDistance = rGraphLink.fDistance;
			fDisturbance = rGraphLink.fDisturbance;
		}
		return *this;
	}

	// serializing...
	virtual int STDCALL operator&( IStructureSaver &ss );
	virtual int STDCALL operator&( IDataTree &ss );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef	std::vector<SRMGraphNode> CRMGraphNodesList;
typedef	std::vector<SRMGraphLink> CRMGraphLinksList;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SRMGraph
{
	CRMGraphNodesList nodes;
	CRMGraphLinksList links;

	//check info
	CTPoint<int> size;														//в размер в VIS патчах ( 16 на 16 VIS тайлов )
	int nSeason;																	//сезон
	std::string szSeasonFolder;										//каталог сезона
	CUsedScriptIDs usedScriptIDs;									//используемые scriptID
	CUsedScriptAreas usedScriptAreas;							//используемые scriptAreas

	//constructors
	SRMGraph() : size( 0, 0 ), nSeason( 0 ) {}
	SRMGraph( const SRMGraph &rGraph )
		: nodes( rGraph.nodes ),
			links( rGraph.links ),
			size( rGraph.size ),
			nSeason( rGraph.nSeason ),
			szSeasonFolder( rGraph.szSeasonFolder ),
			usedScriptIDs( rGraph.usedScriptIDs ),
			usedScriptAreas( rGraph.usedScriptAreas ) {}
	SRMGraph& operator=( const SRMGraph &rGraph )
	{
		if( &rGraph != this )
		{
			nodes = rGraph.nodes;
			links = rGraph.links;
			size = rGraph.size;
			nSeason = rGraph.nSeason;
			szSeasonFolder = rGraph.szSeasonFolder;
			usedScriptIDs = rGraph.usedScriptIDs;
			usedScriptAreas = rGraph.usedScriptAreas;
		}
		return *this;
	}

	// serializing...
	virtual int STDCALL operator&( IStructureSaver &ss );
	virtual int STDCALL operator&( IDataTree &ss );

	int GetSupportedSettings( std::list<std::string> *pSupportedSettingsList ) const;
	bool IsSupportedSetting( const std::string &rszSettingName ) const;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef std::hash_map<std::string, SRMGraph> CRMGraphsHashMap;
typedef	CWeightVector<std::string> CRMGraphWeightVector;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SRMObjectSetShell
{
	TStringWeightVector objects;
	float fWidth;									//VIS tiles
	int nBetweenDistance;					//VIS tiles
	float fRatio;									//(0...1)

	//constructors
	SRMObjectSetShell() : fWidth( 0.0f ), nBetweenDistance( 0 ), fRatio( 0 ) {}
	SRMObjectSetShell( const SRMObjectSetShell &rObjectSetShell ) : objects( rObjectSetShell.objects ), fWidth( rObjectSetShell.fWidth ), nBetweenDistance( rObjectSetShell.nBetweenDistance ), fRatio( rObjectSetShell.fRatio ) {}
	SRMObjectSetShell& operator=( const SRMObjectSetShell &rObjectSetShell )
	{
		if( &rObjectSetShell != this )
		{
			objects = rObjectSetShell.objects;
			fWidth = rObjectSetShell.fWidth;
			nBetweenDistance = rObjectSetShell.nBetweenDistance;
			fRatio = rObjectSetShell.fRatio;
		}
		return *this;
	}

	// serializing...
	virtual int STDCALL operator&( IStructureSaver &ss );
	virtual int STDCALL operator&( IDataTree &ss );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SRMTileSetShell
{
	TIntWeightVector tiles;
	float fWidth;								//VIS tiles

	//constructors
	SRMTileSetShell() : fWidth( 0.0f ) {}
	SRMTileSetShell( const SRMTileSetShell &rTileSetShell ) : tiles( rTileSetShell.tiles ), fWidth( rTileSetShell.fWidth ) {}
	SRMTileSetShell& operator=( const SRMTileSetShell &rTileSetShell )
	{
		if( &rTileSetShell != this )
		{
			tiles = rTileSetShell.tiles;
			fWidth = rTileSetShell.fWidth;
		}
		return *this;
	}
	
	// serializing...
	virtual int STDCALL operator&( IStructureSaver &ss );
	virtual int STDCALL operator&( IDataTree &ss );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef	std::vector<SRMObjectSetShell> CRMObjectSet;
typedef	std::vector<SRMTileSetShell> CRMTileSet;
typedef std::hash_map<std::string, CRMObjectSet> CRMObjectSetHashMap;
typedef std::hash_map<std::string, CRMTileSet> CRMTileSetHashMap;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SRMFieldSet
{
	CRMObjectSet objectsShells;				//деревья
	CRMTileSet tilesShells;						//земля
	
	std::string szProfileFileName;		//имя профиля ( если пустое, то не поднимаем землю )
	float fHeight;										//максимальная высота профиля ( если нулевая, то ничего не происходит ) 
	CTPoint<int> patternSize;					//минимальный - максимальный полуразмер паттерна
	float fPositiveRatio;							// 1 - все поднимаем, 0 - все опускаем
	
	//только для композеров
	int	nSeason;											// сезон (лето/зима/африка :)
	std::string szSeasonFolder;				//каталог сезона
	
	void ValidateFieldSet( const struct STilesetDesc &rTilesetDesc, int nDefaultTileIndex );

	//constructors
	SRMFieldSet() : fHeight( 4.0f ), fPositiveRatio( 0.5f ), patternSize( 2, 5 ), nSeason( 0 ) {}
	SRMFieldSet( const SRMFieldSet &rFieldSet )
		: objectsShells( rFieldSet.objectsShells ),
			tilesShells( rFieldSet.tilesShells ),
			szProfileFileName( rFieldSet.szProfileFileName ),
			fHeight( rFieldSet.fHeight ),
			patternSize( rFieldSet.patternSize ),
			fPositiveRatio( rFieldSet.fPositiveRatio ),
			nSeason( rFieldSet.nSeason ),
			szSeasonFolder( rFieldSet.szSeasonFolder ) {}
	SRMFieldSet& operator=( const SRMFieldSet &rFieldSet )
	{
		if( &rFieldSet != this )
		{
			objectsShells = rFieldSet.objectsShells;
			tilesShells = rFieldSet.tilesShells;
			szProfileFileName = rFieldSet.szProfileFileName;
			fHeight = rFieldSet.fHeight;
			patternSize = rFieldSet.patternSize;
			fPositiveRatio = rFieldSet.fPositiveRatio;
			nSeason = rFieldSet.nSeason;
			szSeasonFolder = rFieldSet.szSeasonFolder;
		}
		return *this;
	}

	// serializing...
	virtual int STDCALL operator&( IStructureSaver &ss );
	virtual int STDCALL operator&( IDataTree &ss );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef std::hash_map<std::string, SRMFieldSet> CRMFieldSetsHashMap;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SRMVSODesc
{
	static const float DEFAULT_WIDTH;
	static const float DEFAULT_OPACITY;

	std::string szVSODescFileName;
	float fWidth;
	float fOpacity;

	//constructors
	SRMVSODesc() : fWidth( DEFAULT_WIDTH ), fOpacity( DEFAULT_OPACITY ) {}
	SRMVSODesc( const SRMVSODesc &rVSODesc ) : szVSODescFileName( rVSODesc.szVSODescFileName ), fWidth( rVSODesc.fWidth ), fOpacity( rVSODesc.fOpacity ) {}
	SRMVSODesc& operator=( const SRMVSODesc &rVSODesc )
	{
		if( &rVSODesc != this )
		{
			szVSODescFileName = rVSODesc.szVSODescFileName;
			fWidth = rVSODesc.fWidth;
			fOpacity = rVSODesc.fOpacity;
		}
		return *this;
	}
	
	// serializing...
	virtual int STDCALL operator&( IStructureSaver &ss );
	virtual int STDCALL operator&( IDataTree &ss );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef CWeightVector<std::string> CRMFieldSetWeightVector;
typedef CWeightVector<SRMVSODesc> CRMVSOWeightVector;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SRMTemplate
{
	CRMFieldSetWeightVector fields;								//информация по заливке пустых пространств
	CRMGraphWeightVector graphs;									//графы расположения патчей и связей между тими
	CRMVSOWeightVector vso;												//промежуточные дороги
		
	//check info
	CTPoint<int> size;														//в размер в VIS патчах ( 16 на 16 VIS тайлов )
	int	nSeason;																	// сезон (лето/зима/африка :)
	std::string szSeasonFolder;										//каталог сезона
	std::string	szPlace;													// зарезервированно
	CUsedScriptIDs usedScriptIDs;									//используемые scriptIDs
	CUsedScriptAreas usedScriptAreas;							//используемые scriptAreas
	
	int nDefaultFieldIndex;												//дефалтовое поле ( по умолчанию 0 )
	
	std::string szScriptFile;											// file with mission's scripts
	CVec3 vCameraAnchor;													// camera start position
	std::vector<BYTE> diplomacies;								// дипломатии, 0, 1 - враждующие стороны, 2 - нейтралы
	SUnitCreationInfo unitCreation;								// для каждого игрока в карте свой набор параметров авиации и других юнитов
	std::string szForestCircleSounds;							// для создания звуков леса
	std::string szForestAmbientSounds;						// для создания звуков леса

	std::string szChapterName;										// имя главы
	int nMissionIndex;														// номер миссии в этой главе
	int nType;																		// тип карты ( смотри CMapInfo )
	int nAttackingSide;														//атакующая сторона ( для малтиплеера ( 0 - 1 ) )

	//MOD Support
	std::string szMODName;
	std::string szMODVersion;


	//constructors
	SRMTemplate() : size( 0, 0 ), nSeason( 0 ), nDefaultFieldIndex( -1 ), vCameraAnchor( VNULL3 ), nMissionIndex( 0 ), nType( 0 ), nAttackingSide( 0 )
	{
		FillDefaultDiplomacies();
	}
	SRMTemplate( const SRMTemplate &rTemplate )
		: fields( rTemplate.fields ),
			graphs( rTemplate.graphs ),
			vso( rTemplate.vso ),
			size( rTemplate.size ),
			nSeason( rTemplate.nSeason ),
			szSeasonFolder( rTemplate.szSeasonFolder ),
			szPlace( rTemplate.szPlace ),
			usedScriptIDs( rTemplate.usedScriptIDs ),
			usedScriptAreas( rTemplate.usedScriptAreas ),
			nDefaultFieldIndex( rTemplate.nDefaultFieldIndex ),
			szScriptFile( rTemplate.szScriptFile ),
			vCameraAnchor( rTemplate.vCameraAnchor ),
			diplomacies( rTemplate.diplomacies ),
			unitCreation( rTemplate.unitCreation ),
			szForestCircleSounds( rTemplate.szForestCircleSounds ),
			szForestAmbientSounds( rTemplate.szForestAmbientSounds ),
			szChapterName( rTemplate.szChapterName ),
			nMissionIndex( rTemplate.nMissionIndex ),
			nType( rTemplate.nType ),
			nAttackingSide( rTemplate.nAttackingSide ),
			szMODName( rTemplate.szMODName ),
			szMODVersion( rTemplate.szMODVersion ) {}

	SRMTemplate& operator=( const SRMTemplate &rTemplate )
	{
		if( &rTemplate != this )
		{
			fields = rTemplate.fields;
			graphs = rTemplate.graphs;
			vso = rTemplate.vso;
			size = rTemplate.size;
			nSeason = rTemplate.nSeason;
			szSeasonFolder = rTemplate.szSeasonFolder;
			szPlace = rTemplate.szPlace;
			usedScriptIDs = rTemplate.usedScriptIDs;
			usedScriptAreas = rTemplate.usedScriptAreas;
			nDefaultFieldIndex = rTemplate.nDefaultFieldIndex;
			szScriptFile = rTemplate.szScriptFile;
			vCameraAnchor = rTemplate.vCameraAnchor;
			diplomacies = rTemplate.diplomacies;
			unitCreation = rTemplate.unitCreation;
			szForestCircleSounds = rTemplate.szForestCircleSounds;
			szForestAmbientSounds = rTemplate.szForestAmbientSounds;
			szChapterName = rTemplate.szChapterName;
			nMissionIndex = rTemplate.nMissionIndex;
			nType = rTemplate.nType;
			nAttackingSide = rTemplate.nAttackingSide;
			szMODName = rTemplate.szMODName;
			szMODVersion = rTemplate.szMODVersion;
		}
		return *this;
	}

	// serializing...
	virtual int STDCALL operator&( IStructureSaver &ss );
	virtual int STDCALL operator&( IDataTree &ss );
	
	void FillDefaultDiplomacies();
	
	//
	int GetSupportedSettings( std::list<std::string> *pSupportedSettingsList ) const;
	bool IsSupportedSetting( const std::string &rszSettingName ) const;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef std::hash_map<std::string, SRMTemplate> CRMTemplatesHashMap;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//для построения дорог
struct SRMPlacedPatch : public SRMPatch
{
	enum EPointSelectionType
	{
		PST_TWO = 0,
		PST_ONE = 1,
		PST_ANY = 2,
		PST_EMPTY = 3,
	};
	
	//структура для поиска дорог
	struct SVSOPoint
	{
		int nID;
		bool bBegin;
		CVec2 vPos;
		std::string szVSODescFileName;

		SVSOPoint() : nID( -1 ), bBegin( true ), vPos( VNULL2 ) {}
		SVSOPoint( const SVSOPoint &rVSOPoint ) : nID( rVSOPoint.nID ), bBegin( rVSOPoint.bBegin ), vPos( rVSOPoint.vPos ), szVSODescFileName( rVSOPoint.szVSODescFileName ) {}
		SVSOPoint& operator=( const SVSOPoint &rVSOPoint )
		{
			if( &rVSOPoint != this )
			{
				nID = rVSOPoint.nID;
				bBegin = rVSOPoint.bBegin;
				vPos = rVSOPoint.vPos;
				szVSODescFileName = rVSOPoint.szVSODescFileName;
			}
			return *this;
		}	
	};

	//общие данные
	CTPoint<int> minXYCorner;						//положение патча в VIS тайлах в AI кординатах (инвертировано относительно terrainY )

	//данные для поиска дорог
	std::list<SVSOPoint> riversPoints;	//точки соединения рек
	std::list<SVSOPoint> roadsPoints;		//точки соединения дорог

	//constructors
	SRMPlacedPatch() : minXYCorner( 0, 0 ) {}
	SRMPlacedPatch( const SRMPatch &rPatch ) : SRMPatch( rPatch ), minXYCorner( 0, 0 ) {}
	SRMPlacedPatch( const SRMPlacedPatch &rPlacedPatch ) : SRMPatch( rPlacedPatch.size, rPlacedPatch.szFileName, rPlacedPatch.szPlace ), minXYCorner( rPlacedPatch.minXYCorner ), riversPoints( rPlacedPatch.riversPoints ), roadsPoints( rPlacedPatch.roadsPoints ) {}
	SRMPatch& operator=( const SRMPlacedPatch &rPlacedPatch )
	{
		if( &rPlacedPatch != this )
		{
			size = rPlacedPatch.size;
			szFileName = rPlacedPatch.szFileName;
			szPlace = rPlacedPatch.szPlace;
			minXYCorner = rPlacedPatch.minXYCorner;
			
			riversPoints = rPlacedPatch.riversPoints;
			roadsPoints = rPlacedPatch.roadsPoints;
		}
		return *this;
	}	

	//рассматриваются все точки
	//чтобы исключить точки их необходимо выкинуть из листов
	static bool GetAndRemoveClosestVSOPoints( int nType,														//дорога - река ( SRMGraphLink::TYPE )
																						SRMPlacedPatch &rStartPlacedPatch,		//начальный патч
																						SRMPlacedPatch &rEndPlacedPatch,			//конечный патч
																						const std::string &rVSODescFileName,	//VSO имя
																						int nPointSelectionType,							//выборка точек см выше EPointSelectionType
																						SVSOPoint *pBeginVSOPoint,						//стартовая точка
																						SVSOPoint *pEndVSOPoint );						//конечная точка
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef	std::vector<SRMPlacedPatch> CRMPlacedPatchesList;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//для построения пустых пространств
class CRMFieldGraph
{
	struct SPatch
	{
		std::vector<bool> marckedVertices;						//посещенные вертексы
		std::vector<CVec2> boundingPolygon;						//см ниже
		CTRect<int> boundingRect;											//прямоугольник, нужен для проведения дополнительных линков
		std::vector<std::vector<int> > linesIndices;	//индексы линий от дорог и рек в массиве lines
		
		// 1(minx, maxy)  2(maxx, maxy)
		// *--------------*
		// |    side 1    |
		// |              |
		// |              |
		// |side 0        |size 2
		// |              |
		// |              |
		// |    side 3    |
		// *--------------*
		// 0(minx, miny) 3(maxx, miny)
		//
		void FillBoundingPolygon( const CTRect<int> &rBoundingRect );
	};
	
	struct SLink
	{
		int nPatchIndex;
		int nSideIndex;
		int nLineIndex;
	};

	struct SLine
	{
		SLink begin;
		SLink end;
		int nID;
		std::list<CVec2> points;
	};

	struct SCaret
	{
		int nPatchIndex;
		int nSideIndex;
		int nLineIndex;
	};

	//входные данные
	std::vector<SPatch> patches;
	std::vector<SLine> lines;
	
	inline static int GetNextVetexIndex( int nVertexIndex ) { return ( ( nVertexIndex >= 3 ) ? 0 : ( nVertexIndex + 1 ) ); }
	inline static int GetPreviousVetexIndex( int nVertexIndex ) { return ( ( nVertexIndex <= 0 ) ? 3 : ( nVertexIndex - 1 ) ); }
	void AddBorderLines( const CTRect<int> &rBoundingRect );
	int IndexLines();
	void UnmarkAllVertices();
	bool FindUnmarkedVertex( int *pPatchIndex, int *pVertexIndex );
	bool GetPolygonAndMarkVertices( int nBeginPatchIndex, int nBeginVertexIndex, std::list<CVec2> *pPolygon, int nMaximumItations );

	public:
	//выходные данные
	std::list<std::list<CVec2> > inclusivePolygons;
	std::list<std::list<CVec2> > exclusivePolygons;
	
	void AddPatch( const CTRect<int> &rBoundingRect );
	void AddLine( const std::list<CVec2> &rPoints, int nID );
	bool ConnectLineToPatch( int nPatchIndex, int nLineIndexLeft, bool bBegin );
	bool FindPolygons( const CTRect<int> &rBoundingRect );

	inline const CVec2& GetPatchMinXYVertex( int nPatchIndex ) { return patches[nPatchIndex].boundingPolygon[0]; }
	inline SPatch& GetPatch( int nPatchIndex ) { return patches[nPatchIndex]; }
	inline SLine& GetLine( int nLineIndex ) { return lines[nLineIndex]; }
	inline int GetLinesCount() { return lines.size(); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef std::hash_map<DWORD, CWeightVector<std::string> > CRMUnitsPlaceHoldersHashMap;
typedef std::hash_map<std::string, CWeightVector<std::string> > CRMUnitsPlaceHoldersMnemonicsHashMap;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SRMTemplateUnitsTable
{
protected:	
	static std::hash_map<DWORD, int> unitRPGTypeToIndex;
	static std::hash_map<std::string, int> unitRPGMnemonicToIndex;
public:
	struct SRandomMissionBonus
	{
		std::string szRPGStats;							// RPG stats name
		int nWeight;												// weight
		//
		int operator&( IDataTree &ss )
		{
			CTreeAccessor saver = &ss;
			saver.Add( "RPGStats", &szRPGStats );
			saver.Add( "Weight", &nWeight );
			return 0;
		}
		int operator&( IStructureSaver &ss )
		{
			CSaverAccessor saver = &ss;
			saver.Add( 1, &szRPGStats );
			saver.Add( 2, &nWeight );
			return 0;
		}
	};
	//
	static const int UNIT_RPG_TYPE_COUNT;
	static const DWORD INVALID_UNIT_RPG_TYPE;
	static const DWORD SQUAD_UNIT_RPG_TYPE;
	static const DWORD UNIT_RPG_TYPES[];
	static const DWORD DEFAULT_LEVELS_COUNT;
	static const std::string UNIT_RPG_MNEMONICS[];

	static int UnitRPGTypeToIndex( DWORD nUnitRPGType );
	static int UnitRPGMnemonicToIndex( const std::string &rszUnitRPGMnenonic );

	static std::string GetUnitRPGMnemonic( DWORD nUnitRPGType );
	static DWORD GetUnitRPGType( const std::string &rszUnitRPGMnenonic );

	std::vector<CRMUnitsPlaceHoldersHashMap> unitPlaceHolders;	// по типам юнитов
	SUnitCreationInfo unitCreationInfo;													// сюда записывается все кроме appear points
	std::vector<SRandomMissionBonus> bonuses;										// random mission bonuses
	//
	const std::string GetRandomBonus() const;
	void GetRandomBonuses( std::vector<std::string> &_bonuses ) const
	{
		_bonuses.clear();
		for ( std::vector<SRandomMissionBonus>::const_iterator it = bonuses.begin(); it != bonuses.end(); ++it )
		{
			for ( int nWeightIndex = 0; nWeightIndex < it->nWeight; ++nWeightIndex )
			{
				_bonuses.push_back( it->szRPGStats );
			}
		}
		std::random_shuffle( _bonuses.begin(), _bonuses.end() );
	}
	
	void GetAllRandomBonuses( std::vector<std::string> &_bonuses ) const
	{
		_bonuses.clear();
		_bonuses.reserve( bonuses.size() );
		for ( std::vector<SRandomMissionBonus>::const_iterator it = bonuses.begin(); it != bonuses.end(); ++it )
		{
			if ( it->nWeight > 0 )
			{
				_bonuses.push_back( it->szRPGStats );
			}
		}
	}
	// serializing...
	virtual int STDCALL operator&( IStructureSaver &ss );
	virtual int STDCALL operator&( IDataTree &ss );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SRMContext
{
	std::vector<SRMTemplateUnitsTable> levels;	//по уровням сложности
	//
	const std::string GetRandomBonus( const int nLevel ) const
	{
		if ( levels.empty() ) 
		{
			return "";
		}
		else if ( nLevel >= levels.size() ) 
		{
			return levels[levels.size() - 1].GetRandomBonus();
		}
		else
		{
			return levels[nLevel].GetRandomBonus();
		}
	}
	//
	void GetRandomBonuses( const int nLevel, std::vector<std::string> &bonuses ) const
	{
		if ( levels.empty() ) 
		{
			bonuses.clear();
		}
		else if ( nLevel >= levels.size() ) 
		{
			levels[levels.size() - 1].GetRandomBonuses( bonuses );
		}
		else
		{
			levels[nLevel].GetRandomBonuses( bonuses );
		}
	}
	//
	void GetAllRandomBonuses( const int nLevel, std::vector<std::string> &bonuses ) const
	{
		if ( levels.empty() ) 
		{
			bonuses.clear();
		}
		else if ( nLevel >= levels.size() ) 
		{
			levels[levels.size() - 1].GetAllRandomBonuses( bonuses );
		}
		else
		{
			levels[nLevel].GetAllRandomBonuses( bonuses );
		}
	}

	//возвращает количество обьектов и обьекты для плеера
	int GetAvailiableUnits( int nPlayer, DWORD nUnitRPGType, std::hash_set<std::string> *pAvailableUnits )
	{
		for ( int nLevelIndex = 0; nLevelIndex < levels.size(); ++nLevelIndex )
		{
			SRMTemplateUnitsTable &rTemplateUnitsTable = levels[nLevelIndex];
			if ( nPlayer < rTemplateUnitsTable.unitPlaceHolders.size() )
			{
				const CWeightVector<std::string>& rAvailiableUnits = rTemplateUnitsTable.unitPlaceHolders[nPlayer][nUnitRPGType];
				for ( int nUnitIndex = 0; nUnitIndex < rAvailiableUnits.size(); ++nUnitIndex )
				{
					pAvailableUnits->insert( rAvailiableUnits[nUnitIndex] );
				}
			}
		}
		return pAvailableUnits->size();
	}

	// serializing...
	virtual int STDCALL operator&( IStructureSaver &ss );
	virtual int STDCALL operator&( IDataTree &ss );
	bool IsValid( int nLevelsCount, int nPlayersCount );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SRMSetting
{
	CRMFieldSetWeightVector fields;							//информация по заливке пустых пространств

	// serializing...
	virtual int STDCALL operator&( IStructureSaver &ss );
	virtual int STDCALL operator&( IDataTree &ss );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SRMUsedTemplateInfo
{
	std::string szTemplateName;
	std::string szGraphName;
	std::string szContextName;
	std::string szSettingName;
	int nGraphAngle;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __RMG_TYPES_H__