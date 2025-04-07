#ifndef __PLANE_PATH_H__
#define __PLANE_PATH_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Path.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************************************
//*													CPlanePath															*
//*******************************************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CPlanePath : public IPath
{
	OBJECT_COMPLETE_METHODS( CPlanePath );
	DECLARE_SERIALIZE;

	CVec2 startPoint, finishPoint;
	float fStartZ;
	float fFinishZ;
public:
	CPlanePath() { }
	CPlanePath( const CVec3 &_startPoint, const CVec2 &_finishPoint ) 
		: startPoint( _startPoint.x,_startPoint.y ), finishPoint( _finishPoint.x, _finishPoint.y ),
			fStartZ( _startPoint.z ), fFinishZ( _startPoint.z ) { }

	CPlanePath( const CVec3 &_startPoint, const CVec3 &_finishPoint ) 
		: startPoint( _startPoint.x,_startPoint.y ), finishPoint( _finishPoint.x, _finishPoint.y ),
			fStartZ( _startPoint.z ), fFinishZ( _finishPoint.z ) { }

	virtual bool IsFinished() const { return false; }

	virtual const CVec2 PeekPoint( int nShift ) { return VNULL2; }
	virtual void Shift( int nShift ) { }

	virtual const CVec2& GetFinishPoint() const { return finishPoint; }
	virtual const CVec2& GetStartPoint() const { return startPoint; }

	virtual void SetFinishZ( const float _fFinishZ ) { fFinishZ = _fFinishZ; }
	virtual void SetStartPoint( const CVec2 &_startPoint ){startPoint = _startPoint;}
	virtual float GetFinishZ() const { return fFinishZ; }
	virtual float GetStartZ() const { return fStartZ; }

	virtual void RecoverState( const CVec2 &point, const SVector &lastKnownGoodTile ) { startPoint = point; }
	virtual void Recalculate( const CVec2 &point, const SVector &lastKnownGoodTile ) { }

	virtual bool CanGoBackward( interface IBasePathUnit *pUnit ) { return false; }
	virtual bool ShouldCheckTurn() const { return false; }
	virtual bool IsWithFormation() const { return false; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CBasePlaneSmoothPath : public ISmoothPath
{
public:
	virtual void SetAviationUnit( IAviationUnit *_pPlane ) {  }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************************************
//*													CPlaneSmoothPath												*
//*******************************************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CPlaneSmoothPath : public CBasePlaneSmoothPath
{
	OBJECT_COMPLETE_METHODS( CPlaneSmoothPath );
	DECLARE_SERIALIZE;

public:

	struct SMemberInfo
	{
		DECLARE_SERIALIZE;
	public:

		CVec2 vWorldPosition;
		WORD wDirection;
		float fCurvatureRadius;
		CVec2 vSpeed;

		NTimer::STime lastMoveTime;
		SMemberInfo() : lastMoveTime( -1 ) {  }
	};


	struct SPathVisitor
	{
		WORD wCurAngle;
		CVec2 vCurPoint;
		SPathVisitor( const CVec2 &vPoint ) : vCurPoint( vPoint ) {  }
		SPathVisitor( const WORD wAngle ) : wCurAngle( wAngle ) {  }
	};
	//
	class CPathFraction : public IRefCount
	{
		DECLARE_SERIALIZE;
		bool bActive;
	public:
		CPathFraction () : bActive( true ) { }
		// return true if the formation offset corresponds this path fraction; in this case vPosition is filled with 
		// world coordinates
		// offset - when it is not first fraction.
		virtual bool CalcPoint( const CVec2 &vFormationOffset/*path coordinates*/, CVec2 * vPosition /*world coordinates*/, WORD *wUnitDir, float *pfCurvatureRadius, CVec2 *pvSpeed, const float fOffset ) const = 0;
		// length in world coordinates, 
		virtual float GetLength() const = 0;
		// if this fraction is being moved by
		bool IsCurrent() const;
		// sets current position
		virtual void SetCurPos( const SPathVisitor &rVisitor ) = 0;
		// mark path as finished
		virtual void SetFinished( const SPathVisitor &rVisitor ) = 0;
		// last segment did'n use this fraction
		void SetActive( const bool _bActive ) { bActive = _bActive; }
		bool IsActive() const { return bActive; }
	};

	// arc path fraction, from angle to angle, 
	class CArcPathFraction : public CPathFraction
	{
		OBJECT_COMPLETE_METHODS( CArcPathFraction );
		DECLARE_SERIALIZE;
		
		CCircle flyCircle;
		WORD wFrom;
		int nAngleSingn;
		float fLenght;

		WORD wCurAngle;
		void CalcLenght();
	public:
		CArcPathFraction() {  }
		// angles - from center
		CArcPathFraction( const CCircle &_flyCircle, const WORD wDirFrom, const int _nAngleSingn );
		
		virtual bool CalcPoint( const CVec2 &vFormationOffset/*path coordinates*/, CVec2 * vPosition /*world coordinates*/, WORD *wUnitDir, float *pfCurvatureRadius, CVec2 *pvSpeed, const float fOffset ) const;
		virtual float GetLength() const { return fLenght; }

		virtual void SetCurPos( const SPathVisitor &rVisitor );
		virtual void SetFinished( const SPathVisitor &rVisitor );
	};

	// line path fraction, from point to point
	class CLinePathFraction : public CPathFraction
	{
		OBJECT_COMPLETE_METHODS( CLinePathFraction );
		DECLARE_SERIALIZE;
		CVec2 vStart;
		CVec2 vCurPoint;

		float fLength;

		void CalcLenght() { fLength = fabs(vCurPoint - vStart); }
	public:
		CLinePathFraction() {  }
		CLinePathFraction( const CVec2 &_vStart )
			: vStart( _vStart ), vCurPoint( _vStart ), fLength( 0 ) {  }

		virtual bool CalcPoint( const CVec2 &vFormationOffset/*path coordinates*/, CVec2 * vPosition /*world coordinates*/, WORD *wUnitDir, float *pfCurvatureRadius, CVec2 *pvSpeed, const float fOffset ) const;
		virtual float GetLength() const { return fLength; }

		virtual void SetCurPos( const SPathVisitor &rVisitor ) { vCurPoint = rVisitor.vCurPoint; CalcLenght(); }
		virtual void SetFinished( const SPathVisitor &rVisitor ) { vCurPoint = rVisitor.vCurPoint; CalcLenght(); }
	};
private:
	bool bTrackHistory;										// true if path history is ti be recorded.
	typedef std::list< CPtr<CPathFraction> > CPathHistory;
	CPathHistory pathHistory;

	enum EHeightState
	{
		HS_HEIGHT_OK,												// horisontal flight

		HS_GAIN_STRAIGHT,										// gain height with constant angle
		HS_GAIN_ESCAPE,											// finishing of gain height
		HS_GAIN_ENTER,											// starting of gain height

		HS_DIVE_STRAIGHT,										// same ...
		HS_DIVE_ENTER,
		HS_DIVE_ESCAPE,
	};
	EHeightState eState;
	NTimer::STime segmentTime;

	CPtr<CPlanePath> pPath;
	interface IBasePathUnit *pUnit;
	interface IAviationUnit *pPlane;

	float fTurnRadiusMax;
	float fTurnRadiusMin;
	
	float fTurnR;
	float fSpeed;
	float fAngleSpeed;
	CVec2 vAngleSpeed;
	CVec2 vCurAngleSpeed;
	bool bGainHeight;											// ������ ��������� ������
	bool bToHorisontal;										// ������ �� �����������/������������
	float fDistanceToChangeHeight;					// ��������� ��� ������ ��������� ������

	CCircle flyCircle;
	CVec2 circePoint;
	short int angleSign;
	WORD startAngle, finishAngle;
	CVec2 dirByLine;

	bool bFinished;
	bool bByCircle;
	
	bool bSmoothTurn; // if true ������ ������� �� � ������ ������
	float fVerTurnRatio;
	
	//
	void CompareWithBest( const CVec2 &p, CVec2 *bestPoint, WORD *wBestAngle, const CCircle &circle, const short int sign );
	// ����� ������ ��������
	void SetTurnRadius( float fTurnRadius );
	float Calc2DDistanceToGo() const;			// ���������, ������� �������� �� �������� ����� (�� �������� �� �������������� ���������)
	static bool IsHeightOK( const IBasePathUnit *pUnit, const IAviationUnit *pPlane, const float fZ, const float fAngleSpeed );
	void FinishPath();
public:

	bool IsInitialized() const { return pPath && pUnit && pPlane; }
	static bool IsHeightOK( const IBasePathUnit *pUnit, const float fZ, const float fAngleSpeed = 0.0f );
	static float CalcCriticalDistance( const CVec2 &vSpeedHorVer, const float _fVerTurnRatio, const float _fTurnRadius );

	virtual void SetAviationUnit( IAviationUnit *_pPlane, IBasePathUnit *_pPathUnit );

	CPlaneSmoothPath() : pUnit( 0 ), pPlane( 0 ), bTrackHistory( false ) { }
	CPlaneSmoothPath( const float fTurnRadiusMin, const float fTurnRadiusMax, const float fSpeed, const float fVerTurnRatio, const bool _bTrackHistory = false );

	virtual bool Init( interface IBasePathUnit *pPathUnit, interface IAviationUnit *pAviationUnit, IPath *pPath, bool bSmoothTurn, bool bCheckTurn = true );
	virtual bool Init( interface IBasePathUnit *pUnit, interface IPath * pPath, bool bSmoothTurn = true, bool bCheckTurn = true );
	virtual bool InitByFormationPath( class CFormation *pFormation, interface IBasePathUnit *pUnit );
	virtual bool Init( interface IMemento *pMemento, interface IBasePathUnit *pUnit );

	virtual const CVec2& GetFinishPoint() const { return pPath->GetFinishPoint(); }

	virtual bool IsFinished() const;
	
	virtual void Stop() { bFinished = true; }

	virtual const CVec3 GetPoint( NTimer::STime timeDiff );
	virtual float& GetSpeedLen() { return fSpeed; }

	virtual void NotifyAboutClosestThreat( interface IBasePathUnit *pUnit, const float fDist ) { }
	virtual void SlowDown() { }

	//
	virtual bool TurnToDir( const WORD &newDir ) { return true; }
	
	virtual bool CanGoBackward() const { return false; }
	virtual bool CanGoForward() const { return true; }
	virtual void GetNextTiles( std::list<SVector> *pTiles ) { }
	virtual CVec2 GetShift( const int nToShift ) const { NI_ASSERT_T( false, "Wrong call" ); return VNULL2; }

	virtual IMemento* GetMemento() const;
	virtual float GetCurvatureRadius() const;
	virtual CVec2 GetCurvatureCenter() const;

	virtual bool IsWithFormation() const { return false; }
	virtual void SetOwner( interface IBasePathUnit *pUnit );
	virtual IBasePathUnit* GetOwner() const;	

		// calsulates world coordinates form formation coordinates
	void CalculateMemberInfo( const CVec2 &vFormationOffset, SMemberInfo *pMemberInfo ) const;
	void ClearUnisedHistory();
};
class CPlanesFormation;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// path for planes, that formation with horisontal shift.
class CPlaneInFormationSmoothPath : public CBasePlaneSmoothPath
{
	OBJECT_COMPLETE_METHODS( CPlaneInFormationSmoothPath );
	DECLARE_SERIALIZE;

	CPlanesFormation * pFormation;
	class CAviation *pOwner;
	
public:
	CPlaneInFormationSmoothPath() : pOwner( 0 ) {  }
	void Init( class CAviation *_pOwner ) ;

	// forward to formation path
	virtual const CVec2& GetFinishPoint() const;
	virtual bool IsFinished() const;
	virtual const CVec3 GetPoint( NTimer::STime timeDiff );
	virtual float& GetSpeedLen();
	virtual float GetCurvatureRadius() const;
	virtual CVec2 GetCurvatureCenter() const;


	// need to correct work of CBasePathUnit
	virtual bool CanGoBackward() const;
	virtual void SetOwner( interface IBasePathUnit *pUnit );
	virtual IBasePathUnit* GetOwner() const;

	// empty functions
	virtual bool Init( interface IBasePathUnit *pUnit, IPath *pPath, bool bSmoothTurn, bool bCheckTurn = true ) { NI_ASSERT_T(false, "wrong call" ); return false; }
	virtual bool Init( interface IMemento *pMemento, interface IBasePathUnit *pUnit ) { NI_ASSERT_T(false, "wrong call" ); return false; }
	virtual bool InitByFormationPath( class CFormation *pFormation, interface IBasePathUnit *pUnit ) { NI_ASSERT_T(false, "wrong call" ); return false; }
	virtual void NotifyAboutClosestThreat( interface IBasePathUnit *pCollUnit, const float fDist ) { NI_ASSERT_T(false, "wrong call" ); }
	virtual void SlowDown() { NI_ASSERT_T(false, "wrong call" ); }
	virtual bool CanGoForward() const { NI_ASSERT_T(false, "wrong call" ); return true; }
	virtual void GetNextTiles( std::list<SVector> *pTiles ) { NI_ASSERT_T(false, "wrong call" ); }
	virtual CVec2 GetShift( const int nToShift ) const { NI_ASSERT_T(false, "wrong call" ); return VNULL2; }
	virtual IMemento* GetMemento() const { NI_ASSERT_T(false, "wrong call" ); return 0; }
	virtual bool IsWithFormation() const { NI_ASSERT_T(false, "wrong call" ); return true; }
	virtual void Stop() { NI_ASSERT_T(false, "wrong call" ); }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __PLANE_PATH_H__