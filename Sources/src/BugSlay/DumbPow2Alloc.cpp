#include "StdAfx.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
const int N_SIZE = 0x20000000;
const int N_WAYS = 16;
static void *pBase;
static int nLock = -1;
static void* freePtrs[N_WAYS];
static void* pAllocated[N_WAYS];
////////////////////////////////////////////////////////////////////////////////////////////////////
static __forceinline void RealEnterCritical()
{
	_asm
	{
Retry:		
		lock add nLock, 1
		jz Ok
		//lock sub nLock, 1
		//pause
		push 0
		call dword ptr[ Sleep ]
		jmp Retry
Ok:
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
static __forceinline void RealLeaveCritical()
{
	_asm 
	{
		mov nLock, -1
		//lock sub nLock, 1
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
static void InitDumbAlloc()
{
	pBase = (void*)0x08000000;
	for(;;)
	{
		void *pTest = VirtualAlloc( pBase, N_SIZE, MEM_RESERVE, PAGE_READWRITE );
		if ( pTest )
			break;
		pBase = (char*)pBase + 0x8000000;
	}
	for ( int k = 0; k < N_WAYS; ++k )
		pAllocated[k] = ((char*)pBase) + k * (N_SIZE/N_WAYS);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
static __forceinline void* RealFastDumbAlloc( int _nSize )
{
	int nSize = GetMSB( _nSize - 1 ) + 1;
	if ( nSize < 2 )
		nSize = 2;
	void *pFree = freePtrs[ nSize - 2 ];
	void *pRes = pFree;
	if ( !pRes )
	{
		char **pNew = (char**)&pAllocated[ nSize - 2 ];
		char *pNewPlace = *pNew;
		if ( !pNewPlace )
			return malloc( _nSize );
		void *pTest = VirtualAlloc( pNewPlace, 0x10000, MEM_COMMIT, PAGE_READWRITE );
		NI_ASSERT( pTest != 0 );
		for ( int nDelta = 0; nDelta < 0x10000; nDelta += (1<<nSize) )
		{
			void *pBlock = pNewPlace + nDelta;
			*(void**)pBlock = pFree;
			pFree = pBlock;
		}
		*pNew = pNewPlace + 0x10000;
		if ( ( ((int)*pNew) & ( N_SIZE/N_WAYS - 1 ) ) == 0 )
		{
			NI_ASSERT_T( false, "Fast memory manager failed!" );
			OutputDebugString( "Fast memory manager pool is exhausted, fall back to malloc\n" );
			*pNew = 0;
		}
		pRes = pFree;
	}
	pFree = *(void**)pRes;
	freePtrs[ nSize - 2 ] = pFree;
	return pRes;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void* __cdecl NBugSlayer::FastDumbAlloc( int _nSize )
{
	if ( !pBase )
		InitDumbAlloc();
	RealEnterCritical();
	void *pRes = RealFastDumbAlloc( _nSize );
	RealLeaveCritical();
	return pRes;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool __cdecl NBugSlayer::FastDumbFree( void *pData )
{
	if ( pData < pBase || pData > ( (char*)pBase + N_SIZE ) )
		return false;
	RealEnterCritical();
	int nSize = ((int)( ((char*)pData) - ((char*)pBase) )) / (N_SIZE/N_WAYS);
	*((void**)pData) = freePtrs[ nSize ];
	freePtrs[ nSize ] = pData;
	RealLeaveCritical();
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
