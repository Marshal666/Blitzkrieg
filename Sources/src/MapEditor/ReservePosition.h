#if !defined(__ReservePosition__MANIPULATOR__)
#define __ReservePosition__MANIPULATOR__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Formats\FmtMap.h"
#include "..\Misc\Manipulator.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CTemplateEditorFrame;

class CMutableReservePosition;
typedef std::list<CMutableReservePosition> TMutableReservePositionList;

class CMutableReservePosition : public SBattlePosition
{
public:
	//���������� ����
	SMapObject* pArtilleryObject;
	SMapObject* pTruckObject;
	bool flag;
	//virtual IManipulator* GetManipulator();
	//void Update( CTemplateEditorFrame *pFrame );
	//static void Update( TMutableAIStartCommandList *pCommands, CTemplateEditorFrame *pFrame );

	//�����������
	CMutableReservePosition() : pArtilleryObject( 0 ), pTruckObject( 0 ), flag( false ) {}
	//��������������
	CMutableReservePosition( const SBattlePosition &rReservePosition )
		: pArtilleryObject( 0 ), pTruckObject( 0 ), flag( false ),
			SBattlePosition( rReservePosition ) {}
	operator SBattlePosition() const
	{
		return SBattlePosition( nArtilleryLinkID, nTruckLinkID, vPos );
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // !defined(__ReservePosition__MANIPULATOR__)
