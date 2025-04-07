#ifndef __DATABASE_H__
#define __DATABASE_H__
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CIniFileDataBase : public IDataBase
{
	OBJECT_MINIMAL_METHODS( CIniFileDataBase );
	//
	std::string szBase;
	DWORD dwStorageAccessMode;
public:
	CIniFileDataBase( const char *pszName, DWORD dwAccessMode );
	// создать и открыть таблицу с указанным именем и правами доступа
	virtual IDataTable* STDCALL CreateTable( const char *pszName, DWORD dwAccessMode );
	// открыть существующую таблицу с указанным именем и правами доступа
	virtual IDataTable* STDCALL OpenTable( const char *pszName, DWORD dwAccessMode );
	// убить элемент хранилища
	virtual bool STDCALL DestroyElement( const char *pszName );
	// переименовать элемент
	virtual bool STDCALL RenameElement( const char *pszOldName, const char *pszNewName );
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __DATABASE_H__
