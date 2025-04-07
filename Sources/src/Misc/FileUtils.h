#ifndef __FILE_UTILS_H__
#define __FILE_UTILS_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <io.h>
#include <string>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NFile
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** Win32 file wrapper
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CFile
{
	HANDLE hFile;
	std::string szFilePath;
public:
	struct SStatus
	{
		FILETIME ctime;											// creation date/time of file
		FILETIME mtime;											// last modification date/time of file
		FILETIME atime;											// last access date/time of file
		int nSize;													// logical size of file in bytes
		DWORD dwAttributes;									// logical OR of CFile::Attribute enum values
		std::string szPathName;							// absolute path name
	};
	//
	enum EOpenFlags 
	{
		modeRead				= 0x0000,
		modeWrite				= 0x0001,
		modeReadWrite		= 0x0002,
		shareCompat			=	0x0000,
		shareExclusive	= 0x0010,
		shareDenyWrite	= 0x0020,
		shareDenyRead		= 0x0030,
		shareDenyNone		= 0x0040,
		modeNoInherit		= 0x0080,
		modeCreate			= 0x1000,
		modeNoTruncate	= 0x2000
	};
	//
	enum EAttribute 
	{
		readOnly							= 0x00000001,
		hidden								= 0x00000002,
		system								= 0x00000004,
		directory							= 0x00000010,
		archive								= 0x00000020,
		encrypted							= 0x00000040,
		normal								= 0x00000080,
		temporary							= 0x00000100,
		sparse_file						= 0x00000200,
		reparse_point					= 0x00000400,
		compressed						= 0x00000800,
		offline								= 0x00001000,
		not_content_indexed		= 0x00002000
	};
	//
	enum ESeekPosition { begin = 0x0, current = 0x1, end = 0x2 };
public:
	CFile() : hFile( INVALID_HANDLE_VALUE ) {  }
	CFile( const char *pszFileName, DWORD dwOpenFlags ) { Open( pszFileName, dwOpenFlags ); }
	virtual ~CFile() { Close(); }
	// open/duplicate/close/flush
	bool Open( const char *pszFileName, DWORD dwOpenFlags );
	CFile* Duplicate() const;
	void Close();
	bool Flush();
	bool IsOpen() const { return hFile != INVALID_HANDLE_VALUE; }
	// read/write/seek/position
	int Read( void *pBuf, int nCount );
	int Write( const void *pBuf, int nCount );
	int Seek( int nOffset, ESeekPosition eFrom );
	int GetPosition() const;
	// length
	int SetLength( int nNewLen );
	int GetLength() const;
	// status & attributes
	bool GetStatus( SStatus *pStatus ) const;
	DWORD GetAttributes() const;
	bool SetAttributes( DWORD dwAttributes );
	bool SetFileTime( const FILETIME *pCreationTime, const FILETIME *pLastAccessTime, const FILETIME *pLastWriteTime );
	//
	operator HANDLE() const { return hFile; }
	//
	const std::string& GetFilePath() const;	// complete path name (ZB. c:\program files\name.txt)
	const std::string GetFileName() const;	// title + ext (ZB. name.txt)
	const std::string GetFileTitle() const;	// title onle (ZB. name)
	const std::string GetFileExt() const;		// extension onle (ZB. txt)
	// statics
	static bool Rename( const char *pszOldName, const char *pszNewName );
	static bool Remove( const char *pszFileName );
	static DWORD GetAttributes( const char *pszFileName );
	static bool SetAttributes( const char *pszFileName, DWORD dwAttributes );
	static bool SetFileTime( const char *pszFileName, const FILETIME *pCreationTime, const FILETIME *pLastAccessTime, const FILETIME *pLastWriteTime );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** file iterator
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CFileIterator
{
	HANDLE hFind;													// find file handle of the last search result
	WIN32_FIND_DATA findinfo;							// last search info
	std::string szPath;                   // path to the file
	std::string szMask;
	bool IsValid() const { return hFind != INVALID_HANDLE_VALUE; }
public:
	CFileIterator() : hFind( INVALID_HANDLE_VALUE ) {  }
	CFileIterator( const char *pszMask ) { FindFirstFile(pszMask); }
	~CFileIterator() { Close(); }
	// file enumeration
	const CFileIterator& FindFirstFile( const char *pszMask );
	const CFileIterator& Next();
	bool Close();
	bool IsEnd() const { return !IsValid(); }
	const CFileIterator& operator++() { return Next(); }
	// current file attributes check
	DWORD GetAttribs() const { return findinfo.dwFileAttributes; }
	bool IsReadOnly() const { return ( GetAttribs() & NFile::CFile::readOnly ) != 0; }
	bool IsSystem() const { return ( GetAttribs() & NFile::CFile::system ) != 0; }
	bool IsHidden() const { return ( GetAttribs() & NFile::CFile::hidden ) != 0; }
	bool IsTemporary() const { return ( GetAttribs() & NFile::CFile::temporary ) != 0; }
	bool IsNormal() const { return ( GetAttribs() & NFile::CFile::normal ) != 0; }
	bool IsArchive() const { return ( GetAttribs() & NFile::CFile::archive ) != 0; }
	bool IsCompressed() const { return ( GetAttribs() & NFile::CFile::compressed ) != 0; }
	bool IsDirectory() const { return ( GetAttribs() & NFile::CFile::directory ) != 0; }
	// special kind of directory: '.' - this dir and '..' - parent dir
	bool IsDots() const
	{
		return ( ( findinfo.cFileName[0] == '.' ) && 
			       ( (findinfo.cFileName[1] == '\0') || 
						   ((findinfo.cFileName[1] == '.') && (findinfo.cFileName[2] == '\0')) ) );
	}
	// composed attributes check
	bool IsMatchesMask( DWORD dwMask ) const { return (GetAttribs() & dwMask) == dwMask; }
	// file time attributes
	FILETIME GetCreationTime() const { return findinfo.ftCreationTime; }
	FILETIME GetLastAccessTime() const { return findinfo.ftLastAccessTime; }
	FILETIME GetLastWriteTime() const { return findinfo.ftLastWriteTime; }
	// file length
	int GetLength() const { return findinfo.nFileSizeLow; }
	// file name (title + ext), full path (absolute path + name), title and extension (w/o '.')
	const std::string GetFileName() const { return findinfo.cFileName; }
	const std::string GetFilePath() const { return szPath + findinfo.cFileName; }
	const std::string GetFileTitle() const;
	const std::string GetFileExt() const;
	const std::string& GetBasePath() const { return szPath; }
	const std::string& GetBaseMask() const { return szMask; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// enumerate all files by mask.
// ��� ����������� ���������� ������� ������ � ����������, � ����� ������ �������� � ��� (��� ������ �� ��������)
template <class TEnumFunc>
void EnumerateFiles( const char *pszStartDir, const char *pszMask, TEnumFunc callback, bool bRecurse )
{
	std::string szDir = pszStartDir;
	// iterate throug all files by mask
	for ( CFileIterator it( (szDir + pszMask).c_str() ); !it.IsEnd(); ++it )
	{
		if ( !it.IsDirectory() )
			callback( it );
	}
	// iterate throug all dirs by "*.*"
	for ( CFileIterator it( (szDir + "*.*").c_str() ); !it.IsEnd(); ++it )
	{
		if ( it.IsDirectory() )
		{
			// skip 'dots'
			if ( it.IsDots() )
				continue;
			// dive into recurse
			if ( bRecurse )
				EnumerateFiles( (it.GetFilePath() +  "\\").c_str(), pszMask, callback, bRecurse );
			//
			callback( it );
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������� ��� EnumerateFiles, ����������� ��� ����� � ����������
class CGetAllFiles
{
	std::vector<std::string> *pFileVector;
public:
	CGetAllFiles( std::vector<std::string> *pFiles ) : pFileVector( pFiles ) {  }
	//
	void operator() ( const NFile::CFileIterator &it )
	{
		if ( !it.IsDirectory() )
		{
			pFileVector->push_back( it.GetFilePath() );
		}
	}
};
// ������� ��� EnumerateFiles, ����������� ��� ����� � ���������� � ���� �� ������������� ���
class CGetAllFilesRelative
{
	std::vector<std::string> *pFileVector;
	std::string szInitDir;
public:
	CGetAllFilesRelative( const char *pszDir, std::vector<std::string> *pFiles ) : szInitDir( pszDir ), pFileVector( pFiles ) {  }
	//
	void operator() ( const NFile::CFileIterator &it )
	{
		if ( !it.IsDirectory() )
		{
			std::string szName = it.GetFilePath();
			NI_ASSERT_T( szName.size() > szInitDir.size(), "Wrong name size" );
			szName = szName.substr( szInitDir.size() );
			pFileVector->push_back( szName );
		}
	}
};
// ������� ��� EnumerateFiles, ����������� ��� ������������� � ���������� � ���� �� ������������� ���
class CGetAllDirectoriesRelative
{
	std::vector<std::string> *pFileVector;
	std::string szInitDir;
public:
	CGetAllDirectoriesRelative( const char *pszInitDir, std::vector<std::string> *pFiles ) : szInitDir( pszInitDir ), pFileVector( pFiles ) {  }
	//
	void operator() ( const NFile::CFileIterator &it )
	{
		if ( !it.IsDirectory() )
		{
			std::string szFileName = it.GetFilePath();
			szFileName = szFileName.substr( szInitDir.size() );							//�������� ��������� ����������
			int nRes = szFileName.rfind( '\\' );
			if ( nRes == std::string::npos )
				return;
			szFileName = szFileName.substr( 0, nRes );	//�������� ��� �����, �������� ������ ����������
			if ( szFileName.size() == 0 )
				return;
			
			for ( int i=0; i<pFileVector->size(); i++ )
			{
				if ( (*pFileVector)[i] == szFileName )
					return;
			}
			
			pFileVector->push_back( szFileName );
		}
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DeleteFiles( const char *pszStartDir, const char *pszMask, bool bRecursive );
void DeleteDirectory( const char *pszDir );
void CreatePath( const char *pszFullPath );
void GetDirNames( const char *pszDirName, std::list<std::string> *pNames, bool bRecursive = true );
void GetFileNames( const char *pszDirName, const char *pszMask, std::list<std::string> *pNames, bool bRecurse = true );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IsFileExist( const char *pszFileName );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string GetFullName( const std::string &szPath );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// return number of bytes, free for the caller on the selected drive
double GetFreeDiskSpace( const char *pszDrive );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // namespace NFile ends
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** CFile helper operators (<< and >> streaming)
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// general template
template <class TYPE>
	inline NFile::CFile& operator<<( NFile::CFile &file, const TYPE &data )
	{
		file.Write( &data, sizeof(data) );
		return file;
	}
template <class TYPE>
	inline NFile::CFile& operator>>( NFile::CFile &file, TYPE &data )
	{
		file.Read( &data, sizeof(data) );
		return file;
	}
// string specialization
template <>
	inline NFile::CFile& operator<<( NFile::CFile &file, const std::string &data )
	{
		int nLength = data.size();
		file << nLength;
		file.Write( data.c_str(), nLength * sizeof(data[0]) );
		return file;
	}
template <>
	inline NFile::CFile& operator>>( NFile::CFile &file, std::string &data )
	{
		int nLength = 0;
		file >> nLength;
		data.resize( nLength );
		file.Read( &(data[0]), nLength * sizeof(data[0]) );
		return file;
	}
template <>
	inline NFile::CFile& operator<<( NFile::CFile &file, const std::wstring &data )
	{
		int nLength = data.size();
		file << nLength;
		file.Write( data.c_str(), nLength * sizeof(data[0]) );
		return file;
	}
template <>
	inline NFile::CFile& operator>>( NFile::CFile &file, std::wstring &data )
	{
		int nLength = 0;
		file >> nLength;
		data.resize( nLength );
		file.Read( &(data[0]), nLength * sizeof(data[0]) );
		return file;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __FILE_UTILS_H__
