#include <d3d8.h>
#include <d3d8types.h>
#include <d3d8caps.h>

#include "..\Misc\Win32Helper.h"

#include "GFX.h"
#include "GFXHelper.h"
#include "CommonStructs.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// ** class CRefCount
// ** this class have only one goal - track ref counter
// ** and self-destruct, then ref counter reaches zero
// ** !!! for experiments and internal use only !!!
// ************************************************************************************************************************ //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CRefCount
{
	int nRefData;
protected:
	virtual ~CRefCount() {  }							// this object cannot be deleted directly - only through 'Release'
public:
	CRefCount() : nRefData( 0 ) {  }			// by default, object created with ref count = '0'
	// ref count methods
	int AddRef() { ++nRefData; return nRefData; }
	int Release() { int nRef = --nRefData; if ( (nRefData & 0x7fffffff) == 0 ) delete this; return (nRef & 0x7fffffff); }
	void Invalidate() { nRefData |= 0x80000000; }
	bool IsValid() const { return (nRefData & 0x80000000) == 0; }
	// unique run-time ID of the object
	DWORD GetRTID() const { return reinterpret_cast<DWORD>( this ); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class TUserObj>
class CPtr2
{
	typedef CPtr2<TUserObj> TPtr;
	TUserObj *pObj;
protected:
	void AddRef( TUserObj *_pObj ) { if ( _pObj ) _pObj->AddRef(); }
	void Release( TUserObj *_pObj ) { if ( _pObj ) _pObj->Release(); }
	// set new object and remove old
	void Set( TUserObj *_pObj ) { TUserObj *pOld = pObj; pObj = _pObj; AddRef( pObj ); Release( pOld ); }
public:
	CPtr2() : pObj( 0 ) {  }
	CPtr2( TUserObj *_pObj ) : pObj( _pObj ) { AddRef( pObj ); }
	CPtr2( const TPtr &ptr ) : pObj( ptr.pObj ) { AddRef( pObj ); }
	~CPtr2() { Release( pObj ); }
	// assignment operators
	TPtr& operator=( TUserObj *_pObj ) { Set( _pObj ); return *this; }
	TPtr& operator=( const TPtr &ptr ) { Set( ptr.pObj ); return *this; }
	//
	bool operator==( const TPtr &a ) const { return GetPtr() == a.GetPtr(); }
	bool operator==( const TUserObj *a ) const { return GetPtr() == a; }
	bool operator!=( const TPtr &a ) const { return GetPtr() != a.GetPtr(); }
	bool operator!=( const TUserObj *a ) const { return GetPtr() != a; }
	bool operator< ( const TUserObj *a ) const { return GetPtr() < a; }
	bool operator> ( const TUserObj *a ) const { return GetPtr() > a; }
	bool operator<=( const TUserObj *a ) const { return GetPtr() <= a; }
	bool operator>=( const TUserObj *a ) const { return GetPtr() >= a; }
	// object access operators (dereference and pointer access)
	operator TUserObj*() const { return pObj; }
	TUserObj* operator->() const { return pObj; }
	// check for empty and valid object
	bool IsEmpty() const { return pObj == 0; }
	bool IsValid() const { return !IsEmpty() && GetBarePtr()->IsValid(); }
	// direct acces to the object... ugly functions, but it is neccessary,
	// because C++ can't cast from smartptr to polymorphics of the stored data
	TUserObj* GetPtr() const { return pObj; }
	CRefCount* GetBarePtr() const { return pObj; }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
