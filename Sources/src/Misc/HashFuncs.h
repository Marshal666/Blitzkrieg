#ifndef __HASHFUNCS_H__
#define __HASHFUNCS_H__
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SDefaultPtrHash
{
	int operator()( const void *pData ) const { return reinterpret_cast<int>( pData ); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SPtrHash
{
	template <class T>
		int operator()( const CPtr<T> &a ) const { return int( a.GetPtr() ); }
	template <class T>
		int operator()( const CObj<T> &a ) const { return int( a.GetPtr() ); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __HASHFUNCS_H__
