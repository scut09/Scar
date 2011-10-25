/********************************************************************
    ����ʱ��: 2011-10-25   20:25
    �ļ���:   Client.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     �ͻ���

*********************************************************************/


#ifndef Client_h__
#define Client_h__

#include "NetworkPacket.h"
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <vector>

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using namespace boost::asio::ip;

	class BoostClient
	{
	public:
		void SendToServer( const PACKAGE& packet )
		{
			m_sock.send_to( buffer( &packet, packet.GetLength() ), m_server_ep );
		}

		void Test()
		{
			PACKAGE p;
			p.SetCMD( REQUEST_ROOM );
			SendToServer( p );
		}

	private:
		io_service		io;

		udp::endpoint	m_server_ep;

		udp::socket		m_sock;


	};


}



#endif // Client_h__