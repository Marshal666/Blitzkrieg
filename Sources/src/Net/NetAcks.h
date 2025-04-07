#ifndef __NETACKS_H_
#define __NETACKS_H_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <winsock.h>
#include <vector>
#include <list>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CBitStream;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NNet
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef unsigned int UPDATE_ID;
typedef unsigned short PACKET_ID;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RTT, acks, rate/congestion tracking
class CAckTracker
{
public:
	CAckTracker();
	static void SetMaxRTT( int nRTT ) { nMaxRTT = nRTT; }
	float GetRTT() const { return fAvrgRTT; }
	float GetRTTDisp() const { return sqrt( fabs( sqr( fAvrgRTT ) - fAvrgRTT2 ) ); }
	float GetTimeSinceLastRecv() const { return fTimeSinceLastRecv; }
	const float GetPing() const { return fPing; }
	// if true is returned then packet considered sent and timer corrected accordingly
	// all packets are considered to be of same size
	bool CanSend(); 
	bool NeedSend() const;
	void Step( std::vector<PACKET_ID> *pRolled, std::vector<PACKET_ID> *pErased, double fDeltaTime );
	PACKET_ID WrtieAcks( CBitStream *pBits, int nPktSize );
	bool ReadAcks( std::vector<PACKET_ID> *acked, CBitStream &bits );
	void PacketLost( PACKET_ID pktID );

private:
	static int nMaxRTT;
	PACKET_ID nPktSent;        // is used to order update packets
	UPDATE_ID nPktLastReceived;// number of last received pkt
	UPDATE_ID nPktHighCounter; // high part of packet counter
	//
	// info on received pkts (acks on them should be sent)
	std::vector<UPDATE_ID> receivedPkts;
	// acknowledgements on packets cache
	DWORD dwAckedBits;
	PACKET_ID nAckedLast;
	//
	float fAvrgRTT, fAvrgRTT2;    // RTT statistics

	// ping information
	float fPing;
	long nPingPacketsReceived;		
	float fSumPktRTT4Period;
	float fLastPingUpdateTime;

	//
	float fWindow;
	int nFlyPackets;
	//float fUpdateTimeDelay;       // recommended delay between updates (in seconds)
	//float fUpdateTimeElapsed;     // time elapsed since last update
	float fTimeSinceLastSend;
	float fTimeSinceLastRecv;     // time elapsed since last receive
	double fCurrentTime;
	//int nUpdateSize;               // recommended update size
	//
	// �����, �������������� �� CUpdateRequest
	class CUpdate 
	{
	public: 
		double fTimeCreated;
		PACKET_ID nPktNumber;
		bool bOnTheWindowEdge;
	};
	// info on sent update packets
	std::list< CUpdate > sentUpdates, rolledUpdates;    // unacknowledged updates
	
	void RegisterRTT( float fRTT );
	void SendPktAcks( CBitStream *pBits );
	void ReceiveAck( std::vector<PACKET_ID> *pAcked, PACKET_ID nPkt );
	void ReceivePktAcks( std::vector<PACKET_ID> *pAcked, CBitStream &bits );
	bool CheckRecvPacketNumber( UPDATE_ID nPkt );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
