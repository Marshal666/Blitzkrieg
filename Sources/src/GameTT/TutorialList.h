#ifndef __IM_TUTORIAL_LIST_H__
#define __IM_TUTORIAL_LIST_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "CustomList.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CInterfaceTutorialList : public CInterfaceCustomList
{
	OBJECT_NORMAL_METHODS( CInterfaceTutorialList );
	//
	// disable explicit destruction
	virtual ~CInterfaceTutorialList() {}
protected:
	CInterfaceTutorialList() {}
	
	//������������� ���� �������
	virtual bool FillListItem( IUIListRow *pRow, const std::string &szFullFileName, bool *pSelectedItem = 0 );		//��������� ������� ������� � ������
	virtual bool OnOk( const std::string &szFullFileName );															//������������ ������ ����, ���������� �����
public:
	virtual bool STDCALL Init();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CICTutorialList : public CInterfaceCommandBase<CInterfaceTutorialList, MISSION_INTERFACE_TUTORIAL_LIST>
{
	OBJECT_NORMAL_METHODS( CICTutorialList );
	
	//	virtual void PreCreate( IMainLoop *pML ) { pML->ResetStack(); }
	virtual void PostCreate( IMainLoop *pML, CInterfaceTutorialList *pInterface ) { pML->PushInterface( pInterface ); }
	//
	CICTutorialList() {  }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif		//__IM_TUTORIAL_LIST_H__
