// KeyBasedData.h: interface for the CKeyBasedData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEYBASEDDATA_H__A200BF93_5018_4053_AF5A_78E9878C0636__INCLUDED_)
#define AFX_KEYBASEDDATA_H__A200BF93_5018_4053_AF5A_78E9878C0636__INCLUDED_

#pragma ONCE

#include "SParticleKey.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SParticleSetup
{
	CTrack	trackSpin;												// ��������� �� ������� ��������   ( 1 - 0 ) ( ����� 0 - 100 )
	CTrack	trackGenerateSpin;								// ( ������� �������� ��� ������ ) ( 0 - 2 )
	CTrack	trackLife;												// ������� ����� ������� ����� ��������� ( 10 - 1000 ) ( ����� 0 - 100 )
	CTrack	trackDensity;											// �-�� ��������� ��������� �  ��. ������� ( 0 -  0.1 ) ( ����� 0 - 100 )
	CVec3		vWind;														// ����� ( 0,0,0 )
	CTrack	trackWeight;										  // ����� �������� ( 0 - 10 ) ( �� ��������� 1 ) ( ����� 0 - 100 )
	CTrack	trackSpeed;											  // ��������� �������� ( 1 - 0 ) ( ����� 0 - 100 ) ( ����� 0 - 100 )
	CTrack	trackGenerateArea;							  // ������ ������� �� ������� �������� �������� ( 1 - 100 ) ( ����� 0 - 100 )
	CVec3		vDirection;												// ����������� ( 0,0,1 )
	int 		nGenerateAngel;										// 0 - max , 100000 ~ min ( ���� ��������� )
	CTrack	trackBeginSpeed;									// ��������� �������� ������� ���  ������ ( 0 - 2 ) ( �� �����  0.20 )
	CVec3		vPosition;
	CTrack 	trackGenerateAngle;								// ���� ��������� 0 - max , 100000 ~ min - ( ����� �� 0 - 100 )
	CTrack 	trackSize;												// ������ ������� ( 1 -  200 ) ( ����� 0 - 100 )
	int			nTextureDX;												// ���������� ��� ������������ �������� - 1
	int			nTextureDY;												// - 1
	float		fGravity;													// g	- "������ g" :)			- ( 0.0001)
	std::string szTextureName;								//
	CTrack 	trackGenerateOpacity;							// ������������ ��� ���������	 ( 0 - 255 ) ( ����� 0 - 100 )
	CTrack 	trackOpacity;											// ��������� �� ������������	( 0 - 1 ) ( ����� 0 - 100 )
	int			nLifeTime;												// ����� �����
	CTrack	trackGenerateSpinRand;						// ������ rand() �� ��������(� ��������� )  ( 0 - 100 )
	CTrack  trackTextureFrame;								// frame in texture [0..1]
	//
	int operator&( IStructureSaver &ss );
	int operator&( IDataTree &ss );
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CKeyBasedData  : public ISharedResource
{
	OBJECT_COMPLETE_METHODS( CKeyBasedData );
	SHARED_RESOURCE_METHODS( nRefData.a );
public:
	SParticleSetup keyData;
	//
	virtual void STDCALL SwapData( ISharedResource *pResource )
	{
		CKeyBasedData *pRes = dynamic_cast<CKeyBasedData*>( pResource );
		NI_ASSERT_TF( pRes != 0, "shared resource is not a CKeyBasedData", return );
		// slow
		std::swap( keyData, pRes->keyData );
	}
	// internal container clearing
	virtual void STDCALL ClearInternalContainer() {  }
	//
	virtual int STDCALL operator&( IDataTree &ss );
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_KEYBASEDDATA_H__A200BF93_5018_4053_AF5A_78E9878C0636__INCLUDED_)
