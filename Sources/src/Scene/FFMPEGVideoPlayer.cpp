#include "StdAfx.h"

#include "FFMPEGVideoPlayer.h"

#include "..\SFX\SFX.h"
#include "..\GFX\GFXHelper.h"
#include "..\Misc\Intersection.h"
#include <mmreg.h>
#include <dsound.h>
#include <math.h>

// Claude needed it, so I delivered
typedef long s32;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CFFMPEGVideoPlayer::CFFMPEGVideoPlayer()
{
	rcDstRect.SetEmpty();
	bMaintainAspect = true;
	nLastPlayedFrame = -1;
	bLooped = false;
	nShadingEffectStart = 17;
	nShadingEffectFinish = 18;
	bStopped = false;
	bPaused = false;
	
	// FFmpeg specific initialization
	pFormatContext = 0;
	pCodecContext = 0;
	pCodec = 0;
	pFrame = 0;
	pFrameRGB = 0;
	pSwsContext = 0;
	nVideoStream = -1;
	pFrameBuffer = 0;
	
	// Audio initialization
	pAudioCodecContext = 0;
	pAudioCodec = 0;
	pAudioFrame = 0;
	nAudioStream = -1;
	pAudioBuffer = 0;
	pDirectSound = 0;
	dwAudioBufferSize = 0;
	dwAudioWritePos = 0;
	dwAudioReadPos = 0;
	
	// timing
	dFrameRate = 0.0;
	dTimePerFrame = 0.0;
	dwStartTime = 0;
	dwPauseTime = 0;
	dwTotalPauseTime = 0;
	dwPlayFlags = 0;
	
	// Audio sync improvements
	bUseAudioSync = false;
	dSyncThreshold = 0.04; // Reduced to 40ms for better sync
	dAudioClock = 0.0;
	dVideoClock = 0.0;
	nAudioSamplesWritten = 0;
	nAudioSamplesPlayed = 0;
	dwLastAudioCheckTime = 0;
	bAudioStarted = false;
	nAudioUnderrunCount = 0;
	
	// Initialize packet
	memset(&packet, 0, sizeof(AVPacket));
	av_init_packet(&packet);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CFFMPEGVideoPlayer::~CFFMPEGVideoPlayer()
{
	CloseFFMPEG();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CFFMPEGVideoPlayer::CloseFFMPEG()
{
	if ( pAudioBuffer )
	{
		pAudioBuffer->Stop();
		pAudioBuffer->Release();
		pAudioBuffer = 0;
	}
	
	if ( pAudioFrame ) 
	{
		av_free( pAudioFrame );
		pAudioFrame = 0;
	}
	
	if ( pAudioCodecContext ) 
	{
		avcodec_close( pAudioCodecContext );
		pAudioCodecContext = 0;
	}
	
	if ( pFrameBuffer ) 
	{
		av_free( pFrameBuffer );
		pFrameBuffer = 0;
	}
	
	if ( pFrameRGB ) 
	{
		av_free( pFrameRGB );
		pFrameRGB = 0;
	}
	
	if ( pFrame ) 
	{
		av_free( pFrame );
		pFrame = 0;
	}
	
	if ( pSwsContext ) 
	{
		sws_freeContext( pSwsContext );
		pSwsContext = 0;
	}
	
	if ( pCodecContext ) 
	{
		avcodec_close( pCodecContext );
		pCodecContext = 0;
	}
	
	if ( pFormatContext ) 
	{
		av_close_input_file( pFormatContext );
		pFormatContext = 0;
	}
	
	// Free any remaining packet data
	if ( packet.data )
		av_free_packet( &packet );
	
	nVideoStream = -1;
	nAudioStream = -1;
	
	// Reset audio sync variables
	dAudioClock = 0.0;
	dVideoClock = 0.0;
	nAudioSamplesWritten = 0;
	nAudioSamplesPlayed = 0;
	dwLastAudioCheckTime = 0;
	bAudioStarted = false;
	nAudioUnderrunCount = 0;
	dwAudioReadPos = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CFFMPEGVideoPlayer::SetupAudioBuffer()
{
	if ( !pDirectSound || !pAudioCodecContext )
		return false;
	
	// Create DirectSound buffer for audio
	WAVEFORMATEX wfx;
	memset( &wfx, 0, sizeof(WAVEFORMATEX) );
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = pAudioCodecContext->channels;
	wfx.nSamplesPerSec = pAudioCodecContext->sample_rate;
	wfx.wBitsPerSample = 16; // We'll convert to 16-bit
	wfx.nBlockAlign = wfx.nChannels * (wfx.wBitsPerSample / 8);
	wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
	
	// Larger buffer for more stable audio - 500ms
	dwAudioBufferSize = wfx.nAvgBytesPerSec / 2;
	
	// Ensure buffer size is aligned to sample boundaries
	int nBytesPerSample = wfx.nChannels * (wfx.wBitsPerSample / 8);
	dwAudioBufferSize = (dwAudioBufferSize / nBytesPerSample) * nBytesPerSample;
	
	DSBUFFERDESC dsbd;
	memset( &dsbd, 0, sizeof(DSBUFFERDESC) );
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_LOCSOFTWARE | DSBCAPS_GLOBALFOCUS | DSBCAPS_GETCURRENTPOSITION2;
	dsbd.dwBufferBytes = dwAudioBufferSize;
	dsbd.lpwfxFormat = &wfx;
	
	HRESULT hr = pDirectSound->CreateSoundBuffer( &dsbd, &pAudioBuffer, 0 );
	if ( FAILED(hr) )
		return false;
	
	// Clear the entire buffer
	LPVOID pClearWrite1, pClearWrite2;
	DWORD dwClearLength1, dwClearLength2;
	if ( SUCCEEDED( pAudioBuffer->Lock( 0, dwAudioBufferSize, &pClearWrite1, &dwClearLength1, &pClearWrite2, &dwClearLength2, 0 ) ) )
	{
		memset( pClearWrite1, 0, dwClearLength1 );
		if ( pClearWrite2 )
			memset( pClearWrite2, 0, dwClearLength2 );
		pAudioBuffer->Unlock( pClearWrite1, dwClearLength1, pClearWrite2, dwClearLength2 );
	}
	
	// Apply master volume with safety check
	float fMasterVolume = GetSingleton<ISFX>()->GetSFXMasterVolume() / 255.0f;
	if ( fMasterVolume > 0.0f )
	{
		s32 nVolume = (s32)(32768 * fMasterVolume);
		// Safer volume calculation
		LONG lVolume = DSBVOLUME_MAX;
		if ( nVolume < 32768 )
		{
			double dVolumeRatio = (double)nVolume / 32768.0;
			if ( dVolumeRatio > 0.0001 ) // Avoid log(0)
			{
				lVolume = (LONG)(2000.0 * log10( dVolumeRatio )); // Convert to centibels
				lVolume = max( lVolume, DSBVOLUME_MIN );
				lVolume = min( lVolume, DSBVOLUME_MAX );
			}
			else
			{
				lVolume = DSBVOLUME_MIN;
			}
		}
		pAudioBuffer->SetVolume( lVolume );
	}
	else
	{
		pAudioBuffer->SetVolume( DSBVOLUME_MIN );
	}
	
	dwAudioWritePos = 0;
	dwAudioReadPos = 0;
	nAudioSamplesWritten = 0;
	nAudioSamplesPlayed = 0;
	dAudioClock = 0.0;
	dwLastAudioCheckTime = GetTickCount();
	bAudioStarted = false;
	nAudioUnderrunCount = 0;
	
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CFFMPEGVideoPlayer::UpdateAudioClock()
{
	if ( !pAudioBuffer || !pAudioCodecContext || !bAudioStarted )
		return;
		
	DWORD dwCurrentTime = GetTickCount();
	if ( dwCurrentTime - dwLastAudioCheckTime < 20 ) // Update every 20ms for better precision
		return;
		
	DWORD dwPlayPos, dwWritePos;
	if ( FAILED( pAudioBuffer->GetCurrentPosition( &dwPlayPos, &dwWritePos ) ) )
		return;
	
	// Calculate how many samples have been played since last check
	DWORD dwPlayPosDiff;
	if ( dwPlayPos >= dwAudioReadPos )
		dwPlayPosDiff = dwPlayPos - dwAudioReadPos;
	else
		dwPlayPosDiff = (dwAudioBufferSize - dwAudioReadPos) + dwPlayPos;
	
	// Convert bytes to samples
	int nBytesPerSample = pAudioCodecContext->channels * 2; // 16-bit stereo/mono
	int nSamplesPlayed = dwPlayPosDiff / nBytesPerSample;
	
	nAudioSamplesPlayed += nSamplesPlayed;
	dwAudioReadPos = dwPlayPos;
	
	// Calculate audio clock based on samples played
	dAudioClock = (double)nAudioSamplesPlayed / (double)pAudioCodecContext->sample_rate;
	
	dwLastAudioCheckTime = dwCurrentTime;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CFFMPEGVideoPlayer::WriteAudioToBuffer( uint8_t* pAudioData, int nDataSize )
{
	if ( !pAudioBuffer || !pAudioData || nDataSize <= 0 )
		return;
	
	// Get current positions
	DWORD dwPlayPos, dwWritePosCursor;
	if ( FAILED( pAudioBuffer->GetCurrentPosition( &dwPlayPos, &dwWritePosCursor ) ) )
		return;
	
	// Calculate how much data is currently in the buffer (used space)
	DWORD dwUsedSpace;
	if ( dwAudioWritePos >= dwPlayPos )
		dwUsedSpace = dwAudioWritePos - dwPlayPos;
	else
		dwUsedSpace = (dwAudioBufferSize - dwPlayPos) + dwAudioWritePos;
	
	// Calculate available space (free space)
	DWORD dwAvailableSpace = dwAudioBufferSize - dwUsedSpace;
	
	// Keep some safety margin (1/8 of buffer)
	DWORD dwSafetyMargin = dwAudioBufferSize / 8;
	if ( dwAvailableSpace <= dwSafetyMargin )
	{
		nAudioUnderrunCount++;
		return; // Buffer is too full, skip this frame
	}
	
	// Don't write more than available space minus safety margin
	DWORD dwMaxWriteSize = dwAvailableSpace - dwSafetyMargin;
	if ( (DWORD)nDataSize > dwMaxWriteSize )
		nDataSize = dwMaxWriteSize;
	
	// Align to sample boundary
	int nBytesPerSample = pAudioCodecContext->channels * 2;
	nDataSize = (nDataSize / nBytesPerSample) * nBytesPerSample;
	
	if ( nDataSize <= 0 )
		return;
	
	LPVOID pWrite1, pWrite2;
	DWORD dwLength1, dwLength2;
	
	HRESULT hr = pAudioBuffer->Lock( dwAudioWritePos, nDataSize, &pWrite1, &dwLength1, &pWrite2, &dwLength2, 0 );
	if ( SUCCEEDED(hr) )
	{
		if ( pWrite1 && dwLength1 > 0 )
			memcpy( pWrite1, pAudioData, dwLength1 );
		
		if ( pWrite2 && dwLength2 > 0 )
			memcpy( pWrite2, pAudioData + dwLength1, dwLength2 );
		
		pAudioBuffer->Unlock( pWrite1, dwLength1, pWrite2, dwLength2 );
		
		// Update write position
		dwAudioWritePos = (dwAudioWritePos + nDataSize) % dwAudioBufferSize;
		
		// Update samples written counter
		int nSamples = nDataSize / nBytesPerSample;
		nAudioSamplesWritten += nSamples;
		
		// Start playing if not already playing and we have enough data
		DWORD dwStatus;
		pAudioBuffer->GetStatus( &dwStatus );
		if ( !(dwStatus & DSBSTATUS_PLAYING) )
		{
			// Wait until we have some data in the buffer before starting
			DWORD dwDataInBuffer;
			if ( dwAudioWritePos >= dwPlayPos )
				dwDataInBuffer = dwAudioWritePos - dwPlayPos;
			else
				dwDataInBuffer = (dwAudioBufferSize - dwPlayPos) + dwAudioWritePos;
			
			if ( dwDataInBuffer >= dwAudioBufferSize / 4 ) // Start when 1/4 full
			{
				pAudioBuffer->Play( 0, 0, DSBPLAY_LOOPING );
				bAudioStarted = true;
				dwAudioReadPos = dwPlayPos;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CFFMPEGVideoPlayer::ConvertAudioSample( const AVFrame* pFrame, int16_t* pOutputBuffer, int nMaxOutputSize )
{
	if ( !pFrame || !pOutputBuffer || !pAudioCodecContext )
		return 0;
	
	int nChannels = pAudioCodecContext->channels;
	int nSamples = pFrame->nb_samples;
	int nOutputSamples = 0;
	
	// Calculate maximum samples we can output
	int nMaxSamples = nMaxOutputSize / (nChannels * 2); // 2 bytes per 16-bit sample
	nSamples = min( nSamples, nMaxSamples );
	
	bool bConversionSuccess = false;
	
	// Handle different audio formats with better quality conversion
	switch ( pAudioCodecContext->sample_fmt )
	{
		case AV_SAMPLE_FMT_S16:
		{
			// Direct copy - already 16-bit interleaved
			int nBytesToCopy = nSamples * nChannels * 2;
			memcpy( pOutputBuffer, pFrame->data[0], nBytesToCopy );
			nOutputSamples = nSamples;
			bConversionSuccess = true;
			break;
		}
		
		case AV_SAMPLE_FMT_S16P:
		{
			// Planar 16-bit to interleaved 16-bit
			int16_t **pPlanar = (int16_t**)pFrame->data;
			for ( int i = 0; i < nSamples; i++ )
			{
				for ( int ch = 0; ch < nChannels; ch++ )
				{
					pOutputBuffer[i * nChannels + ch] = pPlanar[ch][i];
				}
			}
			nOutputSamples = nSamples;
			bConversionSuccess = true;
			break;
		}
		
		case AV_SAMPLE_FMT_FLT:
		{
			// Float to 16-bit interleaved with dithering
			float *pFloat = (float*)pFrame->data[0];
			for ( int i = 0; i < nSamples * nChannels; i++ )
			{
				float sample = pFloat[i];
				
				// Apply soft clipping to prevent harsh distortion
				if ( sample > 1.0f )
					sample = 1.0f;
				else if ( sample < -1.0f )
					sample = -1.0f;
				else if ( sample > 0.8f )
					sample = 0.8f + 0.2f * tanhf( (sample - 0.8f) * 5.0f );
				else if ( sample < -0.8f )
					sample = -0.8f + 0.2f * tanhf( (sample + 0.8f) * 5.0f );
				
				// Convert to 16-bit with proper rounding
				int nSample = (int)(sample * 32767.0f + (sample >= 0 ? 0.5f : -0.5f));
				pOutputBuffer[i] = (int16_t)max( -32768, min( 32767, nSample ) );
			}
			nOutputSamples = nSamples;
			bConversionSuccess = true;
			break;
		}
		
		case AV_SAMPLE_FMT_FLTP:
		{
			// Planar float to 16-bit interleaved with soft clipping
			float **pPlanar = (float**)pFrame->data;
			for ( int i = 0; i < nSamples; i++ )
			{
				for ( int ch = 0; ch < nChannels; ch++ )
				{
					float sample = pPlanar[ch][i];
					
					// Apply soft clipping
					if ( sample > 1.0f )
						sample = 1.0f;
					else if ( sample < -1.0f )
						sample = -1.0f;
					else if ( sample > 0.8f )
						sample = 0.8f + 0.2f * tanhf( (sample - 0.8f) * 5.0f );
					else if ( sample < -0.8f )
						sample = -0.8f + 0.2f * tanhf( (sample + 0.8f) * 5.0f );
					
					// Convert to 16-bit with proper rounding
					int nSample = (int)(sample * 32767.0f + (sample >= 0 ? 0.5f : -0.5f));
					pOutputBuffer[i * nChannels + ch] = (int16_t)max( -32768, min( 32767, nSample ) );
				}
			}
			nOutputSamples = nSamples;
			bConversionSuccess = true;
			break;
		}
		
		case AV_SAMPLE_FMT_S32:
		{
			// 32-bit to 16-bit with proper scaling
			int32_t *pInt32 = (int32_t*)pFrame->data[0];
			for ( int i = 0; i < nSamples * nChannels; i++ )
			{
				// Scale from 32-bit to 16-bit properly
				int64_t sample64 = (int64_t)pInt32[i];
				sample64 = (sample64 * 32767) / 2147483647i64; // Scale maintaining precision
				pOutputBuffer[i] = (int16_t)max( -32768i64, min( 32767i64, sample64 ) );
			}
			nOutputSamples = nSamples;
			bConversionSuccess = true;
			break;
		}
		
		case AV_SAMPLE_FMT_S32P:
		{
			// Planar 32-bit to 16-bit interleaved
			int32_t **pPlanar = (int32_t**)pFrame->data;
			for ( int i = 0; i < nSamples; i++ )
			{
				for ( int ch = 0; ch < nChannels; ch++ )
				{
					int64_t sample64 = (int64_t)pPlanar[ch][i];
					sample64 = (sample64 * 32767) / 2147483647i64;
					pOutputBuffer[i * nChannels + ch] = (int16_t)max( -32768i64, min( 32767i64, sample64 ) );
				}
			}
			nOutputSamples = nSamples;
			bConversionSuccess = true;
			break;
		}
		
		default:
			// Unsupported format
			bConversionSuccess = false;
			break;
	}
	
	return bConversionSuccess ? nOutputSamples : 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ... (SetupRects, SetTarget, SetDstRect methods remain the same)
void CFFMPEGVideoPlayer::SetupRects()
{
	if ( rcDstRect.IsEmpty() || (pCodecContext == 0) || images.empty() || images[0].rcSrcRect.IsEmpty() ) 
		return;
	//
	if ( bMaintainAspect ) 
	{
		const float fCoeffX = rcDstRect.Width() / float( pCodecContext->width );
		const float fCoeffY = rcDstRect.Height() / float( pCodecContext->height );
		if ( (fCoeffX < fCoeffY) && (fabsf(fCoeffX - fCoeffY) > 0.001) ) 
		{
			const float fNewSizeY = pCodecContext->height * fCoeffX;
			rcDstRect.y1 = ( rcDstRect.Height() - fNewSizeY ) / 2.0f;
			rcDstRect.y2 = rcDstRect.y1 + fNewSizeY;
		}
		else if ( (fCoeffY < fCoeffX) && (fabsf(fCoeffY - fCoeffX) > 0.001) ) 
		{
			const float fNewSizeX = pCodecContext->width * fCoeffY;
			rcDstRect.x1 = ( rcDstRect.Width() - fNewSizeX ) / 2.0f;
			rcDstRect.x2 = rcDstRect.x1 + fNewSizeX;
		}
	}
	//
	const float fCoeffX = rcDstRect.Width() / float( pCodecContext->width );
	const float fCoeffY = rcDstRect.Height() / float( pCodecContext->height );
	for ( CImagesList::iterator it = images.begin(); it != images.end(); ++it )
	{
		it->rcRect.x1 = int( rcDstRect.x1 + it->rcSrcRect.x1*fCoeffX ) - 0.5f;
		it->rcRect.y1 = int( rcDstRect.y1 + it->rcSrcRect.y1*fCoeffY ) - 0.5f;
		it->rcRect.x2 = int( rcDstRect.x1 + it->rcSrcRect.x2*fCoeffX ) - 0.5f;
		it->rcRect.y2 = int( rcDstRect.y1 + it->rcSrcRect.y2*fCoeffY ) - 0.5f;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CFFMPEGVideoPlayer::SetTarget( IGFXTexture *pTexture, IGFX *pGFX )
{
	SImagePart image;
	image.pTexture = pTexture;
	images.clear();
	images.push_back( image );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CFFMPEGVideoPlayer::SetDstRect( const RECT &_rcDstRect, bool _bMaintainAspect )
{
	rcDstRect = _rcDstRect;
	bMaintainAspect = _bMaintainAspect;
	SetupRects();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CFFMPEGVideoPlayer::DecodeFrame()
{
	if ( pFormatContext == 0 ) 
		return false;
	
	int nFrameFinished = 0;
	bool bVideoFrameReady = false;
	
	// Keep reading packets until we get a complete video frame
	while ( !bVideoFrameReady && av_read_frame( pFormatContext, &packet ) >= 0 )
	{
		// Is this a packet from the video stream?
		if ( packet.stream_index == nVideoStream )
		{
			// Decode video frame
			avcodec_decode_video2( pCodecContext, pFrame, &nFrameFinished, &packet );
			if ( nFrameFinished )
			{
				bVideoFrameReady = true;
			}
		}
		// Is this a packet from the audio stream?
		else if ( packet.stream_index == nAudioStream && pAudioCodecContext )
		{
			// Process audio packet immediately (don't wait for video frame)
			int nAudioFrameFinished = 0;
			
			// Make a copy of the packet for audio processing since we might need to free the original
			AVPacket audioPacket = packet;
			
			// Decode audio - might need multiple calls for one packet
			while ( audioPacket.size > 0 )
			{
				int nBytesDecoded = avcodec_decode_audio4( pAudioCodecContext, pAudioFrame, &nAudioFrameFinished, &audioPacket );
				
				if ( nBytesDecoded < 0 )
				{
					// Error in decoding, skip this packet
					break;
				}
				
				if ( nAudioFrameFinished && pAudioBuffer )
				{
					// Calculate maximum output buffer size
					int nMaxOutputSamples = pAudioFrame->nb_samples;
					int nMaxOutputSize = nMaxOutputSamples * pAudioCodecContext->channels * 2; // 16-bit
					
					// Allocate output buffer
					int16_t *pOutputBuffer = (int16_t*)av_malloc( nMaxOutputSize );
					if ( pOutputBuffer )
					{
						// Convert audio using improved conversion function
						int nOutputSamples = ConvertAudioSample( pAudioFrame, pOutputBuffer, nMaxOutputSize );
						
						if ( nOutputSamples > 0 )
						{
							int nOutputBytes = nOutputSamples * pAudioCodecContext->channels * 2;
							WriteAudioToBuffer( (uint8_t*)pOutputBuffer, nOutputBytes );
						}
						
						av_free( pOutputBuffer );
					}
				}
				
				// Move to next part of packet
				audioPacket.data += nBytesDecoded;
				audioPacket.size -= nBytesDecoded;
			}
		}
		
		av_free_packet( &packet );
	}
	
	if ( bVideoFrameReady )
	{
		// Convert the image from its native format to BGRA
		sws_scale( pSwsContext, (uint8_t const * const *)pFrame->data, pFrame->linesize, 0, 
				   pCodecContext->height, pFrameRGB->data, pFrameRGB->linesize );
		return true;
	}
	else
	{
		// Check if we need to loop
		if ( bLooped && !bStopped )
		{
			// Seek to beginning
			av_seek_frame( pFormatContext, nVideoStream, 0, AVSEEK_FLAG_BACKWARD );
			avcodec_flush_buffers( pCodecContext );
			if ( pAudioCodecContext )
				avcodec_flush_buffers( pAudioCodecContext );
			
			// Reset timing for loop
			dwStartTime = GetTickCount();
			dwTotalPauseTime = 0;
			nLastPlayedFrame = -1;
			dAudioClock = 0.0;
			dVideoClock = 0.0;
			nAudioSamplesWritten = 0;
			nAudioSamplesPlayed = 0;
			bAudioStarted = false;
			
			return DecodeFrame(); // Try to decode again
		}
		else
		{
			bStopped = true;
			return false;
		}
	}
}

// ... (remaining methods like OpenFFMPEG, CopyFrameToTextures, etc. remain largely the same)
// ... (I'll continue with the key remaining methods that need updates)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CFFMPEGVideoPlayer::Update( const NTimer::STime &time, bool bForcedUpdate )
{
	if ( pFormatContext == 0 ) 
		return ( dwPlayFlags & IVideoPlayer::PLAY_INFINITE ) != 0;
	
	if ( bStopped )
		return ( dwPlayFlags & IVideoPlayer::PLAY_INFINITE ) != 0;
	
	if ( bPaused && !bForcedUpdate )
		return true;
	
	// Update audio clock more frequently
	if ( bUseAudioSync && pAudioBuffer )
		UpdateAudioClock();
	
	if ( bForcedUpdate ) 
	{
		if ( DecodeFrame() )
		{
			CopyFrameToTextures();
			nLastPlayedFrame++;
			dVideoClock = (double)nLastPlayedFrame / dFrameRate;
		}
	}
	else
	{
		// Calculate current time and expected frame
		DWORD dwCurrentTime = GetTickCount() - dwStartTime - dwTotalPauseTime;
		int nExpectedFrame = int( dwCurrentTime / dTimePerFrame );
		
		// Improved audio sync logic
		bool bUseSync = bUseAudioSync && pAudioBuffer && pAudioCodecContext && bAudioStarted && (dAudioClock > 0.1);
		
		if ( bUseSync )
		{
			dVideoClock = (double)nLastPlayedFrame / dFrameRate;
			double dSyncDiff = dVideoClock - dAudioClock;
			
			// More conservative sync adjustments
			if ( dSyncDiff > dSyncThreshold ) // Video ahead
			{
				// Skip this frame occasionally to slow down video
				static int nSkipCounter = 0;
				nSkipCounter++;
				if ( nSkipCounter >= 3 ) // Skip every 3rd frame when ahead
				{
					nSkipCounter = 0;
					return true;
				}
			}
			else if ( dSyncDiff < -dSyncThreshold ) // Video behind
			{
				// Catch up by decoding extra frames (but limit to prevent freezing)
				nExpectedFrame = min( nExpectedFrame + 2, (int)( dAudioClock * dFrameRate ) + 1 );
			}
		}
		
		// Decode frames if we're behind
		bool bNeedUpdate = false;
		int nFramesDecoded = 0;
		while ( nLastPlayedFrame < nExpectedFrame && !bStopped && nFramesDecoded < 3 )
		{
			if ( DecodeFrame() )
			{
				nLastPlayedFrame++;
				bNeedUpdate = true;
				nFramesDecoded++;
			}
			else
				break;
		}
		
		if ( bNeedUpdate )
		{
			CopyFrameToTextures();
			dVideoClock = (double)nLastPlayedFrame / dFrameRate;
		}
	}
	
	return IsPlaying() || ((dwPlayFlags & IVideoPlayer::PLAY_INFINITE) != 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CFFMPEGVideoPlayer::OpenFFMPEG( const char *pszFileName, DWORD dwFlags )
{
	CloseFFMPEG();
	
	// Register all codecs and formats (required in older FFmpeg)
	av_register_all();
	
	// Open video file
	if ( av_open_input_file( &pFormatContext, pszFileName, 0, 0, 0 ) != 0 )
		return false;
	
	// Retrieve stream information
	if ( av_find_stream_info( pFormatContext ) < 0 )
	{
		av_close_input_file( pFormatContext );
		pFormatContext = 0;
		return false;
	}
	
	// Find the first video stream and audio stream
	nVideoStream = -1;
	nAudioStream = -1;
	for ( unsigned int i = 0; i < pFormatContext->nb_streams; i++ )
	{
		if ( pFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO && nVideoStream == -1 ) 
		{
			nVideoStream = i;
		}
		else if ( pFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO && nAudioStream == -1 )
		{
			nAudioStream = i;
		}
	}
	
	if ( nVideoStream == -1 )
	{
		av_close_input_file( pFormatContext );
		pFormatContext = 0;
		return false;
	}
	
	// Get a pointer to the codec context for the video stream
	pCodecContext = pFormatContext->streams[nVideoStream]->codec;
	
	// Find the decoder for the video stream
	pCodec = avcodec_find_decoder( pCodecContext->codec_id );
	if ( pCodec == 0 )
	{
		av_close_input_file( pFormatContext );
		pFormatContext = 0;
		return false;
	}
	
	// Open codec
	if ( avcodec_open( pCodecContext, pCodec ) < 0 )
	{
		av_close_input_file( pFormatContext );
		pFormatContext = 0;
		return false;
	}
	
	// Allocate video frames
	pFrame = avcodec_alloc_frame();
	pFrameRGB = avcodec_alloc_frame();
	
	if ( !pFrame || !pFrameRGB )
	{
		CloseFFMPEG();
		return false;
	}
	
	// Determine required buffer size and allocate buffer
	int nBytes = avpicture_get_size( PIX_FMT_BGRA, pCodecContext->width, pCodecContext->height );
	pFrameBuffer = (uint8_t*)av_malloc( nBytes * sizeof(uint8_t) );
	
	// Assign appropriate parts of buffer to image planes in pFrameRGB
	avpicture_fill( (AVPicture*)pFrameRGB, pFrameBuffer, PIX_FMT_BGRA, 
					pCodecContext->width, pCodecContext->height );
	
	// Initialize SWS context for software scaling
	pSwsContext = sws_getContext( pCodecContext->width, pCodecContext->height, pCodecContext->pix_fmt,
								  pCodecContext->width, pCodecContext->height, PIX_FMT_BGRA,
								  SWS_BILINEAR, 0, 0, 0 );
	
	if ( !pSwsContext )
	{
		CloseFFMPEG();
		return false;
	}
	
	// Calculate frame rate
	AVRational frameRate = pFormatContext->streams[nVideoStream]->r_frame_rate;
	if ( frameRate.num > 0 && frameRate.den > 0 )
		dFrameRate = double(frameRate.num) / double(frameRate.den);
	else
		dFrameRate = 25.0; // default fallback
	
	dTimePerFrame = 1000.0 / dFrameRate; // time per frame in milliseconds
	
	// Setup audio if available
	if ( nAudioStream >= 0 )
	{
		pAudioCodecContext = pFormatContext->streams[nAudioStream]->codec;
		
		// Find the decoder for the audio stream
		pAudioCodec = avcodec_find_decoder( pAudioCodecContext->codec_id );
		if ( pAudioCodec != 0 )
		{
			// Open codec
			if ( avcodec_open( pAudioCodecContext, pAudioCodec ) >= 0 )
			{
				pAudioFrame = avcodec_alloc_frame();
			}
			else
			{
				pAudioCodecContext = 0;
			}
		}
	}
	
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CFFMPEGVideoPlayer::Play( const char *pszFileName, DWORD dwFlags, IGFX *pGFX, interface ISFX *pSFX )
{
	Stop();
	
	// Initialize sound
	if ( pSFX ) 
	{
		pDirectSound = reinterpret_cast<LPDIRECTSOUND>( pSFX->QI(0) );
	}
	
	szFileName = pszFileName;
	dwPlayFlags = dwFlags;
	
	if ( OpenFFMPEG( pszFileName, dwFlags ) == false ) 
		return 0;
	
	if ( images.size() == 1 )							// if we have set 'external' render target
	{
		// setup rects for external texture
		const int nSizeX = Min( images[0].pTexture->GetSizeX(0), pCodecContext->width );
		const int nSizeY = Min( images[0].pTexture->GetSizeY(0), pCodecContext->height );
		images[0].rcSrcRect.Set( 0, 0, nSizeX, nSizeY );
		images[0].rcDstRect.Set( 0, 0, nSizeX, nSizeY );
		images[0].rcMaps.Set( 0, 0, float(nSizeX) / float(images[0].pTexture->GetSizeX(0)), float(nSizeY) / float(images[0].pTexture->GetSizeY(0)) );
	}
	else																	// create 'internal' render target
	{
		const bool bHasNonPow2Textures = (GetGlobalVar( "GFX.Caps.Texture.NonPow2Conditional", 0 ) != 0) || (GetGlobalVar( "GFX.Caps.Texture.NonPow2", 0 ) != 0);
		if ( bHasNonPow2Textures )					// create one non-pow2 texture, if device supports it
		{
			images.clear();

			SImagePart image;
			image.pTexture = pGFX->CreateTexture( pCodecContext->width, pCodecContext->height, 1, GFXPF_ARGB8888, GFXD_STATIC );
			image.rcSrcRect.Set( 0, 0, pCodecContext->width, pCodecContext->height );
			image.rcDstRect.Set( 0, 0, pCodecContext->width, pCodecContext->height );
			image.rcMaps.Set( 0, 0, 1, 1 );
			//
			images.push_back( image );
		}
		else																// create serie of 256x256 textures to cover all render target
		{
			const int nNumTexturesX = (pCodecContext->width % 256) == 0 ? pCodecContext->width / 256 : pCodecContext->width / 256 + 1;
			const int nNumTexturesY = (pCodecContext->height % 256) == 0 ? pCodecContext->height / 256 : pCodecContext->height / 256 + 1;
			const bool bSquareOnly = GetGlobalVar( "GFX.Caps.Texture.SquareOnly", 0 ) != 0;
			//
			int nRestSizeY = pCodecContext->height;
			int nPosY = 0;
			for ( int i = 0; i < nNumTexturesY; ++i )
			{
				const int nSrcSizeY = nRestSizeY >= 256 ? 256 : nRestSizeY;
				int nRestSizeX = pCodecContext->width;
				int nPosX = 0;
				for ( int j = 0; j < nNumTexturesX; ++j )
				{
					const int nSrcSizeX = nRestSizeX >= 256 ? 256 : nRestSizeX;
					int nTextureSizeX = nRestSizeX < 256 ? GetNextPow2( nRestSizeX ) : 256;
					int nTextureSizeY = nRestSizeY < 256 ? GetNextPow2( nRestSizeY ) : 256;
					if ( bSquareOnly ) 
						nTextureSizeX = nTextureSizeY = Max( nTextureSizeX, nTextureSizeY );
					//
					SImagePart image;
					image.pTexture = pGFX->CreateTexture( nTextureSizeX, nTextureSizeY, 1, GFXPF_ARGB8888, GFXD_STATIC );
					image.rcSrcRect.Set( nPosX, nPosY, nPosX + nSrcSizeX, nPosY + nSrcSizeY );
					image.rcDstRect.Set( 0, 0, nSrcSizeX, nSrcSizeY );
					image.rcMaps.Set( 0, 0, float(image.rcDstRect.Width()) / float(nTextureSizeX), float(image.rcDstRect.Height()) / float(nTextureSizeY) );
					//
					images.push_back( image );
					//
					nRestSizeX -= 256;
					nPosX += 256;
				}
				nRestSizeY -= 256;
				nPosY += 256;
			}
		}
	}
	
	// clear system image
	for ( CImagesList::const_iterator it = images.begin(); it != images.end(); ++it )
	{
		SSurfaceLockInfo lock;
		it->pTexture->Lock( 0, &lock );
		//
		for ( int i = 0; i < it->pTexture->GetSizeY(0); ++i )
			memset( ((char*)lock.pData) + i*lock.nPitch, 0, it->pTexture->GetSizeX(0) * 4 ); // 4 bytes per pixel for ARGB
		//
		it->pTexture->Unlock( 0 );
	}
	
	// setup rects (geometry and texture mapping)
	if ( rcDstRect.IsEmpty() ) 
		rcDstRect.Set( 0, 0, pCodecContext->width, pCodecContext->height );
	SetupRects();
	
	// initialize timing
	dwStartTime = GetTickCount();
	dwTotalPauseTime = 0;
	nLastPlayedFrame = -1;
	bStopped = false;
	bPaused = false;
	dVideoClock = 0.0;
	dAudioClock = 0.0;
	
	// decode first frame
	if ( DecodeFrame() )
		CopyFrameToTextures();
	
	// Setup audio buffer if we have audio and DirectSound
	if ( pAudioCodecContext && pDirectSound )
	{
		SetupAudioBuffer();
		// Enable audio sync by default if audio is available
		bUseAudioSync = true;
	}
	
	// return length in milliseconds
	if ( pFormatContext->duration != AV_NOPTS_VALUE )
		return int( (pFormatContext->duration * 1000) / AV_TIME_BASE );
	else
		return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CFFMPEGVideoPlayer::CopyFrameToTextures()
{
	if ( pFrameRGB == 0 || pCodecContext == 0 ) 
		return;
	
	for ( CImagesList::const_iterator it = images.begin(); it != images.end(); ++it )
	{
		SSurfaceLockInfo lock;
		it->pTexture->Lock( 0, &lock );
		
		// Copy frame data to texture
		const int nSrcWidth = it->rcSrcRect.Width();
		const int nSrcHeight = it->rcSrcRect.Height();
		const int nSrcPitch = pFrameRGB->linesize[0];
		const uint8_t *pSrcData = pFrameRGB->data[0] + it->rcSrcRect.y1 * nSrcPitch + it->rcSrcRect.x1 * 4;
		
		uint8_t *pDstData = (uint8_t*)lock.pData;
		const int nDstPitch = lock.nPitch;
		
		for ( int y = 0; y < nSrcHeight; ++y )
		{
			memcpy( pDstData + y * nDstPitch, pSrcData + y * nSrcPitch, nSrcWidth * 4 );
		}
		
		it->pTexture->Unlock( 0 );
		it->pTexture->AddDirtyRect( 0 );
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CFFMPEGVideoPlayer::Stop()
{
	bStopped = true;
	CloseFFMPEG();
	images.clear();
	buffer.clear();
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CFFMPEGVideoPlayer::Pause( bool bPause )
{
	if ( pFormatContext == 0 ) 
		return false;
	
	if ( bPause && !bPaused )
	{
		dwPauseTime = GetTickCount();
		bPaused = true;
		// Pause audio
		if ( pAudioBuffer )
			pAudioBuffer->Stop();
	}
	else if ( !bPause && bPaused )
	{
		dwTotalPauseTime += GetTickCount() - dwPauseTime;
		bPaused = false;
		// Resume audio
		if ( pAudioBuffer && bAudioStarted )
			pAudioBuffer->Play( 0, 0, DSBPLAY_LOOPING );
	}
	
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CFFMPEGVideoPlayer::Draw( IGFX *pGFX )
{
	pGFX->SetShadingEffect( nShadingEffectStart );
	for ( CImagesList::const_iterator it = images.begin(); it != images.end(); ++it )
	{
		// draw
		SGFXRect2 rect;
		rect.rect = it->rcRect;
		rect.maps = it->rcMaps;
		rect.color = 0xffffffff;
		rect.specular = 0xff000000;
		rect.fZ = 0;
		//
		pGFX->SetTexture( 0, it->pTexture );
		pGFX->DrawRects( &rect, 1 );
	}
	pGFX->SetShadingEffect( nShadingEffectFinish );
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CFFMPEGVideoPlayer::Visit( ISceneVisitor *pVisitor, int nType )
{
	pVisitor->VisitSceneObject( this );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CFFMPEGVideoPlayer::IsPlaying() const
{
	return (pFormatContext != 0) && !bStopped;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CFFMPEGVideoPlayer::GetCurrentFrame() const
{
	if ( !IsPlaying() ) 
		return -1;
	return nLastPlayedFrame;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CFFMPEGVideoPlayer::SetCurrentFrame( const int nFrame )
{
	if ( !IsPlaying() ) 
		return false;
	
	return SeekToFrame( nFrame );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CFFMPEGVideoPlayer::SeekToFrame( int nFrame )
{
	if ( pFormatContext == 0 || nVideoStream == -1 )
		return false;
	
	// Calculate timestamp for the frame
	AVStream *pStream = pFormatContext->streams[nVideoStream];
	
	// Create inverse of frame rate (swap num and den)
	AVRational invFrameRate;
	invFrameRate.num = pStream->r_frame_rate.den;
	invFrameRate.den = pStream->r_frame_rate.num;
	
	int64_t timestamp = av_rescale( nFrame, pStream->time_base.den, pStream->time_base.num );
	timestamp = av_rescale_q( timestamp, invFrameRate, pStream->time_base );
	
	// Seek to the frame
	if ( av_seek_frame( pFormatContext, nVideoStream, timestamp, AVSEEK_FLAG_BACKWARD ) < 0 )
		return false;
	
	// Flush codec buffers
	avcodec_flush_buffers( pCodecContext );
	if ( pAudioCodecContext )
		avcodec_flush_buffers( pAudioCodecContext );
	
	// Reset audio buffer
	if ( pAudioBuffer )
	{
		pAudioBuffer->Stop();
		// Clear buffer
		LPVOID pWrite1, pWrite2;
		DWORD dwLength1, dwLength2;
		if ( SUCCEEDED( pAudioBuffer->Lock( 0, dwAudioBufferSize, &pWrite1, &dwLength1, &pWrite2, &dwLength2, 0 ) ) )
		{
			memset( pWrite1, 0, dwLength1 );
			if ( pWrite2 )
				memset( pWrite2, 0, dwLength2 );
			pAudioBuffer->Unlock( pWrite1, dwLength1, pWrite2, dwLength2 );
		}
		dwAudioWritePos = 0;
		dwAudioReadPos = 0;
		bAudioStarted = false;
	}
	
	// Reset timing
	if ( pAudioCodecContext )
	{
		nAudioSamplesWritten = nFrame * pAudioCodecContext->sample_rate / dFrameRate;
		nAudioSamplesPlayed = nFrame * pAudioCodecContext->sample_rate / dFrameRate;
	}
	dAudioClock = (double)nFrame / dFrameRate;
	dVideoClock = (double)nFrame / dFrameRate;
	
	// Decode up to the target frame
	nLastPlayedFrame = -1;
	for ( int i = 0; i <= nFrame; ++i )
	{
		if ( !DecodeFrame() )
			return false;
		nLastPlayedFrame = i;
	}
	
	CopyFrameToTextures();
	
	// Restart audio if it was playing
	if ( pAudioBuffer && !bPaused && bAudioStarted )
		pAudioBuffer->Play( 0, 0, DSBPLAY_LOOPING );
	
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CFFMPEGVideoPlayer::GetLength() const
{
	if ( pFormatContext == 0 )
		return 0;
	
	if ( pFormatContext->duration != AV_NOPTS_VALUE )
		return int( (pFormatContext->duration * 1000) / AV_TIME_BASE );
	else
		return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CFFMPEGVideoPlayer::GetNumFrames() const
{
	if ( pFormatContext == 0 || nVideoStream == -1 )
		return 0;
	
	AVStream *pStream = pFormatContext->streams[nVideoStream];
	if ( pStream->nb_frames > 0 )
		return int( pStream->nb_frames );
	
	// Fallback: estimate from duration and frame rate
	if ( pFormatContext->duration != AV_NOPTS_VALUE && dFrameRate > 0 )
	{
		double dDurationSec = double( pFormatContext->duration ) / AV_TIME_BASE;
		return int( dDurationSec * dFrameRate );
	}
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CFFMPEGVideoPlayer::GetMovieSize( CVec2 *pSize ) const
{
	if ( (pCodecContext == 0) || (pSize == 0) ) 
		return false;
	//
	pSize->x = pCodecContext->width;
	pSize->y = pCodecContext->height;
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CFFMPEGVideoPlayer::SetAudioSyncEnabled( bool bEnabled )
{
	bUseAudioSync = bEnabled;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CFFMPEGVideoPlayer::SetSyncThreshold( double dThreshold )
{
	dSyncThreshold = max( 0.01, min( 0.2, dThreshold ) ); // Clamp between 10ms and 200ms
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double CFFMPEGVideoPlayer::GetAudioVideoDrift() const
{
	if ( !bUseAudioSync || !pAudioBuffer || !pAudioCodecContext )
		return 0.0;
		
	return dVideoClock - dAudioClock;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CFFMPEGVideoPlayer::operator&( IStructureSaver &ss )
{
	CSaverAccessor saver = &ss;
	saver.Add( 1, &rcDstRect );
	saver.Add( 2, &bMaintainAspect );
	saver.Add( 3, &bLooped );
	saver.Add( 4, &nLastPlayedFrame );
	saver.Add( 5, &szFileName );
	saver.Add( 6, &dwPlayFlags );
	saver.Add( 7, &nShadingEffectStart );
	saver.Add( 8, &nShadingEffectFinish );
	saver.Add( 9, &bStopped );
	saver.Add( 10, &bPaused );
	saver.Add( 11, &bUseAudioSync );
	saver.Add( 12, &dSyncThreshold );
	
	bool bPlaying = IsPlaying();
	saver.Add( 20, &bPlaying );
	
	if ( saver.IsReading() ) 
	{
		buffer.clear();
		if ( bPlaying ) 
		{
			const int nStartFromFrame = nLastPlayedFrame;
			Play( szFileName.c_str(), dwPlayFlags, GetSingleton<IGFX>(), GetSingleton<ISFX>() );
			if ( pFormatContext ) 
				SeekToFrame( nStartFromFrame );
		}
	}
	return 0;
}