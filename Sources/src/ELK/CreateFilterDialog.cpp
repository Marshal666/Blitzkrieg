#include "StdAfx.h"

#include "Resource.h"
#include "CreateFilterDialog.h"
#include "CreateFilterNameDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int CCreateFilterDialog::vID[] = 
{
	IDC_CF_FILTERS_LABEL,						//0
	IDC_CF_FILTERS_LIST,						//1
	IDC_CF_ALL_FOLDERS_LABEL,				//2
	IDC_CF_ALL_FOLDERS_LIST,				//3
	IDC_CF_CONDITIONS_LABEL,				//4
	IDC_CF_CONDITIONS_LIST,					//5
	IDC_CF_ADD_FILTER_BUTTON,				//6
	IDC_CF_DELETE_FILTER_BUTTON,		//7
	IDC_CF_RENAME_FILTER_BUTTON,		//8
	IDC_CF_ADD_CONDITION_BUTTON,		//9
	IDC_CF_REMOVE_CONDITION_BUTTON,	//10
	IDC_CF_CHANGED_CHECKBOX,				//12				
	IDC_CF_STATES_LABEL,						//13
	IDC_CF_STATE_0,									//14	
	IDC_CF_STATE_1,									//15
	IDC_CF_STATE_2,									//16
	IDC_CF_STATE_2,									//17
	IDOK,														//18
	IDCANCEL,												//19
};

