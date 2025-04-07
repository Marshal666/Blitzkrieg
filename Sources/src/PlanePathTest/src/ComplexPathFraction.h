#if !defined(_complex_path_fraction_)
#define _complex_path_fraction_

#include "IPlanePathFraction.h"
#include "PlanePathMath.h"
#include "PathFraction.h"

/////////////////////////////////////////////////////////////////////////////
//	CPathFractionComplex
/////////////////////////////////////////////////////////////////////////////
class CPathFractionComplex : public IPathFractionComplex
{
protected:
	typedef std::vector< CPtr<IPathFraction> > CSubstitutes;
	CSubstitutes substitute;
	
	typedef std::pair< const IPathFraction*, float> CCurFraction;

	CCurFraction GetCur( const float fDist ) const
	{
		if ( !substitute.empty() )
		{
			NI_ASSERT_T( !substitute.empty(), "cannot work with empty path" );
			float fDistSoFar = 0;
			float fTmp = 0;
			
			for ( CSubstitutes::const_iterator it = substitute.begin(); it < substitute.end(); ++it )
			{
				fTmp = fDistSoFar;
				fDistSoFar += (*it)->GetLength();
				if ( fDistSoFar > fDist )
					return CCurFraction( *it, fTmp );
			}
			return CCurFraction( substitute.back(), fTmp );
		}
		return CCurFraction( 0, 0 );
	}

	void AfterSubstitute()
	{
		for( CSubstitutes::iterator it = substitute.begin(); it != substitute.end(); )
		{
			if ( (*it)->GetLength() == 0 )
				it = substitute.erase( it );
			else
				++it;
		}
	}
public:

	virtual float STDCALL GetLength() const
	{
		float fDistSoFar = 0;
		for ( CSubstitutes::const_iterator it = substitute.begin(); it < substitute.end(); ++it )
			fDistSoFar += (*it)->GetLength();
		return fDistSoFar;
	}

	virtual CVec3 STDCALL GetPoint( const float fDist ) const
	{
		CCurFraction fr = GetCur( fDist );
		if ( fr.first )
			return fr.first->GetPoint( fDist - fr.second );
		return VNULL3;
	}
	virtual CVec3 STDCALL GetTangent( const float fDist ) const
	{
		CCurFraction fr = GetCur( fDist );
		if ( fr.first )
			return fr.first->GetTangent( fDist - fr.second );
		return VNULL3;
	}
	virtual CVec3 STDCALL GetNormale( const float fDist ) const
	{
		CCurFraction fr = GetCur( fDist );
		if ( fr.first )
			return fr.first->GetNormale( fDist - fr.second );
		return V3_AXIS_Z;
	}
};
/////////////////////////////////////////////////////////////////////////////
//	CPathFractionArc3D
/////////////////////////////////////////////////////////////////////////////
class CPathFractionArc3D : public CPathFractionComplex
{
	OBJECT_COMPLETE_METHODS( CPathFractionArc3D );

	CVec3 i, j, k;													// local coordinate system ( i = v0, j = R - x0, k = i^j )
	CDirectedCircle circle;									// in (i,j,k) coordinate system (center = (0,R) )
	
	CVec3 x0;																// begin of arc fraction
	CVec3 x1;																// end of arc path fraction and start of line fraction
	float fLength;

	//CRAP{ FOR TEST
	CVec3 v1;																// end point speed
	WORD nDiff;															// dirs difference
	//CRAP}

public:
	void Init( const CVec3 &_i, const CVec3 &_j, const CVec3 &_k,
						 const CDirectedCircle &_circle, const CVec3 &_x0, const CVec3 &_x1, const float _fLength,
						 const CVec3 &_v1, const int _nDiff );
	
	//CRAP{ FOR TEST
	virtual CVec3 STDCALL GetPoint( const float fDist ) const;
	virtual CVec3 STDCALL GetTangent( const float fDist ) const;
	virtual CVec3 STDCALL GetNormale( const float fDist ) const;
	//CRAP}
	virtual float STDCALL GetLength() const { return fLength; }
	virtual void STDCALL DoSubstitute( IPathFraction *pNext );
	virtual CVec3 STDCALL GetEndPoint() const;
	virtual CVec3 STDCALL GetStartPoint() const;
	virtual CVec3 STDCALL GetEndTangent() const;
	virtual CVec3 STDCALL GetStartTangent() const;
};
/////////////////////////////////////////////////////////////////////////////
//	CPathFractionArc
/////////////////////////////////////////////////////////////////////////////
// horisontal manuver
class CPathFractionArc : public CPathFractionComplex 
{
	OBJECT_COMPLETE_METHODS( CPathFractionArc )
		
	CDirectedCircle circle;								// initial circle
	CVec2 x0, x1;												// from point 1 to 2
	float fLength;
	
public:
	void Init( const CDirectedCircle &_circle, const CVec2 &_x0, const CVec2 &_x1 )
	{
		circle = _circle;
		x0 = _x0;
		x1 = _x1;
		fLength = 1.0f * ( DirectedDirsDifference(x0 - circle.center, x1 - circle.center, circle.nDir) ) * 2* PI * circle.r / 65535;
	}
	virtual void STDCALL DoSubstitute( IPathFraction *pNext );
	
