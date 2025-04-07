#ifndef __SINGLEPLAYERTRANSCEIVER_H__
#define __SINGLEPLAYERTRANSCEIVER_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Transceiver.h"
#include "..\AILogic\AILogic.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
interface ICommandsHistory;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSinglePlayerTransceiver : public CTRefCount<ITransceiver>
{
	OBJECT_SERVICE_METHODS( CSinglePlayerTransceiver );
	DECLARE_SERIALIZE;
	//
	CPtr<IAILogic> pAILogic;							// shortcut to AI logic
	
	// истори€ команд
	CPtr<ICommandsHistory> pCmdsHistory;
	// общий номер сегмента - дл€ истории команд
	long nCommonSegment;
	bool bHistoryPlaying;
public:
	virtual void STDCALL Init( ISingleton *pSingleton, const int nMultiplayerType );
	virtual void STDCALL Done() { }
	virtual void STDCALL PreMissionInit();
	// set lattency for smooth net playing
	virtual void SetLatency( int nSegments ) {  }
	// perform segments for AI
	virtual void STDCALL DoSegments();
	// register group of units to AI
	virtual int STDCALL CommandRegisterGroup( IRefCount **pUnitsBuffer, const int nLen );
	// unregister group
	virtual void STDCALL CommandUnregisterGroup( const WORD wGroup );
	// send command to group of units
	virtual void STDCALL CommandGroupCommand( const SAIUnitCmd *pCommand, const WORD wGroup, bool bPlaceInQueue );
	// set single command to call planes, reinforcements, etc. returns group number, which was created
	virtual int STDCALL CommandUnitCommand( const struct SAIUnitCmd *pCommand );
	// show different areas... this command actiually has been doing only on client, but it needs group to be registered
	virtual void STDCALL CommandShowAreas( int nGroupID, int nAreaType, bool bShow );
	// обработать pCommand, пришедшую на текущем сегменте
	virtual void STDCALL AddCommandToSend( IAILogicCommand *pCommand );	

	// количество играющих сейчас игроков
	virtual int STDCALL GetNumberOfPlayers() const { return 1; }
	
	virtual bool STDCALL JoinToServer( const char *pszIPAddress, const int nPort, bool bPasswordRequired, const char* pszPassword ) { return false; }
	virtual void STDCALL CreateServer() { }
	virtual void STDCALL InitByCreateServersList() { }
	
	// client commands
	virtual void STDCALL CommandClientTogglePause();
	virtual void STDCALL CommandClientSpeed( const int nChange );
	virtual void STDCALL CommandClientDropPlayer( const WORD *pszPlayerNick ) { }
	
	virtual void STDCALL CommandTimeOut( const bool bSet ) { }
	
	virtual NTimer::STime STDCALL GetMultiplayerTime() { return 0; }

	virtual void STDCALL LoadAllGameParameters();
	
	virtual void STDCALL SetTotalOutOfSync() { }
	
	virtual void STDCALL GameFinished() { }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __SINGLEPLAYERTRANSCEIVER_H__
