/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __WND_UTILS__
#define __WND_UTILS__
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>

inline void ListView_AddColumn( HWND hwnd, std::string strCaption, int nWidth )
{
	LV_COLUMN  Column;
	memset( &Column, 0, sizeof( LV_COLUMN) );

	Column.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	Column.pszText = const_cast<char*>(strCaption.c_str());
	Column.cx = nWidth;
	//Column.iSubItem = nNumber;

	ListView_InsertColumn( hwnd, 1000, &Column );
}

inline int ListView_AddItem( HWND hwnd, std::string strText, LPARAM lParam, int nItem = 0 )
{
	LVITEM Item;
	memset( &Item, 0, sizeof(Item) );
	Item.mask = LVIF_PARAM | LVIF_TEXT;
	Item.iItem = nItem;
	Item.lParam = lParam;
	Item.pszText = const_cast<char*>(strText.c_str());
	Item.cchTextMax = strText.size();
	return ListView_InsertItem( hwnd, &Item );
}

#endif //__WND_UTILS__
