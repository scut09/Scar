/********************************************************************
    创建时间: 2011-10-26   2:40
    文件名:   CNetwork.cpp
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     底层网络支持的实现

*********************************************************************/

#include "GameBag.h"
#include "CNetwork.h"
#include <iostream>

Network::CNetwork::CNetwork( int listen_port, int target_port )
	: m_listen_port( listen_port )
	, m_target_port( target_port )
	, m_broadcast_ep( ip::address::from_string( "255.255.255.255" ), target_port )
{
	// 初始化发送的socket
	m_send_sock = std::shared_ptr<boost::asio::ip::udp::socket>( new boost::asio::ip::udp::socket( io ) );

	m_send_sock->open( ip::udp::v4() );
	// 允许广播
	socket_base::broadcast option( true );
	m_send_sock->set_option( option );

	// 为不同的网卡创建广播的地址
	CreateBroadcastIPAddress();

	// 创建接受的socket
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

	// 启动新线程来接受消息
	m_socket_thread = std::shared_ptr<thread>( new thread( bind( &CNetwork::UDP_Listener, this ) ) );
	// 启动新线程来处理消息
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

		// 调用回调函数处理收到消息
		m_func( p.ip, p.pack );

		boost::this_thread::interruption_point();	// 中断点
	}
}


void Network::CNetwork::UDP_Listener()
{
	//ip::udp::socket		m_receive_sock( io, boost::asio::ip::udp::endpoint( boost::asio::ip::udp::v4(), m_listen_port ) );		// 接受udp的socket
	std::vector<char>	buf( 1472 );	// 缓冲区
	system::error_code	ec;				// 错误码
	ip::udp::endpoint	ep;				// 保存发送端的信息
	PACKAGE				pack;			// 数据包

	while ( 1 )
	{
		boost::this_thread::interruption_point();	// 中断点

		// 阻塞接受消息
		m_receive_sock->receive_from( buffer( buf ), ep, 0, ec );

		if ( ec && ec != error::message_size )
		{
			std::cerr << "Error occurs in CNetwork::Run()\n";
			//::system( "pause" );
			continue;
		}

		pack = *(PACKAGE*)buf.data();

		// 将数据包放入Buffer中
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
			ip |= 0xff;				// 将IP地址最后的位置为255,以便广播
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
