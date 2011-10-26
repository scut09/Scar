/********************************************************************
    创建时间: 2011-10-25   20:25
    文件名:   Client.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     客户端

*********************************************************************/

#ifndef Boost_Client_h__
#define Boost_Client_h__


#include "NetworkPacket.h"
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <vector>
#include "CNetwork.h"

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using namespace boost::asio::ip;

	class BoostClient
	{
	public:
		BoostClient( int port );

		void OnReceive( unsigned long ip, const PACKAGE& p );

		void Send( std::string ip );

	private:

		int							m_port;
		std::shared_ptr<INetwork>	m_network;
	};


}


#endif // Boost_Client_h__
