#ifndef __PATH_UNIT_H__
#define __PATH_UNIT_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "..\Common\Actions.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
interface IStaticPathFinder;
interface ISmoothPath;
interface ICollision;
interface IMemento;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CPathUnit : public IRefCount
{
	DECLARE_SERIALIZE;
	
	CPtr<IStaticPathFinder> pPathFinder;
	
	CObj<ICollision> pCurCollision;
	
	CPtr<IMemento> pPathMemento;
	CObj<ICollision> pCollMemento;
	CPtr<CPathUnit> pLastPushByHardCollUnit;

	// "верное направление", т.е. куда "смотрит" перёд
	SAINotifyPlacement placement;
	SVector curTile;
	// вектор вдоль направления движения
	CVec2 dirVec;
	// правильное направление или движемся задом
	bool bRightDir;

	bool bLocking;
	// поворачивается ли в данный момент
	bool bTurning;
	// если поворачивается, то к какому направлению движения
	WORD desDir;
	bool bFoolStop;
	bool bFixUnlock;
	WORD wDirAtBeginning;
	
	bool bOnLockedTiles;
	NTimer::STime checkOnLockedTime;

	int nCollisions;
	NTimer::STime collStayTime;

	CVec2 vSuspendedPoint;
	bool bTurnCalled;
	SVector lastKnownGoodTile;

	bool bIdle;
	NTimer::STime nextSecondPathSegmTime;

	//
	const CVec2 GetCenterShift() const;
	// выбрать, как поворачиваться - чтобы оказаться задом по направлению к движению или передом
	void ChooseDirToTurn( const WORD &newDir );
	// повернуться, когда уже известно, в какую сторону
	bool MakeTurnToDir( const WORD newDir );

	bool CanMake180DegreesTurn( SRect rect );
protected:
	class CAIUnit *pOwner;
	CVec2 speed;
	NTimer::STime stayTime;

	void CalculateIdle();
public:
	CPathUnit() : pOwner( 0 ) { }
	virtual void Init( class CAIUnit *pOwner, const CVec2 &center, const int z, const WORD dir, const WORD id );

	// ставит направление движения. false - ехать задом
	virtual void SetRightDir( bool bRightDir );
	virtual bool GetRightDir() const { return bRightDir; }
	//
	virtual void GetPlacement(  struct SAINotifyPlacement *pPlacement, const NTimer::STime timeDiff ) const;
	virtual void GetSpeed3( CVec3 *pSpeed ) const ;
	virtual const float GetZ() const { return placement.z; }

	virtual void FirstSegment();
	virtual void SecondSegment( const bool bUpdate = true );
	// возвращает - поехал или нет
	virtual bool SendAlongPath( interface IStaticPath *pStaticPath, const CVec2 &vShift, bool bSmoothTurn = true );
	virtual bool SendAlongPath( interface IPath *pPath );

	bool CanGoByDir( const CVec2 &dir, const SRect &forceRect, SRect bannedRect, CVec2 forceSpeed, int *numIntersect, float *distance, int *nBadness );
	interface IPath* CreatePathByDirection( const CVec2 &startPoint, const CVec2 &dir, const CVec2 &finishPoint );
	
	bool IsStopped() const;

	virtual const CVec2& GetCenter() const { return placement.center; }
	virtual const float GetRotateSpeed() const;
	const SVector GetTile() const { return curTile; }
	virtual const CVec2& GetSpeed() const { return speed; }
	virtual const float GetSpeedLen() const ;
	virtual const float GetMaxPossibleSpeed() const;
	virtual const int GetBoundTileRadius() const;
	virtual interface ISmoothPath* GetCurPath() const { return GetSmoothPath(); }

	interface ICollision* GetCollision() const { return pCurCollision; }
	void SetCollision( ICollision *pCollision );

	// выдаются направления движения
	virtual const CVec2& GetDirVector() const ;
	virtual const WORD GetDir() const;
	// направление переда
	virtual const WORD GetFrontDir() const { return placement.dir; }

	// направление, куда смотрит перед
	const CVec2 GetFrontDirVec() const { if ( bRightDir ) return dirVec; else return -dirVec; }
	
	//bCanBackward - может повернуться либо задом либо передом, на свой выбор
	//bForward - поворачиваться передом
	virtual bool TurnToDir( const WORD &newDir, const bool bCanBackward = true, const bool bForward = true );
	
	virtual interface IStaticPathFinder* GetPathFinder() const { return pPathFinder; }

	virtual void StopUnit();
	virtual void StopTurning();
	virtual void ForceGoByRightDir() { bRightDir = true; }
	void UnsetDirUpdate() { wDirAtBeginning = GetDir(); }
	const WORD GetDirAtTheBeginning() const { return wDirAtBeginning; }
	virtual bool IsIdle() const;
	bool IsTurning() const { return bTurning; }
	bool IsLockingTiles() const { return bLocking; }

	virtual void LockTiles( bool bUpdate = true );
	void ForceLockingTiles( bool bUpdate = true );