const int   FILTERS_COLUMN_START = 0;
const int   FILTERS_COLUMN_COUNT = 2;
LPCTSTR			FILTERS_COLUMN_NAME  [FILTERS_COLUMN_COUNT] = { _T( "Name" ), _T( "Size" ) };
const int   FILTERS_COLUMN_FORMAT[FILTERS_COLUMN_COUNT] = { LVCFMT_LEFT, LVCFMT_RIGHT };
const int		FILTERS_COLUMN_WIDTH [FILTERS_COLUMN_COUNT] = { 200, 60 };

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CALLBACK FiltersCompareFunc( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort )
{
	CCreateFilterDialog* pFilterDialog = reinterpret_cast<CCreateFilterDialog*>( lParamSort );

	CString strItem1 = pFilterDialog->m_FiltersList.GetItemText( lParam1, pFilterDialog->nSortColumn );
	CString strItem2 = pFilterDialog->m_FiltersList.GetItemText( lParam2, pFilterDialog->nSortColumn );
	if ( pFilterDialog->bFiltersSortParam[pFilterDialog->nSortColumn] )
	{
		return strcmp( strItem1, strItem2 );
	}
	else 
	{
		return strcmp( strItem2, strItem1 );
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CCreateFilterDialog::CCreateFilterDialog( CWnd* pParent )
	: CResizeDialog( CCreateFilterDialog::IDD, pParent ), nSortColumn( 0 ), bCreateControls( true )
{
	//{{AFX_DATA_INIT(CCreateFilterDialog)
	//}}AFX_DATA_INIT

	SetControlStyle( IDC_CF_FILTERS_LABEL, ANCHORE_LEFT_TOP | RESIZE_HOR );
	SetControlStyle( IDC_CF_FILTERS_LIST, ANCHORE_LEFT_TOP | RESIZE_HOR_VER, 0.5f, 0.5f, 1.0f, 0.5f );
	
	SetControlStyle( IDC_CF_ALL_FOLDERS_LABEL, ANCHORE_LEFT | ANCHORE_VER_CENTER | RESIZE_HOR, 0.5f, 0.5f, 0.5f, 1.0f );
	SetControlStyle( IDC_CF_ALL_FOLDERS_LIST, ANCHORE_LEFT_BOTTOM | RESIZE_HOR_VER, 0.5f, 0.5f, 0.5f, 0.5f );
	
	SetControlStyle( IDC_CF_CONDITIONS_LABEL, ANCHORE_RIGHT | ANCHORE_VER_CENTER | RESIZE_HOR, 0.5f, 0.5f, 0.5f, 1.0f );
	SetControlStyle( IDC_CF_CONDITIONS_LIST, ANCHORE_RIGHT_BOTTOM | RESIZE_HOR_VER, 0.5f, 0.5f, 0.5f, 0.5f );
	
	SetControlStyle( IDC_CF_ADD_FILTER_BUTTON, ANCHORE_RIGHT_TOP );
	SetControlStyle( IDC_CF_DELETE_FILTER_BUTTON, ANCHORE_RIGHT_TOP );
	SetControlStyle( IDC_CF_RENAME_FILTER_BUTTON, ANCHORE_RIGHT_TOP );

	SetControlStyle( IDC_CF_ADD_CONDITION_BUTTON, ANCHORE_HOR_CENTER | ANCHORE_VER_CENTER );
	SetControlStyle( IDC_CF_REMOVE_CONDITION_BUTTON, ANCHORE_HOR_CENTER | ANCHORE_VER_CENTER );

	SetControlStyle( IDC_CF_CHANGED_CHECKBOX, ANCHORE_RIGHT_BOTTOM | RESIZE_HOR, 0.5f, 0.5f, 0.5f, 1.0f );
	
	SetControlStyle( IDC_CF_STATES_LABEL, ANCHORE_RIGHT_BOTTOM | RESIZE_HOR, 0.5f, 0.5f, 0.5f, 1.0f );
	SetControlStyle( IDC_CF_STATE_0, ANCHORE_RIGHT_BOTTOM | RESIZE_HOR, 0.5f, 0.5f, 0.5f, 1.0f );
	SetControlStyle( IDC_CF_STATE_1, ANCHORE_RIGHT_BOTTOM | RESIZE_HOR, 0.5f, 0.5f, 0.5f, 1.0f );
	SetControlStyle( IDC_CF_STATE_2, ANCHORE_RIGHT_BOTTOM | RESIZE_HOR, 0.5f, 0.5f, 0.5f, 1.0f );
	SetControlStyle( IDC_CF_STATE_3, ANCHORE_RIGHT_BOTTOM | RESIZE_HOR, 0.5f, 0.5f, 0.5f, 1.0f );
	
	SetControlStyle( IDOK, ANCHORE_HOR_CENTER | ANCHORE_BOTTOM );
	SetControlStyle( IDCANCEL, ANCHORE_HOR_CENTER | ANCHORE_BOTTOM );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string CCreateFilterDialog::GetRegistryKey()
{
	CString strPath;
	CString strProgramKey;
	CString strKey;
	strPath.LoadString( IDS_REGISTRY_PATH );
	strProgramKey.LoadString( AFX_IDS_APP_TITLE );
	strKey.LoadString( IDS_CF_REGISTRY_KEY );
	std::string szRegistryKey = NStr::Format( _T( "Software\\%s\\%s\\%s" ), LPCTSTR( strPath ), LPCTSTR( strProgramKey ), LPCTSTR( strKey ) );
	return szRegistryKey;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::DoDataExchange(CDataExchange* pDX)
{
	CResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateFilterDialog)
	DDX_Control(pDX, IDC_CF_CONDITIONS_LIST, m_ConditionsList);
	DDX_Control(pDX, IDC_CF_ALL_FOLDERS_LIST, m_FoldersList);
	DDX_Control(pDX, IDC_CF_FILTERS_LIST, m_FiltersList);
	//}}AFX_DATA_MAP
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CCreateFilterDialog, CResizeDialog)
	//{{AFX_MSG_MAP(CCreateFilterDialog)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_CF_FILTERS_LIST, OnColumnclickFiltersList)
	ON_NOTIFY(NM_RCLICK, IDC_CF_FILTERS_LIST, OnRclickFiltersList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CF_FILTERS_LIST, OnItemchangedFiltersList)
	ON_LBN_SELCHANGE(IDC_CF_CONDITIONS_LIST, OnSelchangeConditionsList)
	ON_LBN_SELCHANGE(IDC_CF_ALL_FOLDERS_LIST, OnSelchangeAllFoldersList)
	ON_BN_CLICKED(IDC_CF_ADD_CONDITION_BUTTON, OnAddConditionButton)
	ON_BN_CLICKED(IDC_CF_REMOVE_CONDITION_BUTTON, OnRemoveConditionButton)
	ON_BN_CLICKED(IDC_CF_ADD_FILTER_BUTTON, OnAddFilterButton)
	ON_COMMAND(IDC_CF_ADD_FILTER_MENU, OnAddFilterMenu)
	ON_BN_CLICKED(IDC_CF_DELETE_FILTER_BUTTON, OnDeleteFilterButton)
	ON_COMMAND(IDC_CF_DELETE_FILTER_MENU, OnDeleteFilterMenu)
	ON_LBN_DBLCLK(IDC_CF_ALL_FOLDERS_LIST, OnDblclkAllFoldersList)
	ON_BN_CLICKED(IDC_CF_RENAME_FILTER_BUTTON, OnRenameFilterButton)
	ON_COMMAND(IDC_CF_RENAME_FILTER_MENU, OnRenameFilterMenu)
	ON_NOTIFY(NM_DBLCLK, IDC_CF_FILTERS_LIST, OnDblclkFiltersList)
	ON_BN_CLICKED(IDC_CF_STATES_LABEL, OnChangedState)
	ON_BN_CLICKED(IDC_CF_STATE_0, OnState0)
	ON_BN_CLICKED(IDC_CF_STATE_1, OnState1)
	ON_BN_CLICKED(IDC_CF_STATE_2, OnState2)
	ON_BN_CLICKED(IDC_CF_STATE_2, OnState3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CCreateFilterDialog::OnInitDialog()
{
  CResizeDialog::OnInitDialog();
	
	while ( resizeDialogOptions.nParameters.size() < ( FILTERS_COLUMN_COUNT ) )
	{
		resizeDialogOptions.nParameters.push_back( 0 );
	}

	CreateControls();
	FillFilters();
	FillFolders( TSimpleFilterItem() );
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::FillFilters()
{
	bCreateControls = true;

	m_FiltersList.DeleteAllItems();
	for ( TFilterHashMap::const_iterator filterIterator = filters.begin(); filterIterator != filters.end(); ++filterIterator )
	{
		int nNewItem = m_FiltersList.InsertItem( LVIF_TEXT, 0, filterIterator->first.c_str(), 0, 0, 0, 0 );
		if ( nNewItem != ( -1 ) )
		{
			m_FiltersList.SetItem( nNewItem, 1, LVIF_TEXT, NStr::Format( _T( "%d" ), filterIterator->second.filter.size() ), 0, 0, 0, 0 );
			if ( filterIterator->first == szCurrentFilter )
			{
				m_FiltersList.SetItemState( nNewItem, LVNI_SELECTED, LVNI_SELECTED );
				LoadFilterToControls();
			}
		}
	}
	szCurrentFilter.clear();
	bCreateControls = false;
	
	UpdateControls();
}

void CCreateFilterDialog::LoadFilterToControls()
{
	int nSelectedFilter = m_FiltersList.GetNextItem( -1, LVNI_SELECTED );
	if ( nSelectedFilter >= 0 )
	{
		std::string szFilterName = m_FiltersList.GetItemText( nSelectedFilter, 0 );
		TFilterHashMap::const_iterator filtersIterator = filters.find( szFilterName );
		if ( filtersIterator != filters.end() )
		{
			bCreateControls = true;

			int nFilterCount = 0;
			m_ConditionsList.ResetContent();
			for ( TSimpleFilter::const_iterator filterIterator = filtersIterator->second.filter.begin(); filterIterator != filtersIterator->second.filter.end(); ++filterIterator )
			{
				std::string szFilterElementText;
				for ( TSimpleFilterItem::const_iterator filterItemIterator = filterIterator->begin(); filterItemIterator != filterIterator->end(); ++filterItemIterator )
				{
					if ( szFilterElementText.empty() )
					{
						szFilterElementText = std::string( "\"" ) + ( *filterItemIterator ) + std::string( "\"" );
					}
					else
					{
						szFilterElementText += std::string( " & \"" ) + ( *filterItemIterator ) + std::string( "\"" );
					}
				}
				int nNewCondition = m_ConditionsList.AddString( szFilterElementText.c_str() );
				if ( nNewCondition >= 0 )
				{
					m_ConditionsList.SetItemData( nNewCondition, nFilterCount );
				}
				++nFilterCount;
			}
			m_FiltersList.SetItem( nSelectedFilter, 1, LVIF_TEXT, NStr::Format( _T( "%d" ), nFilterCount ), 0, 0, 0, 0 );

			CheckDlgButton( IDC_CF_CHANGED_CHECKBOX, ( filtersIterator->second.bTranslated ? BST_CHECKED : BST_UNCHECKED ) );
			CheckDlgButton( IDC_CF_STATE_0, ( filtersIterator->second.states[SELKTextProperty::STATE_NOT_TRANSLATED] > 0 ) ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( IDC_CF_STATE_1, ( filtersIterator->second.states[SELKTextProperty::STATE_OUTDATED] > 0 ) ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( IDC_CF_STATE_2, ( filtersIterator->second.states[SELKTextProperty::STATE_TRANSLATED] > 0 ) ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( IDC_CF_STATE_3, ( filtersIterator->second.states[SELKTextProperty::STATE_APPROVED] > 0 ) ? BST_CHECKED : BST_UNCHECKED );

			bCreateControls = false;

			UpdateControls();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::FillFolders( const TSimpleFilterItem &rSimpleFilterItem )
{
	bCreateControls = true;

	m_FoldersList.ResetContent();
	for ( TEnumFolders::const_iterator folderIterator = folders.begin(); folderIterator != folders.end(); ++folderIterator )
	{
		bool bInsert = true;
		bool bExact = false;
		for ( TSimpleFilterItem::const_iterator itemIterator = rSimpleFilterItem.begin(); itemIterator != rSimpleFilterItem.end(); ++itemIterator )
		{
			if ( ( *itemIterator ) == folderIterator->first.c_str() )
			{
				bExact = true;
				break;
			}
			if ( !SEnumFolderStructureParameter::IsFolderRelative( folders, ( *itemIterator ), folderIterator->first.c_str() ) )
			{
				bInsert = false;
				break;
			}
		}
		if ( bInsert )
		{
			int nNewItem = m_FoldersList.AddString( folderIterator->first.c_str() );
			if ( bExact && ( nNewItem >= 0 ) )
			{
				m_FoldersList.SetCheck( nNewItem, 1 );
			}
		}
	}
	lastSimpleFilterItem = rSimpleFilterItem;
	bCreateControls = false;

	UpdateControls();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::CreateControls()
{
	bCreateControls = true;
	
	m_FiltersList.SetExtendedStyle( m_FiltersList.GetExtendedStyle() | LVS_EX_FULLROWSELECT );
	for ( int nColumnIndex = 0; nColumnIndex < FILTERS_COLUMN_COUNT; ++nColumnIndex )
	{
		if ( resizeDialogOptions.nParameters[nColumnIndex + FILTERS_COLUMN_START] == 0 )
		{
			resizeDialogOptions.nParameters[nColumnIndex + FILTERS_COLUMN_START] = FILTERS_COLUMN_WIDTH[nColumnIndex];
		}
		int nNewColumn = m_FiltersList.InsertColumn( nColumnIndex, FILTERS_COLUMN_NAME[nColumnIndex], FILTERS_COLUMN_FORMAT[nColumnIndex], resizeDialogOptions.nParameters[nColumnIndex + FILTERS_COLUMN_START], nColumnIndex );
		NI_ASSERT_T( nNewColumn == nColumnIndex,
								 NStr::Format( _T( "Invalid Column Index: %d (%d)" ), nNewColumn, nColumnIndex ) );
		bFiltersSortParam.push_back( true );
	}

	bCreateControls = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::ClearControls()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::UpdateControls()
{
	bool bSelectedFilterExists = ( m_FiltersList.GetSelectedCount() > 0 );
	CWnd* pWnd = 0;
	if ( pWnd = GetDlgItem( IDC_CF_ADD_FILTER_BUTTON ) )
	{
		pWnd->EnableWindow( true );
	}
	if ( pWnd = GetDlgItem( IDC_CF_DELETE_FILTER_BUTTON ) )
	{
		pWnd->EnableWindow( bSelectedFilterExists );
	}
	if ( pWnd = GetDlgItem( IDC_CF_ALL_FOLDERS_LIST ) )
	{
		pWnd->EnableWindow( bSelectedFilterExists );
	}
	if ( pWnd = GetDlgItem( IDC_CF_CONDITIONS_LIST ) )
	{
		pWnd->EnableWindow( bSelectedFilterExists );
	}
	if ( pWnd = GetDlgItem( IDC_CF_RENAME_FILTER_BUTTON ) )
	{
		pWnd->EnableWindow( bSelectedFilterExists && m_FoldersList.GetSelCount() );
	}
	if ( pWnd = GetDlgItem( IDC_CF_CHANGED_CHECKBOX ) )
	{
		pWnd->EnableWindow( bSelectedFilterExists );
	}
	if ( pWnd = GetDlgItem( IDC_CF_STATE_0 ) )
	{
		pWnd->EnableWindow( bSelectedFilterExists );
	}
	if ( pWnd = GetDlgItem( IDC_CF_STATE_1 ) )
	{
		pWnd->EnableWindow( bSelectedFilterExists );
	}
	if ( pWnd = GetDlgItem( IDC_CF_STATE_2 ) )
	{
		pWnd->EnableWindow( bSelectedFilterExists );
	}
	if ( pWnd = GetDlgItem( IDC_CF_STATE_3 ) )
	{
		pWnd->EnableWindow( bSelectedFilterExists );
	}

	if ( pWnd = GetDlgItem( IDC_CF_ADD_CONDITION_BUTTON ) )
	{
		pWnd->EnableWindow( false );
		if ( bSelectedFilterExists )
		{
			int nItemsCount = m_FoldersList.GetCount();
			for ( int nItemIndex = 0; nItemIndex < nItemsCount; ++nItemIndex )
			{
				if ( m_FoldersList.GetCheck( nItemIndex ) > 0 )
				{
					pWnd->EnableWindow( true );
					break;
				}
			}
		}
	}

	if ( pWnd = GetDlgItem( IDC_CF_REMOVE_CONDITION_BUTTON ) )
	{
		int nSelCount =  m_ConditionsList.GetSelCount();
		pWnd->EnableWindow( bSelectedFilterExists && ( m_ConditionsList.GetCurSel() >= 0 ) );
	}
	if ( pWnd = GetDlgItem( IDOK ) )
	{
		pWnd->EnableWindow( ( m_FiltersList.GetItemCount() > 0 ) );
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnOK() 
{
	for ( int nColumnIndex = 0; nColumnIndex < FILTERS_COLUMN_COUNT; ++nColumnIndex )
	{
		resizeDialogOptions.nParameters[nColumnIndex + FILTERS_COLUMN_START] = m_FiltersList.GetColumnWidth( nColumnIndex );
	}

	CResizeDialog::OnOK();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnCancel() 
{
	for ( int nColumnIndex = 0; nColumnIndex < FILTERS_COLUMN_COUNT; ++nColumnIndex )
	{
		resizeDialogOptions.nParameters[nColumnIndex + FILTERS_COLUMN_START] = m_FiltersList.GetColumnWidth( nColumnIndex );
	}

	CResizeDialog::OnCancel();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CCreateFilterDialog::OnColumnclickFiltersList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	NI_ASSERT_T( ( pNMListView->iSubItem >= 0 ) && ( pNMListView->iSubItem < FILTERS_COLUMN_COUNT ),
							 NStr::Format( _T( "Invalid sort parameter: %d (0...%d)" ), pNMListView->iSubItem, FILTERS_COLUMN_COUNT - 1 ) );
	
	nSortColumn = pNMListView->iSubItem;
	int nItemCount = m_FiltersList.GetItemCount();
	if ( nItemCount > 0 )
	{
		for ( int nItemIndex = 0; nItemIndex < nItemCount; ++nItemIndex )
		{
			m_FiltersList.SetItemData( nItemIndex, nItemIndex );	
		}
		m_FiltersList.SortItems( FiltersCompareFunc, reinterpret_cast<LPARAM>( this ) );
	}
	bFiltersSortParam[nSortColumn] = !bFiltersSortParam[nSortColumn];
	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnRclickFiltersList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CMenu filtersMenu;
	filtersMenu.LoadMenu( IDM_CF_POPUP_MENUS );
	CMenu *pMenu = filtersMenu.GetSubMenu( 0 );
	if ( pMenu )
	{
		if ( CWnd* pWnd = GetDlgItem( IDC_CF_ADD_FILTER_BUTTON ) )
		{
			pMenu->EnableMenuItem( IDC_CF_ADD_FILTER_MENU, pWnd->IsWindowEnabled() ? MF_ENABLED : MF_GRAYED );
		}
		if ( CWnd* pWnd = GetDlgItem( IDC_CF_DELETE_FILTER_BUTTON ) )
		{
			pMenu->EnableMenuItem( IDC_CF_DELETE_FILTER_MENU, pWnd->IsWindowEnabled() ? MF_ENABLED : MF_GRAYED );
		}
		if ( CWnd* pWnd = GetDlgItem( IDC_CF_RENAME_FILTER_BUTTON ) )
		{
			pMenu->EnableMenuItem( IDC_CF_RENAME_FILTER_MENU, pWnd->IsWindowEnabled() ? MF_ENABLED : MF_GRAYED );
		}

		CPoint point;
		GetCursorPos( &point );
		pMenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, this, 0 );
	}
	filtersMenu.DestroyMenu();
	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnItemchangedFiltersList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if ( !bCreateControls )
	{
		LoadFilterToControls();
		UpdateControls();
	}
	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnSelchangeConditionsList() 
{
	if ( !bCreateControls )
	{
		UpdateControls();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnSelchangeAllFoldersList() 
{
	if ( !bCreateControls )
	{
		TSimpleFilterItem simpleFilterItem;

		int nItemsCount = m_FoldersList.GetCount();
		for ( int nItemIndex = 0; nItemIndex < nItemsCount; ++nItemIndex )
		{
			if ( m_FoldersList.GetCheck( nItemIndex ) > 0 )
			{
				CString strItemText;
				m_FoldersList.GetText( nItemIndex, strItemText );
				simpleFilterItem.push_back( std::string( LPCTSTR( strItemText ) ) );
			}
		}
		if ( lastSimpleFilterItem != simpleFilterItem )
		{
			FillFolders( simpleFilterItem );
		}
		
		UpdateControls();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnAddConditionButton() 
{
	int nSelectedFilter = m_FiltersList.GetNextItem( -1, LVNI_SELECTED );
	if ( nSelectedFilter >= 0 )
	{
		std::string szFilterName = m_FiltersList.GetItemText( nSelectedFilter, 0 );
		TFilterHashMap::iterator filtersIterator = filters.find( szFilterName );
		if ( filtersIterator != filters.end() )
		{
			filtersIterator->second.filter.push_back( TSimpleFilterItem() );
			TSimpleFilterItem &rSimpleFilterItem = filtersIterator->second.filter.back();

			int nItemsCount = m_FoldersList.GetCount();
			for ( int nItemIndex = 0; nItemIndex < nItemsCount; ++nItemIndex )
			{
				if ( m_FoldersList.GetCheck( nItemIndex ) > 0 )
				{
					CString strItemText;
					m_FoldersList.GetText( nItemIndex, strItemText );
					rSimpleFilterItem.push_back( std::string( LPCTSTR( strItemText ) ) );
				}
			}
			LoadFilterToControls();
			FillFolders( TSimpleFilterItem() );
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnRemoveConditionButton() 
{
	int nSelectedFilter = m_FiltersList.GetNextItem( -1, LVNI_SELECTED );
	if ( nSelectedFilter >= 0 )
	{
		std::string szFilterName = m_FiltersList.GetItemText( nSelectedFilter, 0 );
		TFilterHashMap::iterator filtersIterator = filters.find( szFilterName );
		if ( filtersIterator != filters.end() )
		{
			int nItemIndex = m_ConditionsList.GetCurSel();
			if ( nItemIndex >= 0 )
			{
				int nFilterElementIndex = m_ConditionsList.GetItemData( nItemIndex );
				if ( ( nFilterElementIndex >= 0 ) && ( nFilterElementIndex < filtersIterator->second.filter.size() ) )
				{
					int nIndex = 0;
					TSimpleFilter::iterator filterIterator = filtersIterator->second.filter.begin();
					while ( nIndex != nFilterElementIndex )
					{
						++filterIterator;
						++nIndex;
						if ( filterIterator == filtersIterator->second.filter.end() )
						{
							break;
						}
					}
					if ( filterIterator != filtersIterator->second.filter.end() )
					{
						filtersIterator->second.filter.erase( filterIterator ); 	
					}
				}
			}
			
			LoadFilterToControls();
			FillFolders( TSimpleFilterItem() );
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::GetUniqueFilterName( const std::string &rszNewFilterName, std::string *pszFullNewFilterName )
{	
	if ( pszFullNewFilterName )
	{
		( *pszFullNewFilterName ) = rszNewFilterName;
		TFilterHashMap::const_iterator filtersIterator = filters.find( *pszFullNewFilterName );
		int nNewFilterIndex = 0;
		while ( filtersIterator != filters.end() )
		{
			( *pszFullNewFilterName ) = rszNewFilterName + NStr::Format( _T( "_%d" ), nNewFilterIndex );
			filtersIterator = filters.find( *pszFullNewFilterName  );
			++nNewFilterIndex;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnAddFilterButton()
{
	CCreateFilterNameDialog createFilterNameDialog;
	if ( createFilterNameDialog.DoModal() == IDOK )
	{
		std::string szNewFilterName = std::string( LPCTSTR( createFilterNameDialog.m_Name ) );
		
		std::string szFullNewFilterName;
		GetUniqueFilterName( szNewFilterName, &szFullNewFilterName );

		SSimpleFilter filter;
		filters[szFullNewFilterName] = filter;

		szCurrentFilter = szFullNewFilterName;
		FillFilters();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnAddFilterMenu() 
{
	OnAddFilterButton();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnDeleteFilterButton() 
{
	int nSelectedFilter = m_FiltersList.GetNextItem( -1, LVNI_SELECTED );
	if ( nSelectedFilter >= 0 )
	{
		std::string szFilterName = m_FiltersList.GetItemText( nSelectedFilter, 0 );
		TFilterHashMap::iterator filtersIterator = filters.find( szFilterName );
		
		filters.erase( filtersIterator );
		
		szCurrentFilter.clear();
		FillFilters();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnDeleteFilterMenu() 
{
	OnDeleteFilterButton();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnDblclkAllFoldersList() 
{
	OnSelchangeAllFoldersList();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnRenameFilterButton() 
{
	int nSelectedFilter = m_FiltersList.GetNextItem( -1, LVNI_SELECTED );
	if ( nSelectedFilter >= 0 )
	{
		std::string szFilterName = m_FiltersList.GetItemText( nSelectedFilter, 0 );
		TFilterHashMap::iterator filtersIterator = filters.find( szFilterName );
		if ( filtersIterator != filters.end() )
		{
			SSimpleFilter filter = filtersIterator->second;
			
			filters.erase( filtersIterator );
			
			CCreateFilterNameDialog createFilterNameDialog;
			createFilterNameDialog.m_Name = szFilterName.c_str();
			if ( createFilterNameDialog.DoModal() == IDOK )
			{
				szFilterName = std::string( LPCTSTR( createFilterNameDialog.m_Name ) );
			}

			std::string szFullFilterName;
			GetUniqueFilterName( szFilterName, &szFullFilterName );

			filters[szFullFilterName] = filter;

			szCurrentFilter = szFullFilterName;
			FillFilters();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnRenameFilterMenu() 
{
	OnRenameFilterButton();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnDblclkFiltersList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if ( CWnd* pWnd = GetDlgItem( IDC_CF_RENAME_FILTER_BUTTON ) )
	{
		if ( pWnd->IsWindowEnabled() )
		{
			OnRenameFilterButton();
		}
	}
	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnChangedState() 
{
	if ( !bCreateControls )
	{
		int nSelectedFilter = m_FiltersList.GetNextItem( -1, LVNI_SELECTED );
		if ( nSelectedFilter >= 0 )
		{
			std::string szFilterName = m_FiltersList.GetItemText( nSelectedFilter, 0 );
			TFilterHashMap::iterator filtersIterator = filters.find( szFilterName );
			if ( filtersIterator != filters.end() )
			{
				filtersIterator->second.bTranslated = ( IsDlgButtonChecked( IDC_CF_CHANGED_CHECKBOX ) > 0 );
				LoadFilterToControls();
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnState0() 
{
	if ( !bCreateControls )
	{
		int nSelectedFilter = m_FiltersList.GetNextItem( -1, LVNI_SELECTED );
		if ( nSelectedFilter >= 0 )
		{
			std::string szFilterName = m_FiltersList.GetItemText( nSelectedFilter, 0 );
			TFilterHashMap::iterator filtersIterator = filters.find( szFilterName );
			if ( filtersIterator != filters.end() )
			{
				filtersIterator->second.states[SELKTextProperty::STATE_NOT_TRANSLATED] = IsDlgButtonChecked( IDC_CF_STATE_0 );
				LoadFilterToControls();
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnState1() 
{
	if ( !bCreateControls )
	{
		int nSelectedFilter = m_FiltersList.GetNextItem( -1, LVNI_SELECTED );
		if ( nSelectedFilter >= 0 )
		{
			std::string szFilterName = m_FiltersList.GetItemText( nSelectedFilter, 0 );
			TFilterHashMap::iterator filtersIterator = filters.find( szFilterName );
			if ( filtersIterator != filters.end() )
			{
				filtersIterator->second.states[SELKTextProperty::STATE_OUTDATED] = IsDlgButtonChecked( IDC_CF_STATE_1 );
				LoadFilterToControls();
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnState2() 
{
	if ( !bCreateControls )
	{
		int nSelectedFilter = m_FiltersList.GetNextItem( -1, LVNI_SELECTED );
		if ( nSelectedFilter >= 0 )
		{
			std::string szFilterName = m_FiltersList.GetItemText( nSelectedFilter, 0 );
			TFilterHashMap::iterator filtersIterator = filters.find( szFilterName );
			if ( filtersIterator != filters.end() )
			{
				filtersIterator->second.states[SELKTextProperty::STATE_TRANSLATED] = IsDlgButtonChecked( IDC_CF_STATE_2 );
				LoadFilterToControls();
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCreateFilterDialog::OnState3() 
{
	if ( !bCreateControls )
	{
		int nSelectedFilter = m_FiltersList.GetNextItem( -1, LVNI_SELECTED );
		if ( nSelectedFilter >= 0 )
		{
			std::string szFilterName = m_FiltersList.GetItemText( nSelectedFilter, 0 );
			TFilterHashMap::iterator filtersIterator = filters.find( szFilterName );
			if ( filtersIterator != filters.end() )
			{
				filtersIterator->second.states[SELKTextProperty::STATE_APPROVED] = IsDlgButtonChecked( IDC_CF_STATE_3 );
				LoadFilterToControls();
			}
		}
	}
}
