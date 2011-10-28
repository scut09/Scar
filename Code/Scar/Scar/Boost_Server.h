/********************************************************************
    ����ʱ��: 2011-10-25   20:25
    �ļ���:   Server.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     �����

*********************************************************************/

#ifndef Boost_Server_h__
#define Boost_Server_h__

#include "CNetwork.h"
#include "NetworkBase.h"
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

namespace Network
{
	//using namespace boost;
	//using namespace boost::asio;
	//using boost::asio::ip::udp;

	typedef std::hash_map<unsigned long, TCPSocketPointerType> IP_TcpSockMapType;

	// ������
	class BoostServer : public NetworkBase
	{
	public:
		BoostServer();

		virtual void Start( int listen_port, int target_port );

		void TcpSendToPlayers( const PACKAGE& p );

		void UdpSendToPlayers( const PACKAGE& p );

		// ��Ϣ������
		virtual void OtherMessageHandler( unsigned long ip, const PACKAGE& p );
		void QueryRoomHandler( unsigned long ip, const PACKAGE& p );
		void RequestEnterRoomHandler( unsigned long ip, const PACKAGE& p );

	private:
		std::list<PlayerInfo>					m_playerList;		// ����б�
		std::set<std::string>					m_localIP;			// ����IP
		int										m_target_port;		// Ŀ��˿ں�
	};


}

#endif // Boost_Server_h__
