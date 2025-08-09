#ifndef __FFMPEGVIDEOPLAYER_H__
#define __FFMPEGVIDEOPLAYER_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <inttypes.h>

//#include <dsound.h>

// trick the C++ compiled to get these types from dsound
struct IDirectSound;
struct IDirectSoundBuffer;
typedef struct IDirectSound *LPDIRECTSOUND,**LPLPDIRECTSOUND;
typedef struct IDirectSoundBuffer *LPDIRECTSOUNDBUFFER,**LPLPDIRECTSOUNDBUFFER;

#ifndef UINT64_C
  #ifdef _MSC_VER
    // MSVC: Use UL for unsigned long long constants
    #define UINT64_C(val) val##UI64
  #else
    // Other compilers: Use ULL suffix
    #define UINT64_C(val) val##ULL
  #endif
#endif

#ifndef INT64_C
  #ifdef _MSC_VER
    // MSVC uses 'i64' suffix for signed 64-bit constants
    #define INT64_C(val) val##i64
  #else
    // Most GCC/Clang compilers use 'LL' for signed 64-bit
    #define INT64_C(val) val##LL
  #endif
#endif

extern "C" {
	#include <libavformat/avformat.h>
	#include <libavcodec/avcodec.h>
	#include <libavutil/avutil.h>
	#include <libswscale/swscale.h>
}

typedef long s32;

// most of the code for FFMPEGVideoPlayer was written by Claude AI
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
class CFFMPEGVideoPlayer : public CTRefCount<IVideoPlayer>
{
	OBJECT_SERVICE_METHODS( CFFMPEGVideoPlayer );
	DECLARE_SERIALIZE;
	//
	CImagesList images;										// all subimages
	CTRect<float> rcDstRect;							// destination rect to render to
	bool bMaintainAspect;									// do we need maintain aspect ratio?
	DWORD dwPlayFlags;										// play flags
	bool bLooped;													// is looped movie?
	int nLastPlayedFrame;									// last frame, which was played
	bool bStopped;												// ffmpeg playing stopped, but handle was not closed
	bool bPaused;													// pause state
	// shading effects
	int nShadingEffectStart;							// before draw
	int nShadingEffectFinish;							// after draw
	//
	std::vector<char> buffer;							// buffer to play from memory
	std::string szFileName;								// file name (to restore)
	
	// FFmpeg specific members
	AVFormatContext *pFormatContext;
	AVCodecContext *pCodecContext;
	AVCodec *pCodec;
	AVFrame *pFrame;
	AVFrame *pFrameRGB;
	AVPacket packet;
	struct SwsContext *pSwsContext;
	int nVideoStream;
	uint8_t *pFrameBuffer;

	// sound
	AVCodecContext *pAudioCodecContext;
	AVCodec *pAudioCodec;
	AVFrame *pAudioFrame;
	int nAudioStream;
	LPDIRECTSOUNDBUFFER pAudioBuffer;
	LPDIRECTSOUND pDirectSound;
	DWORD dwAudioBufferSize;
	DWORD dwAudioWritePos;
	
	// timing
	double dFrameRate;
	double dTimePerFrame;
	DWORD dwStartTime;
	DWORD dwPauseTime;
	DWORD dwTotalPauseTime;

	// Audio-Video sync members
	double dAudioClock;
	double dVideoClock;
	int nAudioSamplesPlayed;
	DWORD dwLastAudioCheckTime;
	bool bUseAudioSync;
	double dSyncThreshold;
	DWORD dwAudioReadPos;

	int nAudioSamplesWritten;
	bool bAudioStarted;
	int nAudioUnderrunCount;
	
	//
	bool OpenFFMPEG( const char *pszFileName, DWORD dwFlags );
	bool DecodeFrame();
	void CopyFrameToTextures();
	void SetupRects();
	void CloseFFMPEG();
	bool SeekToFrame( int nFrame );
	bool SetupAudioBuffer();
	void WriteAudioToBuffer( uint8_t* pAudioData, int nDataSize );

	void UpdateAudioClock();
	void SetAudioSyncEnabled( bool bEnabled );
	void SetSyncThreshold( double dThreshold );
	double GetAudioVideoDrift() const;
	int ConvertAudioSample( const AVFrame* pFrame, int16_t* pOutputBuffer, int nMaxOutputSize );
	
public:
	CFFMPEGVideoPlayer();
	virtual ~CFFMPEGVideoPlayer();
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
#endif // __FFMPEGVIDEOPLAYER_H__