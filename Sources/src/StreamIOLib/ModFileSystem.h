#ifndef __MODFILESYSTEM_H__
#define __MODFILESYSTEM_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CModFileSystemEnumerator : public IStorageEnumerator
{
	OBJECT_MINIMAL_METHODS( CModFileSystemEnumerator );
	SStorageElementStats stats;						// temporary data storage to fill each call
	typedef std::map<std::string, SStorageElementStats> CStatsMap;
	CStatsMap files;											// all file stats
	CStatsMap::const_iterator itCurrFile;	// current iterated file
	bool bReset;
public:
	CModFileSystemEnumerator() {  }
	//
	void AddFile( const std::string &szName, const SStorageElementStats &stats ) { files[szName] = stats; }
	virtual void STDCALL Reset( const char *pszName );
	virtual bool STDCALL Next();
	virtual const SStorageElementStats* STDCALL GetStats() const { return &stats; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CModFileSystem : public IDataStorage
{
	OBJECT_MINIMAL_METHODS( CModFileSystem );
	//
	typedef std::pair<std::string, CPtr<IDataStorage> > SFileSystemDesc;
	typedef std::list<SFileSystemDesc> CFileSystemsList;
	CFileSystemsList filesystems;					// available file systems, last file system - base
	DWORD dwStorageAccessMode;						// access mode - READ-ONLY for this storage
public:
	CModFileSystem( const char *pszName, DWORD dwAccessMode );
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
	virtual const char* STDCALL GetName() const;
	// добавить новый MOD
	virtual bool STDCALL AddStorage( IDataStorage *pStorage, const char *pszName );
	// убрать MOD
	virtual bool STDCALL RemoveStorage( const char *pszName );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __MODFILESYSTEM_H__
