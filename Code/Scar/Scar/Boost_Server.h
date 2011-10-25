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
#include <boost/smart_ptr.hpp>
#include <iostream>
#include "CNetwork.h"

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using namespace boost::asio::ip;

	// ������
	class BoostServer
	{
	public:
		BoostServer( int port ); 

		void OnReceive( unsigned long ip, const PACKAGE& p );

	private:
		int							m_port;
		std::shared_ptr<INetwork>	m_network;
	};


}

#endif // Boost_Server_h__
