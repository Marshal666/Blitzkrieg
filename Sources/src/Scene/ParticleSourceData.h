#ifndef __PARTICLESOURCEDATA_H__
#define __PARTICLESOURCEDATA_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "PFX.h"
#include "Track.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SExtendedParticle: public SSimpleParticle
{
	NTimer::STime birthTime;              // ����� ��������
	NTimer::STime deathTime;              // ����� ������
	float fSpin;                          // ������� ��������
	CVec3 vSpeed;                         // ������ ��������
	CVec3 vWind;                          // ����� ��� �������
	float fOpacity;                       // ��������� ������������
	STrackContext contextSpeed;						// ��������� ��� ������� ����������
	STrackContext contextZSpeed; 
	STrackContext contextSpin;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum
{
	PSA_TYPE_SQUARE = 0,
	PSA_TYPE_DISK   = 1,
	PSA_TYPE_CIRCLE = 2
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SParticleSourceData : public CTRefCount<ISharedResource>
{
	OBJECT_SERVICE_METHODS( SParticleSourceData );
	DECLARE_SERIALIZE;
	SHARED_RESOURCE_METHODS( nRefData, "ParticleSource.Data" );
public:
	SParticleSourceData();

	bool bComplexParticleSource;					//��� ���������, ���� true, complex particle source
	// ��������� ����������
	int nLifeTime;												// ����� ����� ����� ���������
	float fGravity;												// �������� ���������� (�������� ��������� � ������ �� �����)
	int nTextureDX;												// ������� ������ �� X (��� ������������� ��������)
	int nTextureDY;												// ������� ������ �� Y (��� ������������� ��������)
	std::string szTextureName;            // �������� ��������
	CVec3 vWind;                          // �����
	CVec3 vDirection;                     // ����������� ���������
	int nAreaType;                        // ��� ������� ��� ��������� ���������
	float fRadialWind;                    // ���� ����������� �����
	CTrack trackGenerateArea;							// ������ ������� �� ������� �������� �������� 
	CTrack trackDensity;									// �-�� ��������� ��������� � ��. ������� 
	CTrack trackBeginSpeed;								// ��������� �������� ������� ���  ������ 
	CTrack trackBeginSpeedRandomizer;     // �� ������������
	CTrack trackBeginAngleRandomizer;			// ������������ ���� ������ (� ��������, �� 0 �� PI)
	CTrack trackLife;											// ������� ����� ������� ����� ���������
	CTrack trackLifeRandomizer;           // ������������ ����������� (�� 0 �� 1)
	CTrack trackGenerateSpin;							// ��������� ������� �������� ��� ������ 
	CTrack trackGenerateSpinRandomizer;   // ������������ ����������� (����� ��������, �� ���� �� �������)
	CTrack trackGenerateOpacity;					// ��������� ������������ ��� ������ ( 0 - 255 ) 
	// ��������� ����� �������
	CTrack trackSpin;                     // �����. ������� �������� (0-1)
	CTrack trackSpeed;                    // �����. �������� (0-1)
	CTrack trackSpeedRnd;                 // ��� ������������ (0-1)
	CTrack trackWeight;										// ����� �������� (�������� ��������� � ���������� ����� �� �����)
	CTrack trackTextureFrame;							// frame in texture [0..1]
	CTrack trackSize;											// ������ ������� (0-1)
	CTrack trackOpacity;									// ����������� �� ������������ (0-1)
	CTrack trackIntegralMass;             // ������������� �� g*m(t), ���������� �� ����������� �������� (��� ��� �������) (��������� �� ����, �������������� �� ���� ����)
	float fDensityCoeff;                  // ����������� �� ���������, ������� �� ���������
	//
	virtual void STDCALL Init();
	virtual void STDCALL InitIntegrals();
	virtual void STDCALL SwapData( ISharedResource *pResource );
	// internal container clearing
	virtual void STDCALL ClearInternalContainer() {  }
	virtual bool STDCALL Load( const bool bPreLoad = false );
	//
	virtual int STDCALL operator&( IDataTree &ss );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __PARTICLESOURCEDATA_H__
