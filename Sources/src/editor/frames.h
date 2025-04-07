#ifndef __FRAMES_H__
#define __FRAMES_H__

#include <Mmsystem.h>
#include "..\Misc\FileUtils.h"
#include "ParentFrame.h"
#include "MyOpenFileDialog.h"

using std::string;
using std::vector;

class CETreeCtrl;
class CPropView;

//Вспомогательная функция, вычисляет относительный путь
//Первый параметр - полный путь, относительно которого вычисляется результат
//Второй параметр - полный путь, который надо сделать относительным
bool MakeRelativePath( const char *pszDirectoryName, const char *pszFileName, string &szResult );

//Вычисляет относительный путь только для поддиректорий, иначе возвращает false
bool MakeSubRelativePath( const char *pszDirectoryName, const char *pszFileName, string &szResult );

//Возвращает имя директории по полному имени файла
string GetDirectory( const char *pszFileName );

//Определяет, является ли данный путь полным или относительным
bool IsRelatedPath( const char *pszFileName );

//Из полного имени и относительного создает полное имя
//pszFullName это имя директории, обязано заканчиваться на '\\'
bool MakeFullPath( const char *pszFullDirName, const char *pszRelName, string &szResult );

//вспомогательная функция для всех frames
void ShowFirstChildElementInPropertyView( CETreeCtrl *pTree, CPropView *pOIDockBar );

//Получить время изменения для файла
FILETIME GetFileChangeTime( const char *pszFileName );
FILETIME GetTextureFileChangeTime( const char *pszFileName );
bool operator > ( FILETIME a, FILETIME b );
bool operator < ( FILETIME a, FILETIME b );
bool operator == ( FILETIME a, FILETIME b );

//copy file and change it's modification time to the current system time
BOOL MyCopyFile( const char *pszSrc, const char *pszDest );
void MyCopyDir( const string szSrc, const string szDest );

inline DWORD COLORREF2GFXColor( COLORREF color )
{
	return 0xff000000 | ( (color >> 16) & 0xff) | ( color & 0x0000ff00 ) | ( (color & 0xff) << 16 );
}

void SetDefaultCamera();
void SetHorizontalCamera();

class CGameWnd;
class CFrameManager
{
public:
	enum EFrameType
	{
		E_UNKNOWN_FRAME,
		E_GUI_FRAME,
		E_ANIMATION_FRAME,
		E_SPRITE_FRAME,
		E_EFFECT_FRAME,
		E_OBJECT_FRAME,
		E_MESH_FRAME,
		E_WEAPON_FRAME,
		E_BUILDING_FRAME,
		E_TILESET_FRAME,
		E_FENCE_FRAME,
		E_PARTICLE_FRAME,
		E_TRENCH_FRAME,
		E_SQUAD_FRAME,
		E_MINE_FRAME,
		E_BRIDGE_FRAME,
		E_MISSION_FRAME,
		E_CHAPTER_FRAME,
		E_CAMPAIGN_FRAME,
		E_3DROAD_FRAME,
		E_3DRIVER_FRAME,
		E_MEDAL_FRAME,
	};

	std::vector<CParentFrame *> frames;

private:
	EFrameType activeFrameType;
	CParentFrame *pActiveFrame;
	CGameWnd *pGameWnd;

public:
	CFrameManager();
	~CFrameManager() {}
	
	CParentFrame *GetActiveWnd() { return pActiveFrame; }
	void SetGameWnd( CGameWnd *pWnd ) { pGameWnd = pWnd; }
	void AddFrame( CParentFrame *pFrame );

	EFrameType GetActiveFrameType() { return activeFrameType; }
	void SetActiveFrame( CParentFrame *pNewActiveFrame );
	CParentFrame *GetFrame( int nID );
	CParentFrame *GetActiveFrame() { return GetFrame( GetActiveFrameType() ); }
	CGameWnd* GetGameWnd() { return pGameWnd; }
	
	CParentFrame *ActivateFrameByExtension( const char *pszExtension );
};

extern CFrameManager g_frameManager;

#endif		//__FRAMES_H__
