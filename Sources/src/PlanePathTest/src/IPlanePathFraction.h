#if !defined(_IPathFraction_included_)
#define _IPathFraction_included_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
//	IPathFraction 
/////////////////////////////////////////////////////////////////////////////
interface IPathFraction : public IRefCount
{
	virtual float STDCALL GetLength() const = 0;
	virtual CVec3 STDCALL GetPoint( const float fDist ) const = 0;
	virtual CVec3 STDCALL GetTangent( const float fDist ) const = 0;
	// direction of plane's top (ideal)
	virtual CVec3 STDCALL GetNormale( const float fDist ) const { return V3_AXIS_Z;}

	// returns end point. unlike to GetPoint it works on unsubstituted paths
	virtual CVec3 STDCALL GetEndPoint() const { return GetPoint( GetLength() );}
	virtual CVec3 STDCALL GetStartPoint() const { return GetPoint(0.0f);}

	virtual CVec3 STDCALL GetEndTangent() const { return GetTangent(GetLength());}
	virtual CVec3 STDCALL GetStartTangent() const { return GetTangent(0.0f);}

	// before this path fraction is passed, is could be nessesary to substitute
	// internal path fractions. may use next path fraction to ensure smoothness
	virtual void STDCALL DoSubstitute( IPathFraction *pNext ) {  }
};

/////////////////////////////////////////////////////////////////////////////
//	IPathFractionComplex 
/////////////////////////////////////////////////////////////////////////////
interface IPathFractionComplex : public IPathFraction
{
	// before this path fraction is passed, is could be nessesary to substitute
	// internal path fractions. may use next path fraction to ensure smoothness
	//virtual void STDCALL DoSubstitute( IPathFraction *pNext ) = 0;
};

#endif //_IPathFraction_included_