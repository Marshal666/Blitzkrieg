#ifndef __TRAIN_PATH_H__
#define __TRAIN_PATH_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Path.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CEdgePoint;
interface IEdge;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SPathEdge
{
	DECLARE_SERIALIZE;
public:
	CPtr<CEdgePoint> pFirstPoint;
	CPtr<CEdgePoint> pLastPoint;

	SPathEdge() { }
	SPathEdge( CEdgePoint *_pFirstPoint, CEdgePoint *_pLastPoint ) : pFirstPoint( _pFirstPoint ), pLastPoint( _pLastPoint ) { }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CTrainPath : public IStaticPath
{
	OBJECT_COMPLETE_METHODS( CTrainPath );
	DECLARE_SERIALIZE;

	std::list<SPathEdge> edges;

	CVec2 vStartPoint;
	CVec2 vFinishPoint;

	// 
public:
	CTrainPath() { }
	CTrainPath( interface IStaticPathFinder *pPathFinder, class CTrainPathUnit *pTrain );

	virtual const SVector GetStartTile() const;
	virtual const SVector GetFinishTile() const;
	virtual const CVec2& GetFinishPoint() const;

	virtual const int GetLength() const { return edges.size(); }
	virtual void MoveFinishPointBy( const CVec2 &vMove ) { }

	std::list< SPathEdge >::iterator GetStartEdgeIter() { return edges.begin(); }	
	std::list< SPathEdge >::iterator GetEndEdgesIter() { return edges.end(); }	
	CEdgePoint* GetFirstPoint( std::list< SPathEdge >::iterator iter );
	CEdgePoint* GetLastPoint( std::list< SPathEdge >::iterator iter );

	const CVec2 GetStartPoint() const { return vStartPoint; }
	// направление начала движения
	const CVec2 GetDirToGo();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CTrainSmoothPath : public ISmoothPath
{
	OBJECT_COMPLETE_METHODS( CTrainSmoothPath );
	DECLARE_SERIALIZE;

	CTrainPathUnit *pOwner;
	CPtr<CTrainPath> pTrainPath;
	NTimer::STime lastUpdateTime;
	float fSpeed;
	bool bFinished;

	struct SPathPoint
	{
		DECLARE_SERIALIZE; 
	public:
		std::list< SPathEdge >::iterator iter;
		CPtr<CEdgePoint> pPoint;
	};

	struct SCarriagePos
	{
		DECLARE_SERIALIZE;
	public:
		SPathPoint frontWheel;
		SPathPoint backWheel;
	};

	std::vector<SCarriagePos> carriages;
	int nRecalculating;

	bool bRecalculatedPath;
	CVec2 vRealFinishPoint;

	// для saver/load
	int iteratorShift;
	bool bJustLoaded;

	//
	void InitTrain();
	// передвинуть переднее колесо вагона n на расстояние fDist
	void MoveFrontWheel( const int n, float const fDist );

	void CheckPath();
	void DelSharpAngles();
	void LoadIterators();
	void FinishPath();
public:
	CTrainSmoothPath() : bJustLoaded( false ), fSpeed( 0 ), lastUpdateTime( 0 ), bFinished( true ), nRecalculating( 0 ), bRecalculatedPath( false ) { }

	bool Init( IStaticPath *pTrainPath );

	virtual bool Init( interface IBasePathUnit *pUnit, IPath *pPath, bool bSmoothTurn, bool bCheckTurn = true );
	virtual bool Init( interface IMemento *pMemento, interface IBasePathUnit *pUnit );
	virtual bool InitByFormationPath( class CFormation *pFormation, interface IBasePathUnit *pUnit );

	virtual const CVec2& GetFinishPoint() const { return pTrainPath->GetFinishPoint(); }

	virtual bool IsFinished() const;
	
	virtual void Stop() { }

	virtual const CVec3 GetPoint( NTimer::STime timeDiff );
	virtual float& GetSpeedLen();

	virtual void NotifyAboutClosestThreat( interface IBasePathUnit *pCollUnit, const float fDist );
	virtual void SlowDown() { }

	virtual bool CanGoBackward() const { return false; }
	virtual bool CanGoForward() const { return true; }
	virtual void GetNextTiles( std::list<SVector> *pTiles ) { pTiles->clear(); }
	// погрешность до SAIConsts::SPLINE_STEP, используется в основном для формации
	virtual CVec2 GetShift( const int nToShift ) const { return VNULL2; }
	
	virtual IMemento* GetMemento() const;
	//radius of curvance. positive if rotation in positive direction, negative otherwise
	virtual float GetCurvatureRadius() const { return 0.0f; }
	virtual CVec2 GetCurvatureCenter() const { return CVec2( float(1e15), float(1e15) ); }
	
	virtual bool IsWithFormation() const { return false; }

	virtual void GetSpeed3( CVec3 *vSpeed ) const
	{
	//CRAP{ пока Виталик в своих путях не станет вычислать скорость
	*vSpeed = VNULL3;
	//CRAP}
	}

	CEdgePoint* GetBackWheelPoint( const int n ) const;
	CEdgePoint* GetFrontWheelPoint( const int n ) const;

	void SetNewFrontWheel( const int n, CEdgePoint *pNewPoint );
	void SetNewBackWheel( const int n, CEdgePoint *pNewPoint );

	// для save/load
	virtual void SetOwner( interface IBasePathUnit *pUnit );
	virtual IBasePathUnit* GetOwner() const;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CTrainSmoothPathMemento : public IMemento
{
	OBJECT_COMPLETE_METHODS( CTrainSmoothPathMemento );
	DECLARE_SERIALIZE;
public:
	CPtr<CTrainPath> pPath;

	CTrainSmoothPathMemento() { }
	CTrainSmoothPathMemento( CTrainPath *pPath );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __TRAIN_PATH_H__
