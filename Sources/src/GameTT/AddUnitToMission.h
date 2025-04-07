#ifndef __IM_ADD_UNIT_TO_MISSION_H__
#define __IM_ADD_UNIT_TO_MISSION_H__
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "InterMission.h"
#include "iMission.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CInterfaceAddUnitToMission : public CInterfaceInterMission
{
	OBJECT_NORMAL_METHODS( CInterfaceAddUnitToMission );
	// input
	NInput::CCommandRegistrator commandMsgs;
	//
	virtual bool STDCALL ProcessMessage( const SGameMessage &msg );
	// disable explicit destruction
	virtual ~CInterfaceAddUnitToMission();
	CInterfaceAddUnitToMission();
	
	void UpdateUnitsList();
	void SelectItem();
	void DisplaySlotsFromST();
	void EnableItem( IUIContainer *pItem, bool bEnable );
	
	//������ ��������, �������� ����� AI �������
	//���������� ������ �������� ������� ������, ����������� � ������, ��� -1, ���� ���� �� ����.
	static std::vector< std::vector<int> > m_missionSlots;
public:
	virtual bool STDCALL Init();
	virtual void STDCALL StartInterface();

	//��� ������� ��������� ����� �� ����� � ��������� ������� ����������� ������� ������ ������
	//���������� ����� ������������ � ScenarioTracker
	static bool AddDefaultSlotsToST();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CICAddUnitToMission : public CInterfaceCommandBase<IInterfaceBase, MISSION_INTERFACE_ADD_UNIT_TO_MISSION>
{
	OBJECT_NORMAL_METHODS( CICAddUnitToMission );
	
	virtual void PreCreate( IMainLoop *pML ) {}
	virtual void PostCreate( IMainLoop *pML, IInterfaceBase *pInterface ) { pML->PushInterface( pInterface ); }
	//
	CICAddUnitToMission() {  }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif		//__IM_ADD_UNIT_TO_MISSION_H__
