#ifndef __BINKVIDEOPLAYER_H__
#define __BINKVIDEOPLAYER_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <bink.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SImagePart
{
	CPtr<IGFXTexture> pTexture;					// real vid-mem texture
	CTRect<long> rcSrcRect;							// source rect to blit uncompressed bink from
	CTRect<long> rcDstRect;							// destination rect to blit uncompressed bink data to (from source rect)
	CTRect<float> rcMaps;								// mapping coords
	CTRect<float> rcRect;								// drawing rect
	//
	SImagePart() : rcSrcRect( 0, 0, 0, 0 ), rcDstRect( 0, 0, 0, 0 ), rcMaps( 0, 0, 0, 0 ), rcRect( 0, 0, 0, 0 ) {  }
};
typedef std::vector<SImagePart> CImagesList;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CBinkVideoPlayer : public CTRefCount<IVideoPlayer>
{
	OBJECT_SERVICE_METHODS( CBinkVideoPlayer );
	DECLARE_SERIALIZE;
	//
	CImagesList images;										// all subimages
	CTRect<float> rcDstRect;							// destination rect to render to
	bool bMaintainAspect;									// do we need maintain aspect ratio?
	DWORD dwCopyFlags;										// copy flags
	DWORD dwPlayFlags;										// play flags
	HBINK hBink;													// bink main handler
	bool bLooped;													// is looped movie?
	int nLastPlayedFrame;									// last frame, which was played
	bool bStopped;												// bink playing stopped, but handle was not closed
	// shading effects
	int nShadingEffectStart;							// before draw
	int nShadingEffectFinish;							// after draw
	//
	std::vector<char> buffer;							// buffer to play bink from memory
	std::string szFileName;								// bink file name (to restore)
	//
	bool OpenBink( const char *pszFileName, DWORD dwOpenFlags, DWORD dwFlags );
	// do one frame
	bool DoOneFrame( bool bCheckForStop = true );
	void CopyRects();
	void SetupRects();
public:
	CBinkVideoPlayer();
	virtual ~CBinkVideoPlayer();
	// setup target to render video to. by default it renders to own internal texture(s)
	virtual void STDCALL SetTarget( interface IGFXTexture *pTexture, IGFX *pGFX );
	// set destination rect to render to
	virtual void STDCALL SetDstRect( const RECT &_rcDstRect, bool bMaintainAspect );
	// set loop mode
	virtual void STDCALL SetLoopMode( bool _bLooped ) { bLooped = _bLooped; }
	// playing position
	virtual int STDCALL GetCurrentFrame() const;
	virtual bool STDCALL SetCurrentFrame( const int nFrame );
	// shading effect
	virtual void SetShadingEffect( const int nEffect, bool bStart )
	{
		if ( bStart ) 
			nShadingEffectStart = nEffect;
		else
			nShadingEffectFinish = nEffect;
	}
	// frame update
	virtual bool STDCALL Update( const NTimer::STime &time, bool bForcedUpdate );
	// playing capabilities
	virtual int STDCALL Play( const char *pszFileName, DWORD dwFlags, IGFX *pGFX, interface ISFX *pSFX );
	virtual bool STDCALL Stop();
	virtual bool STDCALL Pause( bool bPause );
	virtual bool STDCALL IsPlaying() const;
	// movie statistics:
	virtual int STDCALL GetLength() const;
	virtual int STDCALL GetNumFrames() const;
	virtual bool STDCALL GetMovieSize( CVec2 *pSize ) const;
	// drawing
	virtual bool STDCALL Draw( interface IGFX *pGFX );
	// visiting
	virtual void STDCALL Visit( interface ISceneVisitor *pVisitor, int nType = -1 );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __BINKVIDEOPLAYER_H__
