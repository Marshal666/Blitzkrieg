// MultiplayerCommandManagerInternal.h: interface for the MultiplayerCommandManagerInternal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTIPLAYERCOMMANDMANAGERINTERNAL_H__9EC0CE88_5727_4A04_BE2F_8F45320AD784__INCLUDED_)
#define AFX_MULTIPLAYERCOMMANDMANAGERINTERNAL_H__9EC0CE88_5727_4A04_BE2F_8F45320AD784__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MultiplayerCommandManager.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CMPToUICommandManager : public IMPToUICommandManager
{
	DECLARE_SERIALIZE;
	OBJECT_COMPLETE_METHODS(CMPToUICommandManager);

	std::list<SToUICommand> commandsToUI;
	std::list<SFromUINotification> notificationsFromUI;

	std::list< CPtr<SChatMessage> > chatMessagesToUI;
	std::list< CPtr<SChatMessage> > chatMessagesFromUI;
	CPtr<SChatMessage> pTakenMessage;

	EMultiplayerConnectionType eConnectionType;

	SFromUINotification delayedNotificaion;
	void Clear()
	{
		commandsToUI.clear();
		notificationsFromUI.clear();
		chatMessagesToUI.clear();
		chatMessagesFromUI.clear();
		delayedNotificaion.Clear();
	}

public:
	//adding
	virtual void STDCALL AddCommandToUI( SToUICommand & cmd );
	virtual void STDCALL AddNotificationFromUI( SFromUINotification & notify ) ;
	
	//recieveing. return true if put command by ptr. if ptr == 0 or no more commands
	// returns false;
	virtual bool STDCALL GetCommandToUI( SToUICommand *pCmd );
	virtual bool STDCALL GetNotificationFromUI( SFromUINotification *pNotify );

	virtual bool STDCALL PeekCommandToUI( SToUICommand *pCmd );
	virtual bool STDCALL PeekNotificationFromUI( SFromUINotification *pNotify );

	// chat
	virtual SChatMessage* STDCALL GetChatMessageFromUI();
	virtual SChatMessage* STDCALL GetChatMessageToUI();
	virtual SChatMessage* STDCALL PeekChatMessageToUI();
	virtual void STDCALL AddChatMessageToUI( SChatMessage *pMessage );
	virtual void STDCALL AddChatMessageFromUI( SChatMessage *pMessage );

	virtual void STDCALL InitUISide();
	
	virtual void STDCALL SetConnectionType( const enum EMultiplayerConnectionType eType ) { eConnectionType = eType; }
	virtual enum EMultiplayerConnectionType STDCALL GetConnectionType() const { return eConnectionType; }

	virtual void STDCALL DelayedNotification( SFromUINotification &notify );
	virtual void STDCALL SendDelayedNotification();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_MULTIPLAYERCOMMANDMANAGERINTERNAL_H__9EC0CE88_5727_4A04_BE2F_8F45320AD784__INCLUDED_)
