/********************************************************************
    ����ʱ��: 2011-10-26   2:40
    �ļ���:   CNetwork.cpp
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     �ײ�����֧�ֵ�ʵ��

*********************************************************************/


#include "CNetwork.h"
#include <iostream>

Network::CNetwork::CNetwork( int port, int target_port )
	: m_listen_port( port )
	, m_target_port( target_port )
	, m_broadcast_ep( ip::address::from_string( "255.255.255.255" ), target_port )
{
	// ��ʼ�����͵�socket
	m_send_sock = std::shared_ptr<boost::asio::ip::udp::socket>( new boost::asio::ip::udp::socket( io ) );

	m_send_sock->open( ip::udp::v4() );
	// ����㲥
	socket_base::broadcast option( true );
	m_send_sock->set_option( option );
}

Network::CNetwork::~CNetwork()
{
	m_thread->interrupt();
	m_thread->join();
	m_send_sock->close();
}

void Network::CNetwork::Start( INetworkCallbackType func )
{
	m_func = func;

	// �������߳�������Run()����
	m_thread = std::shared_ptr<thread>( new thread( bind( &CNetwork::Run, this ) ) );

	//m_thread->join();
}

void Network::CNetwork::Close()
{
	m_thread->interrupt();
	m_thread.reset();
}

void Network::CNetwork::Send( const std::string& ip, const PACKAGE& pack )
{
	m_send_sock->send_to( buffer( (char*)&pack, pack.GetLength() ), ip::udp::endpoint( ip::address::from_string( ip ), m_target_port ) );
}

void Network::CNetwork::Send( unsigned long ip, const PACKAGE& pack )
{
	if ( ip == 0 )	// �㲥
	{
		m_send_sock->send_to( buffer( (char*)&pack, pack.GetLength() ), m_broadcast_ep );
	}
	else
	{
		m_send_sock->send_to( buffer( (char*)&pack, pack.GetLength() ), ip::udp::endpoint( ip::address_v4( ip ), m_target_port ) );
	}
}

void Network::CNetwork::Run()
{
	ip::udp::socket		sock( io, boost::asio::ip::udp::endpoint( boost::asio::ip::udp::v4(), m_listen_port ) );		// ����udp��socket
	std::vector<char>	buf( 1280 );	// ������
	system::error_code	ec;				// ������
	ip::udp::endpoint	ep;				// ���淢�Ͷ˵���Ϣ
	PACKAGE				pack;			// ���ݰ�

	while ( 1 )
	{
		boost::this_thread::interruption_point();

		// ����������Ϣ
		sock.receive_from( buffer( buf ), ep, 0, ec );

		if ( ec && ec != error::message_size )
		{
			std::cerr << "Error occurs in CNetwork::Run()\n";
			//::system( "pause" );
			continue;
		}

		pack = *(PACKAGE*)buf.data();

		// ���ûص����������յ���Ϣ
		m_func( ep.address().to_v4().to_ulong(), pack );
	}
}