	// локает в любом случае, если это в принципе возможно
	void LockTilesForEditor();
	// bUpdate - делать ли update maxes при unlock
	virtual void UnlockTiles( const bool bUpdate );
	void FixUnlocking() { bFixUnlock = true; }
	void UnfixUnlocking() { bFixUnlock = false; }

	virtual const CVec2 GetAABBHalfSize() const;

	const SRect GetUnitRect() const;
	virtual const SRect GetUnitRectForLock() const;
	const SRect GetFullSpeedRect( bool bForInfantry ) const;
	const SRect GetSpeedRect( bool bForInfantry ) const;
	const SRect GetSmallRect() const;

	//
	bool CanShootUnit( const CPathUnit *pTarget ) const;
	bool TooClose( const CPathUnit *pTarget ) const;

	virtual void SetNewCoordinates( const CVec3 &newCenter, bool bStopUnit = true );
	virtual void SetNewCoordinatesForEditor( const CVec3 &newCenter ) { SetNewCoordinates( newCenter ); }
	virtual void SetCoordWOUpdate( const CVec3 &newCenter );
	virtual void SetFrontDirWOUpdate( const WORD newDir );
	bool CanSetNewCoord( const CVec3 &newCenter );

	// проапдейдить направление по новому направлению движения
	void UpdateDirection( const WORD newDir );
	void UpdateDirection( const CVec2 &dirVec );
	virtual void UpdateDirectionForEditor( const CVec2 &dirVec );
	bool CanSetNewDir( const CVec2 &newDir );

	//
	bool CanLockTiles( bool bForceLocking = false ) const;
	bool CanUnlockTiles() const;
	
	virtual bool CanTurnToFrontDir( const WORD wDir );

	//
	const SUnitBaseRPGStats* GetStats() const;
	class CAIUnit* GetOwner() const { return pOwner; }
	virtual BYTE GetAIClass() const;
	int GetID() const;	

	void IncNCollisions() { ++nCollisions; }
	const int GetNCollisions() const { return nCollisions; }
	void NullCollisions() { nCollisions = 0; }

	void SetLastPushByHardCollUnit( class CPathUnit *pUnit ) { pLastPushByHardCollUnit = pUnit; }
	CPathUnit* GetLastPushByHardCollUnit() const { return pLastPushByHardCollUnit; }
	const NTimer::STime GetStayTime() const { return stayTime; }
	
	void NullCollStayTime() { collStayTime = 0; }
	void UpdateCollStayTime( const NTimer::STime candStayTime );
	const NTimer::STime GetCollStayTime() const { return collStayTime; }
	
	// можно ли повернуть к направлению vNewDir, если за bounding box берётся smallRect
	bool CanRotateTo( SRect smallRect, const CVec2 &vNewDir, bool bWithUnits, bool bCanGoBackward = true );
	void SetSuspendedPoint( const CVec2 &vPoint ) { vSuspendedPoint = vPoint; }
	bool HasSuspendedPoint() const { return vSuspendedPoint.x != -1.0f; }
	// проверяет, можно ли повернуться к wNewDir, 
	// если нельзя - возвращает false и посылает вдоль пути до точки, где можно сделать полный поворот, если такай точка найдена
	virtual bool CheckToTurn( const WORD wNewDir );

	// разрушение объектов, на которые наехали
	void CheckForDestroyedObjects( const CVec2 &center ) const;
	virtual IStaticPath* CreateBigStaticPath( const CVec2 &vStartPoint, const CVec2 &vFinishPoint, interface IPointChecking *pPointChecking );

	virtual ISmoothPath* GetSmoothPath() const = 0;
	virtual void SetCurPath( interface ISmoothPath *pNewPath ) = 0;
	virtual void RestoreDefaultPath() = 0;

	virtual bool IsInOneTrain( interface IBasePathUnit *pUnit ) const;
	virtual bool CanMove() const { return true; }
	virtual bool CanRotate() const;
	
	virtual const SVector GetLastKnownGoodTile() const;

	// for restore default aviation path
	virtual void InitAviationPath( const SMechUnitRPGStats* pStats ) { NI_ASSERT_T(false, "wrong call"); }
	
	virtual void TrackDamagedState( const bool bTrackDamaged ) { }

	const NTimer::STime GetNextSecondPathSegmTime() const { return nextSecondPathSegmTime; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSimplePathUnit : public CPathUnit
{
	OBJECT_COMPLETE_METHODS( CSimplePathUnit );
	DECLARE_SERIALIZE;

	CPtr<ISmoothPath> pSmoothPath;
	CPtr<ISmoothPath> pDefaultPath; //for temprorary storage of default smooth path
public:
	CSimplePathUnit() { }

	virtual void Init( class CAIUnit *pOwner, const CVec2 &center, const int z, const WORD dir, const WORD id );

	virtual void InitAviationPath( const SMechUnitRPGStats* pStats );

	virtual ISmoothPath* GetSmoothPath() const;
	virtual void SetCurPath( interface ISmoothPath *pNewPath );
	virtual void RestoreDefaultPath();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __PATH_UNIT_H__
