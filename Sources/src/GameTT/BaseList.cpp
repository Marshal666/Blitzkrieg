#include "StdAfx.h"

#include <time.h>

#include "BaseList.h"
#include "SaveLoadCommon.h"
#include "CommonId.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const NInput::SRegisterCommandEntry commonCommands[] = 
{
	{ "cancel_load"	,	IMC_CANCEL					},
	{ "load_mission", IMC_OK							},
	{ "key_up",				MESSAGE_KEY_UP			},
	{ "key_down",			MESSAGE_KEY_DOWN		},
	{ "key_left",			MESSAGE_KEY_LEFT		},
	{ "key_right",		MESSAGE_KEY_RIGHT		},
	{ 0							,	0										}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CGetAllDirsRelative::operator() ( const NFile::CFileIterator &it )
{
	if ( it.IsDirectory() )
	{
		std::string szName = it.GetFilePath();
		NI_ASSERT_T( szName.size() > szInitDir.size(), "Wrong name size" );
		szName = szName.substr( szInitDir.size() );
		pFileVector->push_back( szName );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CInterfaceBaseList::~CInterfaceBaseList()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CInterfaceBaseList::FillListFromCurrentDir()
{
	IUIListControl *pList = checked_cast<IUIListControl*>( pUIScreen->GetChildByID( 1000 ) );
	NI_ASSERT( pList != 0 );
	
	//удаляем все items из ListControl
	for ( int i = pList->GetNumberOfItems() - 1; i >= 0; i-- )
	{
		pList->RemoveItem( i );
	}
	
	// enumerate all available files and dirs
	dirsList.clear();
	filesList.clear();
	std::vector< std::string > dirs;		//временное хранилище директорий
	std::vector< std::string > files;

	if ( bStorageFiles )
	{
		IDataStorage *pStorage = GetSingleton<IDataStorage>();
		CPtr<IStorageEnumerator> pEnumerator = pStorage->CreateEnumerator();
		pEnumerator->Reset( "*.*" );
		std::hash_set<std::string> setOfDirs;

		while (	pEnumerator->Next() )
		{
			const SStorageElementStats *pStats = pEnumerator->GetStats();
			if ( strncmp( pStats->pszName, szCurrentDir.c_str(), szCurrentDir.size() ) )
				continue;			//не равны

			//проверим, что справа нету вложенных директорий
			std::string szCurrentName = pStats->pszName + szCurrentDir.size();
			int nPos = szCurrentName.rfind( '\\' );
			if ( nPos != std::string::npos )		//правее есть еще директории
			{
				//возьмем имя директории
				szCurrentName = szCurrentName.substr( 0, szCurrentName.find('\\') );
				setOfDirs.insert( szCurrentName );
				continue;
			}

			nPos = szCurrentName.rfind( '.' );
			if ( nPos == std::string::npos )
			{
				//это директория, добавляем ее в список директорий
				dirs.push_back( szCurrentName );
			}
			std::string szExtension = szCurrentName.substr( nPos );
			for ( int k = 0; k < fileMasks.size(); ++k )
			{
				if ( szExtension == fileMasks[k].c_str() + 1 )
				{
					//совпадает маска файла, добавляем в список файлов
					files.push_back( szCurrentName );
				}
			}
		}
		
		for ( std::hash_set<std::string>::const_iterator it = setOfDirs.begin(); it != setOfDirs.end(); ++it )
		{
			dirs.push_back( *it );
		}
	}
	else
	{
		//директории
		NFile::EnumerateFiles( szCurrentDir.c_str(), "*.*", CGetAllDirsRelative(szCurrentDir.c_str(), &dirs), false );
		//	std::sort( dirs.begin(), dirs.end() );
		
		//файлы
		switch ( nSortType )
		{
		case E_SORT_BY_NAME:
			{
				for ( int i = 0; i < fileMasks.size(); ++i )
				{
					NFile::EnumerateFiles( szCurrentDir.c_str(), fileMasks[i].c_str(), NFile::CGetAllFilesRelative(szCurrentDir.c_str(), &files), false );
				}
				std::sort( files.begin(), files.end() );
				break;
			}
			
		case E_SORT_BY_TIME:
			{
				for ( int i = 0; i < fileMasks.size(); ++i )
				{
					std::vector<SLoadFileDesc> filesWithTimeInfo;
					NFile::EnumerateFiles( szCurrentDir.c_str(), fileMasks[i].c_str(), CGetFiles2Load(filesWithTimeInfo, szCurrentDir), false );
					std::sort( filesWithTimeInfo.begin(), filesWithTimeInfo.end(), SLoadFileLessFunctional() );
					for ( int k = 0; k < filesWithTimeInfo.size(); ++k )
						files.push_back( filesWithTimeInfo[k].szFileName );
				}
				break;
			}
			
		default:
			NI_ASSERT_T( 0, "Sort type does not supported!" );
		}
	}

	if ( bOnlyDirs )
	{
		files = dirs;
		dirs.clear();
	}
	if ( bNotDiveIntoSubdirs )
	{
		dirs.clear();
	}
	
	PrepareList( &files );
	
	if ( szCurrentDir.size() > szTopDir.size() )
	{
		//добавляем директорию путь наверх
		dirs.insert( dirs.begin(), ".." );
	}
	
	// add strings to list control
	for ( int i = 0; i < dirs.size(); i++ )
	{
		pList->AddItem();
		IUIListRow *pRow = pList->GetItem( i );
		pRow->SetUserData( i );
		
		//установим имя директории
		IUIContainer *pContainer = checked_cast<IUIContainer*> ( pRow->GetElement( 0 ) );
		dirsList.push_back( dirs[i] );
		std::wstring wszTemp;
		NStr::ToUnicode( &wszTemp, dirs[i] );
		pContainer->SetWindowText( 0, wszTemp.c_str() );
		
		IUIElement *pElement = pContainer->GetChildByID( 1 );
		NI_ASSERT_T( pElement != 0, "Invalid list control name dialog, it should contain icon" );
		pElement->SetState( 0 );			//директория
		
		std::string szFullName = szCurrentDir;
		szFullName += dirs[i];
		if ( !FillListItem( pRow, szFullName ) )
			return;
	}
	
	bool bSelected = false;
	for ( int i = 0; i < files.size(); i++ )
	{
		pList->AddItem();
		const int nItemNumber = i + dirsList.size();
		IUIListRow *pRow = pList->GetItem( nItemNumber );
		pRow->SetUserData( nItemNumber );
		
		//установим имя файла
		IUIContainer *pContainer = checked_cast<IUIContainer*> ( pRow->GetElement( 0 ) );
		filesList.push_back( files[i] );
		//отрежем extension
		std::wstring wszTemp;
		NStr::ToUnicode( &wszTemp, files[i].substr( 0, files[i].rfind( '.' ) ) );
		pContainer->SetWindowText( 0, wszTemp.c_str() );
		
		IUIElement *pElement = pContainer->GetChildByID( 1 );
		NI_ASSERT_T( pElement != 0, "Invalid list control name dialog, it should contain icon" );
		pElement->SetState( 1 );			//файл
		//TODO вместо 1 ставить соответствующее маске

		std::string szFullName = szCurrentDir;
		szFullName += files[i];
		bool bToSelect = false;
		if ( !FillListItem( pRow, szFullName, &bToSelect ) )
			return;
		if ( !bSelected && bToSelect )
		{
			pList->SetSelectionItem( pList->GetItemByID( nItemNumber ) );
			bSelected = true;
		}
	}

	pList->InitialUpdate();
	
	//Определим текущий выделенный элемент
	if ( !bSelected )
	{
		if ( pList->GetNumberOfItems() < nBeginSelItem )
			nBeginSelItem = pList->GetNumberOfItems() - 1;
		pList->SetSelectionItem( nBeginSelItem );
	}
	
	pUIScreen->Reposition( pGFX->GetScreenRect() );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CInterfaceBaseList::Init()
{
	NStr::SetCodePage( GetACP() );
	CInterfaceScreenBase::Init();
	SetBindSection( "loadmission" );
	commandMsgs.Init( pInput, commonCommands );
	
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CInterfaceBaseList::StartInterface()
{
	CInterfaceScreenBase::StartInterface();
	pUIScreen = CreateObject<IUIScreen>( UI_SCREEN );
	pUIScreen->Load( szInterfaceName.c_str() );
	pUIScreen->Reposition( pGFX->GetScreenRect() );

	IUIListControl *pList = checked_cast<IUIListControl*>( pUIScreen->GetChildByID( 1000 ) );
	pList->Sort( nFirstSortColumn );		//сортируем по данному столбцу

	FillListFromCurrentDir();

	// add UI screen to scene
	pScene->AddUIScreen( pUIScreen );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CInterfaceBaseList::FillListItem( IUIListRow *pRow, const std::string &szFullFileName, bool *pSelectedItem )
{
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CInterfaceBaseList::OnOk( const std::string &szFullFileName )
{
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CInterfaceBaseList::ProcessMessage( const SGameMessage &msg )
{
	switch ( msg.nEventID )
	{
		case IMC_OK:
			{
				//попробуем взять текущий selection из list control
				IUIElement *pElement = pUIScreen->GetChildByID( 1000 );		//should be List Control
				IUIListControl *pList = checked_cast<IUIListControl*>( pElement );
				
				if ( IsIgnoreSelection() )
				{
					OnOk();
					return true;
				}

				if ( !pList )
					return true;			//не нашелся list control
				int nSelItem = pList->GetSelectionItem();			//индекс в списке
				if ( nSelItem == -1 )
					return true;
				
				IUIListRow *pSelRow = pList->GetItem( nSelItem );
				int nSel = pSelRow->GetUserData();						//индекс в массиве
				if ( nSel < dirsList.size() )
				{
					//сменим текущую директорию
					if ( dirsList[ nSel ] == ".." )
					{
						//поднимемся наверх
						NI_ASSERT_T( !stack.empty(), "Popup stack is empty" );
						nBeginSelItem = stack.back();
						stack.pop_back();
						szCurrentDir.pop_back();
						szCurrentDir = szCurrentDir.substr( 0, szCurrentDir.rfind('\\')+1 );
					}
					else
					{
						szCurrentDir += dirsList[ nSel ];
						szCurrentDir += "\\";
						stack.push_back( nSelItem );
						nBeginSelItem = 0;
					}
					FillListFromCurrentDir();
				}
				else
				{
					std::string szFullName;
					if ( bStorageFiles )
						szFullName = GetSingleton<IDataStorage>()->GetName();
					szFullName += szCurrentDir;
					szFullName += filesList[nSel - dirsList.size() ];
					OnOk( szFullName.c_str() );
				}
				return true;
			}
	}
	//
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CInterfaceBaseList::StepLocal( bool bAppActive )
{
	if ( !bAppActive ) 
		return false;
	//
	const CVec2 vPos = pCursor->GetPos();
	CInterfaceScreenBase::OnCursorMove( vPos );
	if ( pUIScreen )		//в некоторых экранах pUIScreen нету
		pUIScreen->Update( pTimer->GetAbsTime() );
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
