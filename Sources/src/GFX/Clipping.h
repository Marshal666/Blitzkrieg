#ifndef __CLIPPING_H__
#define __CLIPPING_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Cohen-Sutherland line clipping
//
//              |          |
//         0110 |   0100   | 1100
//           ---+----------+---
//              |          |
//              |          |
//         0010 |   0000   | 1000
//              |          |
//              |          |
//           ---+----------+---
//         0011 |   0001   | 1001
//              |          |
//
//
//  if (outcode1 | outcode2 == 0)
//    line segment is inside
//  else if ( outcode1 & outcode2 ! = 0 )
// 	  line segment is outside
//  else
// 	  don't know
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CLIP_CS_TOP			0x0004
#define CLIP_CS_LEFT		0x0002
#define CLIP_CS_BOTTOM	0x0001
#define CLIP_CS_RIGHT		0x0008
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline const DWORD GetCSClipFlags( const float x1, const float y1, const float x2, const float y2, const float x, const float y )
{
	const float t1 = x - x1, t2 = y - y1, t3 = x2 - x, t4 = y2 - y;
	return (( FP_BITS_CONST(t1) >> 30 ) & 2 ) |
				 (( FP_BITS_CONST(t2) >> 29 ) & 4 ) |
				 (( FP_BITS_CONST(t3) >> 28 ) & 8 ) |
				 (( FP_BITS_CONST(t4) >> 31 )     );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// if we got rid of this rect, returned false
bool ClipAARect( const CTRect<float> &bounds, CTRect<float> *pRect, CTRect<float> *pMaps );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __CLIPPING_H__
