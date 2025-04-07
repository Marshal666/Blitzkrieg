#ifndef __TRANSCEIVER_H__
#define __TRANSCEIVER_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "..\Main\iMainClassIDs.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
interface ITransceiver : public IRefCount
{
	enum { tidTypeID = MAIN_TRANSCEIVER };
	//
	virtual void STDCALL Init( ISingleton *pSingleton, const int nMultiplayerType ) = 0;
	virtual void STDCALL Done() = 0;
	virtual void STDCALL PreMissionInit() = 0;
	// set lattency for smooth net playing
	virtual void SetLatency( int nSegments ) = 0;
	// perform segments for AI
	virtual void STDCALL DoSegments() = 0;
	// register group of units to AI
	virtual int STDCALL CommandRegisterGroup( IRefCount **pUnitsBuffer, const int nLen ) = 0;
	// unregister group
	virtual void STDCALL CommandUnregisterGroup( const WORD wGroup ) = 0;
	// send command to group of units
	virtual void STDCALL CommandGroupCommand( const struct SAIUnitCmd *pCommand, const WORD wGroup, bool bPlaceInQueue ) = 0;
	// set single command to call planes, reinforcements, etc. returns group number, which was created
	virtual int STDCALL CommandUnitCommand( const struct SAIUnitCmd *pCommand ) = 0;
	// show different areas... this command actiually has been doing only on client, but it needs group to be registered
	virtual void STDCALL CommandShowAreas( int nGroupID, int nAreaType, bool bShow ) = 0;
	// обработать pCommand, пришедшую на текущем сегменте
	virtual void STDCALL AddCommandToSend( interface IAILogicCommand *pCommand ) = 0;
	
	// количество играющих сейчас игроков
	virtual int STDCALL GetNumberOfPlayers() const = 0;
	
	virtual bool STDCALL JoinToServer( const char *pszIPAddress, const int nPort, bool bPasswordRequired, const char* pszPassword ) = 0;
	virtual void STDCALL CreateServer() = 0;
	virtual void STDCALL InitByCreateServersList() = 0;
	
	// client commands
	virtual void STDCALL CommandClientTogglePause() = 0;
	virtual void STDCALL CommandClientSpeed( const int nChange ) = 0;
	virtual void STDCALL CommandClientDropPlayer( const WORD *pszPlayerNick ) = 0;
	
	virtual void STDCALL CommandTimeOut( const bool bSet ) = 0;
	
	virtual NTimer::STime STDCALL GetMultiplayerTime() = 0;

	virtual void STDCALL LoadAllGameParameters() = 0;
	
	virtual void STDCALL SetTotalOutOfSync() = 0;

	virtual void STDCALL GameFinished() = 0;
	
	// for debug
	virtual interface INetDriver* STDCALL GetInGameNetDriver() const { return 0; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __TRANSCEIVER_H__
