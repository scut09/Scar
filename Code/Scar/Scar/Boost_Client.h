/********************************************************************
    ����ʱ��: 2011-10-25   20:25
    �ļ���:   Client.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     �ͻ���

*********************************************************************/

#ifndef Boost_Client_h__
#define Boost_Client_h__


#include "NetworkPacket.h"
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <vector>
#include "CNetwork.h"
#include <map>

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using namespace boost::asio::ip;

	class BoostClient
	{
	public:
		void Start( int listen_port, int target_port );

		void OnReceive( unsigned long ip, const PACKAGE& p );

		void Send( std::string ip );

		void QueryRoom();

	private:

		int										m_port;
		std::shared_ptr<INetwork>				m_network;
		std::map<std::string, BroadcastRoomBag>	m_roomMap;
	};


}


#endif // Boost_Client_h__
