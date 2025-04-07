/*----------------------------------------------------------------------
       John Robbins - Microsoft Systems Journal Bugslayer Column
----------------------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "BugSlayer.h"
// The project internal header file.
#include "Internal.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HMODULE* STDCALL AllocAndFillProcessModuleList( HANDLE hHeap, LPUINT puiCount )
{
  ASSERT( FALSE == IsBadWritePtr(puiCount , sizeof(LPUINT)) );
  if ( TRUE == IsBadWritePtr( puiCount , sizeof(LPUINT) ) )
  {
    SetLastError( ERROR_INVALID_PARAMETER );
    return 0;
  }

  ASSERT( NULL != hHeap ) ;
  if ( NULL == hHeap )
  {
    SetLastError( ERROR_INVALID_PARAMETER );
    return 0;
  }

  // First, ask how many modules are really loaded.
  UINT uiQueryCount;

  BOOL bRet = GetLoadedModules ( GetCurrentProcessId(), 0, 0, &uiQueryCount );
  ASSERT( TRUE == bRet );
  ASSERT( 0 != uiQueryCount );

  if ( (FALSE == bRet) || (0 == uiQueryCount) )
		return 0;

  // The HMODULE array.
  // Allocate the buffer to hold the returned array.
  HMODULE* pModArray = (HMODULE*)HeapAlloc( hHeap, HEAP_ZERO_MEMORY, uiQueryCount*sizeof(HMODULE) );
  ASSERT( NULL != pModArray );
  if ( NULL == pModArray )
		return 0;

  // bRet holds BOOLEAN return values.
  bRet = GetLoadedModules( GetCurrentProcessId(), uiQueryCount, pModArray, puiCount );
  // Save off the last error so that the assert can still fire and
  //  not change the value.
  DWORD dwLastError = GetLastError();
  ASSERT( TRUE == bRet );

  if ( FALSE == bRet )
  {
    // Get rid of the last buffer.
    free ( pModArray );
    pModArray = 0;
    SetLastError( dwLastError );
  }
  else
    SetLastError( ERROR_SUCCESS );
  // All OK, Jumpmaster!
  return pModArray;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
