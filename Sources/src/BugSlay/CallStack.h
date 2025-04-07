#ifndef __CALLSTACK_H__
#define __CALLSTACK_H__
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "BugSlayer.h"

#include <string>
#include <list>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SCallStackEntry
{
	std::string szModuleName;             // module name
	std::string szFileName;               // source file name
	int nLineNumber;                      // source file line number
	DWORD dwLineDisp;                     // line displacement
	std::string szFunctionName;           // function name
	DWORD dwFunctionDisp;                 // function displacement
	DWORD params[4];                      // possible function params
};
typedef std::list<SCallStackEntry> CCallStackEntryList;
// ignores
const DWORD IGNORE_THIS     = 0x00000001;
const DWORD IGNORE_NON_THIS = 0x00000002;
const DWORD IGNORE_FILE     = 0x00000004;
const DWORD IGNORE_NON_FILE = 0x00000008;
const DWORD IGNORE_ALL      = 0x00000010;
const DWORD IGNORE_LOG      = 0x00000020;
struct SIgnoresEntry
{
	std::string szCondition;
	std::string szFunctionName;
	std::string szFileName;
	int nLineNumber;
	DWORD dwFlags;
	//
	bool operator==( const SIgnoresEntry &ig ) const
	{
		return ( ( szCondition == ig.szCondition ) && 
			       ( szFileName == ig.szFileName   ) && 
						 ( nLineNumber == ig.nLineNumber ) && 
						 ( dwFlags == ig.dwFlags         ) );
	}
};
typedef std::list<SIgnoresEntry> SIgnoresList;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NBugSlayer
{
	bool IsIgnore( const char *pszFileName, int nLineNumber );
	void AddIgnore( const char *pszFunctionName, const char *pszFileName, int nLineNumber, const char *pszCondition, DWORD dwFlag );
	void RemoveIgnore( SIgnoresEntry *pEntry );
	//
	void SetModuleHandle( HINSTANCE hInstance );
	HINSTANCE GetModuleHandle();
	// emergency commands
	void STDCALL ExecuteEmergencyCommands();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool STDCALL GetFirstStackTrace( EXCEPTION_POINTERS *pExPtrs, SCallStackEntry &entry );
bool STDCALL GetNextStackTrace( EXCEPTION_POINTERS *pExPtrs, SCallStackEntry &entry );
LPCTSTR ConvertSimpleException( DWORD dwExcept );
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EBSUReport __cdecl ShowAssertionDlg( HINSTANCE hInstance, HWND hWnd,
																		 const char *pszFileName, int nLineNumber,
                                     const char *pszCondition, const char *pszDescription, 
                                     CCallStackEntryList &entries, SIgnoresList &ignores,
																		 const char *pszExtInfo );
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EBSUReport __cdecl ShowExceptionDlg( HINSTANCE hInstance, HWND hWnd,
                                     const char *pszCondition, const char *pszDescription, 
                                     CCallStackEntryList &entries, const char *pszExtInfo );
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __CALLSTACK_H__
