#if !defined(__AIMapSoundInfo__MANIPULATOR__)
#define __AIMapSoundInfo__MANIPULATOR__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Scene\Scene.h"
#include "..\Formats\FmtMap.h"
#include "..\Misc\Manipulator.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CTemplateEditorFrame;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//коллекционер обьектов
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CMSHelper
{
	static const char DEFAULT_SOUND_NAME[];
	bool isInitialized;

public:
	std::list<std::string> soundsList;

	CMSHelper() : isInitialized( false ) {}
	
	bool IsInitialized(){ return isInitialized; }
	void Initialize();
};

class CMutableMapSoundInfo;
typedef std::vector<CMutableMapSoundInfo> TMutableMapSoundInfoVector;

class CMutableMapSoundInfo : public CMapSoundInfo
{
	//Внутренние константы
	
	//Перевод из предка в потомок и обратно
	void MutateTo() {}
	void MutateFrom() {}

public:	
	friend class CMapSoundInfoManipulator;

	//Внутренние переменные
	CPtr<IVisObj> pVisObj;

	//Конструкторы и операторы преобразования
	CMutableMapSoundInfo() { MutateTo(); }
	CMutableMapSoundInfo( const CMapSoundInfo &rMapSoundInfo )
		:	CMapSoundInfo( rMapSoundInfo ) { MutateTo(); }
	CMapSoundInfo& Mutate() { MutateFrom(); return *this; }

	//Манипулятор
	virtual IManipulator* GetManipulator();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CMapSoundInfoManipulator : public CManipulator
{
	OBJECT_MINIMAL_METHODS( CMapSoundInfoManipulator );
	CMutableMapSoundInfo *pMutableObject;

public:
	CMapSoundInfoManipulator();

	void SetName( const variant_t &value );		
	void GetName( variant_t *pValue, int nIndex = -1 );	

	inline void SetObject( CMutableMapSoundInfo *_pMutableObject ) { pMutableObject = _pMutableObject; }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // !defined(__AIMapSoundInfo__MANIPULATOR__)
