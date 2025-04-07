#ifndef __TURRET_H__
#define __TURRET_H__

#pragma ONCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "UpdatableObject.h"
#include "LinkObject.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAIUnit;
class CBasicGun;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CTurret : public CLinkObject
{
	DECLARE_SERIALIZE;

	struct SRotating
	{
		// скорость вращения в горизонтальной плоскости
		float wRotationSpeed;
		// угол относ. юнита в момент начала поворота, желательный угол
		WORD wCurAngle, wFinalAngle;
		// в какую сторону поворачивается - + или -
		signed char sign;

		// время, когда начался и закончится процесс поворачивания
		NTimer::STime startTime, endTime;
		
		// поворот закончен
		bool bFinished;
	};

	// горизонтальная наводка
	SRotating hor;
	// вертикальная наводка
	SRotating ver;

	// можно ли вернуть башню к default углу поворота
	bool bCanReturn;

	// наводится ли по вертикали
	bool bVerAiming;

	CPtr<CAIUnit> pTracedUnit;
	CPtr<CBasicGun> pLockingGun;

	WORD wDefaultHorAngle;
	bool bReturnToNULLVerAngle;

	//
	WORD GetCurAngle( const SRotating &rotateInfo ) const;
	void SetTurnParameters( SRotating *pRotateInfo, const WORD wAngle, const bool bInstantly );
	WORD ConstraintAngle( const WORD wDesAngle, const WORD wTurnConstraint ) const;
public:
	CTurret() { }
	CTurret( const WORD wHorRotationSpeed, const WORD wVerRotationSpeed, bool bReturnToNULLVerAngle );
	
	const float GetHorRotationSpeed() const { return hor.wRotationSpeed; }
	
	virtual void Turn( const WORD wHorAngle, const WORD wVerAngle, const bool bInstantly = false );
	// возвращает - был произведён поворот, или turret уже в нужном положении
	virtual bool TurnHor( const WORD wHorAngle, const bool bInstantly = false );
	// возвращает - был произведён поворот, или turret уже в нужном положении
	virtual bool TurnVer( const WORD wVerAngle, const bool bInstantly = false );

	void StopTurning();
	void StopHorTurning();
	void StopVerTurning();
	// закончен ли поворот
	bool IsFinished() const { return hor.bFinished && ver.bFinished; }
	bool IsHorFinished() const { return hor.bFinished; }
	bool IsVerFinished() const { return ver.bFinished; }
	// можно вернуть пушку к нулевому углу поворота
	void SetCanReturn();

	WORD GetHorCurAngle() const { return GetCurAngle( hor ); }
	WORD GetVerCurAngle() const { return GetCurAngle( ver ); }

	WORD GetHorFinalAngle() const { return hor.wFinalAngle; }
	WORD GetVerFinalAngle() const { return ver.wFinalAngle; }
	
	const NTimer::STime& GetHorEndTime() const { return hor.endTime; }
	const NTimer::STime& GetVerEndTime() const { return ver.endTime; }
	const NTimer::STime GetEndTurnTime() const { return Max( GetHorEndTime(), GetVerEndTime() ); }

	void Segment();

	// сопровождать пушкой врага
	void TraceAim( class CAIUnit *pUnit, class CBasicGun *pGun );
	class CAIUnit* GetTracedUnit() { return pTracedUnit; }
	void StopTracing();
	
	const float GetHorRotateSpeed() const { return hor.wRotationSpeed; }
	const float GetVerRotateSpeed() const { return ver.wRotationSpeed; }

	bool DoesRotateVert() const { return ver.wRotationSpeed != 0; }

	virtual CVec2 GetOwnerCenter() = 0;
	virtual WORD GetOwnerFrontDir() = 0;
	virtual float GetOwnerZ() = 0;
	virtual const int GetOwnerParty() const = 0;

	virtual WORD GetHorTurnConstraint() const = 0;
	virtual WORD GetVerTurnConstraint() const = 0;

	virtual void GetHorTurretTurnInfo( struct SAINotifyTurretTurn *pTurretTurn ) = 0;
	virtual void GetVerTurretTurnInfo( struct SAINotifyTurretTurn *pTurretTurn ) = 0;
	
