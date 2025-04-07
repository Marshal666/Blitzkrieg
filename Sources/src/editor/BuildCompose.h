#ifndef __BUILD_COMPOSE_H__
#define __BUILD_COMPOSE_H__

bool ComposeSingleObject( const char *pszObjFileName, const char *pszShadowFileName, const char *pszResultFileName, const CVec2 &zeroPos );
bool ComposeSingleObjectPack( const char *pszObjFileName, const char *pszShadowFileName, const char *pszResultFileName, const CVec2 &zeroPos, const CArray2D<BYTE> &pass, const CVec2 &vOrigin );

bool ComposeImageToTexture( const char *pszSource, const char *pszResult, bool bCorrect = true );
CTRect<float> GetImageSize( const char *pszImageFile );

#endif		//__BUILD_COMPOSE_H__
