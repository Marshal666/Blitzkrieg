#ifndef __AREA_MAP_H__
#define __AREA_MAP_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class TYPE, class TStorageType = CPtr<TYPE>, class TPosition = CVec3, class TCoeffType = float>
class CAreaMap : public CArray2D< std::list<TStorageType> >
{
public:
	typedef std::list<TStorageType> CDataList;
	typedef CArray2D<CDataList> CBaseArea;
private:
	const TCoeffType tCellSize;								// area map cell size
	// service functional
	class CObjEqualFunctional
	{
		const TYPE *pObj;
	public:
		explicit CObjEqualFunctional( const TYPE *_pObj ) : pObj( _pObj ) {  }
		bool operator()( const TStorageType &ptr ) const { return ptr == pObj; }
	};
	// add object to the (nX, nY) cell
	void AddTo( int nX, int nY, TYPE *pObj )
	{
		CDataList &data = (*this)[nY][nX];
		CDataList::const_iterator pos = std::find_if( data.begin(), data.end(), CObjEqualFunctional(pObj) );
		if ( pos == data.end() )
			data.push_back( pObj );
	}
	// remove object from the (nX, nY) cell
	void RemoveFrom( int nX, int nY, TYPE *pObj )
	{
		if ( (nX < 0) || (nX >= GetSizeX()) || (nY < 0) || (nY >= GetSizeY()) )
			return;
		CDataList &data = (*this)[nY][nX];
		CDataList::iterator pos = std::find_if( data.begin(), data.end(), CObjEqualFunctional(pObj) );
		if ( pos != data.end() )
			data.erase( pos );
	}
	// diable copy constructor and assignment operator
	CAreaMap( const CAreaMap &a ) {  }
	CAreaMap& operator=( const CAreaMap &a ) { return *this; }
public:
	explicit CAreaMap( TCoeffType _tCellSize ) : tCellSize( _tCellSize ) {  }
	// move object to the new position.
	// if this is a new object, this will be added to the area map
	void MoveTo( TYPE *pObj, const TPosition &vNewPos )
	{
		const TPosition vOldPos = pObj->GetPosition();
		const int nOldIndexX = int( vOldPos.x / tCellSize );
		const int nOldIndexY = int( vOldPos.y / tCellSize );
		const int nNewIndexX = int( vNewPos.x / tCellSize );
		const int nNewIndexY = int( vNewPos.y / tCellSize );
		// if we are moved to the new cell, add to the new and, then, remove from the old one
		if ( (nOldIndexX != nNewIndexX) || (nOldIndexY != nNewIndexY) )
		{
			AddTo( nNewIndexX, nNewIndexY, pObj );
			RemoveFrom( nOldIndexX, nOldIndexY, pObj );
		}
		// set new position for the object
		pObj->SetPosition( vNewPos );
	}
	// add new object
	void Add( TYPE *pObj )
	{
		const TPosition vPos = pObj->GetPosition();
		const int nX = int( vPos.x / tCellSize );
		const int nY = int( vPos.y / tCellSize );
		AddTo( nX, nY, pObj );
	}
	// remove object from the area map
	void Remove( TYPE *pObj )
	{
		const TPosition vPos = pObj->GetPosition();
		const int nX = int( vPos.x / tCellSize );
		const int nY = int( vPos.y / tCellSize );
		RemoveFrom( nX, nY, pObj );
	}

	// add new object to position
	void AddToPosition( TYPE *pObj, const TPosition &vPos )
	{
		const int nX = int( vPos.x / tCellSize );
		const int nY = int( vPos.y / tCellSize );
		AddTo( nX, nY, pObj );
	}