	// залокать turret gun-ом ( если уже была залокана, то старый lock исчезает )
	void Lock( const class CBasicGun *pGun );
	// unlock turret ( если залокана другим gun-ом, то ничего не делается )
	void Unlock( const class CBasicGun *pGun );
	// залокана ли каким-либо gun-ом, не равным pGun
	bool IsLocked( const class CBasicGun *pGun );

	void SetDefaultHorAngle( const WORD wHorAngle ) { wDefaultHorAngle = wHorAngle; }
	const WORD& GetDefaultHorAngle() const { return wDefaultHorAngle; }
	
	virtual bool IsOwnerOperable() const = 0;
	virtual bool IsAlive() const = 0;

	virtual const bool IsVisible( const BYTE cParty ) const { return true; }
	virtual void GetTilesForVisibility( CTilesSet *pTiles ) const { pTiles->clear(); }
	virtual bool ShouldSuspendAction( const EActionNotify &eAction ) const { return false; }

	// можно/нельзя вращать
	virtual void SetRotateTurretState( bool bCanRotate ) {}
	virtual bool GetRotateTurretState() const { return true; }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CUnitTurret : public CTurret
{
	OBJECT_COMPLETE_METHODS( CUnitTurret );
	DECLARE_SERIALIZE;
	
	CPtr<CAIUnit> pOwner;
	int nModelPart;
	DWORD dwGunCarriageParts;
	WORD wHorConstraint; 
	WORD wVerConstraint;

	bool bCanRotateTurret;
public:
	CUnitTurret() { }
	CUnitTurret( class CAIUnit *pOwner, const int nModelPart, const DWORD dwGunCarriageParts, const WORD wHorRotationSpeed, const WORD wVerRotationSpeed, const WORD wHorConstraint, const WORD wVerConstraint );

	// возвращает - был произведён поворот, или turret уже в нужном положении	
	virtual bool TurnHor( const WORD wHorAngle, const bool bInstantly = false );
	// возвращает - был произведён поворот, или turret уже в нужном положении
	virtual bool TurnVer( const WORD wVerAngle, const bool bInstantly = false );

	virtual void GetHorTurretTurnInfo( struct SAINotifyTurretTurn *pTurretTurn );
	virtual void GetVerTurretTurnInfo( struct SAINotifyTurretTurn *pTurretTurn );

	virtual CVec2 GetOwnerCenter();
	virtual WORD GetOwnerFrontDir();
	virtual float GetOwnerZ();
	virtual const int GetOwnerParty() const;

	virtual WORD GetHorTurnConstraint() const;
	virtual WORD GetVerTurnConstraint() const { return wVerConstraint; }

	virtual bool IsOwnerOperable() const;
	virtual bool IsAlive() const;

	virtual void SetRotateTurretState( bool bCanRotate ) { bCanRotateTurret = bCanRotate; }
	virtual bool GetRotateTurretState() const { return bCanRotateTurret; }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CMountedTurret : public CTurret
{
	OBJECT_COMPLETE_METHODS( CMountedTurret );	
	DECLARE_SERIALIZE;
	
	class CBuilding *pBuilding;
	int nSlot;

	CVec2 center;
	WORD dir;
	WORD wHorTurnConstraint;
	WORD wVerTurnConstraint;
public:
	CMountedTurret() { }
	CMountedTurret( CBuilding *pBuliding, const int nSlot );

	virtual void GetHorTurretTurnInfo( struct SAINotifyTurretTurn *pTurretTurn ) { }
	virtual void GetVerTurretTurnInfo( struct SAINotifyTurretTurn *pTurretTurn ) { }

	virtual CVec2 GetOwnerCenter() { return center; }
	virtual WORD GetOwnerFrontDir() { return dir; }
	virtual float GetOwnerZ() { return 0; }
	virtual const int GetOwnerParty() const;

	virtual WORD GetHorTurnConstraint() const;
	virtual WORD GetVerTurnConstraint() const;

	virtual bool IsOwnerOperable() const { return true; }
	virtual bool IsAlive() const;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __TURRET_H__
