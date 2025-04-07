#include "StdAfx.h"

#include "FileUtils.h"

#include <stdlib.h>
#include <direct.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NFile
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** class CFile functions
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CFile::Open( const char *pszFileName, DWORD dwOpenFlags )
{
	// map access flags
	DWORD dwAccess = 0;
	switch ( dwOpenFlags & 3 )
	{
		case modeRead:
			dwAccess = GENERIC_READ;
			break;
		case modeWrite:
			dwAccess = GENERIC_WRITE;
			break;
		case modeReadWrite:
			dwAccess = GENERIC_READ | GENERIC_WRITE;
			break;
		default:
			return false;
	}
	// map share mode
	DWORD dwShareMode = 0;
	switch ( dwOpenFlags & 0x70 )
	{
		case shareCompat:										// map compatibility mode to exclusive
		case shareExclusive:
			dwShareMode = 0;
			break;
		case shareDenyWrite:
			dwShareMode = FILE_SHARE_READ;
			break;
		case shareDenyRead:
			dwShareMode = FILE_SHARE_WRITE;
			break;
		case shareDenyNone:
			dwShareMode = FILE_SHARE_WRITE | FILE_SHARE_READ;
			break;
		default:
			return false;
	}
	// map creation flags
	DWORD dwCreateFlag = 0;
	if ( dwOpenFlags & modeCreate )
	{
		if ( dwOpenFlags & modeNoTruncate )
			dwCreateFlag = OPEN_ALWAYS;
		else
			dwCreateFlag = CREATE_ALWAYS;
	}
	else
		dwCreateFlag = OPEN_EXISTING;
	// map modeNoInherit flag
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof( sa );
	sa.lpSecurityDescriptor = 0;
	sa.bInheritHandle = ( dwOpenFlags & modeNoInherit ) == 0;
	// extract full file path
	const std::string szFullFilePath = GetFullName( pszFileName );
	// attempt file creation
	hFile = ::CreateFile( szFullFilePath.c_str(), dwAccess, dwShareMode, &sa, dwCreateFlag, FILE_ATTRIBUTE_NORMAL, 0 );
	if (hFile == INVALID_HANDLE_VALUE)
		return false;
	szFilePath = szFullFilePath;
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CFile* CFile::Duplicate() const
{
	if ( !IsOpen() ) 
		return 0;

	HANDLE hNewFile;
	if ( !::DuplicateHandle( ::GetCurrentProcess(), hFile, ::GetCurrentProcess(), 
		                       &hNewFile, 0, FALSE, DUPLICATE_SAME_ACCESS) )
	{
		return 0;
	}
	CFile* pFile = new CFile();
	pFile->hFile = hNewFile;
	pFile->szFilePath = szFilePath;
	return pFile;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CFile::Close()
{
	if ( IsOpen() ) 
		::CloseHandle( hFile );
	hFile = INVALID_HANDLE_VALUE;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CFile::Flush()
{
	return IsOpen() ? ::FlushFileBuffers( hFile ) != 0 : false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CFile::Read( void *pBuf, int nCount)
{
	if ( !IsOpen() || (nCount <= 0) ) 
		return 0;
	//
	DWORD dwRead = 0;
	if ( !::ReadFile(hFile, pBuf, nCount, &dwRead, NULL) )
		return 0;
	return int( dwRead );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CFile::Write( const void *pBuf, int nCount )
{
	if ( !IsOpen() || (nCount <= 0) ) 
		return 0;
	//
	DWORD dwWritten = 0;
	if ( !::WriteFile(hFile, pBuf, nCount, &dwWritten, NULL) )
		return 0;
	return int( dwWritten );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CFile::Seek( int nOffset, ESeekPosition eFrom )
{
	return IsOpen() ? ::SetFilePointer( hFile, nOffset, 0, (DWORD)eFrom ) : -1;
}
int CFile::GetPosition() const
{
	return IsOpen() ? ::SetFilePointer( hFile, 0, 0, FILE_CURRENT ) : -1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CFile::SetLength( int nLength )
{
	if ( IsOpen() ) 
		return -1;
	if ( Seek(nLength, begin) != -1 ) 
	{
		if ( ::SetEndOfFile(hFile) )
			return nLength;
	}
	return -1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CFile::GetLength() const
{
	SStatus status;
	if ( GetStatus(&status) )
		return status.nSize;
	else
		return -1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CFile::GetStatus( SStatus *pStatus ) const 
{
	if ( !IsOpen() || szFilePath.size() > _MAX_PATH ) 
		return false;
	BY_HANDLE_FILE_INFORMATION info;
	if ( !::GetFileInformationByHandle(hFile, &info) )
		return false;
	pStatus->ctime = info.ftCreationTime;
	pStatus->mtime = info.ftLastWriteTime;
	pStatus->atime = info.ftLastAccessTime;
	pStatus->nSize = info.nFileSizeLow;
	pStatus->szPathName = szFilePath;
	pStatus->dwAttributes = info.dwFileAttributes;
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DWORD CFile::GetAttributes( const char *pszFileName )
{
	return ::GetFileAttributes( pszFileName );
}
bool CFile::SetAttributes( const char *pszFileName, DWORD dwAttributes )
{
	return ::SetFileAttributes( pszFileName, dwAttributes ) != 0;
}
bool CFile::Rename( const char *pszOldName, const char *pszNewName )
{
	return ::MoveFile( pszOldName, pszNewName ) != 0;
}
bool CFile::Remove( const char *pszFileName )
{
	return ::DeleteFile( pszFileName ) != 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const std::string& CFile::GetFilePath() const { return szFilePath; }
const std::string CFile::GetFileName() const
{
	return szFilePath.substr( szFilePath.rfind('\\') + 1 );
}
const std::string CFile::GetFileTitle() const
{
	const int nNamePos = szFilePath.rfind( '\\' );
	const int nExtPos = szFilePath.rfind( '.' );
	if ( (nNamePos != std::string::npos) && (nExtPos != std::string::npos) && (nExtPos > nNamePos) ) 
		return szFilePath.substr( nNamePos + 1, nExtPos - nNamePos );
	return "";
}
const std::string CFile::GetFileExt() const
{
	const int nPos = szFilePath.rfind( '.' );
	return nPos != std::string::npos ? szFilePath.substr( nPos + 1 ) : "";
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** class CFileIterator functions
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CFileIterator& CFileIterator::FindFirstFile( const char *pszMask )
{
	szPath = pszMask;
	int pos = szPath.rfind( '\\' );
	if ( pos == std::string::npos )
	{
		szMask = pszMask;
		szPath.clear();
	}
	else
	{
		szMask = szPath.substr( pos + 1 );
		szPath = szPath.substr( 0, pos );
	}
	//
	if ( szPath[szPath.size() - 1] != '\\' ) 
		szPath += "\\";
	// create absolute path from the relative one
	szPath = GetFullName( szPath );
	//
	if ( szPath[szPath.size() - 1] != '\\' ) 
		szPath += "\\";
	//
	hFind = ::FindFirstFile( pszMask, &findinfo );
	return *this;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CFileIterator& CFileIterator::Next()
{
	if ( !IsValid() )
		return *this;
	if ( ::FindNextFile(hFind, &findinfo) == 0 )
		Close();
	return *this;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CFileIterator::Close() 
{ 
	if ( IsValid() ) 
	{
		const bool bRet = ::FindClose( hFind ) != 0; 
		hFind = INVALID_HANDLE_VALUE;
		return bRet;
	}
	return true; 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const std::string CFileIterator::GetFileTitle() const
{
	std::string szTitle = findinfo.cFileName;
	return szTitle.substr( 0, szTitle.rfind( '.' ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const std::string CFileIterator::GetFileExt() const
{
	std::string szExt = findinfo.cFileName;
	int pos = szExt.rfind( '.' );
	if ( pos == std::string::npos )
		return "";
	return szExt.substr( pos + 1 );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
//                                         external file utilites
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CDeleteFiles
{
	bool bDeleteRO;
	bool bDeleteDir;
public:
	CDeleteFiles( bool _bDeleteRO, bool _bDeleteDir ) : bDeleteRO( _bDeleteRO ), bDeleteDir( _bDeleteDir ) {  }
	//
	void operator()( const CFileIterator &it )
	{
		if ( !it.IsDirectory() )
		{
			if ( bDeleteRO && it.IsReadOnly() )
				SetFileAttributes( it.GetFilePath().c_str(), it.GetAttribs() & ~NFile::CFile::readOnly );
			DeleteFile( it.GetFilePath().c_str() );
		}
		else if ( bDeleteDir )
		{
			if ( bDeleteRO && it.IsReadOnly() )
				SetFileAttributes( it.GetFilePath().c_str(), it.GetAttribs() & ~NFile::CFile::readOnly );
			RemoveDirectory( it.GetFilePath().c_str() );
		}
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DeleteFiles( const char *pszStartDir, const char *pszMask, bool bRecursive )
{
	EnumerateFiles( pszStartDir, pszMask, CDeleteFiles(true, false), bRecursive );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DeleteDirectory( const char *pszDir )
{
	EnumerateFiles( pszDir, "*.*", CDeleteFiles(true, true), true );
	RemoveDirectory( pszDir );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CDirFileEnum
{
	std::list<std::string> *pNames;				// store names here
	bool bDir;														// enumerate dirs
	bool bFile;														// enumerate files
public:
	CDirFileEnum( std::list<std::string> *_pNames, bool _bDir, bool _bFile ) 
		: pNames( _pNames ), bDir( _bDir ), bFile( _bFile ) {  }
	void operator()( const CFileIterator &it )
	{
		if ( it.IsDirectory() )
		{
			if ( bDir )
				pNames->push_back( it.GetFilePath() );
		}
		else if ( bFile )
			pNames->push_back( it.GetFilePath() );
	}
};
void GetDirNames( const char *pszDirName, std::list<std::string> *pNames, bool bRecursive )
{
	EnumerateFiles( pszDirName, "*.*", CDirFileEnum(pNames, true, false), bRecursive );
}
void GetFileNames( const char *pszDirName, const char *pszMask, std::list<std::string> *pNames, bool bRecurse )
{
	EnumerateFiles( pszDirName, pszMask, CDirFileEnum(pNames, false, true), bRecurse );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void CreatePath( const char *pszFullPath )
{	
	std::vector<std::string> szNames;
	NStr::SplitString( pszFullPath, szNames, '\\' );
	if ( szNames.empty() )
		return;
	// remember current directory
	char pszBuffer[1024];
	GetCurrentDirectory( 1024, pszBuffer );
	// create new directory sequence
	SetCurrentDirectory( (szNames.front() + "\\").c_str() );
	for ( std::vector<std::string>::const_iterator it = szNames.begin() + 1; it != szNames.end(); ++it )
	{
		CreateDirectory( it->c_str(), 0 );
		SetCurrentDirectory( ((*it) + "\\").c_str() );
	}
	// restore old current directory
	SetCurrentDirectory( pszBuffer );
}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// return number of bytes, free for the caller on the selected drive
double GetFreeDiskSpace( const char *pszDrive )
{
	typedef BOOL (WINAPI *GDFSE)( LPCTSTR, PULARGE_INTEGER, PULARGE_INTEGER, PULARGE_INTEGER );

	GDFSE pfnGetDiskFreeSpaceEx = (GDFSE)GetProcAddress( GetModuleHandle("kernel32.dll"), "GetDiskFreeSpaceExA" );
	bool bRetVal = false;
	double fRetVal = 0;
	if ( pfnGetDiskFreeSpaceEx )
	{
	 ULARGE_INTEGER i64FreeBytesToCaller, i64TotalBytes, i64FreeBytes;
	 bRetVal = (*pfnGetDiskFreeSpaceEx)( pszDrive, &i64FreeBytesToCaller,
																	     &i64TotalBytes, &i64FreeBytes );
	 fRetVal = double( __int64(i64FreeBytesToCaller.QuadPart) );
	} 
	else 
	{
		DWORD dwSectPerClust, dwBytesPerSect, dwFreeClusters, dwTotalClusters;
		bRetVal = GetDiskFreeSpace( pszDrive, &dwSectPerClust, &dwBytesPerSect,
																&dwFreeClusters, &dwTotalClusters );
		fRetVal = double( dwFreeClusters ) * double( dwSectPerClust ) * double( dwBytesPerSect );
	}

	return ( bRetVal == 0 ? 0 : fRetVal );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IsFileExist( const char *pszFileName )
{
	return _access( pszFileName, 0 ) != -1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string GetFullName( const std::string &szPath )
{
	const DWORD BUFFER_SIZE = 1024;
	char buffer[BUFFER_SIZE];
	char *pszBufferFileName = 0;
	GetFullPathName( szPath.c_str(), 1024, buffer, &pszBufferFileName );
	return buffer;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // namespace NFile ends
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
