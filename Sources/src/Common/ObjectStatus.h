#ifndef __OBJECTSTATUS_H__
#define __OBJECTSTATUS_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "..\Main\RPGStats.h"
#include "..\GameTT\iMission.h"
#include "..\AILogic\AILogic.h"
#include "..\AILogic\DifficultyLevel.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** get stats, common for infantry and mechanical units
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void GetBaseStatusFromRPGStats( SMissionStatusObject *pStatus, const SUnitBaseRPGStats *pRPG, 
																			 const int nParty, bool bEnableModification )
{
	if ( pRPG->pPrimaryGun && pRPG->pPrimaryGun->pWeapon && !pRPG->pPrimaryGun->pWeapon->shells.empty() ) 
	{
		const CDifficultyLevel *pLevel = GetSingleton<IAILogic>()->GetDifficultyLevel();
		const SWeaponRPGStats::SShell &shell = pRPG->pPrimaryGun->pWeapon->shells[0];
		if ( bEnableModification ) 
		{
			pStatus->weaponstats[0] = shell.fDamagePower;// * pLevel->GetDamageCoeff( nParty );
			pStatus->weaponstats[1] = shell.nPiercing * pLevel->GetPiercingCoeff( nParty );
			pStatus->weaponstats[2] = pRPG->pPrimaryGun->pWeapon->nCeiling;
		}
		else
		{
			pStatus->weaponstats[0] = shell.fDamagePower;
			pStatus->weaponstats[1] = shell.nPiercing;
			pStatus->weaponstats[2] = pRPG->pPrimaryGun->pWeapon->nCeiling;
		}
	}
	else
		Zero( pStatus->weaponstats );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** get mechanical unit stats
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void GetStatusFromRPGStats( SMissionStatusObject *pStatus, const SMechUnitRPGStats *pRPG, 
																	 const bool bEnemy = false, bool bEnableModification = true )
{
	GetBaseStatusFromRPGStats( pStatus, pRPG, bEnemy ? 1 : 0, false /*bEnableModification*/ ); // ������ �� ��������� ���������� ����������� �������
	//
	pStatus->armors[0] = pRPG->GetArmor( RPG_FRONT );
	pStatus->armors[1] = ( pRPG->GetArmor( RPG_LEFT ) + pRPG->GetArmor( RPG_RIGHT ) ) / 2;
	pStatus->armors[2] = pRPG->GetArmor( RPG_BACK );
	pStatus->armors[3] = pRPG->GetArmor( RPG_TOP );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** get infantry unit stats
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void GetStatusFromRPGStats( SMissionStatusObject *pStatus, const SInfantryRPGStats *pRPG, 
																	 const bool bEnemy = false, bool bEnableModification = true )
{
	GetBaseStatusFromRPGStats( pStatus, pRPG, bEnemy ? 1 : 0, false /*bEnableModification*/ ); // ������ �� ��������� ���������� ����������� �������
	//
	Zero( pStatus->armors );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __OBJECTSTATUS_H__