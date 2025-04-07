#ifndef __COMMON_H__
#define __COMMON_H__

using std::vector;
using std::string;

interface IObjVisObj;

void FillTileMaps( int nSizeX, int nSizeY, vector<STileMapsDesc> &tileMaps, bool bGenerateInverse );
bool IsSpriteHit( IObjVisObj *pSprite, const CVec2 &point, CVec2 *pShift );
bool CheckDDSExtension( const char *pszFileName );

#endif		//__COMMON_H__
