#include "StdAfx.h"

#include "..\GFX\GFX.h"
#include "..\GFX\GFXHelper.h"
#include "..\Formats\fmtMap.h"
#include "..\Formats\fmtTerrain.h"
#include "..\Scene\Terrain.h"
#include "..\Image\Image.h"
#include "Builders.h"
#include "TerrainBuilder.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** terrain map pre-processing
// **
// **
// **
// ************************************************************************************************************************ //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline BYTE GetTileType( BYTE color )
{
	return color >> 4;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �������� ��������� � ����� � ��� � �����: mask <=> value
// �������� ������������ ���: (neighbours & mask) == value
// ��������
//        L => M order             M => L order       hex numbers
// a)  01010010 : 00010000 ==> 01001010 : 00001000 ==> 0x4a : 0x08
// b)  11010000 : 10000000 ==> 00001011 : 00000001 ==> 0x0b : 0x01
// c)  01101000 : 00100000 ==> 00010110 : 00000100 ==> 0x16 : 0x04
// d)  01001010 : 00001000 ==> 01010010 : 00010000 ==> 0x52 : 0x10
// e)  00001010 : 00001010 ==> 01010000 : 01010000 ==> 0x50 : 0x50
// f)  00010010 : 00010010 ==> 01001000 : 01001000 ==> 0x48 : 0x48
// �����������
// a') 01011000 : 01000000 ==> 00011010 : 00000010 ==> 0x1a : 0x02
// b') 00001011 : 00000001 ==> 11010000 : 10000000 ==> 0xd0 : 0x80
// c') 00010110 : 00000100 ==> 01101000 : 00100000 ==> 0x68 : 0x20
// d') 00011010 : 00000010 ==> 01011000 : 01000000 ==> 0x58 : 0x40
// e') 01010000 : 01010000 ==> 00001010 : 00001010 ==> 0x0a : 0x0a
// f') 01001000 : 01001000 ==> 00010010 : 00010010 ==> 0x12 : 0x12
//
// cMasks[i][0] = mask
// cMasks[i][1] = value
// cMasks[i][2] = main type get from 0xXY
static const int nNumMaskOrders = 12;
static BYTE cMasks[nNumMaskOrders][3] = 
{
	{ 0x4a, 0x08, 0x12 },									// 00 = a
	{ 0x0b, 0x01, 0x02 },									// 01 = b
	{ 0x16, 0x04, 0x00 },									// 02 = c
	{ 0x52, 0x10, 0x10 },									// 03 = d
	{ 0x50, 0x50, 0x10 },									// 04 = e
	{ 0x48, 0x48, 0x12 },									// 05 = f
	{ 0x1a, 0x02, 0x01 },									// 06 = a'
	{ 0xd0, 0x80, 0x20 },									// 07 = b'
	{ 0x68, 0x20, 0x22 },									// 08 = c'
	{ 0x58, 0x40, 0x21 },									// 09 = d'
	{ 0x0a, 0x0a, 0x01 },									// 10 = e'
	{ 0x12, 0x12, 0x01 } 									// 11 = f'
};
// f', d, c | e, d', b' | f, a, c' | e', a', b
static const int nMasksOrder[nNumMaskOrders] = { 11, 3, 2, 4, 9, 7, 5, 0, 8, 10, 6, 1 };
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CTerrainBuilder::ComparePriority( BYTE r1, BYTE r2 ) const
{
	return Sign( tileset.terrtypes[r1].nPriority - tileset.terrtypes[r2].nPriority );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���������� � ��������� �������� ������
// 2 4 7
// 1 X 6
// 0 3 5
//
// create neighbours mask with only one type of color
BYTE CTerrainBuilder::GetNeighboursMask( const CArray2D<SMainTileInfo> &tiles, const int nX, const int nY, BYTE cSuper, const CTRect<int> &rect, const CTRect<int> &rcSuper ) const
{
	const int nX1 = nX > 1 ? nX - 1 : 0;
	const int nX2 = nX < rcSuper.Width() - 1 ? nX + 1 : nX;
	const int nY1 = nY > 1 ? nY - 1 : 0;
	const int nY2 = nY < rcSuper.Height() - 1 ? nY + 1 : nY;
	BYTE cColor = GetTerrainType( tiles( nX, nY ).tile );
	BYTE cRetVal = 0;
	//
	if ( (GetTerrainType(tiles( nX1, nY2 ).tile) == cSuper) && ComparePriority( GetTerrainType(tiles( nX1, nY2 ).tile), cColor ) == 1 )	// -1, +1
		cRetVal |= 1 << 0;
	if ( (GetTerrainType(tiles( nX1, nY  ).tile) == cSuper) && ComparePriority( GetTerrainType(tiles( nX1, nY  ).tile), cColor ) == 1 )	// -1, +0
		cRetVal |= 1 << 1;
	if ( (GetTerrainType(tiles( nX1, nY1 ).tile) == cSuper) && ComparePriority( GetTerrainType(tiles( nX1, nY1 ).tile), cColor ) == 1 )	// -1, -1
		cRetVal |= 1 << 2;
	if ( (GetTerrainType(tiles( nX , nY2 ).tile) == cSuper) && ComparePriority( GetTerrainType(tiles( nX , nY2 ).tile), cColor ) == 1 )	// +0, +1
		cRetVal |= 1 << 3;
	if ( (GetTerrainType(tiles( nX , nY1 ).tile) == cSuper) && ComparePriority( GetTerrainType(tiles( nX , nY1 ).tile), cColor ) == 1 )	// +0, -1
		cRetVal |= 1 << 4;
	if ( (GetTerrainType(tiles( nX2, nY2 ).tile) == cSuper) && ComparePriority( GetTerrainType(tiles( nX2, nY2 ).tile), cColor ) == 1 )	// +1, +1
		cRetVal |= 1 << 5;
	if ( (GetTerrainType(tiles( nX2, nY  ).tile) == cSuper) && ComparePriority( GetTerrainType(tiles( nX2, nY  ).tile), cColor ) == 1 )	// +1, +0
		cRetVal |= 1 << 6;
	if ( (GetTerrainType(tiles( nX2, nY1 ).tile) == cSuper) && ComparePriority( GetTerrainType(tiles( nX2, nY1 ).tile), cColor ) == 1 )	// +1, -1
		cRetVal |= 1 << 7;
	
	return cRetVal;
}
class CTerraTypesLessFunctional
{
	const STilesetDesc &tileset;
public:
	explicit CTerraTypesLessFunctional( const STilesetDesc &_tileset ) : tileset( _tileset ) {  }
	bool operator()( const int type1, const int type2 ) const
	{
		return tileset.terrtypes[type1].nPriority < tileset.terrtypes[type2].nPriority;
	}
};
// create neighbours mask with all types of color
int CTerrainBuilder::GetNeighboursMask( const CArray2D<SMainTileInfo> &tiles, const int nX, const int nY, 
																			  const CTRect<int> &rect, const CTRect<int> &rcSuper, 
																				SComplexCrosses *pCrosses ) const
{
	static CCrossesList localcrosses;
	localcrosses.clear();
	// {-1, -1}, {+0, -1}, {+1, -1} => 2, 4, 7
	// {-1, +0},         , {+1, +0} => 1, X, 6
	// {-1, +1}, {+0, +1}, {+1, +1} => 0, 3, 5
	const int nX1 = nX > 1 ? nX - 1 : 0;
	const int nX2 = nX < rcSuper.Width() - 1 ? nX + 1 : nX;
	const int nXs[3] = { nX1, nX, nX2 };
	const int nY1 = nY > 1 ? nY - 1 : 0;
	const int nY2 = nY < rcSuper.Height() - 1 ? nY + 1 : nY;
	const int nYs[3] = { nY1, nY, nY2 };
	BYTE cColor = GetTerrainType( tiles( nX, nY ).tile );
	DWORD dwVal = 0;

	if ( ComparePriority( GetTerrainType(tiles( nX1, nY2 ).tile), cColor ) == 1 )	// -1, +1
		dwVal |= 1 << GetTerrainType( tiles( nX1, nY2 ).tile );
	if ( ComparePriority( GetTerrainType(tiles( nX1, nY  ).tile), cColor ) == 1 )	// -1, +0
		dwVal |= 1 << GetTerrainType( tiles( nX1, nY  ).tile );
	if ( ComparePriority( GetTerrainType(tiles( nX1, nY1 ).tile), cColor ) == 1 )	// -1, -1
		dwVal |= 1 << GetTerrainType( tiles( nX1, nY1 ).tile );
	if ( ComparePriority( GetTerrainType(tiles( nX , nY2 ).tile), cColor ) == 1 )	// +0, +1
		dwVal |= 1 << GetTerrainType( tiles( nX , nY2 ).tile );
	if ( ComparePriority( GetTerrainType(tiles( nX , nY1 ).tile), cColor ) == 1 )	// +0, -1
		dwVal |= 1 << GetTerrainType( tiles( nX , nY1 ).tile );
	if ( ComparePriority( GetTerrainType(tiles( nX2, nY2 ).tile), cColor ) == 1 )	// +1, +1
		dwVal |= 1 << GetTerrainType( tiles( nX2, nY2 ).tile );
	if ( ComparePriority( GetTerrainType(tiles( nX2, nY  ).tile), cColor ) == 1 )	// +1, +0
		dwVal |= 1 << GetTerrainType( tiles( nX2, nY  ).tile );
	if ( ComparePriority( GetTerrainType(tiles( nX2, nY1 ).tile), cColor ) == 1 )	// +1, -1
		dwVal |= 1 << GetTerrainType( tiles( nX2, nY1 ).tile );
	// process multitile crosses
	int nNumCrosses = 0;
	if ( dwVal != 0 )
	{
		// extract terrain types and sort it by priority
		std::vector<int> types;
		types.reserve( 256 );
		while ( dwVal != 0 ) 
		{
			int nBit = GetLSB( dwVal );
			types.push_back( nBit );
			dwVal &= ~( 1 << nBit );
		}
		std::sort( types.begin(), types.end(), CTerraTypesLessFunctional(tileset) );
		// process types
		for ( std::vector<int>::const_iterator it = types.begin(); it != types.end(); ++it )
		{
			const int nBit = *it;
			BYTE cNeighbours = GetNeighboursMask( tiles, nX, nY, nBit, rect, rcSuper );
			// loop by corners
			for ( int k=0; k<4; ++k )
			{
				// loop by types
				for ( int l=0; l<3; ++l )
				{
					int nIndex = k*3 + l;
					if ( (cNeighbours & cMasks[nMasksOrder[nIndex]][0]) == cMasks[nMasksOrder[nIndex]][1] )
					{
						localcrosses.push_back( SCrossTileInfo() );
						SCrossTileInfo &tile = localcrosses.back();
						// main tile
						const int dx = ( cMasks[nMasksOrder[nIndex]][2] & 0xF0 ) >> 4;
						const int dy = ( cMasks[nMasksOrder[nIndex]][2] & 0x0F );
						const int nMainTileX = nXs[dx];
						const int nMainTileY = nYs[dy];
						const int nMainTile = tiles[nMainTileY][nMainTileX].tile;
						tile.tile = tiles[nMainTileY][nMainTileX].tile;
						// cross tile
						tile.x = nX % STerrainPatchInfo::nSizeX;
						tile.y = nY % STerrainPatchInfo::nSizeY;
						tile.cross = nMasksOrder[nIndex];

						const int nTerraType = GetTerrainType( tile.tile );
						const int nCrosset = tileset.terrtypes[nTerraType].nCrosset;
						tile.cross = crosset.crosses[nCrosset].tiles[tile.cross].GetMapsIndex();
						//
						tile.flags = SCrossTileInfo::CROSS;

						++nNumCrosses;
						break;
					}
				}
			}
		}
	}
	if ( localcrosses.empty() )
	{	
		return 0;
	}
	// post process crosses and analyze it in order to create noise crosses
	// has this entire set noise or not?
	bool bHasNoiseAnd = HasNoise( tiles[nY][nX].tile ), bHasNoiseOr = false;
	for ( CCrossesList::const_iterator it = localcrosses.begin(); it != localcrosses.end(); ++it )
	{
		bHasNoiseAnd = bHasNoiseAnd && HasNoise( it->tile );
		bHasNoiseOr = bHasNoiseOr || HasNoise( it->tile );
	}
	if ( bHasNoiseAnd )										// crosses with one noise over all crosses in this tile
	{
		// copy crosses to base layer
		while ( !localcrosses.empty() ) 
		{
			pCrosses->base.push_back( localcrosses.front() );
			localcrosses.pop_front();
		}
		// if this entire set has noise, then just add ONE NOISE-ONLY tile to the set
		pCrosses->noise.push_back( SCrossTileInfo() );
		SCrossTileInfo &tile = pCrosses->noise.back();
		tile.flags = SCrossTileInfo::NOISE;
		tile.x = nX % STerrainPatchInfo::nSizeX;
		tile.y = nY % STerrainPatchInfo::nSizeY;
		tile.tile = 0;
		tile.cross = 0;
		if ( HasNoise(tiles[nY][nX].tile) )
			tiles[nY][nX].noise = 2;
		++nNumCrosses;
	}
	else if ( bHasNoiseOr )								// layered crosses with noise
	{
		pCrosses->layers.resize( Max(int(pCrosses->layers.size()), nNumCrosses) );
		// if this entire set has no noise, then set noise only for those tiles, which has and re-layer this crosses
		int nLayerIndex = 0;
		for ( CCrossesList::const_iterator it = localcrosses.begin(); it != localcrosses.end(); ++it, ++nLayerIndex )
		{
			pCrosses->layers[nLayerIndex].push_back( *it );
			pCrosses->layers[nLayerIndex].back().flags = HasNoise( it->tile ) ? SCrossTileInfo::MIXED : SCrossTileInfo::CROSS;
		}
		localcrosses.clear();
	}
	else																	// crosses without noise at all
	{
		// copy crosses to base layer
		while ( !localcrosses.empty() ) 
		{
			pCrosses->base.push_back( localcrosses.front() );
			localcrosses.pop_front();
		}
	}
	//
	return nNumCrosses;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// convert image color to the tile type
void CTerrainBuilder::ConvertImageSegment( CImageAccessor &image, const CTRect<int> &rect ) const
{
	for ( int i=rect.y1; i<rect.y2; ++i )
		for ( int j=rect.x1; j<rect.x2; ++j )
			image[i][j].r = GetTileType( image[i][j].r );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTerrainBuilder::GenerateTiles( const CImageAccessor &image, STerrainInfo *pTerrainInfo ) const
{
	const int nTerrainSizeX = image->GetSizeX();
	const int nTerrainSizeY = image->GetSizeY();
	pTerrainInfo->tiles.SetSizes( nTerrainSizeX, nTerrainSizeY );
	for ( int j=0; j<nTerrainSizeY; ++j )
	{
		for ( int i=0; i<nTerrainSizeX; ++i )
		{
			pTerrainInfo->tiles[j][i].tile = tileset.terrtypes[image[j][i].r].GetMapsIndex();
			pTerrainInfo->tiles[j][i].noise = HasNoise( pTerrainInfo->tiles[j][i].tile );
			//pTerrainInfo->tiles[j][i].shade = image[j][i].b;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������� ���������� ������
int CTerrainBuilder::PreprocessMapSegment( CArray2D<SMainTileInfo> &tiles, const CTRect<int> &rect ) const
{
	// �������� �� ������ ��� �������� ������� ����� �����. ������ ��� �� ��� ���, ���� ����� ��������� �� �����
	bool bChanged = false;
	int nPassCounter = 0;									// ������� �������� ��� ����������� (����� �� ����� � ����������� ����)
	do 
	{
		bChanged = false;
		for ( int i=rect.y1 + 1; i<rect.y2 - 1; ++i )
		{
			for ( int j=rect.x1 + 1; j<rect.x2 - 1; ++j )
			{
				// (i,j) < (i,j-1) && (i,j) < (i,j+1)
				if ( ( ComparePriority(GetTerrainType(tiles[i][j].tile), GetTerrainType(tiles[i][j - 1].tile)) == -1 ) && 
					   ( ComparePriority(GetTerrainType(tiles[i][j].tile), GetTerrainType(tiles[i][j + 1].tile)) == -1 ) )
				{
					tiles[i][j].tile = SelectMinPriority( tiles[i][j - 1].tile, tiles[i][j + 1].tile );
					bChanged = true;
				}
			}
		}

		for ( int i=rect.y1 + 1; i<rect.y2 - 1; ++i )
		{
			for ( int j=rect.x1 + 1; j<rect.x2 - 1; ++j )
			{
				// (i,j) < (i-1,j) && (i,j) < (i+1,j)
				if ( ( ComparePriority(GetTerrainType(tiles[i][j].tile), GetTerrainType(tiles[i - 1][j].tile)) == -1 ) && 
					   ( ComparePriority(GetTerrainType(tiles[i][j].tile), GetTerrainType(tiles[i + 1][j].tile)) == -1 ) )
				{
					tiles[i][j].tile = SelectMinPriority( tiles[i - 1][j].tile, tiles[i + 1][j].tile );
					bChanged = true;
				}
			}
		}
		++nPassCounter;
	} while ( bChanged && (nPassCounter < 20) );
	// set noise flags for each tile
	SetNoise( tiles, rect );
	//
	return nPassCounter;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTerrainBuilder::SetNoise( CArray2D<SMainTileInfo> &tiles, const CTRect<int> &rect ) const
{
	for ( int i = rect.y1; i != rect.y2; ++i )
	{
		for ( int j = rect.x1; j != rect.x2; ++j )
			tiles[i][j].noise = HasNoise( tiles[i][j].tile );
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CTerrainBuilder::MapSegmentGenerateCrosses( CArray2D<SMainTileInfo> &tiles, const CTRect<int> &rect, 
																							  const CTRect<int> &rcSuper, SComplexCrosses *pCrosses ) const
{
	// generate cross masks
	int nNumCrosses = 0;
	for ( int i=rect.y1; i<rect.y2; ++i )
		for ( int j=rect.x1; j<rect.x2; ++j )
			nNumCrosses += GetNeighboursMask( tiles, j, i, rect, rcSuper, pCrosses );
	//
	return nNumCrosses;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTerrainBuilder::GetPatchRect( int nX, int nY, CTRect<int> *pRect ) const
{
	pRect->Set( nX       * STerrainPatchInfo::nSizeX, nY       * STerrainPatchInfo::nSizeX, 
				      (nX + 1) * STerrainPatchInfo::nSizeX, (nY + 1) * STerrainPatchInfo::nSizeX );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** terrain patch builder
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CopyCrossesList( STerrainPatchInfo::CCrossesList *pDst, const CTerrainBuilder::CCrossesList &src )
{
	pDst->clear();
	pDst->reserve( src.size() );
	for ( CTerrainBuilder::CCrossesList::const_iterator it = src.begin(); it != src.end(); ++it )
		pDst->push_back( *it );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTerrainBuilder::CopyCrosses( STerrainPatchInfo *pPatch, const SComplexCrosses &crosses ) const
{
	// copy base crosses
	CopyCrossesList( &pPatch->basecrosses, crosses.base );
	// copy noise crosses
	CopyCrossesList( &pPatch->noisecrosses, crosses.noise );
	// copy layers
	pPatch->layercrosses.resize( crosses.layers.size() );
	int nLayerIndex = 0;
	for ( std::vector<CCrossesList>::const_iterator it = crosses.layers.begin(); it != crosses.layers.end(); ++it, ++nLayerIndex )
		CopyCrossesList( &pPatch->layercrosses[nLayerIndex], *it );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTerrainBuilder::PreprocessMap( IImage *pImage, STerrainInfo *pTerrainInfo ) const
{
	const int nTerrainSizeX = pImage->GetSizeX();
	const int nTerrainSizeY = pImage->GetSizeY();
	// check map correctness
	div_t divResX = div( nTerrainSizeX, STerrainPatchInfo::nSizeX );
	div_t divResY = div( nTerrainSizeY, STerrainPatchInfo::nSizeY );
	NI_ASSERT_TF( (divResX.rem == 0) && (divResY.rem == 0), "Can't create map with dims not multiple to patch dims", return );
	//
	int nNumPatchesX = divResX.quot;
	int nNumPatchesY = divResY.quot;
	// complete pre-process map
	CImageAccessor image = pImage;
	CTRect<int> rcSuper( 0, 0, nTerrainSizeX, nTerrainSizeY );
	ConvertImageSegment( image, rcSuper );
	// generate tiles from terra types
	GenerateTiles( image, pTerrainInfo );
	//
	PreprocessMapSegment( pTerrainInfo->tiles, rcSuper );
	// generate patches and create crosses for each one
	pTerrainInfo->patches.SetSizes( nNumPatchesX, nNumPatchesY );
	for ( int j=0; j<nNumPatchesY; ++j )
	{
		for ( int i=0; i<nNumPatchesX; ++i )
		{
			STerrainPatchInfo &patch = pTerrainInfo->patches[j][i];
			patch.nStartX = i * STerrainPatchInfo::nSizeX;
			patch.nStartY = j * STerrainPatchInfo::nSizeY;
			// 
			CTRect<int> rcRect;
			GetPatchRect( i, j, &rcRect );
			SComplexCrosses crosses;
			MapSegmentGenerateCrosses( pTerrainInfo->tiles, rcRect, rcSuper, &crosses );
			// copy crosses
			CopyCrosses( &patch, crosses );
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CTileEqualFunctional
{
	const BYTE tile;
public:
	explicit CTileEqualFunctional( const BYTE _tile ) : tile( _tile ) {  }
	bool operator()( const SMainTileDesc &desc ) { return desc.nIndex == tile; }
};
int CTerrainBuilder::GetTerrainType( BYTE tile ) const
{
	CTypesMap::const_iterator pos = terratypes.find( tile );
	if ( pos != terratypes.end() )
		return pos->second;
	else
	{
		for ( int i=0; i<tileset.terrtypes.size(); ++i )
		{
			const STerrTypeDesc &type = tileset.terrtypes[i];
			if ( std::find_if( type.tiles.begin(), type.tiles.end(), CTileEqualFunctional(tile) ) != type.tiles.end() )
			{
				terratypes[tile] = i;
				return i;
			}
		}
	}
	NI_ASSERT_T( false, NStr::Format("Can't find terrain type for %d tile", tile) );
	return -1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CTerrainBuilder::GetCrossType( BYTE tile ) const
{
	CTypesMap::const_iterator pos = crosstypes.find( tile );
	if ( pos != crosstypes.end() )
		return pos->second;
	else
	{
		for ( int i=0; i<crosset.crosses.size(); ++i )
		{
			const SCrossDesc &type = crosset.crosses[i];
			for ( int j=0; j<type.tiles.size(); ++j )
			{
				if ( std::find_if( type.tiles[j].tiles.begin(), type.tiles[j].tiles.end(), CTileEqualFunctional(tile) ) != type.tiles[j].tiles.end() )
				{
					crosstypes[tile] = j;
					return j;
				}
			}
		}
	}
	NI_ASSERT_T( false, NStr::Format("Can't find cross type for %d tile", tile) );
	return -1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CTerrainBuilder::GetCrossetType( BYTE tile ) const
{
	CTypesMap::const_iterator pos = crossettypes.find( tile );
	if ( pos != crossettypes.end() )
		return pos->second;
	else
	{
		for ( int i=0; i<crosset.crosses.size(); ++i )
		{
			const SCrossDesc &type = crosset.crosses[i];
			for ( int j=0; j<type.tiles.size(); ++j )
			{
				if ( std::find_if( type.tiles[j].tiles.begin(), type.tiles[j].tiles.end(), CTileEqualFunctional(tile) ) != type.tiles[j].tiles.end() )
				{
					crossettypes[tile] = i;
					return i;
				}
			}
		}
	}
	NI_ASSERT_T( false, NStr::Format("Can't find crosset type for %d tile", tile) );
	return -1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const bool CTerrainBuilder::HasNoise( BYTE tile ) const
{
	const int nTerrType = GetTerrainType( tile );
	return tileset.terrtypes[nTerrType].bMicroTexture;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
