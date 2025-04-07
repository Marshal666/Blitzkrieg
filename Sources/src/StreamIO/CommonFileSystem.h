#ifndef __COMMONFILESYSTEM_H__
#define __COMMONFILESYSTEM_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SCommonFileInfo
{
	DWORD dwModTime;										// file modification time
	IDataStorage *pStorage;							// storage, this file stored in
	//
	SCommonFileInfo() : dwModTime( 0 ), pStorage( 0 ) {  }
	SCommonFileInfo( DWORD _dwModTime, IDataStorage *_pStorage ) : dwModTime( _dwModTime ), pStorage( _pStorage ) {  }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCommonFileSystemEnumerator : public IStorageEnumerator
{
	OBJECT_MINIMAL_METHODS( CCommonFileSystemEnumerator );
	std::string szMask;										// enumeration mask
	std::string szFileName;								// current enumerated file name
	SStorageElementStats stats;						// temporary data storage to fill each call
	//
	typedef std::hash_map<std::string, SCommonFileInfo> CFilesMap;
	const CFilesMap &files;
	CFilesMap::const_iterator itCurrFile;
	bool bReset;
public:
	CCommonFileSystemEnumerator( const CFilesMap &_files ) : files( _files ), bReset( true ), itCurrFile( files.begin() ) {  }
	//
	virtual void STDCALL Reset( const char *pszName );
	virtual bool STDCALL Next();
	virtual const SStorageElementStats* STDCALL GetStats() const { return &stats; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCommonFileSystem : public IDataStorage
{
	OBJECT_MINIMAL_METHODS( CCommonFileSystem );
	//
	CPtr<IDataStorage> pZipStorage;				// zip file system
	CPtr<IDataStorage> pFileStorage;			// open file system
	typedef std::hash_map<std::string, SCommonFileInfo> CFilesMap;
	CFilesMap files;											// соответствие имени файла и информации, необходимой для его получени
	//
	std::string szBase;
	DWORD dwStorageAccessMode;
	//
	void EnumerateFiles( const std::string &szName, IDataStorage *pStorage );
public:
	CCommonFileSystem( const char *pszName, DWORD dwAccessMode );
	// проверить, есть ли такой поток
	virtual const bool STDCALL IsStreamExist( const char *pszName );
	// создать и открыть поток с указанным именем и правами доступа
	virtual IDataStream* STDCALL CreateStream( const char *pszName, DWORD dwAccessMode );
	// открыть существующий поток с указанным именем и правами доступа
	virtual IDataStream* STDCALL OpenStream( const char *pszName, DWORD dwAccessMode );
	// получить описание stream'а
	virtual bool STDCALL GetStreamStats( const char *pszName, SStorageElementStats *pStats );
	// убить элемент хранилища
	virtual bool STDCALL DestroyElement( const char *pszName );
	// переименовать элемент
	virtual bool STDCALL RenameElement( const char *pszOldName, const char *pszNewName );
	// перечисление элементов
	virtual IStorageEnumerator* STDCALL CreateEnumerator();
	// получить имя этого storage
	virtual const char* STDCALL GetName() const { return szBase.c_str(); }
	// добавить новый MOD
	virtual bool STDCALL AddStorage( IDataStorage *pStorage, const char *pszName );
	// убрать MOD
	virtual bool STDCALL RemoveStorage( const char *pszName );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __COMMONFILESYSTEM_H__
