#ifndef __UICOMPLEXSCROLL_H__
#define __UICOMPLEXSCROLL_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "UIBasic.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CUIComplexScroll : public CMultipleWindow
{
	DECLARE_SERIALIZE;
	
	class CUIScrollBar *pScrollBar;				//���������������� �� ����� �������� � ������������ ��� ��������� ������� � �����������
	struct IUIDialog * pItemContainer;

	int nCurrentPosToAdd;									// position to add new element to

	int nScrollBarWidth;
	int m_nY;												//����� �� Y �� ������ ������, ����� ����� ��������������
	int nLeftSpace, nRightSpace;		//������ ������ �������������� ����� �� ���� � ������ �� ����������
	int nTopSpace, nBottomSpace;		//������ ������ �������������� ������ � �����
	bool bScrollBarAlwaysVisible;
	int nVSubSpace;									// subspace between elements

	void UpdateScrollBar( const int nMaxValue, const int nCurValue );
	void GetBorderRect( CTRect<float> *pBorderRect ) const;
	void RepositionScrollbar();
	void UpdatePosition();
	
public:
	CUIComplexScroll();
	~CUIComplexScroll() {}

	virtual int STDCALL operator&( IDataTree &ss );
	virtual void STDCALL Reposition( const CTRect<float> &rcParent );
	virtual bool STDCALL ProcessMessage( const SUIMessage &msg );

	//mouse wheel
	virtual bool STDCALL OnMouseWheel( const CVec2 &vPos, EMouseState mouseState, float fDelta ) = 0;

	// drawing
	virtual void STDCALL Draw( IGFX *pGFX );
	virtual void STDCALL Visit( interface ISceneVisitor *pVisitor );

	// adding item window
	virtual void STDCALL AddItem( IUIElement *pElement, const bool bResizeToFitText );
	virtual void STDCALL Clear();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CUIComplexScrollBridge : public IUIComplexScroll, public CUIComplexScroll
{
	OBJECT_NORMAL_METHODS( CUIComplexScrollBridge );
	DECLARE_SUPER( CUIComplexScroll );
	DEFINE_UICONTAINER_BRIDGE;
	
	virtual void STDCALL AddItem( IUIElement *pElement, const bool bResizeToFitText ) { CSuper::AddItem( pElement, bResizeToFitText ); }
	virtual void STDCALL Clear() { CSuper::Clear(); }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __UICOMPLEXSCROLL_H__
