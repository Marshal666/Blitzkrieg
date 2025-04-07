#ifndef __UI_CONSOLE_H__
#define __UI_CONSOLE_H__
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "UIBasic.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CUIConsole : public CSimpleWindow
{
	DECLARE_SERIALIZE;
public:
	struct SColorString
	{
		DECLARE_SERIALIZE;
	public:
		std::wstring szString;
		DWORD dwColor;
		
		SColorString() : dwColor( 0xffffffff ) {  }
		SColorString( const wchar_t *pszStr, DWORD col ) : szString( pszStr ), dwColor( col ) {  }
		SColorString( const std::wstring &szStr, DWORD col ) : szString( szStr ), dwColor( col ) {  }
		int operator&( IDataTree &ss );
	};
private:
	typedef std::vector<std::wstring> CVectorOfStrings;
	typedef std::vector<SColorString> CVectorOfColorStrings;
	CVectorOfColorStrings vectorOfStrings;		//все строчки в консоли
	CVectorOfStrings vectorOfCommands;				//выполненные команды в консоли, для выбора предыдущих команд по стрелочкам вверх/вниз
	
	DWORD dwLastOpenTime;				//время когда началась анимация открытия консоли
	DWORD dwLastCloseTime;			//время когда началась анимация закрытия консоли
	bool bAnimation;						//флаг того, что происходит анимация, полезен для скорости
	int nCursorPos;							//позиция курсора в текущей редактируемой строке
	int nBeginString;						//начальная отображаемая строка из списка строк
															//0 считается самой свежей строчкой
	int nBeginCommand;					//текущая команда из лога команд
	DWORD m_dwColor;
	bool bShowCursor;						//видимый ли курсор в текущий момент
	DWORD dwLastCursorAnimatedTime;	//для анимации курсора
	
	std::wstring szEditString;	//текущая редактируемая строка
	//для обработки команд
	typedef std::list< CPtr<IConsoleCommandHandler> > CCommandsList;
	CCommandsList commandsChain;
	Script consoleScript;				// console script

	//это дело вызывается после считывания новой комманды из буфера
	void ParseCommand( const std::wstring &szCommand );
	void InitConsoleScript();
	bool RunScriptFile( const std::string &szScriptFileName );
	typedef std::hash_map< std::string, int > CConsoleFunctions;
	CConsoleFunctions consoleFunctions;

public:
	CUIConsole();
	~CUIConsole() {}

	// serializing...
	virtual int STDCALL operator&( IDataTree &ss );

	virtual bool STDCALL IsVisible();
	virtual void STDCALL ShowWindow( int _nCmdShow );
	virtual bool STDCALL IsAnimationStage() { return bAnimation; }
	
	//консоля всегда занимает всю ширину экрана
	virtual void STDCALL Reposition( const CTRect<float> &rcParent );
	//это нужно для анимации консоли, свертывания и развертывания
	virtual bool STDCALL Update( const NTimer::STime &currTime );
	//кроме рисования окошка, здесь должны отображаться строчки
	virtual void STDCALL Draw( interface IGFX *pGFX );
	virtual void STDCALL Visit( interface ISceneVisitor *pVisitor );

	virtual bool STDCALL OnChar( int nAsciiCode, int nVirtualKey, bool bPressed, DWORD keyState );
	
	virtual void STDCALL RegisterCommand( IConsoleCommandHandler *pHandler );
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CUIConsoleBridge : public IUIConsole, public CUIConsole
{
	OBJECT_NORMAL_METHODS( CUIConsoleBridge );
	DECLARE_SUPER( CUIConsole );
	DEFINE_UIELEMENT_BRIDGE;
	
	virtual void STDCALL RegisterCommand( IConsoleCommandHandler *pHandler ) { CSuper::RegisterCommand( pHandler ); }
	virtual bool STDCALL IsAnimationStage() { return CSuper::IsAnimationStage(); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif		//__UI_CONSOLE_H__
