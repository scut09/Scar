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

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using namespace boost::asio::ip;

	class BoostClient
	{
	public:
		BoostClient( int port ) : m_port( port )
		{
			// ��������
			m_network = std::shared_ptr<Network::CNetwork>( new Network::CNetwork( port, 12345 ) );
			// ע����ܻص�����
			m_network->Start( [this]( unsigned long ip, const PACKAGE& p )
			{
				OnReceive( ip, p );
			} );
		}

		void OnReceive( unsigned long ip, const PACKAGE& p )
		{

		}

		void Send( std::string ip )
		{
			PACKAGE p;
			p.SetCMD( REQUEST_ROOM );
			m_network->Send( ip, m_port, p );
		}


	private:
		int							m_port;
		std::shared_ptr<INetwork>	m_network;
	};


}


#endif // Boost_Client_h__
