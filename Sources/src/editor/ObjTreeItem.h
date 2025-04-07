#ifndef __OBJECT_TREE_ITEM_H__
#define __OBJECT_TREE_ITEM_H__

#include "TreeItem.h"

class CObjectTreeRootItem : public CTreeItem
{
	OBJECT_NORMAL_METHODS( CObjectTreeRootItem );
public:
	CObjectTreeRootItem() { bStaticElements = true; nItemType = E_OBJECT_ROOT_ITEM; InitDefaultValues(); }
	~CObjectTreeRootItem() {}

	void ComposeAnimations( const char *pszProjectFileName, const char *pszResultingDir, const CVec2 &zeroPos, const CArray2D<BYTE> &pass, const CVec2 &vOrigin );
	FILETIME FindMaximalSourceTime( const char *pszProjectFileName );
	
	virtual void InitDefaultValues();
};

class CObjectCommonPropsItem : public CTreeItem
{
	OBJECT_NORMAL_METHODS( CObjectCommonPropsItem );
public:
	CObjectCommonPropsItem() { nItemType = E_OBJECT_COMMON_PROPS_ITEM; nImageIndex = 0; InitDefaultValues(); }
	~CObjectCommonPropsItem() {};
	
	//Получение внутренних параметров
	int GetHealth() { return values[0].value; }
	int GetArmor() { return values[1].value; }
	int GetSilhouette() { return values[2].value; }
	const char *GetAmbientSound() { return values[3].value; }
	const char *GetCycledSound() { return values[4].value; }

	//Установка
	void SetHealth( int nVal ) { values[0].value = nVal; }
	void SetArmor( int nVal ) { values[1].value = nVal; }
	void SetSilhouette( int nVal ) { values[2].value = nVal; }
	void SetAmbientSound( const char *pszVal ) { values[3].value = pszVal; }
	void SetCycledSound( const char *pszVal ) { values[4].value = pszVal; }
	
	virtual void InitDefaultValues();
};

class CObjectPassesItem : public CTreeItem
{
	OBJECT_NORMAL_METHODS( CObjectPassesItem );
public:
	CObjectPassesItem() { bStaticElements = false; nItemType = E_OBJECT_PASSES_ITEM; nImageIndex = 7; InitDefaultValues(); }
	~CObjectPassesItem() {};
	
	virtual void InitDefaultValues();
	virtual void MyKeyDown( int nChar );
};

class CObjectPassPropsItem : public CTreeItem
{
	OBJECT_NORMAL_METHODS( CObjectPassPropsItem );
public:
	CObjectPassPropsItem() { bStaticElements = true; nItemType = E_OBJECT_PASS_PROPS_ITEM; nImageIndex = 3; InitDefaultValues(); }
	~CObjectPassPropsItem() {};

	int GetPassAIClass();
//	void SetPassAIClass( int nVal );

	virtual void InitDefaultValues();
	virtual void MyKeyDown( int nChar );
	virtual void UpdateItemValue( int nItemId, const CVariant &value );
};

class CObjectGraphicsItem : public CTreeItem
{
	OBJECT_NORMAL_METHODS( CObjectGraphicsItem );
public:
	CObjectGraphicsItem() { bStaticElements = true; nItemType = E_OBJECT_GRAPHICS_ITEM; nImageIndex = 2; InitDefaultValues(); }
	~CObjectGraphicsItem() {};

	virtual void InitDefaultValues();
};

class CObjectGraphicPropsItem : public CTreeItem
{
	OBJECT_NORMAL_METHODS( CObjectGraphicPropsItem );
public:
	CObjectGraphicPropsItem() { bStaticElements = true; /* nItemType = E_OBJECT_GRAPHIC_PROPS_ITEM */; nImageIndex = 3; InitDefaultValues(); }
	~CObjectGraphicPropsItem() {};
	
	//Получение внутренних параметров
	const char *GetFileName() { return values[0].value; }
	const char *GetShadowFileName() { return values[1].value; }
	
