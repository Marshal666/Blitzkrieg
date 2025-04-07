#ifndef __UI_LIST_H__
#define __UI_LIST_H__
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "UIBasic.h"
#include "UISlider.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SColumnProperties
{
	DECLARE_SERIALIZE;
public:
	int nWidth;									//������ �������
	std::string szFileName;			//XML ���� �� �������� ��������� ���������� ��������
	int nSorterType;
	SColumnProperties() : nWidth( 0 ), nSorterType( 0 ) {}
	
	// serializing...
	virtual int STDCALL operator&( IDataTree &ss );
};
typedef std::vector<SColumnProperties> CVectorOfColumnProperties;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SUIListRow : public IUIListRow
{
	OBJECT_NORMAL_METHODS( SUIListRow );
	DECLARE_SERIALIZE;
public:
	typedef std::vector< CPtr<IUIElement> > CUIListSubItems;
	CUIListSubItems subItems;
	int nUserData;
	
	SUIListRow() : nUserData( 0 ) {}
	virtual int STDCALL GetNumberOfElements() const { return subItems.size(); }
	virtual IUIElement* STDCALL GetElement( int nIndex ) const;
	virtual void STDCALL SetUserData( int nData ) { nUserData = nData; }
	virtual int  STDCALL GetUserData() const { return nUserData; }
	
	// serializing...
	//	virtual int STDCALL operator&( IDataTree &ss );
};
typedef std::vector< CPtr<SUIListRow> > CUIListItems;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SUIListHeader : public IUIListRow
{
	OBJECT_NORMAL_METHODS( SUIListHeader );
	DECLARE_SERIALIZE;
public:
	struct SColumn
	{
		CPtr<IUIElement> pElement;
		CPtr<IUIListSorter> pSorter;
		int operator&( IStructureSaver &ss )
		{
			CSaverAccessor saver = &ss;
			saver.Add( 1, &pElement );
			saver.Add( 2, &pSorter );
			return 0;
		}
	};
	typedef std::vector< SColumn > CUIListHeaderItems;
	CUIListHeaderItems subItems;
	int nUserData;

	SUIListHeader() : nUserData( 0 ) {}
	virtual int STDCALL GetNumberOfElements() const { return subItems.size(); }
	virtual IUIElement* STDCALL GetElement( int nIndex ) const;
	virtual void STDCALL SetUserData( int nData ) { nUserData = nData; }
	virtual int  STDCALL GetUserData() const { return nUserData; }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//������ ����� ���� ��� MultipleWindow � ����� ��������� ��������� (������ �������� �� childs)
//�� �� ������� Serialize, �� ��������� ������ childs, �����, ������ ������ � �������� �������� ��������
class CUIList : public CMultipleWindow
{
	DECLARE_SERIALIZE;
	//
	CObj<IUIScrollBar> pScrollBar;				//���������������� �� ����� �������� � ������������ ��� ��������� ������� � �����������

	int nLeftSpace;												//������ item ����� � ������ �� ���� ��������
	int nTopSpace;												//������ item �� ���� header ������ � �� ���� �������� �����
	int nHeaderTopSpace;									//������ header �� ����� ��������
	int nItemHeight;											//������ ������ item
	int nHSubSpace;												//���������� ����� ����� subitems �� �����������
	int nVSubSpace;												//���������� ����� ����� items �� ���������
	bool bLeftScrollBar;
	bool bScrollBarAlwaysVisible;
	int nHeaderSize;											//������ header �� ���������, ���� > 0 �� ���� ���������
	int nScrollBarWidth;
	int nSelection;
	int nSortedHeaderIndex;
	bool bSortAscending;

	SUIListHeader headers;
	CUIListItems listItems;
	CVectorOfColumnProperties columnProperties;

	//��� ��������� Selection
	std::vector<SWindowSubRect> selSubRects;
	CPtr<IGFXTexture> pSelectionTexture;				// ������� ��� - ��������

	void UpdateItemsCoordinates();				//��������� ���������� ���� ���������� item
	void UpdateScrollBarStatus();					//���������� ����� ���������, ����� �� ���������� ScrollBar � ���������� ��� ���������
	void EnsureSelectionVisible();				//����� selection ���� ��������� �������, ���������� ������� ����������.

	IUIElement* CreateComponent( const char *pszFileName );
	CVec2 GetComponentSize( const char *pszFileName );		//���������� ������ ��������
	void InitItemHeight();								//���������� �� ������������, ����� ���������� ������ �������

	//������� ��������� ������ �� ��������� ������� �������
	void NotifySelectionChanged();
	void NotifyDoubleClick( int nItem );
	void RemoveFocusFromItem( int nIndex );
	void MoveSelectionItemUp();

	//������������� ��������� ����������
	void InitSortFunctors();
public:
	CUIList();
	virtual ~CUIList();

	//mouse wheel
	virtual bool STDCALL OnMouseWheel( const CVec2 &vPos, EMouseState mouseState, float fDelta ) = 0;

	virtual void STDCALL Reposition( const CTRect<float> &rcParent );

	virtual bool STDCALL OnChar( int nAsciiCode, int nVirtualKey, bool bPressed, DWORD keyState );
	virtual bool STDCALL ProcessMessage( const SUIMessage &msg );

	// serializing...
	virtual int STDCALL operator&( IDataTree &ss );

	// drawing
	virtual void STDCALL Draw( IGFX *pGFX );
	virtual void STDCALL Visit( interface ISceneVisitor *pVisitor );

	virtual bool STDCALL OnLButtonDblClk( const CVec2 &vPos );
	virtual bool STDCALL OnLButtonDown( const CVec2 &vPos, EMouseState mouseState );
	
	//Public interface
	//Get number of items
	virtual int STDCALL GetNumberOfItems() { return listItems.size(); }
	//Add new line of items
	virtual void STDCALL AddItem( int nData = 0 );			//��������� ����� ������� VectorElements � ����� ������
	//Remove last line of items
	virtual void STDCALL RemoveItem( int nIndex );			//������� ������� �� ����� ������
	//Get line
	virtual IUIListRow* STDCALL GetItem( int nIndex );
	//Get index of item by user data, if no such nID then returns -1
	virtual int STDCALL GetItemByID( int nID );
	//selection operations
	virtual void STDCALL SetSelectionItem( int nSel );
	virtual int STDCALL GetSelectionItem() { return nSelection; }
	virtual void STDCALL InitialUpdate();
	virtual void STDCALL SetSortFunctor( int nColumn, IUIListSorter *pSorter );
	virtual bool STDCALL Sort( int nColumn, const int nSortType = 0 );
	virtual bool STDCALL ReSort();
	
	/*
	int GetNumberOfItems() { return listItems.size(); }
	void SetNumberOfItems( int n );
	*/
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CUIListBridge : public IUIListControl, public CUIList
{
	OBJECT_NORMAL_METHODS( CUIListBridge );
	DECLARE_SUPER( CUIList );
	DEFINE_UICONTAINER_BRIDGE;
	//Get number of items
	virtual int STDCALL GetNumberOfItems() { return CSuper::GetNumberOfItems(); }
	//Add new line of items
	virtual void STDCALL AddItem( int nData = 0 ) { CSuper::AddItem( nData ); }
	//Remove last line of items
	virtual void STDCALL RemoveItem( int nIndex ) { CSuper::RemoveItem( nIndex ); }
	//Get line
	virtual IUIListRow* STDCALL GetItem( int nIndex ) { return CSuper::GetItem( nIndex ); }
	//Get index of item by user data, if no such nID then returns -1
	virtual int STDCALL GetItemByID( int nID ) { return CSuper::GetItemByID( nID ); }
	//selection operations
	virtual void STDCALL SetSelectionItem( int nSel ) { CSuper::SetSelectionItem( nSel ); }
	virtual int STDCALL GetSelectionItem() { return CSuper::GetSelectionItem(); }
	virtual void STDCALL InitialUpdate() { CSuper::InitialUpdate(); }
	virtual void STDCALL SetSortFunctor( int nColumn, IUIListSorter *pSorter ) { CSuper::SetSortFunctor( nColumn, pSorter ); }
	virtual bool STDCALL Sort( int nColumn, const int nSortType ) { return CSuper::Sort( nColumn, nSortType ); }
	virtual bool STDCALL ReSort() { return CSuper::ReSort(); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif //__UI_LIST_H__
