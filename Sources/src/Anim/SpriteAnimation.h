#ifndef __SPRITEANIMATION_H__
#define __SPRITEANIMATION_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSpriteAnimation : public ISpriteAnimation
{
	OBJECT_COMPLETE_METHODS( CSpriteAnimation );
	DECLARE_SERIALIZE;
	//
	CPtr<SSpriteAnimationFormat> pAnimations; // all animations
	const SSpriteAnimationFormat::SSpriteAnimation *pAnimation; // current animation shortcut
	int nCurrAnim;												// current animation
	CScaleTimer timer;										// timer...
	std::vector<float> timescales;				// time scaling coeffs for each animation
	int nCurrDirection;										// current direction
	float fScale;													// scaling coeff
	SSpriteRect rect;											// temporal storage for return value
	int nFrameIndex;											// index for static non-animated frames
	//
	bool ReAcquireAnimation()
	{
		if ( (pAnimations != 0) && (nCurrAnim != -1) )
		{
			pAnimation = pAnimations->GetAnimation( nCurrAnim );
			if ( pAnimation == 0 )
			{
				nCurrAnim = -1;
				return false;
			}
			else if ( pAnimation->dirs.empty() ) 
			{
				//NI_ASSERT_SLOW_T( !pAnimation->dirs.empty(), NStr::Format("Empty animation %d set for \"%s\"", nCurrAnim, pAnimations->GetSharedResourceName()) );
				pAnimation = 0;
				nCurrAnim = -1;
				return false;
			}
			else
			{
				timer.SetScale( timescales[nCurrAnim] );
				return true;
			}
		}
		else
			return false;
	}
public:
	CSpriteAnimation()
		: pAnimations( 0 ), pAnimation( 0 ), nCurrAnim( -1 ), nCurrDirection( 0 ), fScale( 1 ), nFrameIndex( -1 ) {  }
	//
	bool Init( SSpriteAnimationFormat *_pAnimations );
	//
	virtual void STDCALL Visit( IAnimVisitor *pVisitor );
	// set current time 
	virtual void STDCALL SetTime( DWORD time ) 
	{ 
		timer.Update( time ); 
	}
	// set animation start time
	virtual void STDCALL SetStartTime( DWORD time ) 
	{ 
		timer.Reset( time ); 
	}
	// set animation time scale coeff
	virtual void STDCALL SetAnimSpeedCoeff( float fCoeff ) 
	{ 
		// CRAP{ can change animation speed only for movement animations (and idle - for projectiles and so on)
		if ( (nCurrAnim == ANIMATION_IDLE) || (nCurrAnim == ANIMATION_MOVE) || (nCurrAnim == ANIMATION_CRAWL) ) 
		{
			timer.SetScale( fCoeff ); 
			if ( nCurrAnim != -1 ) 
				timescales[nCurrAnim] = fCoeff; 
		}
		// CRAP}
	}
	// change animation
	virtual bool STDCALL SetAnimation( const int nAnim ) { nCurrAnim = nAnim; return ReAcquireAnimation(); }
	virtual int STDCALL GetAnimation() const { return nCurrAnim; };
	// get current animation lenght
	virtual int STDCALL GetLengthOf( const int nAnim )
	{
		if ( pAnimations )
		{
			const SSpriteAnimationFormat::SSpriteAnimation *pTempAnim = pAnimations->GetAnimation( nAnim );
			NI_ASSERT_SLOW_TF( pTempAnim != 0, NStr::Format("Can't get animation %d for the length check for \"%s\"", nAnim, pAnimations->GetSharedResourceName()), return 1 );
			return pTempAnim->GetLength();
		}
		else
			return 1;
	}
	// set scaling coeff
	virtual void STDCALL SetScale( float _fScale ) { fScale = _fScale; }
	// set animation direction
	virtual void STDCALL SetDirection( int nDirection ) { nCurrDirection = nDirection; }
	// get current mapping rect
	virtual const SSpriteRect& STDCALL GetRect()
	{
		if ( (pAnimation == 0) && !ReAcquireAnimation() )
			return rect;
		else if ( nFrameIndex == -1 )
			rect = pAnimation->GetRect( nCurrDirection, timer.Get() );
		else
			rect = pAnimation->GetRect( nFrameIndex );
		//
		rect.rect *= fScale;
		return rect;
	}
	// get translation speed, attached to this animation
	virtual float STDCALL GetSpeed() const { return pAnimation ? pAnimation->fSpeed : 1; }
	// frame index setup
	virtual void STDCALL SetFrameIndex( int nIndex ) { nFrameIndex = nIndex; }
	virtual int STDCALL GetFrameIndex() { return nFrameIndex; }
	// hit test
	virtual const bool STDCALL IsHit( const CVec3 &relpos, const CVec2 &point, CVec2 *pShift ) const;
	virtual const bool STDCALL IsHit( const CVec3 &relpos, const CTRect<float> &rcRect ) const;
	// scale timer
	virtual const CScaleTimer& STDCALL GetScaleTimer() const { return timer; }
	virtual void STDCALL SetScaleTimer( const CScaleTimer &_timer ) { timer = _timer; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CComplexSprite : public CTRefCount<ISpriteAnimation>
{
	OBJECT_SERVICE_METHODS( CComplexSprite );
	DECLARE_SERIALIZE;
	//
	CPtr<SSpritesPack> pSprites;
	CScaleTimer timer;										// timer...
	int nFrameIndex;											// current frame index (if it is)
	SSpriteRect spriteRect;								// temp sprite rect
	//
	const SSpritesPack::SSprite& GetSprite() const { return pSprites->sprites[nFrameIndex == -1 ? 0 : nFrameIndex]; }
public:
	bool Init( SSpritesPack *_pSprites ) { pSprites = _pSprites; nFrameIndex = 0; return true; }
	//
	virtual void STDCALL Visit( IAnimVisitor *pVisitor );
	// set current time 
	virtual void STDCALL SetTime( DWORD time ) { timer.Update( time ); }
	// set animation start time
	virtual void STDCALL SetStartTime( DWORD time ) { timer.Reset( time ); }
	// set animation time scale coeff
	virtual void STDCALL SetAnimSpeedCoeff( float fCoeff ) { timer.SetScale( fCoeff ); }
	// change animation
	virtual bool STDCALL SetAnimation( const int nAnim ) { return true; }
	virtual int STDCALL GetAnimation() const { return 0; };
	// get current animation lenght
	virtual int STDCALL GetLengthOf( const int nAnim ) { return 1; }
	// set scaling coeff
	virtual void STDCALL SetScale( float _fScale ) {  }
	// set animation direction
	virtual void STDCALL SetDirection( int nDirection ) {  }
	// get current mapping rect
	virtual const SSpriteRect& STDCALL GetRect()
	{
		const int nLocalFrameIndex = nFrameIndex == -1 ? 0 : nFrameIndex;
		const CTRect<float> &rcBoundBox = pSprites->sprites[nLocalFrameIndex].GetBoundBox();
		spriteRect.rect.Set( rcBoundBox.x1, rcBoundBox.y1, rcBoundBox.x2, rcBoundBox.y2 );
		spriteRect.fDepthLeft = spriteRect.fDepthRight = pSprites->sprites[nLocalFrameIndex].fMinDepth;
		return spriteRect;
	}
	// get translation speed, attached to this animation
	virtual float STDCALL GetSpeed() const { return 1; }
	// frame index setup
	virtual void STDCALL SetFrameIndex( int nIndex ) { nFrameIndex = nIndex; }
	virtual int STDCALL GetFrameIndex() { return nFrameIndex; }
	// hit test
	virtual const bool STDCALL IsHit( const CVec3 &relpos, const CVec2 &point, CVec2 *pShift ) const;
	virtual const bool STDCALL IsHit( const CVec3 &relpos, const CTRect<float> &rcRect ) const;
	// scale timer
	virtual const CScaleTimer& STDCALL GetScaleTimer() const { return timer; }
	virtual void STDCALL SetScaleTimer( const CScaleTimer &_timer ) { timer = _timer; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __SPRITEANIMATION_H__