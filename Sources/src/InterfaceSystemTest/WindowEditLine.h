// WindowEditLine.h: interface for the CWindowEditLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOWEDITLINE_H__7531A3C4_0749_49AD_8A73_4500671399F2__INCLUDED_)
#define AFX_WINDOWEDITLINE_H__7531A3C4_0749_49AD_8A73_4500671399F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Window.h"
interface IGFXText;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// for edit text. keep focus if being clicked upon
class CWindowEditLine : public CWindow, public IEditLine
{
	OBJECT_COMPLETE_METHODS(CWindowEditLine)
	DECLARE_SERIALIZE
	DECLARE_CLONABLE_CLASS 

	CNCPtr<IGFXText> pGfxText;								// text to display
	NTimer::STime timeSegment;							// for counting segment times

	int nCursorPos;									//позици€ курсора в текущей редактируемой строке
	bool bShowCursor;								//дл€ мигани€ курсора
	bool bFocused;									//дл€ отображени€ курсора
	int m_nBeginSel;								//начало выделени€
	int m_nEndSel;									//конец выделени€
	DWORD dwSelColor;								//цвет дл€ выделенного текста
	int m_nBeginDragSel;						//начало выделени€ мышкой

	bool bNumericMode;							//ввод€тс€ только числа
	bool bGameSpySymbols;						//ограничение на вводимые символы
	bool bLocalPlayerNameMode;			// local player's name allowed symbols
	bool bFileNameSymbols;					//символы доступные дл€ имени файла
	
	int nMaxLength;									//если эта переменна€ установлена, то включено ограничение на количество символов в тексте
	int nBeginText;		//с этой позиции начинаетс€ отображение текста szFullText
	bool bTextScroll;	//если установлена эта переменна€, то можно вводить текст шире пол€ edit box

	//дл€ скроллинга текста влево и вправо
	//в pGFXText будет хранитьс€ лишь часть отображаемой строки, а в этой переменной полностью текст
	std::wstring wszFullText;
	std::string szFontName;	
	DWORD dwColor;

	int nLeftSpace;
	int nRightSpace;
	int nYOffset;

	// effects sequence names
	std::string szOnReturn;
	std::string szOnEscape;

	//selection under mouse position
	int GetSelection( const int nX );
	// deletes text under selection
	bool DeleteSelection();
	// determines weather the sybmbol is valid according to allowable set
	bool IsValidSymbol( const wchar_t chr ) const;
	void NotifyTextChanged();
	void EnsureCursorVisible();
	bool IsTextInsideEditLine();

	void FillWindowRectEditLine( CTRect<float> *pRect );

	void CreateText();
	// message sink registration
	void RegisteMessageSinks();
	void UnRegisteMessageSinks();
public:
	CWindowEditLine() : timeSegment( 0 ), nCursorPos( 0 ), bShowCursor( 1 ), bFocused( 0 ),
		bTextScroll( 0 ), nMaxLength( -1 ), bGameSpySymbols( 0 ), bFileNameSymbols( 0 ),
		m_nBeginSel( -1 ), m_nEndSel( -1 ), dwSelColor( 0xff2e401b ), m_nBeginDragSel( -1 ),
		nBeginText( 0 ), bNumericMode( 0 ), bLocalPlayerNameMode ( false ) 
	{
	}
	
	virtual void RemoveFocus();
	virtual void STDCALL Init();

	// IWindow
	virtual void STDCALL Visit( interface ISceneVisitor *pVisitor );
	virtual void STDCALL Segment( const NTimer::STime timeDiff );

	virtual void STDCALL OnMouseMove( const CVec2 &_vPos, const int nButton );
	virtual void STDCALL OnButtonDown( const CVec2 &_vPos, const int nButton );
	virtual int STDCALL operator&( IDataTree &ss );
	virtual void STDCALL OnChar( const wchar_t chr );

	// IEditLine
	virtual void STDCALL SetCursor( const int nPos );
	virtual void STDCALL SetSelection( const int nBegin, const int nEnd );
	virtual void STDCALL SetText( const wchar_t *pszText );
	virtual const wchar_t * STDCALL GetText() const { return wszFullText.c_str(); }

	//begin message sinks
	void OnReturn( const struct SGameMessage &msg );
	void OnTab( const struct SGameMessage &msg );
	void OnBack( const struct SGameMessage &msg );
	void OnDelete( const struct SGameMessage &msg );
	void OnLeft( const struct SGameMessage &msg );
	void OnCtrlLeft( const struct SGameMessage &msg );
	void OnRight( const struct SGameMessage &msg );
	void OnCtrlRight( const struct SGameMessage &msg );
	void OnHome( const struct SGameMessage &msg );
	void OnEnd( const struct SGameMessage &msg );
	void OnEscape( const struct SGameMessage &msg );
	//end message sinks
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_WINDOWEDITLINE_H__7531A3C4_0749_49AD_8A73_4500671399F2__INCLUDED_)





















