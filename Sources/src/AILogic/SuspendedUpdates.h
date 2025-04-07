#ifndef __SUSPENDED_UPDATES_H__
#define __SUSPENDED_UPDATES_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "..\Misc\AreaMap.h"
#include "UpdatableObject.h"
#include "AIHashFuncs.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSuspendedUpdates
{
	DECLARE_SERIALIZE;

	// отложенные updates
	// по €чейке - список объектов, которые в ней хран€т updates
	typedef CAreaMap<IUpdatableObj, CPtr<IUpdatableObj>, SVector, int> CObjectsByCells;
	CObjectsByCells objectsByCells;
	// по объекту - updates, которые дл€ него отложены
	std::hash_map< CObj<IUpdatableObj>, std::vector< CPtr<IDataStream> >, SUpdatableObjectObjHash > updates;
	// по объекту - тайлы, при видимости которых нужно послать все отложенные updates
	typedef std::hash_map< int, std::hash_set<SVector, STilesHash > > CTilesMap;
	CTilesMap tilesOfObj;
	
	// объекту - отложенные updates дипломатии
	// предполагаетс€, что таких updates будет немного
	typedef std::hash_map< CObj<IUpdatableObj>, CPtr<IDataStream>, SUpdatableObjectObjHash > CDiplomacyUpdatesType;
	CDiplomacyUpdatesType diplomacyUpdates;

	// дл€ каждого eAction все вспомненные updates
	struct SRecalledUpdate
	{
		virtual int STDCALL operator&( IStructureSaver &ss ) { CSaverAccessor saver = &ss; saver.Add( 1, &pObj ); saver.Add( 3, &pUpdateInfo ); return 0; }
	public:	
		CObj<IUpdatableObj> pObj;
		CPtr<IDataStream> pUpdateInfo;

		SRecalledUpdate() { }
		SRecalledUpdate( IUpdatableObj *_pObj, IDataStream *_pUpdateInfo ) 
			: pObj( _pObj ), pUpdateInfo( _pUpdateInfo ) { }

		void Recall( SSuspendedUpdate *pRecallTo );
	};

	typedef std::list<SRecalledUpdate> CRecalledUpdatesType;
	std::vector<CRecalledUpdatesType> recalledUpdates;

	// тайлы, которые стали видны после очередного сканировани€ тумана
	std::hash_set< SVector, STilesHash > visibleTiles;

	int nMyParty;

	//
	// удалить всЄ, св€занное с pObj, кроме diplomacy updates
	void DeleteObjectInfo( IUpdatableObj *pObj );
	// удал€ет отложенные update дл€ eAction объекта pObj
	void DeleteUpdate( IUpdatableObj *pObj, const EActionNotify &eAction );
	void CommonInit();
	void SuspendUpdate( const EActionNotify &eAction, IUpdatableObj * pObj, const  SSuspendedUpdate &update );
	void UpdateVisibleTiles( const std::hash_set< SVector, STilesHash > &tilesSet, std::hash_set<SVector, STilesHash> *pCoverTiles );
public:
	CSuspendedUpdates();

	void Init( const int nStaticMapSizeX, const int nStaticMapSizeY );
	void Clear();

	// апдейт составного объекта
	void AddComplexObjectUpdate( const EActionNotify &eAction, IUpdatableObj * pObj, const  SSuspendedUpdate &update );
	
	// вызываетс€ при сканировании warfog, когда tile стал виден стороной nParty
	void TileBecameVisible( const SVector &tile, const int nParty );

	// проверить, не нужно ли отложить; если нужно, то запоминает update и возвращает true, иначе - false
	bool CheckToSuspend( const EActionNotify &eAction, IUpdatableObj *pObj, const SSuspendedUpdate &update );

	// есть отложенный update eAction дл€ pObj
	bool DoesExistSuspendedUpdate( IUpdatableObj *pObj, const EActionNotify &eAction );

	// не остались ли recalled updates дл€ этого eActions
	bool IsRecalledEmpty( const EActionNotify &eAction ) const;
	const int GetNRecalled( const EActionNotify &eAction ) const;

	// записать очередной вспомненный update дл€ eAction
	void GetRecalled( const EActionNotify &eAction, SSuspendedUpdate *pUpdate );
	// удалить всЄ, св€занное с pObj, если дл€ pObj есть какие-нибудь updates, кроме diplomacy updates
	void DeleteUpdates( IUpdatableObj *pObj );

	void Segment();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __SUSPENDED_UPDATES_H__
