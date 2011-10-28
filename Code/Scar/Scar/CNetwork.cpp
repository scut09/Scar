/********************************************************************
    ����ʱ��: 2011-10-26   2:40
    �ļ���:   CNetwork.cpp
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     �ײ�����֧�ֵ�ʵ��

*********************************************************************/

#include "GameBag.h"
#include "CNetwork.h"
#include <iostream>

Network::CNetwork::CNetwork( int listen_port, int target_port )
	: m_listen_port( listen_port )
	, m_target_port( target_port )
	, m_broadcast_ep( ip::address::from_string( "255.255.255.255" ), target_port )
{
	// ��ʼ�����͵�socket
	m_send_sock = std::shared_ptr<boost::asio::ip::udp::socket>( new boost::asio::ip::udp::socket( io ) );

	m_send_sock->open( ip::udp::v4() );
	// ����㲥
	socket_base::broadcast option( true );
	m_send_sock->set_option( option );

	// Ϊ��ͬ�����������㲥�ĵ�ַ
	CreateBroadcastIPAddress();

	// �������ܵ�socket
	m_receive_sock = std::shared_ptr<boost::asio::ip::udp::socket>(
		new boost::asio::ip::udp::socket( io, boost::asio::ip::udp::endpoint( boost::asio::ip::udp::v4(), listen_port ) ) );
}

Network::CNetwork::~CNetwork()
{
	Close();
}

void Network::CNetwork::Start( INetworkCallbackType func )
{
	m_func = func;

	// �������߳���������Ϣ
	m_socket_thread = std::shared_ptr<thread>( new thread( bind( &CNetwork::UDP_Listener, this ) ) );
	// �������߳���������Ϣ
	m_handle_thread = std::shared_ptr<thread>( new thread( bind( &CNetwork::UDP_Handler, this ) ) );
	//m_thread->join();
}

void Network::CNetwork::Close()
{
	std::cout << "Start CNetwork::Close()\n";
	m_send_sock->close();
	m_receive_sock->close();
	m_socket_thread->interrupt();
	m_handle_thread->interrupt();
	m_socket_thread.reset();
	m_handle_thread.reset();
	//m_socket_thread->join();
	//m_handle_thread->join();
	std::cout << "End CNetwork::Close()\n";
}

void Network::CNetwork::Send( const std::string& ip, const PACKAGE& pack )
{
	m_send_sock->send_to( buffer( (char*)&pack, pack.GetLength() ), ip::udp::endpoint( ip::address::from_string( ip ), m_target_port ) );
}

void Network::CNetwork::Send( unsigned long ip, const PACKAGE& pack )
{
	m_send_sock->send_to( buffer( (char*)&pack, pack.GetLength() ), ip::udp::endpoint( ip::address_v4( ip ), m_target_port ) );
}


void Network::CNetwork::UDP_Handler()
{
	while ( 1 )
	{
		IP_Package p = m_udp_packetBuffer.Get();

		// ���ûص����������յ���Ϣ
		m_func( p.ip, p.pack );

		boost::this_thread::interruption_point();	// �жϵ�
	}
}


void Network::CNetwork::UDP_Listener()
{
	//ip::udp::socket		m_receive_sock( io, boost::asio::ip::udp::endpoint( boost::asio::ip::udp::v4(), m_listen_port ) );		// ����udp��socket
	std::vector<char>	buf( 1472 );	// ������
	system::error_code	ec;				// ������
	ip::udp::endpoint	ep;				// ���淢�Ͷ˵���Ϣ
	PACKAGE				pack;			// ���ݰ�

	while ( 1 )
	{
		boost::this_thread::interruption_point();	// �жϵ�

		// ����������Ϣ
		m_receive_sock->receive_from( buffer( buf ), ep, 0, ec );

		if ( ec && ec != error::message_size )
		{
			std::cerr << "Error occurs in CNetwork::Run()\n";
			//::system( "pause" );
			continue;
		}

		pack = *(PACKAGE*)buf.data();

		// �����ݰ�����Buffer��
		m_udp_packetBuffer.Put( IP_Package( ep.address().to_v4().to_ulong(), pack ) );
	}
}

void Network::CNetwork::CreateBroadcastIPAddress()
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
			unsigned long ip = ep.address().to_v4().to_ulong();
			ip |= 0xff;				// ��IP��ַ����λ��Ϊ255,�Ա�㲥
			m_broadcast_ip.insert( ip );					
		}
	}
}

void Network::CNetwork::Broadcast( const PACKAGE& pack )
{
	for ( auto ipIter = m_broadcast_ip.begin(); ipIter != m_broadcast_ip.end(); ++ipIter )
	{			
		m_broadcast_ep.address( boost::asio::ip::address_v4( *ipIter ) );
		m_send_sock->send_to( buffer( (char*)&pack, pack.GetLength() ), m_broadcast_ep );
	}
}
