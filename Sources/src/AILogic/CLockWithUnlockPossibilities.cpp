#include "stdafx.h"

#include "CLockWithUnlockPossibilities.h"
#include "AIUnit.h"
#include "AIStaticMap.h"
#include "SerializeOwner.h"
#include "UnitsIterators2.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern CStaticMap theStaticMap;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************************************
//*										  CLockWithUnlockPossibilities								*
//*******************************************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CLockWithUnlockPossibilities::TryLockAlongTheWay( const bool bLock, const BYTE _bAIClass )
{
	// залочить/разлочить тайлы 
	if ( bLock )
	{
		NI_ASSERT_T( pathTiles.size() == 0, "wrong call" );
		NI_ASSERT_T( formerTilesType.size() == 0, "wrong call" );
		// найти количество юнитов, которые могут быть на нашем пути.
		int nUnits = 0;
		for ( CUnitsIter<0,3> iter( 0, ANY_PARTY, bigRect.center, Max( bigRect.width, Max(bigRect.lengthAhead,bigRect.lengthBack) ) );
					!iter.IsFinished(); iter.Iterate() )
		{
			if ( bigRect.IsIntersected( (*iter)->GetUnitRect() ) ) 
			{
				if ( ++nUnits > 1 )
					return false;
			}
		}

		// разлочить танк
		// запомнить состояние залоченности на всем пути и выяснить возможность танку выехать
		GetTilesCoveredByRect( bigRect, &pathTiles );

		
		formerTilesType.resize( pathTiles.size() );
		int i = 0;
		bool bPossible = true;
		bAIClass = _bAIClass;
		for ( CTilesSet::iterator it = pathTiles.begin(); it != pathTiles.end(); ++it )
		{
			BYTE b = theStaticMap.GetTileLockInfo( (*it) );
			formerTilesType[i] = b;
			bPossible &= !(formerTilesType[i] & bAIClass); // может ли танк проехать по нужному пути
			++i;
		}
		if (!bPossible)
		{
			pathTiles.clear();
			formerTilesType.clear();
			return false;
		}
		else
		{
			// разлочить старые
			Unlock();

			// все по-новому залочить
			for ( CTilesSet::iterator it = pathTiles.begin(); it != pathTiles.end(); ++it )
			{
				theStaticMap.LockTile( (*it), AI_CLASS_ANY );
			}
			SVector vMax, vMin;
			theStaticMap.CalcMaxesBoundsByTiles( pathTiles, &vMin, &vMax );
			theStaticMap.UpdateMaxesForAddedStObject( vMin.x, vMax.x, vMin.y, vMax.y, AI_CLASS_ANY );
		}
	}
	else
	{
		if ( pathTiles.size() != 0 ) // что-то лочили
		{
			//разлочить 
			for ( CTilesSet::iterator it = pathTiles.begin(); it != pathTiles.end(); ++it )
				theStaticMap.UnlockTile( (*it), AI_CLASS_ANY );
			SVector vMax, vMin;
			theStaticMap.CalcMaxesBoundsByTiles( pathTiles, &vMin, &vMax );
			theStaticMap.UpdateMaxesForRemovedStObject( vMin.x, vMax.x, vMin.y, vMax.y, AI_CLASS_ANY );

			//залочить как было до начала движения
			Lock();

			pathTiles.clear();
			formerTilesType.clear();
		}
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLockWithUnlockPossibilities::Lock()
{
	int i=0;
	BYTE aiClass=0;
	bool aiAnyExists = false;
	for ( CTilesSet::iterator it = pathTiles.begin(); it != pathTiles.end(); ++it )
	{
		theStaticMap.LockTile( (*it), formerTilesType[i] );
		aiClass |= formerTilesType[i];
		aiAnyExists |= (formerTilesType[i]==AI_CLASS_ANY);
		++i;
	}
	SVector vMax, vMin;
	theStaticMap.CalcMaxesBoundsByTiles( pathTiles, &vMin, &vMax );
	if ( aiAnyExists )
		theStaticMap.UpdateMaxesForAddedStObject( vMin.x, vMax.x, vMin.y, vMax.y, AI_CLASS_ANY );
	theStaticMap.UpdateMaxesForAddedStObject( vMin.x, vMax.x, vMin.y, vMax.y, aiClass&(~AI_CLASS_ANY) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLockWithUnlockPossibilities::Unlock()
{
	int i=0;
	BYTE aiClass=0;
	bool aiAnyExists = false;
	for ( CTilesSet::iterator it = pathTiles.begin(); it != pathTiles.end(); ++it )
	{
		theStaticMap.UnlockTile( (*it), formerTilesType[i] );
		aiClass |= formerTilesType[i];
		aiAnyExists |= (formerTilesType[i]==AI_CLASS_ANY);
		++i;
	}
	SVector vMax, vMin;
	theStaticMap.CalcMaxesBoundsByTiles( pathTiles, &vMin, &vMax );
	if ( aiAnyExists )
		theStaticMap.UpdateMaxesForRemovedStObject( vMin.x, vMax.x, vMin.y, vMax.y, AI_CLASS_ANY );
	theStaticMap.UpdateMaxesForRemovedStObject( vMin.x, vMax.x, vMin.y, vMax.y, aiClass&(~AI_CLASS_ANY) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CLockWithUnlockPossibilities::operator&( IStructureSaver &ss )
{
	CSaverAccessor saver = &ss;

	saver.Add( 5, &pathTiles );
	saver.Add( 6, &formerTilesType );
	saver.Add( 7, &bigRect );
	saver.Add( 8, &bLocked );
	saver.Add( 9, &bAIClass );
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
