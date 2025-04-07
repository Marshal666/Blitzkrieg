#ifndef __COMMANDS_HISTORY_INTERFACE_H__
#define __COMMANDS_HISTORY_INTERFACE_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "iMain.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
interface ICommandsHistory : public IRefCount
{
	// type ID
	enum { tidTypeID = MAIN_COMMANDS_HISTORY };

	// очистка всего, куда пишется history, перед стартом мисии, 
	// запоминание текущих RandomSeed и ScenarioTracker
	virtual void STDCALL PrepareToStartMission() = 0;

	// загрузка и инициализация для multiplayer, если задан параметр -lh
	virtual bool STDCALL LoadCommandLineHistory() = 0;

	// вместе с самими командами загружается RandomSeed
	// return true if no error occurs
	virtual bool STDCALL Load( const char *pszFileName ) = 0;
	// параметр по умолчанию только для тестирования
	// если имя пустое, то смотрится то, что было установлено параметром -sh
	virtual void STDCALL Save( const char *pszFileName = "" ) = 0;

	virtual void STDCALL Clear() = 0;

	virtual void STDCALL AddCommand( const int nSegment, interface IAILogicCommand *pCmd ) = 0;
	virtual void STDCALL ExecuteSegmentCommands( const int nSegment, interface ITransceiver *pTranceiver ) = 0;
	virtual void STDCALL CheckStartMapCheckSum( const int nCheckSum ) = 0;

	virtual const int GetNumPlayersInMPGame() const = 0;
	virtual const int GetMPPlayerLogicID( const int nPlayer ) const = 0;
	virtual const int GetMPPlayerSide( const int nPlayer ) const = 0;
	
	virtual const char* STDCALL GetModName() const = 0;
	virtual const char* STDCALL GetModVersion() const = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // COMMANDS_HISTORY_INTERFACE_H__
