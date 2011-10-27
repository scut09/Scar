/********************************************************************
    ����ʱ��: 2011-10-25   20:25
    �ļ���:   Server.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     �����

*********************************************************************/

#ifndef Boost_Server_h__
#define Boost_Server_h__

#include "NetworkPacket.h"
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <vector>
#include <string>
#include <list>
#include <boost/smart_ptr.hpp>
#include <iostream>
#include "CNetwork.h"
#include <set>

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using namespace boost::asio::ip;

	// ������
	class BoostServer
	{
	public:
		void OnReceive( unsigned long ip, const PACKAGE& p );

		void Start( int listen_port, int target_port );

	private:
		std::set<std::string>		m_localIP;

		int							m_port;
		std::shared_ptr<INetwork>	m_network;

		std::list<PlayerInfo>		m_playerList;
	};


}

#endif // Boost_Server_h__
