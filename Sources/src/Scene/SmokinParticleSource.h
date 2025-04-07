#ifndef __SMOKINPARTICLESOURCE_H__
#define __SMOKINPARTICLESOURCE_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "PFX.h"
#include "SmokinParticleSourceData.h"
#include "KeyBasedParticleSource.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SExtendedParticleSource
{
	CPtr<IParticleSource> pSource;        // ��, ��� �����
	CVec3 vSpeed;                         // ������ ��������
	CVec3 vWind;                          // ����� ��� �������
	STrackContext contextSpeed;						// ��������� ��� ������� ����������
	STrackContext contextZSpeed;          // 
	//
	int operator&( IStructureSaver &ss );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSmokinParticleSource : public IParticleSource, public IParticleSourceWithInfo
{
	OBJECT_NORMAL_METHODS(CSmokinParticleSource);
	DECLARE_SERIALIZE;
	CPtr<SSmokinParticleSourceData> pData;			// ������ �� ���������
	NTimer::STime nStartTime;             // ����� ��������
	NTimer::STime nLastUpdateTime;				// ����� ���������� ����������
	CVec3 vPosition;											// ������������ ��������� ���������
	float fDirectionPhi;                   // ����������� ��������� � ����������� ������� ���������
	float fDirectionTheta;                 // ����������� ��������� � ����������� ������� ���������
	CVec3 vDirection;                     // ����������� ��������� ��� ����� pData
	float lastError;                      // �������� �� ������� ����� ��������� ��� ��������� ���������
	std::list<SExtendedParticleSource> particles; // ���
	float fScale;                         // ������� �������
	bool bStopped;                        // ��������� �������
	STrackContext contextDensity;         // �������� ��� �������������� ��������� ���������
	typedef CVec3 GetParticlePositionFunction( const float area, const CVec3 &vPosition );
	GetParticlePositionFunction *pfnGPPfunc;
public:
			// data retrieving for rendering
	virtual interface IGFXTexture* STDCALL GetTexture() const;
	virtual const int STDCALL GetNumParticles() const;
	virtual void STDCALL FillParticleBuffer( SSimpleParticle *buff ) const;
	// position/direction
	virtual const CVec3 STDCALL GetPos() const;
	virtual void STDCALL SetPos( const CVec3 &vPos );
	virtual const CVec3 STDCALL GetDirection() const;
	virtual void STDCALL SetDirection( const SHMatrix &mDir );
	virtual void STDCALL SetScale( float _fScale );
	// update and work with time
	virtual void STDCALL Update( const NTimer::STime &time );
	virtual void STDCALL SetStartTime( const NTimer::STime &time );
	virtual const NTimer::STime STDCALL GetStartTime() const;
	virtual const NTimer::STime STDCALL GetEffectLifeTime() const;
	virtual bool STDCALL IsFinished() const;
	// statistics
	virtual void STDCALL GetInfo( SParticleSourceInfo &info );
	virtual float STDCALL GetArea() const;
	virtual void STDCALL Stop();
	//
	virtual void Init( SSmokinParticleSourceData *_pData );
	virtual int STDCALL GetOptimalUpdateTime() const;
	virtual void STDCALL SetSuspendedState( bool bState );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif 
