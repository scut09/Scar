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



	// 服务器
	class BoostServer
	{
	public:
		void OnReceive( unsigned long ip, const PACKAGE& p );

		void Start( int listen_port, int target_port );

	private:
		void SaveLocalIPAddress()
		{
			using namespace boost::asio::ip;
			boost::asio::io_service io;

			tcp::resolver resolver( io ); 
			tcp::resolver::query query( boost::asio::ip::host_name(), "" ); 
			tcp::resolver::iterator iter = resolver.resolve( query ); 
			tcp::resolver::iterator end; 

			while ( iter != end ) 
			{   
				tcp::endpoint ep = *iter++;    
				if ( ep.address().is_v4() )
				{
					m_localIP.insert( ep.address().to_string() );
					//std::cout << ep.address().to_string() << std::endl;
				}
			} 
		}

	public:


	private:
		std::set<std::string>		m_localIP;

		int							m_port;
		std::shared_ptr<INetwork>	m_network;

		std::list<PlayerInfo>		m_playerList;
	};


}

#endif // Boost_Server_h__
