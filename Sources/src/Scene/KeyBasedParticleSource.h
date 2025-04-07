#ifndef __KEYBASEDPARTICLESOURCE_H__
#define __KEYBASEDPARTICLESOURCE_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "PFX.h"
#include "ParticleSourceData.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CKeyBasedParticleSource : public IParticleSource, public IParticleSourceWithInfo
{
	OBJECT_NORMAL_METHODS(CKeyBasedParticleSource);
	DECLARE_SERIALIZE;
	//
	CPtr<SParticleSourceData> pData;			// данные об источнике
	NTimer::STime nStartTime;             // врем€ рождени€
	NTimer::STime nLastUpdateTime;				// врем€ последнего обновлени€
	NTimer::STime nLastParticleUpdate;    // врем€ последнего обновлени€ сгенеренных партиклов
	CVec3 vPosition;											// относительно положение источника
	float fDirectionPhi;                  // направление источника в сферической системе координат
	float fDirectionTheta;                // направление источника в сферической системе координат
	CVec3 vDirection;                     // направдение источнике без учета pData
	CPtr<IGFXTexture> pTexture;           // текстура с партиклами
	float lastError;                      // поправка на нецелое число партиклов при последней генерации
	std::vector< CTRect<float> > rcRects;  // координаты текстурных фреймов
	std::list<SExtendedParticle> particles; // они
	float fScale;                         // масштаб эффекта
	bool bStopped;                        // остановка эффекта
	bool bSuspended;               
	STrackContext contextDensity;         // контекст дл€ интегрировани€ плотности партиклов
	typedef CVec3 GetParticlePositionFunction( const float area, const CVec3 &vPosition );
	GetParticlePositionFunction *pfnGPPfunc; // указатель на функцию, определ€ющую характер области вылета частиц
public:
			// data retrieving for rendering
	virtual interface IGFXTexture* STDCALL GetTexture() const;
	virtual const int STDCALL GetNumParticles() const;
	virtual void STDCALL FillParticleBuffer( SSimpleParticle *buff ) const;
	// position/direction
	virtual const CVec3 STDCALL GetPos() const;
	virtual void STDCALL SetPos( const CVec3 &vPos );
	virtual const CVec3 STDCALL GetDirection() const;
	virtual void STDCALL SetScale( float _fScale );
	virtual void STDCALL SetDirection( const SHMatrix &mDir );
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
	virtual void Init( SParticleSourceData *_pData );
	virtual int STDCALL GetOptimalUpdateTime() const;
	virtual void STDCALL SetSuspendedState( bool bState );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CParticleGenerator
{
	static float fStartAngle;
	static float nCurrParticle;
	static float fStep;
public:
	static CVec3 GetParticlePositionSquare( const float area, const CVec3 &vPosition );
	static CVec3 GetParticlePositionDisk( const float area, const CVec3 &vPosition );
	static CVec3 GetParticlePositionCircle( const float area, const CVec3 &vPosition );
	static void ResetGenerator( int nNextNumParticles );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __KEYBASEDPARTICLESOURCE_H__
