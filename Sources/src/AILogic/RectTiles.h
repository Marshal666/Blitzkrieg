#ifndef __RECTTILES_H__
#define __RECTTILES_H__

#pragma ONCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "AIHashFuncs.h"
#include "AICellsTiles.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef std::list<SVector> CTilesSet;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// для GetTilesCoveredByRectSides
class CTilesCollector
{
public:
	CTilesSet *pTiles;
	CTilesCollector(CTilesSet *pTiles) : pTiles(pTiles) { }
	bool operator() ( float x, float y );
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IsRectOnLockedTiles( const SRect &rect, const BYTE aiClass );
// возвращает tiles, которые накрывает данный четырёхугольник
void GetTilesCoveredByQuadrangle( const CVec2 &v1, const CVec2 &v2, const CVec2 &v3, const CVec2 &v4, CTilesSet *pTiles );
// возвращает tiles, которые накрывает данный rect
void GetTilesCoveredByRect( const SRect &rect, CTilesSet *pTiles );
//возвращает tiles, которые пересекаются со сторонами данного rect
void GetTilesCoveredByRectSides( const SRect &rect, CTilesSet *pTiles );
//то же самое, за исключением стороны, которая лежит в сторону dir от центра 
void GetTilesCoveredByRectSides( const SRect &rect, CTilesSet *pTiles, WORD dir );
//тайлы под стороной, которая лежит в сторону dir от центра 
void GetTilesCoveredBySide( const SRect &rect, CTilesSet *pTiles, WORD dir );
// свободна ли карта под rect ( нет залоканных тайлов и не пересекается с юнитами ), юнит pUnit не учитывается
bool IsMapFullyFree( const SRect &rect, interface IBasePathUnit *pUnit );
void GetTilesNextToRect( const SRect &rect, CTilesSet *pTiles );
//same as above, excludes tiles near given direction from center.
void GetTilesNextToRect( const SRect &rect, CTilesSet *pTiles, const WORD wDirExclude );
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool operator < ( const SVector &cell1, const SVector &cell2 );
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __RECTTILES_H__
