#ifndef __SPRITE_TREE_ITEM_H__
#define __SPRITE_TREE_ITEM_H__

#include "TreeItem.h"
#include "ThumbList.h"

class CSpriteTreeRootItem : public CTreeItem
{
	OBJECT_NORMAL_METHODS( CSpriteTreeRootItem );
public:
	CSpriteTreeRootItem() { bStaticElements = true; nItemType = E_SPRITE_ROOT_ITEM; InitDefaultValues(); }
	~CSpriteTreeRootItem() {}
	
	virtual void InitDefaultValues();
	void ComposeAnimations( const char *pszProjectFileName, const char *pszResultingDir, bool bSetCycledFlag );
	FILETIME FindMaximalSourceTime( const char *pszProjectFileName );
};

class CSpritePropsItem : public CTreeItem
{
	OBJECT_NORMAL_METHODS( CSpritePropsItem );
public:
	CSpritePropsItem() { nItemType = E_SPRITE_PROPS_ITEM; InitDefaultValues(); nImageIndex = 3; }
	~CSpritePropsItem() {};

	virtual void InitDefaultValues();

	virtual void MyLButtonClick();
	virtual void MyKeyDown( int nChar );
};

class CSpritesItem : public CTreeItem
{
public:
	OBJECT_NORMAL_METHODS( CSpritesItem );

private:
	SThumbItems m_allThumbItems;		//��� items ������������ � AllDirThumbList
	SThumbItems m_selThumbItems;		//��� items ������������ � SelectedDirThumbList
	CImageList imageList;						//���� image list ��� ����� ThumbList
	bool bLoaded;										//���� ���� ��� �������� items ������ � ������ ����� ������������ �������� ����� � ���������� ��� ������ �� frame

public:
	CSpritesItem() {
		nItemType = E_SPRITES_ITEM;
		InitDefaultValues();
		bComplexItem = true;
		nImageIndex = 7;
		bLoaded = false;
		imageList.Create(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, ILC_COLOR24, 0, 1);
	}
	~CSpritesItem() {};

	SThumbItems* GetAllThumbItems() { return &m_allThumbItems; }
	SThumbItems* GetSelThumbItems() { return &m_selThumbItems; }
	CImageList*  GetImageList() { return &imageList; }

	virtual bool CopyItemTo( CTreeItem *pTo );

	//��������� ���������� ����������
	const char *GetDirName();
	int GetFrameTime();
	CVec2 GetPosition();

	void SetLoadedFlag( bool bState ) { bLoaded = bState; }
	bool GetLoadedFlag() { return bLoaded; }
	virtual void InsertChildItems();					//���������� ����� �������� ���� ����������� ��� ��������� �� � ������

	virtual void InitDefaultValues();
	virtual void UpdateItemValue( int nItemId, const CVariant &value );
	virtual void MyLButtonClick();
};


#endif		//__SPRITE_TREE_ITEM_H__