	// remove object from positions
	void RemoveFromPosition( TYPE *pObj, const TPosition &vPos )
	{
		const int nX = int( vPos.x / tCellSize );
		const int nY = int( vPos.y / tCellSize );
		RemoveFrom( nX, nY, pObj );
	}
	//
	const bool IsInArea( const TPosition &vPos ) const
	{
		return ( vPos.x >= 0 ) && (vPos.y >= 0) && (vPos.x < GetSizeX()*tCellSize) && (vPos.y < GetSizeY()*tCellSize);
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class TYPE>
class CStructAreaMapComparator
{
	const TYPE &obj;
public:
	CStructAreaMapComparator( const TYPE &_obj ) : obj( _obj ) {  }
	const bool operator()( const TYPE &obj2 ) const { return obj == obj2; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class TYPE, class TPosition = CVec3, class TComparator = CStructAreaMapComparator<TYPE>, class TCoeffType = float>
class CStructAreaMap : public CArray2D< std::list<TYPE> >
{
public:
	typedef std::list<TYPE> CDataList;
	typedef CArray2D<CDataList> CBaseArea;
private:
	const TCoeffType tCellSize;								// area map cell size
	// add object to the (nX, nY) cell
	void AddTo( int nX, int nY, const TYPE &obj )
	{
		CDataList &data = (*this)[nY][nX];
		CDataList::const_iterator pos = std::find_if( data.begin(), data.end(), TComparator(obj) );
		if ( pos == data.end() )
			data.push_back( obj );
	}
	// remove object from the (nX, nY) cell
	void RemoveFrom( int nX, int nY, const TYPE &obj )
	{
		if ( (nX < 0) || (nX >= GetSizeX()) || (nY < 0) || (nY >= GetSizeY()) )
			return;
		CDataList &data = (*this)[nY][nX];
		CDataList::iterator pos = std::find_if( data.begin(), data.end(), TComparator(obj) );
		if ( pos != data.end() )
			data.erase( pos );
	}
	// diable copy constructor and assignment operator
	CStructAreaMap( const CStructAreaMap &a ) {  }
	CStructAreaMap& operator=( const CStructAreaMap &a ) { return *this; }
public:
	explicit CStructAreaMap( TCoeffType _tCellSize ) : tCellSize( _tCellSize ) {  }
	// move object to the new position.
	// if this is a new object, this will be added to the area map
	void MoveTo( TYPE &obj, const TPosition &vNewPos )
	{
		const TPosition vOldPos = obj.GetPosition();
		const int nOldIndexX = int( vOldPos.x / tCellSize );
		const int nOldIndexY = int( vOldPos.y / tCellSize );
		const int nNewIndexX = int( vNewPos.x / tCellSize );
		const int nNewIndexY = int( vNewPos.y / tCellSize );
		// if we are moved to the new cell, add to the new and, then, remove from the old one
		if ( (nOldIndexX != nNewIndexX) || (nOldIndexY != nNewIndexY) )
		{
			AddTo( nNewIndexX, nNewIndexY, obj );
			RemoveFrom( nOldIndexX, nOldIndexY, obj );
		}
		// set new position for the object
		obj.SetPosition( vNewPos );
	}
	// add new object
	void Add( const TYPE &obj )
	{
		const TPosition vPos = obj.GetPosition();
		const int nX = int( vPos.x / tCellSize );
		const int nY = int( vPos.y / tCellSize );
		AddTo( nX, nY, obj );
	}
	// remove object from the area map
	void Remove( const TYPE &obj )
	{
		const TPosition vPos = obj.GetPosition();
		const int nX = int( vPos.x / tCellSize );
		const int nY = int( vPos.y / tCellSize );
		RemoveFrom( nX, nY, obj );
	}

	// add new object to position
	void AddToPosition( const TYPE &obj, const TPosition &vPos )
	{
		const int nX = int( vPos.x / tCellSize );
		const int nY = int( vPos.y / tCellSize );
		AddTo( nX, nY, obj );
	}

	// remove object from positions
	void RemoveFromPosition( const TYPE &obj, const TPosition &vPos )
	{
		const int nX = int( vPos.x / tCellSize );
		const int nY = int( vPos.y / tCellSize );
		RemoveFrom( nX, nY, obj );
	}
	//
	const bool IsInArea( const TPosition &vPos ) const
	{
		return ( vPos.x >= 0 ) && (vPos.y >= 0) && (vPos.x < GetSizeX()*tCellSize) && (vPos.y < GetSizeY()*tCellSize);
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __AREA_MAP_H__
