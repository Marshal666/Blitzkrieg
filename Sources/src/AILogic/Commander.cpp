#include "stdafx.h"

#include "Commander.h"
#include "GeneralHelper.h"
#include "TimeCounter.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern CTimeCounter timeCounter;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CCommander::STaskCalcSeverityPredicate::STaskCalcSeverityPredicate()
: nNumberNegative( 0 ), 
	fSeverityNegative( 0 ),
	nNumberPositive( 0 ),
	fSeverityPositive( 0 )
{  
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const float CCommander::STaskCalcSeverityPredicate::GetSeverity() const
{
	if ( nNumberPositive + nNumberNegative )
	{
		return ( fSeverityNegative + fSeverityPositive ) / ( nNumberNegative + nNumberPositive ) ;
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************************************
//*											CCommander*
//*******************************************************************
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CCommander::CCommander()
: fMeanSeverity( 0 )
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float CCommander::GetMeanSeverity() const 
{ 
	return fMeanSeverity; 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCommander::Segment()
{

	// ��������� ������ ����� �������
	SSegmentPredicate segmentPred;
	std::for_each( tasks.begin(), tasks.end(), segmentPred );

	// ������� ����������� ������
	SFinishedPredicate finishedPred;
	Tasks::iterator finishedFirst = std::remove_if( tasks.begin(), tasks.end(), finishedPred );

	// ������� ���� ���������� � ����������� �����
	STakeWorkersPredicate takeWorkers( this );
	std::for_each( finishedFirst, tasks.end(), takeWorkers );
	
	// ������� ����������� ������
	tasks.erase( finishedFirst, tasks.end() );

	// ������������� ������ �� �����������
	STaskSortPresicate pr;
	std::sort( tasks.begin(), tasks.end(), pr );

	// ��������� ������� ��������� ���� ������
	STaskCalcSeverityPredicate calcSeverity;
	calcSeverity = std::for_each( tasks.begin(), tasks.end(), calcSeverity );
	fMeanSeverity = calcSeverity.GetSeverity();

	
	// � ������, ������� ��� ������ ���������� ������� ������ �����
	for ( Tasks::iterator i = tasks.begin(); i != tasks.end(); ++i )
		(*i)->ReleaseWorker( this, fMeanSeverity );
	
	for ( Tasks::reverse_iterator i = tasks.rbegin(); i != tasks.rend(); ++i )
		(*i)->AskForWorker( this, fMeanSeverity );

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCommander::EnumWorkersInternal( const enum EForceType eType, IWorkerEnumerator *pEn, CommonUnits *pUnits )
{
	// the simple optimisation
	if ( pEn->NeedNBest( eType ) > 1 )
	{
		std::vector< std::pair<float, CPtr<CCommonUnit> > > units;
		for ( CommonUnits::iterator it = pUnits->begin(); it != pUnits->end(); ++it )
			units.push_back( std::pair<float, CPtr<CCommonUnit> >( 0, *it ) );
		pUnits->clear();
		SCalcRatingPredicate calcRating( pEn, eType );
		std::for_each( units.begin(), units.end(), calcRating );
		std::sort( units.begin(), units.end(), calcRating );
		
		bool bNeedMore = true;
		for ( int i = 0; i < units.size(); ++i )
		{
			if ( bNeedMore && pEn->EvaluateWorker( units[i].second, eType ) )
			{
				if ( pEn->EnumWorker( units[i].second, eType ) )
					bNeedMore = true;
			}
			else
				pUnits->push_back( units[i].second );
		}
	}
	else if ( 1 == pEn->NeedNBest( eType ) )
	{
		SGeneralHelper::SFindBestByEnumeratorPredicate prBest( pEn, eType );
		prBest = std::for_each( pUnits->begin(), pUnits->end(), prBest );
		if ( prBest.pBest )
		{
			pEn->EnumWorker( prBest.pBest, eType );
			CommonUnits::iterator added = std::find_if( pUnits->begin(), pUnits->end(), std::bind2nd(std::equal_to<CCommonUnit*>(), prBest.pBest));
			pUnits->erase( added );
		}
	}
	else
	{
  	SGeneralHelper::SFindByEnumeratorPredicate pr( pEn, eType );
		CommonUnits::iterator suitable = std::remove_if( pUnits->begin(), pUnits->end(), pr );
		
		bool bNeedMore = true;
		for ( CommonUnits::iterator it = suitable; it != pUnits->end() && bNeedMore; )
		{
			bNeedMore = pEn->EnumWorker( *it, eType );
			it = pUnits->erase( it );
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
