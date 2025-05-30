#include "stdafx.h"

#include "Artillery.h"
#include "Guns.h"
#include "ArtilleryStates.h"
#include "ArtRocketStates.h"
#include "Formation.h"
#include "Updater.h"
#include "StaticObjects.h"
#include "ArtilleryBulletStorage.h"
#include "Diplomacy.h"
#include "GroupLogic.h"
#include "Soldier.h"
#include "Turret.h"
#include "UnitGuns.h"
#include "ShootEstimatorInternal.h"
#include "AIStaticMap.h"
#include "Technics.h"
#include "Statistics.h"
#include "MultiplayerInfo.h"
#include "General.h"
#include "DifficultyLevel.h"
#include "TankStates.h"

#include "..\Common\AdditionalActions.h"
#include "..\Scene\Scene.h"

// for profiling
#include "TimeCounter.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern CSupremeBeing theSupremeBeing;
extern NTimer::STime curTime;
extern CUpdater updater;
extern CStaticObjects theStatObjs;
extern CDiplomacy theDipl;
extern CGroupLogic theGroupLogic;
extern CStaticMap theStaticMap;
extern CStatistics theStatistics;
extern CMultiplayerInfo theMPInfo;
extern CDifficultyLevel theDifficultyLevel;

extern CTimeCounter timeCounter;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BASIC_REGISTER_CLASS( CArtillery );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CArtillery::~CArtillery()
{
	if ( bBulletStorageVisible && pBulletStorage.IsValid() )
		HideAmmoBox();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CAIUnit *CArtillery::GetHookingTransport()
{
	if ( IsBeingHooked() )
		return pHookingTransport;
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CArtillery::IsBeingHooked() const
{
	return IsValidObj( pHookingTransport );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::SetBeingHooked( class CAIUnit *pUnit )
{
	pHookingTransport = pUnit;
	if ( IsBeingHooked() )
	{
		SetSelectable( false );
		updater.Update( ACTION_NOTIFY_STATE_CHANGED, this, ECS_HOOK_CANNON );
	}
	else
	{
		SetSelectable( GetPlayer() == theDipl.GetMyNumber() );
		updater.Update( ACTION_NOTIFY_STATE_CHANGED, this, ECS_UNHOOK_CANNON );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CUnitGuns* CArtillery::GetGuns() const 
{ 
	return pGuns; 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CUnitGuns* CArtillery::GetGuns() 
{ 
	return pGuns; 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::CreateAmmoBox()
{
	// � ����� ������ ���� ���� � ���������
	// ���� "Barrel"
	CPtr<IObjectsDB> pIDB = GetSingleton<IObjectsDB>();

	CGDBPtr<SGDBObjectDesc> pDesc = pIDB->GetDesc( "ShellBox02" );
	const int nDBIndex = pIDB->GetIndex( "ShellBox02" );

	const SStaticObjectRPGStats* pStats = static_cast<const SStaticObjectRPGStats*>( pIDB->GetRPGStats( pDesc ) );

	pBulletStorage = new CArtilleryBulletStorage( pStats, GetAmmoBoxCoordinates(), nDBIndex, 1.0f, 0, this );
	Mem2UniqueIdObjs();
	pBulletStorage->MoveTo( GetAmmoBoxCoordinates() );
	bBulletStorageVisible = false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::UpdateAmmoBoxVisibility()
{
	if ( IsVisibleByPlayer() )
	{
		if ( !bBulletStorageVisible )
			ShowAmmoBox();
	}
	else 
		if ( bBulletStorageVisible )
			HideAmmoBox();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::ShowAmmoBox()
{
	NI_ASSERT_T( pBulletStorage != 0, "Ammo box isn't created" );
	NI_ASSERT_T( bBulletStorageVisible == false, "Ammo box is already visible" );

	updater.Update( ACTION_NOTIFY_NEW_ST_OBJ, pBulletStorage );

	const CVec2 newCenter = GetAmmoBoxCoordinates();
	if ( pBulletStorage->GetCenter() != newCenter )
		pBulletStorage->MoveTo( newCenter );
	
	bBulletStorageVisible = true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::HideAmmoBox()
{
	NI_ASSERT_T( pBulletStorage != 0, "Ammo box isn't created" );
	NI_ASSERT_T( bBulletStorageVisible == true, "Ammo box isn't visible" );

	updater.Update(	ACTION_NOTIFY_DELETED_ST_OBJ, pBulletStorage );
	
	bBulletStorageVisible = false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::TakeDamage( const float fDamage, const SWeaponRPGStats::SShell *pShell, const int nPlayerOfShoot, CAIUnit *pShotUnit )
{
	CAIUnit::TakeDamage( fDamage, pShell, nPlayerOfShoot, pShotUnit );
	if ( GetHitPoints() <= 0.0f )
	{
		// ����� ������, ����� �������������
		if ( HasServeCrew() )
		{
			while ( IsValidObj( pCrew ) && pCrew->Size() != 0 )
			{
				theStatistics.UnitKilled( nPlayerOfShoot, (*pCrew)[0]->GetPlayer(), 1, (*pCrew)[0]->GetStats()->fPrice );
				theMPInfo.UnitsKilled( nPlayerOfShoot, (*pCrew)[0]->GetStats()->fPrice, (*pCrew)[0]->GetPlayer() );
				
				(*pCrew)[0]->Die( false, 0 );
			}
			if ( IsValidObj( pCrew ) )
				pCrew->SetSelectable( pCrew->GetPlayer() == theDipl.GetMyNumber() );
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::Disappear()
{
	if ( HasServeCrew() && GetStats()->type != RPG_TYPE_ART_MORTAR && GetStats()->type != RPG_TYPE_ART_HEAVY_MG )
		pCrew->Disappear();

	if ( pBulletStorage && bBulletStorageVisible )
		HideAmmoBox();

	CAIUnit::Disappear();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CVec2 CArtillery::GetAmmoBoxCoordinates() 
{
	const bool b360DegreesRotate = pStats->platforms[1].constraint.wMax >= 65535;
	CVec2 vGunDir;
	
	if ( b360DegreesRotate && GetStats()->type != RPG_TYPE_ART_AAGUN )
	{
		CTurret *pTurret = GetTurret( 0 );
		const WORD wCurTurretHorDir = pTurret->GetHorCurAngle();
		vGunDir = GetVectorByDirection( GetFrontDir() + wCurTurretHorDir );
	}
	else
		vGunDir = GetDirVector();
	
	const CVec2 vAmmoPoint( pStats->vAmmoPoint.y, -pStats->vAmmoPoint.x );
	return GetCenter() + ( vAmmoPoint^vGunDir);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CArtillery::TurnToDir( const WORD &newDir, const bool bCanBackward, const bool bForward )
{
	lastCheckToInstall = curTime;	
	if ( !MustHaveCrewToOperate() || fOperable != 0.0f )
	{
		pStaticPathToSend = 0;
		pIPathToSend = 0;

		if ( !IsInstalled() && !IsInInstallAction() )
			return CAIUnit::TurnToDir( newDir, bCanBackward );
		InstallAction( ACTION_NOTIFY_UNINSTALL_ROTATE );
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CArtillery::TurnToUnit( const CVec2 &targCenter )
{
	lastCheckToInstall = curTime;	
	if ( !MustHaveCrewToOperate() || fOperable != 0.0f )
	{
		pStaticPathToSend = 0;
		pIPathToSend = 0;

		if ( !IsInstalled() && !IsInInstallAction() )
			return CAIUnit::TurnToUnit( targCenter );
		InstallAction( ACTION_NOTIFY_UNINSTALL_ROTATE );
	}

	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CArtillery::IsBeingCaptured() const 
{ 
	return IsValidObj( pCapturingUnit ); 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::SetCapturingUnit( CFormation * pFormation ) 
{ 
	pCapturingUnit = pFormation; 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::DelCrew()
{
	NI_ASSERT_T( MustHaveCrewToOperate(), "del crew from gun without possible crew" );

	const int nGuns = GetNGuns();
	for ( int i = 0; i < nGuns; ++i )
		GetGun( i )->StopFire();
	if ( !pCrew || !pCrew->IsValid() || !pCrew->IsAlive() )
		theGroupLogic.UnitCommand( SAIUnitCmd(ACTION_COMMAND_STOP_THIS_ACTION), this, false );
	pCrew = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::ChangePlayer( const BYTE cPlayer )
{
	CAIUnit::ChangePlayer( cPlayer );
	//register this artillery to supremeBeing again
	theSupremeBeing.AddReinforcement( this );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::SetCrew( class CFormation * _pCrew, const bool bCapture )
{
	NI_ASSERT_T( _pCrew != 0 , "wrong crew !");

	pCrew = _pCrew;
	ChangePlayer( pCrew->GetPlayer() ); // ������� ������� �������
	if ( bCapture )
		theGroupLogic.UnitCommand( SAIUnitCmd( ACTION_MOVE_GUNSERVE, this ), pCrew, false );

	if ( GetPlayer() != theDipl.GetNeutralPlayer() )
		theSupremeBeing.UnitAskedForResupply( this, ERT_HUMAN_RESUPPLY, false );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CFormation* CArtillery::GetCrew() const
{
	return pCrew;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CArtillery::MustHaveCrewToOperate()const
{
	return pStats->vGunners[0].size() != 0 ;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CArtillery::HasServeCrew()const
{
	return IsValidObj( pCrew );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::InitGuns()
{
	if ( pStats->platforms.size() > 1 )
	{
		const int nTurrets = pStats->platforms.size() - 1;
		turrets.resize( nTurrets );

		for ( int i = 0; i < nTurrets; ++i )
		{
			const SMechUnitRPGStats::SPlatform &platform = pStats->platforms[i+1];
			turrets[i] = new CUnitTurret( 
																		this, platform.nModelPart, platform.dwGunCarriageParts, 
																		platform.wHorizontalRotationSpeed, platform.wVerticalRotationSpeed,
																		platform.constraint.wMax, platform.constraintVertical.wMax
																	);

			if ( GetStats()->type == RPG_TYPE_ART_AAGUN )
				turrets[i]->Turn( 0, 16384 * 3 + 16384 / 2, true );
		}
	}

	pGuns = new CMechUnitGuns();
	pGuns->Init( this );

	SetShootEstimator( new CTankShootEstimator( this ) );

	if ( GetFirstArtilleryGun() != 0 )
		behUpdateDuration = SConsts::LONG_RANGE_ARTILLERY_UPDATE_DURATION;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::Init( const CVec2 &center, const int z, const SUnitBaseRPGStats *_pStats, const float fHP, const WORD dir, const BYTE player, const WORD id, EObjVisType eVisType, const int dbID )
{
	nInitialPlayer = player;
	pStats = static_cast<const SMechUnitRPGStats*>( _pStats );
	bInstalled = true;
	installActionTime = 0;
	eCurInstallAction = ACTION_NOTIFY_NONE;
	eNextInstallAction = ACTION_NOTIFY_NONE;

	fDispersionBonus = 1.0f;
	lastCheckToInstall = 0;
	eCurrentStateOfInstall = ACTION_NOTIFY_INSTALL_TRANSPORT;
	fOperable = 1.0f;

	bInstallActionInstant = false;
	vShift = VNULL2;

	behUpdateDuration = GetStats()->type == RPG_TYPE_ART_AAGUN ? SConsts::AA_BEH_UPDATE_DURATION : SConsts::BEH_UPDATE_DURATION;

	CAIUnit::Init( center, z, fHP, dir, player, id, eVisType, dbID );

	CreateAmmoBox();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IStatesFactory* CArtillery::GetStatesFactory() const
{
	if ( GetStats()->type == RPG_TYPE_ART_ROCKET )
		return CArtRocketStatesFactory::Instance();

	return CArtilleryStatesFactory::Instance();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CArtillery::IsInstallActionFinished()
{
	switch ( eCurInstallAction )
	{
		case ACTION_NOTIFY_INSTALL_TRANSPORT:		return curTime - installActionTime >= pStats->nUninstallTransport;
		case ACTION_NOTIFY_INSTALL_ROTATE:			return curTime - installActionTime >= pStats->nUninstallRotate;
		case ACTION_NOTIFY_INSTALL_MOVE: 				return curTime - installActionTime >= pStats->nUninstallRotate;
		case ACTION_NOTIFY_UNINSTALL_TRANSPORT: return curTime - installActionTime >= pStats->nUninstallTransport;
		case ACTION_NOTIFY_UNINSTALL_MOVE:			return curTime - installActionTime >= pStats->nUninstallRotate;
		case ACTION_NOTIFY_UNINSTALL_ROTATE:		return curTime - installActionTime >= pStats->nUninstallRotate;

		default: NI_ASSERT_T( false, NStr::Format( "Wrong curInstallAction (%d)", int( eCurInstallAction ) ) );
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CArtillery::ShouldSendInstallAction( const EActionNotify &eAction ) const
{
	switch ( eAction )
	{
		case ACTION_NOTIFY_INSTALL_TRANSPORT:		return pStats->nUninstallTransport != 0;
		case ACTION_NOTIFY_INSTALL_ROTATE:			return pStats->nUninstallRotate != 0;
		case ACTION_NOTIFY_INSTALL_MOVE: 				return pStats->nUninstallRotate != 0;
		case ACTION_NOTIFY_UNINSTALL_TRANSPORT: return pStats->nUninstallTransport != 0;
		case ACTION_NOTIFY_UNINSTALL_MOVE:			return pStats->nUninstallRotate != 0;
		case ACTION_NOTIFY_UNINSTALL_ROTATE:		return pStats->nUninstallRotate != 0;
		default: NI_ASSERT_T( false, NStr::Format( "Wrong eAction (%d)", int( eAction ) ) );
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IsInstallAction( const EActionNotify &eAction )
{
	return
		eAction == ACTION_NOTIFY_INSTALL_TRANSPORT ||
		eAction == ACTION_NOTIFY_INSTALL_MOVE			 ||
		eAction == ACTION_NOTIFY_INSTALL_ROTATE;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EActionNotify GetOppositeInstallState( const EActionNotify &eAction )
{
	switch ( eAction )
	{
		case ACTION_NOTIFY_INSTALL_TRANSPORT:		return ACTION_NOTIFY_UNINSTALL_TRANSPORT;
		case ACTION_NOTIFY_INSTALL_ROTATE:			return ACTION_NOTIFY_UNINSTALL_ROTATE;
		case ACTION_NOTIFY_INSTALL_MOVE: 				return ACTION_NOTIFY_UNINSTALL_MOVE;
		case ACTION_NOTIFY_UNINSTALL_TRANSPORT: return ACTION_NOTIFY_INSTALL_TRANSPORT;
		case ACTION_NOTIFY_UNINSTALL_MOVE:			return ACTION_NOTIFY_INSTALL_MOVE;
		case ACTION_NOTIFY_UNINSTALL_ROTATE:		return ACTION_NOTIFY_INSTALL_ROTATE;
		default:	return ACTION_NOTIFY_NONE;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const float CArtillery::GetRotateSpeed() const
{
	if ( !MustHaveCrewToOperate() )
		return CAIUnit::GetRotateSpeed();
	else if ( fOperable == 0.0f )
		return 0.00001f;
	return fOperable * CAIUnit::GetRotateSpeed();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const float CArtillery::GetMaxSpeedHere( const CVec2 &point, bool bAdjust ) const
{
	if ( !MustHaveCrewToOperate() )
		return CAIUnit::GetMaxSpeedHere( point );

	float fSpeed = fOperable * CAIUnit::GetMaxSpeedHere( point, false );
	if ( bAdjust )
		AdjustWithDesirableSpeed( &fSpeed );
	
	return fSpeed;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::SetOperable( float _fOperable )
{
	// ���� ������� ��������������, ���� ��� �������, � �� ��������, �� ��������� �����
	if ( fOperable == 0.0f && _fOperable != 0.0f && GetStats()->type == RPG_TYPE_ART_AAGUN && IsInstalled() )
	{
		for ( int i = 0; i < GetNTurrets(); ++i )
		{
			if ( GetTurret( i )->GetVerCurAngle() == 16384 * 3 )
				GetTurret( i )->TurnVer( 16384 * 3 + 16384 / 2 );
		}
	}

	fOperable = _fOperable;
	if ( fOperable == 0.0f || !HasServeCrew() )
	{
		for ( int i = 0; i < GetNGuns(); ++i )	
			GetGun( i )->StopFire();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::SetCamoulfage()
{
	CAIUnit::SetCamoulfage();
	if ( HasServeCrew() )
	{
		const int nSold = pCrew->Size();
		for ( int i=0; i < nSold; ++i )
			(*pCrew)[i]->SetCamoulfage();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::RemoveCamouflage( ECamouflageRemoveReason eReason )
{
	CAIUnit::RemoveCamouflage( eReason );
	if ( HasServeCrew() )
	{
		int nSold = pCrew->Size();
		for ( int i=0; i < nSold; ++i )
			(*pCrew)[i]->RemoveCamouflage( eReason );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::SetSelectable	( bool bSelectable )
{
	CAIUnit::SetSelectable( bSelectable );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::Segment()
{
	CAIUnit::Segment();

	if ( IsAlive() )
	{
		for ( int i = 0; i < GetNTurrets(); ++i )
			GetTurret( i )->Segment();
	}

	if ( eCurInstallAction != ACTION_NOTIFY_NONE )
	{
		// ��� ������� ����� � ������� ��� ����������� ���������� installAction
		if ( installActionTime == 0 )
		{
			// ��� ����� �������� ��� ����� ������� ����� �� �����������
			int i = 0;
			bool bCanDoInstallAction = true;
			for ( int i = 0; i < GetNTurrets(); ++i )
			{
				bool bFiring = false;
				if ( !GetTurret( i )->IsHorFinished() )
					bCanDoInstallAction = false;
				else
				{
					for ( int j = 0; j < GetNGuns() && !bFiring; ++j )
					{
						if ( GetGun( j )->IsFiring() && GetGun( j )->GetTurret() == GetTurret( i ) )
						{
							bFiring = true;
							bCanDoInstallAction = false;
						}
					}

					if ( bCanDoInstallAction && !bFiring && GetTurret( i )->GetHorCurAngle() != 0 )
					{
						GetTurret( i )->SetDefaultHorAngle( 0 );
						GetTurret( i )->TurnHor( 0 );
						bCanDoInstallAction = false;
					}
				}

				if ( !GetTurret( i )->IsVerFinished() )
					bCanDoInstallAction = false;
				else if ( !bFiring && GetTurret( i )->GetVerCurAngle() != 16384 * 3 )
				{
					GetTurret( i )->TurnVer( 16384 * 3 );
					bCanDoInstallAction = false;
				}
					
				++i;
			}

			if ( bCanDoInstallAction || !ShouldSendInstallAction( eCurInstallAction ) )
			{
				installActionTime = bInstallActionInstant ? 1 : curTime;
				if ( ShouldSendInstallAction( eCurInstallAction ) )
					updater.Update( eCurInstallAction, this, bInstallActionInstant ? 0 : -1 );
			}
		}
		else if ( IsInstallActionFinished() )
		{
			bInstalled = IsInstallAction( eCurInstallAction );

			// ����� ��������� � default position ����������������� ������
			if ( bInstalled && ( pStats->type == RPG_TYPE_ART_AAGUN || pStats->type == RPG_TYPE_SPG_AAGUN ) && IsOperable() )
			{
				for ( int i = 0; i < GetNTurrets(); ++i )
					GetTurret( i )->TurnVer( 16384 * 3 + 16384 / 2 );
			}

			eCurrentStateOfInstall = eCurInstallAction;
			eCurInstallAction = eNextInstallAction;
			eNextInstallAction = ACTION_NOTIFY_NONE;
			lastCheckToInstall = curTime;

			if ( bInstalled && !IsInstallAction( eCurInstallAction ) || !bInstalled && IsInstallAction( eCurInstallAction ) )
				installActionTime = curTime;
			else
				eCurInstallAction = ACTION_NOTIFY_NONE;
		}
	}
	else if ( eNextInstallAction != ACTION_NOTIFY_NONE )
	{
		eCurInstallAction = eNextInstallAction;
		eNextInstallAction = ACTION_NOTIFY_NONE;
		lastCheckToInstall = curTime;

		installActionTime = 0;

		const bool bAAGun = pStats->type == RPG_TYPE_ART_AAGUN || pStats->type == RPG_TYPE_SPG_AAGUN;
		// ������������ � default ������� ������ ��� deinstallation
		if ( !IsInstallAction( eCurInstallAction ) )
		{
			for ( int i = 0; i < GetNTurrets(); ++i )
			{
				GetTurret( i )->SetDefaultHorAngle( 0 );
				GetTurret( i )->Turn( 0, 16384 * 3 );
			}
		}
	}

	if ( IsUninstalled() && IsOperable() )
	{
		if ( pStaticPathToSend != 0 )
		{
			CAIUnit::SendAlongPath( pStaticPathToSend, vShift );
			pStaticPathToSend = 0;
			lastCheckToInstall = curTime;
		}
		else if ( pIPathToSend != 0 )
		{
			CAIUnit::SendAlongPath( pIPathToSend );
			pIPathToSend = 0;
			lastCheckToInstall = curTime;
		}
	}

	const bool bBoxMustBeShown =	GetNGuns() > 0 && GetNAmmo( 0 ) != 0 &&	// ���� �� �������
													IsInstalled() &&
													pStats->vAmmoPoint != VNULL2 &&			// ���� �� ���� ������
													IsVisible( theDipl.GetMyParty() ); // ����� ��� ����� �����
	if ( bBoxMustBeShown )
	{
		if ( bBulletStorageVisible && pBulletStorage )
		{
			const CVec2 vAmmoBoxCoordinates( GetAmmoBoxCoordinates() );
			if ( pBulletStorage->GetCenter() != vAmmoBoxCoordinates )
			{
				updater.Update(	ACTION_NOTIFY_PLACEMENT, pBulletStorage );
				pBulletStorage->MoveTo( vAmmoBoxCoordinates );
			}
		}
		else if ( !bBulletStorageVisible )
		{
			ShowAmmoBox();
		}
	}
	else if ( bBulletStorageVisible && !bBoxMustBeShown )
		HideAmmoBox();
	
	
	// ������������ ������ ���� �� �� ���.
	// ����� � ���� ������ �����������.
	if ( MustHaveCrewToOperate() && !HasServeCrew()  && ( IsOperable() || IsSelectable() || GetPlayer() != theDipl.GetNeutralPlayer()) )
	{
		SetSelectable( false );
		if ( EUSN_BEING_TOWED != GetState()->GetName() )
			ChangePlayer( theDipl.GetNeutralPlayer() );
		const int nGuns = GetNGuns();
		SetOperable( 0 );
	}

	if ( !MustHaveCrewToOperate() || fOperable > 0.0f )
		pGuns->Segment();

	if ( !IsIdle() )
		lastCheckToInstall = curTime;
	else if ( !IsInstalled() && !IsInInstallAction() && IsOperable() )
	{
		if ( curTime - lastCheckToInstall >= 1500 + Random( 0, 500 ) )
		{
			NI_ASSERT_T( IsInstallAction( GetOppositeInstallState( eCurrentStateOfInstall ) ), NStr::Format( "Wrong current install state (%d)", int(eCurrentStateOfInstall) ) );
			InstallAction( GetOppositeInstallState( eCurrentStateOfInstall ) );
		}
	}
	else
		lastCheckToInstall = curTime;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec2 CArtillery::GetTowPoint()
{
	const CVec2 vTurn( GetDirVector().y, -GetDirVector().x );
	const CVec2 vTow( (pStats->vTowPoint) ^ vTurn );
	return vTow + GetCenter();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::InstallBack( bool bAlreadyDone )
{
	switch( eCurrentStateOfInstall )
	{
		case ACTION_NOTIFY_UNINSTALL_ROTATE:
			InstallAction( ACTION_NOTIFY_INSTALL_ROTATE, bAlreadyDone );
			break;
		case ACTION_NOTIFY_UNINSTALL_TRANSPORT:
			InstallAction( ACTION_NOTIFY_INSTALL_TRANSPORT, bAlreadyDone );
			break;
		case ACTION_NOTIFY_UNINSTALL_MOVE:
			InstallAction( ACTION_NOTIFY_INSTALL_MOVE, bAlreadyDone );
			break;
		default:
			NI_ASSERT_T(false,"wrtong call");
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::InstallAction( const EActionNotify eInstallAction, bool bAlreadyDone )
{
	//bAlreadyDone = true, ������ �������� ����� ������ ����������.
	if (	eInstallAction == ACTION_NOTIFY_INSTALL_ROTATE ||
				eInstallAction == ACTION_NOTIFY_INSTALL_TRANSPORT ||
				eInstallAction == ACTION_NOTIFY_INSTALL_MOVE )
	{
		if ( IsUninstalled() )
			eNextInstallAction = eInstallAction;
		else
			eNextInstallAction = ACTION_NOTIFY_NONE;
	}
	else if ( eInstallAction == ACTION_NOTIFY_UNINSTALL_ROTATE ||
						eInstallAction == ACTION_NOTIFY_UNINSTALL_TRANSPORT ||
						eInstallAction == ACTION_NOTIFY_UNINSTALL_MOVE )
	{
		if ( IsInstalled() )
		{
			if ( IsInTankPit() )
				theGroupLogic.InsertUnitCommand( SAIUnitCmd(ACTION_MOVE_LEAVE_TANK_PIT), this );
			else
				eNextInstallAction = eInstallAction;
		}
		else
			eNextInstallAction = ACTION_NOTIFY_NONE;
	}
	else
			NI_ASSERT_T( false, "Wrong install action" );
	
	if ( eInstallAction == eNextInstallAction )
		bInstallActionInstant = bAlreadyDone;

	for ( int i = 0; i < GetNTurrets(); ++i )
		GetTurret( i )->StopTracing();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::ForceInstallAction()
{
	lastCheckToInstall = 0;

	for ( int i = 0; i < GetNTurrets(); ++i )
		GetTurret( i )->StopTracing();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CArtillery::IsIdle() const
{
	return !pStaticPathToSend.IsValid() && !pIPathToSend.IsValid() && CAIUnit::IsIdle();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CArtillery::SendAlongPath( IStaticPath *pStaticPath, const CVec2 &_vShift, bool bSmoothTurn )
{
	if ( IsInstalled() || IsInInstallAction() )
		InstallAction( ACTION_NOTIFY_UNINSTALL_MOVE );

	pStaticPathToSend = pStaticPath;
	vShift = _vShift;
	lastCheckToInstall = curTime;

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::SendAcknowledgement( EUnitAckType ack, bool bForce )
{
	SendAcknowledgement( GetCurCmd(), ack, bForce );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::SendAcknowledgement( CAICommand *pCommand, EUnitAckType ack, bool bForce )
{
	if ( HasServeCrew() )
		pCrew->SendAcknowledgement( pCommand, ack, bForce );
	else if ( !MustHaveCrewToOperate() )
	{
		CAIUnit::SendAcknowledgement( pCommand, ack, bForce );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CArtillery::SendAlongPath( IPath *pPath )
{
	if ( IsInstalled() || IsInInstallAction() )
		InstallAction( ACTION_NOTIFY_UNINSTALL_MOVE );

	pIPathToSend = pPath;
	lastCheckToInstall = curTime;

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CArtillery::IsLightGun() const
{
	return pStats->type == RPG_TYPE_ART_GUN || pStats->type == RPG_TYPE_ART_AAGUN;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float CArtillery::GetMaxFireRange() const
{
	return pGuns->GetMaxFireRange( this );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::GetRangeArea( SShootAreas *pRangeArea ) const
{
	std::construct( pRangeArea );	
	if ( GetState()->GetName() == EUSN_RANGING )
	{
		CCircle rangeCircle;
		static_cast<const CArtilleryRangeAreaState*>(GetState())->GetRangeCircle( &rangeCircle );
		pRangeArea->areas.push_back( SShootArea() );
		SShootArea &area = pRangeArea->areas.back();
		area.eType = SShootArea::ESAT_RANGE_AREA;
		area.fMinR = 0.0f;
		area.fMaxR = rangeCircle.r;
		area.vCenter3D = CVec3( rangeCircle.center, 0.0f );
		area.wStartAngle = 65535;
		area.wFinishAngle = 65535;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CArtillery::GetNGuns() const 
{ 
	return pGuns->GetNTotalGuns(); 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CBasicGun* CArtillery::GetGun( const int n ) const 
{ 
	return pGuns->GetGun( n ); 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NTimer::STime& CArtillery::GetBehUpdateDuration() const
{
	return behUpdateDuration;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CBasicGun* CArtillery::ChooseGunForStatObj( CStaticObject *pObj, NTimer::STime *pTime ) 
{ 
	return pGuns->ChooseGunForStatObj( this, pObj, pTime ); 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CBasicGun* CArtillery::GetFirstArtilleryGun() const
{ 
	return pGuns->GetFirstArtilleryGun(); 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const bool CArtillery::CanShootToPlanes() const 
{ 
	return pGuns->CanShootToPlanes(); 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CArtillery::HasSlaveTransport() 
{ 
	return pSlaveTransport && pSlaveTransport->IsValid() && pSlaveTransport->IsAlive();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::DoAllowShoot( bool allow )
{
	for ( int i=0; i< GetNGuns(); ++i )
	{
		allow ? GetGun( i )->CanShoot() : GetGun( i )->DontShoot();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::ClearWaitForReload()
{
	for ( int i=0; i< GetNGuns(); ++i )
	{
		CBasicGun *pGun = GetGun( i );
		if ( pGun ->IsWaitForReload() )
		{
			pGun ->ClearWaitForReload();
			break;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CArtillery::IsColliding() const
{
	return GetState()->GetName() != EUSN_BEING_TOWED;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::StopUnit()
{
	// ���� ������� ����� �� �����������, ���������� ��� ����������� ����� ��������� �����������
	if ( !ShouldSendInstallAction( ACTION_NOTIFY_INSTALL_TRANSPORT ) )
		InstallAction( ACTION_NOTIFY_INSTALL_TRANSPORT );

	CAIUnit::StopUnit();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CVec3 Multi( const SHMatrix &matrix, const CVec3 &vec )
{
	CVec3 vResult;

	vResult.x = matrix.m[0][0] * vec.x + matrix.m[0][1] * vec.y;
	vResult.y = matrix.m[1][0] * vec.x + matrix.m[1][1] * vec.y;
	vResult.z = vec.z;

	return vResult;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const DWORD CArtillery::GetNormale( const CVec2 &vArtCenter ) const
{
	if ( GetState()->GetName() == EUSN_BEING_TOWED )
	{
		CAITransportUnit *pTransport = static_cast<CArtilleryBeingTowedState*>( GetState() )->GetTowingTransport();
		const CVec2 vTraCenter = pTransport->GetCenter();
		CVec3 vTraCenter3D( vTraCenter, theStaticMap.GetVisZ( vTraCenter.x, vTraCenter.y ) );

		const CVec2 vArtCenter = GetCenter();
		const CVec3 vArtCenter3D( vArtCenter, theStaticMap.GetVisZ( vArtCenter.x, vArtCenter.y ) );
		const SMechUnitRPGStats *pArt = static_cast<const SMechUnitRPGStats*>( GetStats() );

		const CVec3 vTraHookPoint3D = pTransport->GetHookPoint3D();


		const CVec3 vArtNormale = DWORDToVec3( CAIUnit::GetNormale() );
		const CVec2 vArtDir = GetVectorByDirection( GetFrontDir() );
		CVec3 vArtDir3D;
		vArtDir3D.x = vArtDir.x;
		vArtDir3D.y = vArtDir.y;
		vArtDir3D.z = ( -vArtDir3D.x * vArtNormale.x - vArtDir3D.y * vArtNormale.y ) / vArtNormale.z;
		Normalize( &vArtDir3D );

		const CVec3 vArtHookPointDir = vArtDir3D * pArt->vTowPoint.y;
		const CVec3 vAxisOfYaw = vArtNormale ^ vArtHookPointDir;

		const CVec3 vArtNewHookPointDir = vTraHookPoint3D - vArtCenter3D;
		CVec3 vNewArtNormale = vArtNewHookPointDir ^ vAxisOfYaw;

		Normalize( &vNewArtNormale );
		if ( vNewArtNormale.z < 0 )
			vNewArtNormale.z = -vNewArtNormale.z;

		return Vec3ToDWORD( vNewArtNormale );
	}
	else
		return CAIUnit::GetNormale();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const DWORD CArtillery::GetNormale() const
{
	return GetNormale( GetCenter() );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CVec3 CArtillery::GetHookPoint3D() const
{
	const CVec3 vArtNormale = DWORDToVec3( GetNormale() );
	const CVec2 vArtDir = GetVectorByDirection( GetFrontDir() );
	CVec3 vArtDir3D;
	vArtDir3D.x = vArtDir.x;
	vArtDir3D.y = vArtDir.y;
	vArtDir3D.z = ( -vArtDir3D.x * vArtNormale.x - vArtDir3D.y * vArtNormale.y ) / vArtNormale.z;
	Normalize( &vArtDir3D );

	const CVec2 vArtCenter( GetCenter() );
	const CVec3 vArtCenter3D( vArtCenter.x, vArtCenter.y, theStaticMap.GetVisZ( vArtCenter.x, vArtCenter.y ) );

	return vArtCenter3D + vArtDir3D * static_cast<const SMechUnitRPGStats*>( GetStats() )->vTowPoint.y;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CVec2 CArtillery::GetHookPoint() const
{
	const CVec3 vHookPoint3D( GetHookPoint3D() );
	return CVec2( vHookPoint3D.x, vHookPoint3D.y );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CArtillery::LookForTarget( CAIUnit *pCurTarget, const bool bDamageUpdated, CAIUnit **pBestTarget, CBasicGun **pGun )
{
	CAIUnit::LookForTarget( pCurTarget, bDamageUpdated, pBestTarget, pGun );

	// � ������� ���� ���
	if ( *pBestTarget == 0 && 
			 ( pCurTarget == 0 || pCurTarget->GetStats()->IsInfantry() ) && theDipl.IsAIPlayer( GetPlayer() ) )
	{
		LookForFarTarget( pCurTarget, bDamageUpdated, pBestTarget, pGun );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const float CArtillery::GetDispersionBonus() const
{ 
	return fDispersionBonus * theDifficultyLevel.GetDispersionCoeff( theDipl.GetNParty( GetPlayer() ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const bool CArtillery::NeedDeinstall() const
{ 
	return GetStats()->nUninstallRotate != 0 || GetStats()->nUninstallTransport != 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
