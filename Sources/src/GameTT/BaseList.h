#ifndef __BASE_LIST_H__
#define __BASE_LIST_H__
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "..\Common\InterfaceScreenBase.h"
#include "..\Input\InputHelper.h"
#include "..\Misc\FileUtils.h"
#include "iMission.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CInterfaceBaseList : public CInterfaceScreenBase
{
	OBJECT_NORMAL_METHODS( CInterfaceBaseList );
	//
	std::vector<std::string> dirsList;		//������ ����������
	std::vector<std::string> filesList;		//������ ������
	std::list<int> stack;									//���� ��� ���������� ��������� items, ����� ��� �������� ����� ����������
	// input
	NInput::CCommandRegistrator commandMsgs;
	//private:
	virtual void FillListFromCurrentDir();
	friend class CInterfaceCustomList;
protected:
	//��� ���������� ���������������� � ������������� ����������� �������
	std::vector<std::string> fileMasks;			//��� ��������� ������� ���� ��������� ����� ������, ������� ������
	std::string szCurrentDir;								//������� ����������
	std::string szTopDir;										//���� ���� ���������� �� �����������
	std::string szInterfaceName;						//��� ������������� �����

	enum E_SORT_TYPES
	{
		E_SORT_BY_NAME,
		E_SORT_BY_TIME,
	};
	int nSortType;
	int bStorageFiles;
	int nFirstSortColumn;
	bool bOnlyDirs;												// can enumerate only dirs
	int nBeginSelItem;
	bool bNotDiveIntoSubdirs;							// don't display directories and don't allow to enter to subdirectories
	
	CInterfaceBaseList() : CInterfaceScreenBase( "Current" ), nSortType( 0 ), bStorageFiles( false ),
		nBeginSelItem( 0 ), nFirstSortColumn( 0 ), bOnlyDirs( false ), bNotDiveIntoSubdirs( false ) {  }
	// disable explicit destruction
	virtual ~CInterfaceBaseList();
	
	virtual bool STDCALL StepLocal( bool bAppActive );
	virtual bool STDCALL ProcessMessage( const SGameMessage &msg );
	//������������� ���� �������
	virtual bool FillListItem( IUIListRow *pRow, const std::string &szFullFileName, bool *pSelectedItem = 0 );		//��������� ������� ������� � ������
	virtual bool OnOk( const std::string &szFullFileName );															//������������ ������ ����, ���������� �����
	virtual bool IsIgnoreSelection() const { return false; }														// user may not select, but enter to edit box
	virtual bool OnOk() { return false; }																								// no selection, use edit box input.
	virtual void PrepareList( std::vector<std::string> *pFiles ) { }					// inspects list ( may add something ) 
public:
	virtual bool STDCALL Init();
	virtual void STDCALL StartInterface();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
class CICBaseList : public CInterfaceCommandBase<CInterfaceBaseList, MISSION_INTERFACE_BASE_LIST>
{
OBJECT_NORMAL_METHODS( CICBaseList );

	bool bLoadGameIM;			//load game from inter mission interface
	virtual void PostCreate( IMainLoop *pML, CInterfaceBaseList *pILM );
	//
	CICBaseList() : bLoadGameIM( false ) {  }
	public:
	virtual void STDCALL Configure( const char *pszConfig );
	};
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ������� ��� EnumerateFiles, ����������� ��� ����� � ���������� � ���� �� ������������� ���
class CGetAllDirsRelative
{
	std::vector<std::string> *pFileVector;
	std::string szInitDir;
public:
	CGetAllDirsRelative( const char *pszDir, std::vector<std::string> *pFiles ) : szInitDir( pszDir ), pFileVector( pFiles ) {  }
	//
	void operator() ( const NFile::CFileIterator &it );
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __BASE_LIST_H__
