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
#include <map>
#include <set>

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using namespace boost::asio::ip;

	class BoostClient
	{
	public:
		BoostClient()
		{
			SaveLocalIPAddress();
		}

		void Start( int listen_port, int target_port );

		void OnReceive( unsigned long ip, const PACKAGE& p );

		void Send( std::string ip );

		void QueryRoom();

		void EnterRoom( const std::string& ip )
		{
			PACKAGE pack;
			pack.SetCMD( REQUEST_ENTER_ROOM );
			m_network->Send( 0, pack );
		}

		const std::map<std::string, BroadcastRoomBag>& GetRooms() const
		{
			return m_roomMap;
		}

		const std::set<std::string>& GetLocalIP() const
		{
			return m_localIP;
		}

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
					std::cout << ep.address().to_string() << std::endl;
				}
			} 
		}

	private:

		int										m_port;
		std::shared_ptr<INetwork>				m_network;
		std::map<std::string, BroadcastRoomBag>	m_roomMap;
		std::set<std::string>					m_localIP;
	};


}


#endif // Boost_Client_h__
