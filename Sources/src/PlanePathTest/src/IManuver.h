/* Generated by Together */

#ifndef IMANUVER_H
#define IMANUVER_H


extern float g;
/**
 * � �������� ������� ���� ID.
 * @interface
 */
interface IManuver : public IRefCount
{
	// world position
	virtual CVec3 STDCALL GetPos() const = 0;
	// plane speed 
	virtual CVec3 STDCALL GetSpeed() const = 0;
	// plane's top direction
	virtual CVec3 STDCALL GetNormale() const = 0;
	// preferred top direction
	virtual CVec3 STDCALL GetTopDirection() const = 0;

	// advance plane according it's speed 
	//return true if manuver is finished.
	virtual bool STDCALL Advance( const NTimer::STime timeDiff ) = 0;

	// PREDICTION
	// return approximate point, where plane will be in fT time.
	virtual CVec3 GetProspectivePoint( const float fT ) const = 0;
	
	// init manuver to specific point, or destination (COMBAT ONLY)
	virtual void Init( const enum EManuverDestination dest, interface IPlane *pPlane, interface IPlane *pEnemy = 0 ) { NI_ASSERT_T(false,"WRONG CALL");}


	//CRAP{ FOR TEST
	virtual const CVec3 STDCALL GetEndPoint() const = 0;
	//CRAP}
};
#endif //IMANUVER_H