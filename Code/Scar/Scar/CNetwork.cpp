/********************************************************************
    创建时间: 2011-10-26   2:40
    文件名:   CNetwork.cpp
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     底层网络支持的实现

*********************************************************************/


#include "CNetwork.h"
#include <iostream>

Network::CNetwork::CNetwork( int port, int target_port )
	: m_listen_port( port )
	, m_target_port( target_port )
	, m_broadcast_ep( ip::address::from_string( "255.255.255.255" ), target_port )
{
	// 初始化发送的socket
	m_send_sock = std::shared_ptr<boost::asio::ip::udp::socket>( new boost::asio::ip::udp::socket( io ) );

	m_send_sock->open( ip::udp::v4() );
	// 允许广播
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

	// 启动新线程来运行Run()函数
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
	if ( ip == 0 )	// 广播
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
	ip::udp::socket		sock( io, boost::asio::ip::udp::endpoint( boost::asio::ip::udp::v4(), m_listen_port ) );		// 接受udp的socket
	std::vector<char>	buf( 1280 );	// 缓冲区
	system::error_code	ec;				// 错误码
	ip::udp::endpoint	ep;				// 保存发送端的信息
	PACKAGE				pack;			// 数据包

	while ( 1 )
	{
		boost::this_thread::interruption_point();

		// 阻塞接受消息
		sock.receive_from( buffer( buf ), ep, 0, ec );

		if ( ec && ec != error::message_size )
		{
			std::cerr << "Error occurs in CNetwork::Run()\n";
			//::system( "pause" );
			continue;
		}

		pack = *(PACKAGE*)buf.data();

		// 调用回调函数处理收到消息
		m_func( ep.address().to_v4().to_ulong(), pack );
	}
}
