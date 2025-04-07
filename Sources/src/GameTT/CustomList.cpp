#include "StdAfx.h"

#include "..\Main\GameStats.h"
#include "CommonId.h"
#include "CustomList.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CInterfaceCustomList::~CInterfaceCustomList()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CInterfaceCustomList::FillListFromCurrentDir()
{
	IUIListControl *pList = checked_cast<IUIListControl*>( pUIScreen->GetChildByID( 1000 ) );
	NI_ASSERT( pList != 0 );
	ITextManager *pTextM = GetSingleton<ITextManager>();
	IDataStorage *pStorage = GetSingleton<IDataStorage>();
	
	//удал€ем все items из ListControl
	for ( int i=pList->GetNumberOfItems()-1; i>=0; i-- )
	{
		pList->RemoveItem( i );
	}
	
	// enumerate all available files and dirs
	dirsList.clear();
	filesList.clear();
	std::vector< std::string > dirs;		//временное хранилище директорий
	std::vector< std::string > files;
	
	IFilesInspectorEntryCollector *pCollector = checked_cast<IFilesInspectorEntryCollector *>( GetSingleton<IFilesInspector>()->GetEntry( szCollectorName.c_str() ) );
	const std::vector<std::string> &tutorialFiles = pCollector->GetCollected();
	std::hash_set<std::string> setOfDirs;		//здесь € сохран€ю все директории
	
	for ( int i=0; i<tutorialFiles.size(); i++ )
	{
		if ( strncmp( tutorialFiles[i].c_str(), szCurrentDir.c_str(), szCurrentDir.size() ) )
			continue;			//не равны
		
		//проверим, что справа нету вложенных директорий
		std::string szCurrentName = tutorialFiles[i].c_str() + szCurrentDir.size();
		int nPos = szCurrentName.rfind( '\\' );
		if ( nPos != std::string::npos )		//правее есть еще директории
		{
			//возьмем им€ директории
			szCurrentName = szCurrentName.substr( 0, szCurrentName.find('\\') );
			setOfDirs.insert( szCurrentName );
			continue;
		}
	}
	
	for ( std::hash_set<std::string>::iterator it = setOfDirs.begin(); it != setOfDirs.end(); ++it )
	{
		//найдем все непустые поддиректории внутри данной директории
		std::string szCmpDir = szCurrentDir + *it;
		szCmpDir += '\\';
		std::hash_set<std::string> setOfSubDirs;
		for ( int i=0; i<tutorialFiles.size(); i++ )
		{
			std::string szCurrentName = tutorialFiles[i];
			if ( strncmp( szCurrentName.c_str(), szCmpDir.c_str(), szCmpDir.size() ) )
				continue;			//не равны
			szCurrentName = szCurrentName.substr( szCmpDir.size() );
			
			//проверим, что это поддиректори€
			int nPos = szCurrentName.rfind( '\\' );
			if ( nPos != std::string::npos )		//правее есть еще директории
			{
				szCurrentName = szCurrentName.substr( 0, nPos );
				setOfSubDirs.insert( szCurrentName );
				continue;
			}
			
			//проверим, что это за файл
			nPos = szCurrentName.rfind( '.' );
			if ( nPos == std::string::npos )
				continue;

			std::string szExtension = szCurrentName.substr( nPos );
			for ( int k=0; k<fileMasks.size(); k++ )
			{
				if ( szExtension == fileMasks[k].c_str() + 1 )
				{
					//совпадает маска файла, добавл€ем в список файлов
					std::string szName = szCmpDir;
					szName += szCurrentName;
					files.push_back( szName );
				}
			}
		}

		for ( std::hash_set<std::string>::iterator it=setOfSubDirs.begin(); it!=setOfSubDirs.end(); ++it )
		{
			dirs.push_back( *it );
		}
	}
	
	
	int nIndex = 0;
	if ( szCurrentDir.size() > szTopDir.size() )
		dirs.push_back( ".." );
	
	// add strings to list control
	for ( int i=0; i<dirs.size(); i++ )
	{
		pList->AddItem();
		IUIListRow *pRow = pList->GetItem( nIndex );
		pRow->SetUserData( nIndex );
		nIndex++;
		
		//установим им€ директории
		IUIContainer *pContainer = checked_cast<IUIContainer*> ( pRow->GetElement( 0 ) );
		dirsList.push_back( dirs[i] );
		std::wstring wszTemp;
		NStr::ToUnicode( &wszTemp, dirs[i] );
		pContainer->SetWindowText( 0, wszTemp.c_str() );
		
		IUIElement *pElement = pContainer->GetChildByID( 1 );
		NI_ASSERT_T( pElement != 0, "Invalid list control name dialog, it should contain icon" );
		pElement->SetState( 0 );			//директори€
		
/*
		std::string szFullName = szCurrentDir;
		szFullName += dirs[i];
		if ( !FillListItem( pRow, szFullName ) )
			return;
*/
	}

	for ( int k=0; k<files.size(); k++ )
	{
		std::string szName = files[k];
		// считаем инфу из файла, как будто он содержит SBasicGameStats
		if ( pStorage->IsStreamExist(szName.c_str()) == false )
			continue;
		{
			const int nPos = szName.rfind( '.' );
			if ( nPos != std::string::npos ) 
				szName.resize( nPos );
		}
		const SBasicGameStats *pStats = NGDB::GetGameStats<SBasicGameStats>( szName.c_str(), IObjectsDB::BASIC );
		if ( (pStats == 0) || pStats->szHeaderText.empty() )
			continue;
		
		CPtr<IText> p = pTextM->GetDialog( pStats->szHeaderText.c_str() );
		NI_ASSERT_T( p != 0, (std::string("Can not get text by key") + pStats->szHeaderText).c_str() );
		if ( !p )
			continue;
		
		//заполним внутренний список имен файлов
		filesList.push_back( szName.substr( szCurrentDir.size() ) );
		
		//добавим локализованное им€ в список на экране
		pList->AddItem();
		IUIListRow *pRow = pList->GetItem( nIndex );
		pRow->SetUserData( nIndex );
		nIndex++;
		
		//установим им€ файла
		IUIContainer *pContainer = checked_cast<IUIContainer*> ( pRow->GetElement( 0 ) );
		pContainer->SetWindowText( 0, p->GetString() );
		
		IUIElement *pElement = pContainer->GetChildByID( 1 );
		NI_ASSERT_T( pElement != 0, "Invalid list control name dialog, it should contain icon" );
		pElement->SetState( 1 );			//файл
		//TODO вместо 1 ставить соответствующее маске
		
		FillListItem( pRow, szName );
	}

	pList->InitialUpdate();
	
	//ќпределим текущий выделенный элемент
	if ( pList->GetNumberOfItems() < nBeginSelItem )
		nBeginSelItem = pList->GetNumberOfItems();
	pList->SetSelectionItem( nBeginSelItem );
	
	pUIScreen->Reposition( pGFX->GetScreenRect() );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CInterfaceCustomList::ProcessMessage( const SGameMessage &msg )
{
	if ( CInterfaceBaseList::ProcessMessage( msg ) )
		return true;

	switch ( msg.nEventID )
	{
		case IMC_CANCEL:
			{
				IMainLoop *pML = GetSingleton<IMainLoop>();
				CloseInterface();
				return true;
			}
/*
		case IMC_OK:
			{
				//попробуем вз€ть текущий selection из list control
				IUIElement *pElement = pUIScreen->GetChildByID( 1000 );		//should be List Control
				IUIListControl *pList = checked_cast<IUIListControl*>( pElement );
				if ( !pList )
					return true;			//не нашелс€ list control
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
						//поднимемс€ наверх
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
*/
	}

	//
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