	void SetFileName( const char *pszFileName ) { values[0].value = pszFileName; }
	void SetShadowName( const char *pszFileName ) { values[1].value = pszFileName; }
	
	virtual void UpdateItemValue( int nItemId, const CVariant &value );
	virtual void MyLButtonClick();
};

class CObjectGraphic1PropsItem : public CObjectGraphicPropsItem
{
	OBJECT_NORMAL_METHODS( CObjectGraphic1PropsItem );
public:
	CObjectGraphic1PropsItem() { nItemType = E_OBJECT_GRAPHIC1_PROPS_ITEM; InitDefaultValues(); }
	~CObjectGraphic1PropsItem() {};
	
	virtual void InitDefaultValues();
};

class CObjectGraphicW1PropsItem : public CObjectGraphicPropsItem
{
	OBJECT_NORMAL_METHODS( CObjectGraphicW1PropsItem );
public:
	CObjectGraphicW1PropsItem() { nItemType = E_OBJECT_GRAPHICW1_PROPS_ITEM; InitDefaultValues(); }
	~CObjectGraphicW1PropsItem() {};
	
	virtual void InitDefaultValues();
};

class CObjectGraphicA1PropsItem : public CObjectGraphicPropsItem
{
	OBJECT_NORMAL_METHODS( CObjectGraphicA1PropsItem );
public:
	CObjectGraphicA1PropsItem() { nItemType = E_OBJECT_GRAPHICA1_PROPS_ITEM; InitDefaultValues(); }
	~CObjectGraphicA1PropsItem() {};
	
	virtual void InitDefaultValues();
};


class CObjectSpritePropsItem : public CTreeItem
{
	OBJECT_NORMAL_METHODS( CObjectSpritePropsItem );
public:
//	CObjectSpritePropsItem() { nItemType = E_OBJECT_SPRITE_PROPS_ITEM; nImageIndex = 2; InitDefaultValues(); }
	CObjectSpritePropsItem() {}
	~CObjectSpritePropsItem() {};
	
	//Получение внутренних параметров
//	const char *GetFileName() { return values[0].value; }
	
//	virtual void InitDefaultValues();
//	virtual void UpdateItemValue( int nItemId, const CVariant &value );
};

class CObjectShadowPropsItem : public CTreeItem
{
	OBJECT_NORMAL_METHODS( CObjectShadowPropsItem );
public:
//	CObjectShadowPropsItem() { nItemType = E_OBJECT_SHADOW_PROPS_ITEM; nImageIndex = 3; InitDefaultValues(); }
	CObjectShadowPropsItem() {}
	~CObjectShadowPropsItem() {};
	
	//Получение внутренних параметров
//	const char *GetFileName() { return values[0].value; }
	
//	virtual void InitDefaultValues();
//	virtual void UpdateItemValue( int nItemId, const CVariant &value );
};

class CObjectParticlesItem : public CTreeItem
{
	OBJECT_NORMAL_METHODS( CObjectParticlesItem );
public:
//	CObjectParticlesItem() { nItemType = E_OBJECT_PARTICLES_ITEM; nImageIndex = 4; InitDefaultValues(); }
	CObjectParticlesItem() {}
	~CObjectParticlesItem() {};

//	virtual void InitDefaultValues();
};

class CObjectEffectsItem : public CTreeItem
{
	OBJECT_NORMAL_METHODS( CObjectEffectsItem );
public:
	CObjectEffectsItem() { bStaticElements = true; nItemType = E_OBJECT_EFFECTS_ITEM; InitDefaultValues(); nImageIndex = 1; }
	~CObjectEffectsItem() {};
	
	//Получение внутренних параметров
	const char *GetEffectExplosion() { return values[0].value; }
	const char *GetEffectDeath() { return values[1].value; }
	
	void SetEffectExplosion( const char *pszVal ) { values[0].value = pszVal; }
	void SetEffectDeath( const char *pszVal ) { values[1].value = pszVal; }

	virtual void InitDefaultValues();
};

#endif		//__OBJECT_TREE_ITEM_H__