	//CRAP{ FOR TEST
	virtual CVec3 STDCALL GetPoint( const float fDist ) const;
	virtual CVec3 STDCALL GetTangent( const float fDist ) const;

	//CRAP}
};
/////////////////////////////////////////////////////////////////////////////
//	CPathFractionArcLine3D
/////////////////////////////////////////////////////////////////////////////
// sircle arc - line path fraction (in 3D)
// v1 in x1 doesn't matter. the only thing is that whole maneuver is in 1 plane (v0, x1-x0)
class CPathFractionArcLine3D : public CPathFractionComplex
{
	OBJECT_COMPLETE_METHODS( CPathFractionArcLine3D )
	CPtr<CPathFractionArc3D> pArc;
	CPtr<IPathFraction>  pLine;

	bool TryCircle( const CVec3 &x0, const CVec3 &v0, const CVec3 &x1, const float fR, const int nDir, CVec3 *vT );
public:
	// creates arc and line path fractions if 3D (but manuver is flat)
	// nPathDirection = 1 => circle first, -1 => line is first
	void Init( const CVec3 &x0, const CVec3 &_v0, const CVec3 &x1, const float fR/*circle radius*/);
	virtual float STDCALL GetLength() const;
	
	virtual void STDCALL DoSubstitute( IPathFraction *pNext );
	
	// access to inner path portions without substitute.
	CPathFractionArc3D * GetArc() { return pArc; }
	IPathFraction * GetLine() { return pLine; }
};
/////////////////////////////////////////////////////////////////////////////
//	CPathFractionCircleLineCircle
/////////////////////////////////////////////////////////////////////////////
// s-shaped path (circle arc - line - circle arc )
class CPathFractionCircleLineCircle : public CPathFractionComplex
{
	OBJECT_COMPLETE_METHODS( CPathFractionCircleLineCircle )

	CPtr<CPathFractionArc> pStart;
	CPtr<CPathFractionArc> pFinish;
	CPtr<CPathFractionLine>  pLine;

	float fZ;

	void Init( const CDirectedCircle &_start, const CVec2 &_vStart1, const CVec2 &_vStart2,
						 const CDirectedCircle &_finish, const CVec2 &_vFinish1, const CVec2 &_vFinish2 );

	void TryPath( const CVec2 &x0, const CVec2 &x1, 
								const CDirectedCircle &r1, const CDirectedCircle &o1, 
								CPathFractionCircleLineCircle *pPath, CPathFractionCircleLineCircle *pBest,
								bool *bInitted ) const;

public:

	//3D path
	void Init( const CVec3 &x0, const CVec3 &x1,
						 const CVec3 &v0, const CVec3 &v1,
						 const float fR0, const float fR1 )
	{
		Init( CVec2(x0.x, x0.y), CVec2(x1.x, x1.y),
					CVec2(v0.x, v0.y), CVec2(v1.x, v1.y), 
					fR0, fR1,
					x0.z );
	}
	//

	void Init( const CVec2 &x0, const CVec2 &x1,
						 const CVec2 &v0, const CVec2 &v1,
						 const float fR0, const float fR1,
						 const float _fZ );
	
	// from vStart2 to vFinish1 plane travels by line
	CPathFractionCircleLineCircle() {  }
	
	virtual CVec3 STDCALL GetPoint( const float fDist ) const
	{	
		return CPathFractionComplex::GetPoint( fDist ) + CVec3(0,0,fZ); 
	}
	
	virtual float STDCALL GetLength() const
	{ 
		return pStart->GetLength() + pLine->GetLength() + pFinish->GetLength(); 
	}


	virtual void STDCALL DoSubstitute( IPathFraction *pNext )
	{
		pStart->DoSubstitute( 0 );
		pFinish->DoSubstitute( 0 );
		substitute.resize( 3 );
		substitute[0] = pStart;
		substitute[1] = pLine;
		substitute[2] = pFinish;
	}
};
/////////////////////////////////////////////////////////////////////////////
//	CPathFractionCircleLineCircle3D
/////////////////////////////////////////////////////////////////////////////
// path is suitable if 
// 1) direction change is small ( < Pi/2 )
// 2) direction difference of v0 and x1-x0 is small
// 3) distance is long ( > 2R )
class CPathFractionCircleLineCircle3D : public CPathFractionComplex
{
	OBJECT_COMPLETE_METHODS( CPathFractionCircleLineCircle3D )
	
	CPtr<CPathFractionArcLine3D> pStart;
	CPtr<CPathFractionArcLine3D> pFinish;

public:

	void Init( const CVec3 &x0, const CVec3 &x1,			// coordinates
						 const CVec3 &v0, const CVec3 &v1,			// directions
						 const float r0, const float r1 );			// turn radii
	virtual void STDCALL DoSubstitute( IPathFraction *pNext );
	
};
/////////////////////////////////////////////////////////////////////////////
#endif //_complex_path_fraction_