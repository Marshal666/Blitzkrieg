#ifndef __LOCALIZATION_H__
#define __LOCALIZATION_H__

#include "TreeItem.h"

class CLocalizationItem : public CTreeItem
{
	OBJECT_NORMAL_METHODS( CLocalizationItem );
public:
	CLocalizationItem() { nItemType = E_LOCALIZATION_ITEM; nImageIndex = 1; InitDefaultValues(); }
	~CLocalizationItem() {};
	
	const char *GetLocalizationName() { return values[0].value; }
	const char *GetLocalizationDesc() { return values[1].value; }
	const char *GetLocalizationStats() { return values[2].value; }
	
	virtual void InitDefaultValues();
	void UpdateItemValue( int nItemId, const CVariant &value );
};

#endif		//__LOCALIZATION_H__
