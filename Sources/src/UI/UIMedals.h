#ifndef __UI_MEDALS_H__
#define __UI_MEDALS_H__
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "UIBasic.h"
#include "UISlider.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CUIMedals : public CMultipleWindow
{
	DECLARE_SERIALIZE;
	CUIScrollBar *pScrollBar;				//���������������� �� ����� �������� � ������������ ��� ��������� ������� � �����������
	int nSpace;											//������ ������ ����� �� �������� � ������ �� ����������
	int nVTextSpace;								//������ ������ ������ �� ������
	int nHSubSpace;									//������ ����� ������ �� ������ �� �����������
	int nVSubSpace;									//������ ����� ������ �� ������ �� ���������
	int nNextPosX, nNextPosY;				//������� ��������� ������
	int nMedalsCount;								//����� �������
	std::vector< CTRect<float> > medalMaps;		//��� ���������� ���������� ��������� �������
	
public:
	CUIMedals() : nSpace( 4 ), nHSubSpace( 10 ), nVSubSpace( 10 ), nMedalsCount( 0 ),
		nNextPosX( 0 ), nNextPosY( 0 ), nVTextSpace( 5 ) {}
	~CUIMedals() {}
	
	// serializing...
	virtual int STDCALL operator&( IDataTree &ss );
	virtual void STDCALL Reposition( const CTRect<float> &rcParent );
	
	virtual bool STDCALL ProcessMessage( const SUIMessage &msg );
	
	// drawing
	virtual void STDCALL Draw( IGFX *pGFX );
	virtual void STDCALL Visit( interface ISceneVisitor *pVisitor );
	
	virtual void STDCALL ShowWindow( int _nCmdShow );
	
	void ClearMedals();
	void AddMedal( IGFXTexture *pTexture, const CTRect<float> &mapImageRect, const WORD *pszMedalsName );
	void UpdateMedals();
	
private:
	void ComputeHPositions();					//����������� ���� ��� ��� ���������� �������, ����� �������������� ������ �� ���������
	void UpdatePositions();						//���������� ��� ���������� ������� ScrollBar
	void UpdateScrollbar();						//���������� ����� ���������� ���� objectives ��� ���������� ScrollBar
	void InitMaps();									//��� ������������� ���������� ���������
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CUIMedalsBridge : public IUIContainer, public CUIMedals
{
	OBJECT_NORMAL_METHODS( CUIMedalsBridge );
	DECLARE_SUPER( CUIMedals );
	DEFINE_UICONTAINER_BRIDGE;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif		//__UI_MEDALS_H__
