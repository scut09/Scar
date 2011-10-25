/********************************************************************
    创建时间: 2011-10-25   20:25
    文件名:   Server.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     服务端

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

	// 服务器
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
