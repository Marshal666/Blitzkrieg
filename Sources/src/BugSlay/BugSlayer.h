#ifndef __BUGSLAYER_H__
#define __BUGSLAYER_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <imagehlp.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// dialog notification function retcodes
enum EBSUReport
{
	BSU_ABORT,
	BSU_DEBUG,
	BSU_IGNORE,
	BSU_CONTINUE,
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NBugSlayer
{
	// assert dialog notification function
	EBSUReport STDCALL ReportAssert( const char *pszCondition, const char *pszDescription,
																	 const char *pszFileName, int nLineNumber, bool bForceMode );
	EBSUReport STDCALL ReportAssertHR( HRESULT result, const char *pszDescription,
																		 const char *pszFileName, int nLineNumber, bool bForceMode );
	// memory tracking system
	void STDCALL MemSystemRegister( size_t nSize, void *ptr );
	void STDCALL MemSystemFree( void *ptr );
	void STDCALL MemSystemAddIgnoredPath( const char *pszPath );
	void STDCALL MemSystemDumpStats();
	//
	void* __cdecl FastDumbAlloc( int _nSize );
	bool __cdecl FastDumbFree( void *pData );
	// emergency commands
	void STDCALL AddEmergencyCommand( interface IBaseCommand *pCommand );
	void STDCALL RemoveAllEmergencyCommands();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   For the specified process id, this function returns the HMODULES for all modules loaded into
// that process address space.  This function works for both NT and 95.
BOOL STDCALL GetLoadedModules( DWORD dwPID, UINT uiCount, HMODULE *paModArray, LPUINT puiRealCount );

//   Returns the base name of the specified module in a manner that is portable between
// NT and Win95/98.
DWORD STDCALL BSUGetModuleBaseName( HANDLE hProcess, HMODULE hModule, LPTSTR lpBaseName, DWORD nSize );
//   Returns TRUE if the operating system is NT.  I simply got tired of always having to call
// GetVersionEx each time I needed to check. Additionally, I also need to check the OS inside
// loops so this function caches the results so it is faster.
BOOL STDCALL IsNT();

// The type for the filter function called by the Crash Handler API.
typedef LONG (STDCALL *PFNCHFILTFN)( EXCEPTION_POINTERS *pExPtrs );
//  Sets the filter function that will be called when there is a fatal crash.  The passed in function
// will only be called if the crash is one of the modules passed to AddCrashHandlerLimitModule.  If no
// modules have been added to narrow down the interested modules then the callback filter function
// will always be called.
BOOL STDCALL SetCrashHandlerFilter( PFNCHFILTFN pFn );
LONG STDCALL CrashHandlerFilter( EXCEPTION_POINTERS *pExPtrs );

//  Adds a module to the list of modules that CrashHandler will call the callbeack function for.
// If no modules are added, then the callback is called for all crashes.  Limiting the specific modules
// allows the crash handler to be installed for just the modules you are responsible for.
BOOL STDCALL AddCrashHandlerLimitModule( HMODULE hMod );

//  Returns the number of limit modules for the crash handler.
UINT STDCALL GetLimitModuleCount();

//  Returns the limit modules currently active.
enum
{
	GLMA_SUCCESS      =  1,
	GLMA_BADPARAM     = -1,
	GLMA_BUFFTOOSMALL = -2,
	GLMA_FAILURE      =  0
};
int STDCALL GetLimitModulesArray( HMODULE *pahMod, UINT uiSize );

//  Returns a string that describes the fault that occured.  The return string looks similar to the
// string returned by Win95's fault dialog. The returned buffer is constant and do not change it.
//  This function can only be called from the callback.
LPCTSTR STDCALL GetFaultReason( EXCEPTION_POINTERS *pExPtrs );

//  These functions allow you to get the stack trace information for a crash.
// Call GetFirstStackTraceString and then GetNextStackTraceString to get the entire stack trace for a crash.
enum
{
	GSTSO_PARAMS  = 0x01,
	GSTSO_MODULE  = 0x02,
	GSTSO_SYMBOL  = 0x04,
	GSTSO_SRCLINE = 0x08
};
LPCTSTR STDCALL GetFirstStackTraceString( DWORD dwOpts, EXCEPTION_POINTERS *pExPtrs );
LPCTSTR STDCALL GetNextStackTraceString( DWORD dwOpts, EXCEPTION_POINTERS *pExPtrs );

//  Returns a string with all the registers and their values.  This function hides all the platform differences.
LPCTSTR STDCALL GetRegisterString( EXCEPTION_POINTERS *pExPtrs );

// get source filename and line number at the requested depth
bool STDCALL GetSourceLine( DWORD pointer, const char* &pszFileName, int &nLineNumber );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// STLport debug message system
#if defined( __STL_DEBUG_MESSAGE )
extern void __stl_debug_message( const char *pszFormat, ... );
#endif //  defined( __STL_DEBUG_MESSAGE )
#if defined( __STL_DEBUG_TERMINATE )
extern void __stl_debug_terminate();
#endif // defined( __STL_DEBUG_TERMINATE )
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEBUG_BREAK { _asm { int 3 } }
// macros for retrieving 5 callstack addresses for further use with 'GetSourceLine()' function
// here we are using macro due to we need an 'clear' callstack, which is not corrupted by 'inline' function call
#define GET_CALLSTACK_ADDRS( addresses, depth )							\
{																														\
	if ( IsBadWritePtr(addresses, depth*sizeof(DWORD)) == 0 )	\
	{																													\
		int *pBuf;																							\
		_asm { mov pBuf, ebp }																	\
		memset( addresses, 0, depth*sizeof(DWORD) );						\
		for ( int i=0; i<depth; ++i )														\
		{																												\
			if ( IsBadReadPtr( pBuf, 8 ) )												\
				break;																							\
			addresses[i] = pBuf[1];																\
			pBuf = (int*)pBuf[0];																	\
		}																												\
	}																													\
	else																											\
		DEBUG_BREAK;																						\
}
// ASSERT macros.
// For showing calling stack when errors occur in major functions.
// Meant to be enabled in release builds.
#if defined( _DO_ASSERT ) || defined( _DO_ASSERT_SLOW )
#define NI_ASSERT_TF( x, user_text, statement )    NI_FORCE_ASSERT( x, user_text, statement, false )
#define NI_ASSERT_T( x, user_text )                NI_FORCE_ASSERT( x, user_text,         ;, false )
#define NI_ASSERT( x )                             NI_FORCE_ASSERT( x,        "",         ;, false )
#define NI_ASSERTHR_TF( x, user_text, statement )  NI_FORCE_ASSERT_HR( x, user_text, statement, false )
#define NI_ASSERTHR_T( x, user_text )              NI_FORCE_ASSERT_HR( x, user_text,         ;, false )
#define NI_ASSERTHR( x )                           NI_FORCE_ASSERT_HR( x,        "",         ;, false )
#else
#define NI_ASSERT_TF( x, user_text, statement )    {  }
#define NI_ASSERT_T( x, user_text )                {  }
#define NI_ASSERT( x )                             {  }
#define NI_ASSERTHR_TF( x, user_text, statement )  {  }
#define NI_ASSERTHR_T( x, user_text )              {  }
#define NI_ASSERTHR( x )                           {  }
#endif // defined( _DO_ASSERT ) || defined( _DO_ASSERT_SLOW )
// ASSERT_SLOW macros.
// For showing calling stack when errors occur in performance-critical functions.
// Meant to be disabled in release builds.
#if defined( _DO_ASSERT_SLOW )
#define NI_ASSERT_SLOW_TF( x, user_text, statement )    NI_FORCE_ASSERT( x, user_text, statement, false )
#define NI_ASSERT_SLOW_T( x, user_text )                NI_FORCE_ASSERT( x, user_text,         ;, false )
#define NI_ASSERT_SLOW( x )                             NI_FORCE_ASSERT( x,        "",         ;, false )
#define NI_ASSERTHR_SLOW_TF( x, user_text, statement )  NI_FORCE_ASSERT_HR( x, user_text, statement, false )
#define NI_ASSERTHR_SLOW_T( x, user_text )              NI_FORCE_ASSERT_HR( x, user_text,         ;, false )
#define NI_ASSERTHR_SLOW( x )                           NI_FORCE_ASSERT_HR( x,        "",         ;, false )
#else
#define NI_ASSERT_SLOW_TF( x, user_text, statement )    {  }
#define NI_ASSERT_SLOW_T( x, user_text )                {  }
#define NI_ASSERT_SLOW( x )                             {  }
#define NI_ASSERTHR_SLOW_TF( x, user_text, statement )  {  }
#define NI_ASSERTHR_SLOW_T( x, user_text )              {  }
#define NI_ASSERTHR_SLOW( x )                           {  }
#endif // defined( _DO_ASSERT_SLOW )
//
// main ASSERT macros
//
#if defined( _DO_ASSERT ) || defined( _DO_ASSERT_SLOW )
#define NI_FORCE_ASSERT( x, user_text, statement, bForce )                        \
if ( static_cast<DWORD>(x) == 0 )                                                 \
{                                                                                 \
  switch( NBugSlayer::ReportAssert( #x, user_text, __FILE__, __LINE__, bForce ) ) \
  {                                                                               \
  case BSU_CONTINUE:                                                              \
    { statement; }                                                                \
    break;                                                                        \
  case BSU_DEBUG:                                                                 \
    DEBUG_BREAK;                                                                  \
    break;                                                                        \
	case BSU_IGNORE:                                                                \
	  break;                                                                        \
	case BSU_ABORT:                                                                 \
		SetCrashHandlerFilter( 0 );																										\
	  _exit( 0xDEAD );                                                              \
		break;																																				\
  }                                                                               \
}
#define NI_FORCE_ASSERT_HR( x, user_text, statement, bForce )                     \
if ( (static_cast<DWORD>(x) & 0x80000000) != 0 )                                  \
{                                                                                 \
  switch( NBugSlayer::ReportAssertHR( x, user_text, __FILE__, __LINE__, bForce ) )\
	{                                                                               \
  case BSU_CONTINUE:                                                              \
		{ statement; }                                                                \
    break;                                                                        \
  case BSU_DEBUG:                                                                 \
    DEBUG_BREAK;                                                                  \
    break;                                                                        \
	case BSU_IGNORE:                                                                \
	  break;                                                                        \
	case BSU_ABORT:                                                                 \
		SetCrashHandlerFilter( 0 );																										\
	  _exit( 0xDEAD );                                                              \
		break;																																				\
	}                                                                               \
}
#else
#define NI_FORCE_ASSERT( x, user_text, statement, bForce )    {  }
#define NI_FORCE_ASSERT_HR( x, user_text, statement, bForce ) {  }
#endif // defined( _DO_ASSERT ) || defined( _DO_ASSERT_SLOW )
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __BUGSLAYER_H__
