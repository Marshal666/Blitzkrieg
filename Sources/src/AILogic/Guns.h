#ifndef __GUNS_H__
#define __GUNS_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "UpdatableObject.h"
#include "LinkObject.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************************************
//*								  ќружие юнита																		*
//*******************************************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SCommonGunInfo : public IRefCount
{
	OBJECT_COMPLETE_METHODS( SCommonGunInfo );
	DECLARE_SERIALIZE;
public:
	bool bFiring;
	int nAmmo;
	NTimer::STime lastShoot;
	int nGun;

	SCommonGunInfo() { }
	SCommonGunInfo( bool _bFiring, const int _nAmmo, const int _nGun ) : bFiring( _bFiring ), nAmmo( _nAmmo ), lastShoot( 0 ), nGun( _nGun ) { }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
interface IGunsFactory
{
	enum EGunTypes { MOMENT_CML_GUN, MOMENT_BURST_GUN, VIS_CML_BALLIST_GUN, VIS_BURST_BALLIST_GUN, PLANE_GUN, MORALE_GUN };

	virtual class CBasicGun* CreateGun( const EGunTypes eType, const int nShell, SCommonGunInfo *pCommonGunInfo ) const = 0;
	virtual int GetNCommonGun() const = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CBasicGun : public CLinkObject
{
	DECLARE_SERIALIZE;
public:
	virtual const float GetAimTime( bool bRandomize = true ) const = 0;
	virtual const float GetRelaxTime( bool bRandomize = true ) const = 0;
	virtual class CAIUnit* GetOwner() const = 0;
	virtual void SetOwner( class CAIUnit *pUnit ) = 0;
	virtual bool IsAlive() const = 0;
	virtual bool IsGrenade() const = 0;
	
	virtual void GetMechShotInfo( SAINotifyMechShot *pMechShotInfo, const NTimer::STime &time ) const = 0;
	virtual void GetInfantryShotInfo( SAINotifyInfantryShot *pInfantryShotInfo, const NTimer::STime &time ) const = 0;

	virtual bool InFireRange( class CAIUnit *pTarget ) const = 0;
	virtual bool InFireRange( const CVec3 &vPoint ) const = 0;
	virtual float GetFireRange( float z ) const = 0;
	// возвращает fRandgeMax from rpgstats с учЄтом всех модификаторов - коэффициентов
	virtual float GetFireRangeMax() const = 0;
	virtual bool InGoToSideRange( const class CAIUnit *pTarget ) const = 0;
	virtual bool TooCloseToFire( const class CAIUnit *pTarget ) const = 0;
	virtual bool TooCloseToFire( const CVec3 &vPoint ) const = 0;

	virtual void StartPointBurst( const CVec3 &_target, bool bReAim ) = 0;
	virtual void StartPointBurst( const CVec2 &target, bool bReAim ) = 0;
	virtual void StartEnemyBurst( class CAIUnit *pEnemy, bool bReAim ) = 0;
	virtual void Segment() = 0;

	// в данный момент в состо€нии наводки и стрельбы
	virtual bool IsFiring() const = 0;
	// в данный момент выстреливает очередь
	virtual bool IsBursting() const = 0;
	virtual void StopFire() = 0;

	//begin artillery specific
	virtual bool IsWaitForReload() const =0;
	virtual void ClearWaitForReload() =0;
	//end artillery specific

	virtual void Fire( const CVec2 &target, const float z = 0 ) = 0;
	virtual interface IBallisticTraj* CreateTraj( const CVec2 &vTarget ) const = 0;

	virtual const SBaseGunRPGStats& GetGun() const = 0;
	virtual const SWeaponRPGStats* GetWeapon() const = 0;
	virtual const SWeaponRPGStats::SShell& GetShell() const = 0;
	virtual bool IsOnTurret() const = 0;
	
	virtual void TraceAim( class CAIUnit *pUnit ) = 0;
	virtual void StopTracing() = 0;
	virtual bool IsRelaxing() const = 0;
	// можно ли стрельнуть по цели не враща€ ни turret ни base и не двига€сь, cDeltaAngle - учитывать ли deltaAngle
	virtual bool CanShootWOGunTurn( class CAIUnit *pEnemy, const BYTE cDeltaAngle ) = 0;
	// направление, по которому в данный момент смотрит орудие
	virtual const WORD GetGlobalDir() const = 0;
	// если на турели, то повернуть в относительный угол wAngle
	virtual void TurnToRelativeDir( const WORD wAngle ) = 0;

	// сколько ещЄ нужно relax
	virtual const NTimer::STime GetRestTimeOfRelax() const = 0;
	virtual const float GetRotateSpeed() const = 0;

	// стрельба, когда двигатьс€ запрещено, но вращатьс€ можно ( если юнит может вращатьс€ )
	virtual bool CanShootToUnitWOMove( class CAIUnit *pEnemy ) = 0;
	virtual bool CanShootToObjectWOMove( class CStaticObject *pObj ) = 0;
	virtual bool CanShootToPointWOMove( const CVec2 &point, const float fZ, const WORD wHorAddAngle = 0, const WORD wVertAddAngle = 0, CAIUnit *pEnemy = 0 ) = 0;
	
	// можно ли стрельнуть в объект по пр€мому приказу ( с учЄтом того - может owner ездить или нет )
	virtual bool CanShootToUnit( class CAIUnit *pEnemy ) = 0;
	virtual bool CanShootToObject( class CStaticObject *pObj ) = 0;
	// можно ли стрельнуть в объект по пр€мому приказу ( подъезжать нельз€ )
	virtual bool CanShootToPoint( const CVec2 &point, const float fZ, const WORD wHorAddAngle = 0, const WORD wVertAddAngle = 0 ) = 0;
	// можно ли дострельнуть по высоте
	virtual bool CanShootByHeight( CAIUnit *pTarget ) const = 0;
	virtual bool CanShootByHeight( const float fZ ) const = 0;
	
	// дл€ самолЄтов
	virtual void StartPlaneBurst( class CAIUnit *pEnemy, bool bReAim ) = 0;

	// можно пристрелить, не поворачива€ base ( turret вращать можно )
	virtual bool IsInShootCone( const CVec2 &point, const WORD wAddAngle = 0 ) const = 0;

	virtual const float GetDispersion() const = 0;
	// во столько раз разброс вдоль траектории борльше разброса поперек траектории
	virtual const float GetDispRatio( byte nShellType, const float fDist ) const =0; 
	virtual const int GetFireRate() const = 0;
	virtual void LockInCurAngle() = 0;
	virtual void UnlockCurAngle() = 0;
	
	virtual WORD GetHorTurnConstraint() const = 0;
	virtual WORD GetVerTurnConstraint() const = 0;
	virtual class CTurret* GetTurret() const = 0;

	// можно пробить броню с учЄтом стороны, которой повЄрнут pTarget
	virtual bool CanBreakArmor( class CAIUnit *pTarget ) const = 0;
	// можно пробить броню с какой-нибудь стороны
	virtual bool CanBreach( const class CCommonUnit *pTarget ) const = 0;
	// можно пробить броню со стороны nSide
	virtual bool CanBreach( const class CCommonUnit *pTarget, const int nSide ) const = 0;
	virtual bool CanBreach( const SHPObjectRPGStats *pStats, const int nSide ) const = 0;
	
	// будет делать все действи€, нужные дл€ стрельбы по цели (повороты, прицеливание), но не будет стрел€ть
	virtual void DontShoot() = 0;
	// отмен€ет DontShoot()
	virtual void CanShoot() = 0;
	virtual bool IsShootAllowed()=0;

	// стрел€ет ли общий gun ( с учЄтом патронов - т.е. учитываютс€ все guns, наход€щиес€ с ним в одном стволе )
	virtual bool IsCommonGunFiring() const = 0;
	// равен ли pGun ( с учЄтом патронов )
	virtual bool IsCommonEqual( const CBasicGun *pGun ) const = 0;

	// "номер ствола" ( gun-ы, отличающиес€ только патронами, но наход€щиес€ в одном стволе )
	virtual int GetCommonGunNumber() const = 0;

	virtual int GetNAmmo() const = 0;
	
	virtual WORD GetTrajectoryZAngle( const CVec2 &vToAim, const float z ) const = 0;
	
	// сказать, почему отказалс€ стрел€ть
	virtual const EUnitAckType& GetRejectReason() const = 0;
	virtual void SetRejectReason( const EUnitAckType &eRejectReason ) = 0;
	
	// разрешить/запретить атаковать без учЄта ограничени€ на поворот оруди€ по горизонтали
	virtual void SetCircularAttack( const bool bCanAttack ) = 0;
	
	virtual void AddParallelGun( CBasicGun *pGun ) = 0;
	virtual void SetToParallelGun() = 0;
	
	// среднее значение
	virtual const int GetPiercing() const = 0;
	// разброс
	virtual const int GetPiercingRandom() const = 0;
	// рандомное значение piercing
	virtual const int GetRandomPiercing() const = 0;
	virtual const int GetMaxPossiblePiercing() const = 0;
	virtual const int GetMinPossiblePiercing() const = 0;

	// среднее значение damage
	virtual const float GetDamage() const = 0;
	// разброс
	virtual const float GetDamageRandom() const = 0;
	// рандомное значение damage
	virtual const float GetRandomDamage() const = 0;
	
	// for AA guns.
	virtual const NTimer::STime GetTimeToShootToPoint( const CVec3 &vPoint ) const { NI_ASSERT_T(false, "wrong call"); return 0; }
	virtual const NTimer::STime GetTimeToShoot( const CVec3 &vPoint ) const { NI_ASSERT_T( false, "wrong call" ); return 0; }
	
	virtual bool IsBallisticTrajectory() const = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float GetDispByRadius( const class CBasicGun *pGun, const CVec2 &attackerPos, const CVec2 &explCoord );
float GetDispByRadius( const class CBasicGun *pGun, const float fDist );
float GetDispByRadius( const float fDispRadius, const float fRangeMax, const float fDist );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const float GetFireRangeMax( const SWeaponRPGStats *pStats, CAIUnit *pOwner );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __GUNS_H__
