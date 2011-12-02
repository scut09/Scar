/********************************************************************
创建时间: 2011-10-26   2:40
文件名:   CNetwork.cpp
作者:     华亮 Cedric Porter [ Stupid ET ]	
说明:     底层网络支持的实现

*********************************************************************/

#include "GameBag.h"
#include "CNetwork.h"
#include <iostream>

Network::CNetwork::CNetwork( int listen_port, int target_port, int pool_size )
	: m_listen_port( listen_port )
	, m_target_port( target_port )
	, m_broadcast_ep( ip::address::from_string( "255.255.255.255" ), target_port )
	, m_pool( pool_size )		
{
	// 初始化发送的socket
	m_send_sock = //boost::shared_ptr<boost::asio::ip::udp::socket>( 
		new boost::asio::ip::udp::socket( m_pool.get_io_service() );// );

	m_send_sock->open( ip::udp::v4() );
	// 允许广播
	socket_base::broadcast option( true );
	m_send_sock->set_option( option );

	// 为不同的网卡创建广播的地址
	CreateBroadcastIPAddress();

	
	// 创建接受的udp socket
	m_receive_sock = //boost::shared_ptr<boost::asio::ip::udp::socket>(
		new boost::asio::ip::udp::socket( m_pool.get_io_service(),
		boost::asio::ip::udp::endpoint( boost::asio::ip::udp::v4(), listen_port ) );// );

	// 创建tcp的acceptor
	m_acceptor //= boost::shared_ptr<ip::tcp::acceptor>( 
		= new ip::tcp::acceptor( m_pool.get_io_service(),
		ip::tcp::endpoint( ip::tcp::v4(), listen_port ) ) ;//);

	// 创建io_service_pool异步完成的等待线程
	m_io_thread.reset( new thread( boost::bind( &io_service_pool::run, &m_pool ) ) );
}

Network::CNetwork::~CNetwork()
{
	Close();
}

void Network::CNetwork::Start( INetworkCallbackType func )
{
	// 保存消息处理函数
	m_func = func;

	// 启动新线程来处理消息
	m_handle_thread.reset( new thread( bind( &CNetwork::Message_Handler, this ) ) );

	StartTCP();	
	StartUDP();
}

void Network::CNetwork::Close()
{
	std::cout << "<CNetwork::Close()>\n";
	try
	{
		m_acceptor->cancel();
		m_acceptor->close();
		
		m_receive_sock->cancel();
		m_receive_sock->close();

		m_send_sock->cancel();
		m_send_sock->close();

		m_pool.stop();
		m_io_thread->interrupt();
		m_handle_thread->interrupt();

		m_io_thread->join();
		m_handle_thread->join();

		delete m_send_sock;
		delete m_receive_sock;
		delete m_acceptor;



		//m_acceptor.reset();
		//m_handle_thread.reset();
		//m_io_thread.reset();
	}
	catch ( const std::exception& e )
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "</CNetwork::Close()>\n";
}

void Network::CNetwork::SendTo( const std::string& ip, const PACKAGE& pack )
{
	if ( ip != "" )
	{
		m_send_sock->send_to( buffer( (char*)&pack, pack.GetLength() ), 
			ip::udp::endpoint( ip::address::from_string( ip ), m_target_port ) );
	}
}

void Network::CNetwork::SendTo( unsigned long ip, const PACKAGE& pack )
{
	if ( ip )
	{
		m_send_sock->send_to( buffer( (char*)&pack, pack.GetLength() ), 
			ip::udp::endpoint( ip::address_v4( ip ), m_target_port ) );
	}
}


void Network::CNetwork::Message_Handler()
{
	while ( 1 )
	{
		IP_Package p = m_packetBuffer.Get();

		// 调用回调函数处理收到消息
		m_func( p.ip, p.pack );

		boost::this_thread::interruption_point();	// 中断点
	}
}

void Network::CNetwork::CreateBroadcastIPAddress()
{
	try
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
	catch ( std::exception& e)
	{
		std::cout << "CNetwork::CreateBroadcastIPAddress()'s exception: " << e.what() << std::endl;
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

void Network::CNetwork::StartTCP()
{
	TCPSocketPointerType sock( new ip::tcp::socket( m_pool.get_io_service() ) );

	// 异步acceptor
	m_acceptor->async_accept( *sock, 
		boost::bind( &CNetwork::TCPAcceptHandler, this, placeholders::error, sock ) );
}

void Network::CNetwork::TCPAcceptHandler( const boost::system::error_code& ec, TCPSocketPointerType sock )
{
	if ( ec )	return;

	// 为当前socket创建缓冲
	boost::shared_ptr< std::vector<char> > buf( new std::vector<char>( BUFFER_SIZE, 0 ) );
	// 异步读取
	sock->async_read_some( buffer( *buf ), boost::bind( &CNetwork::TCPReadHandler, this, placeholders::error, sock, buf ) );

	StartTCP();		// 再次开启TCP监听，继续等待其他连接
}

void Network::CNetwork::TCPReadHandler( const boost::system::error_code& ec, 
	TCPSocketPointerType sock, boost::shared_ptr< std::vector<char> > buf )
{
	if ( ec )	return;

	PACKAGE* pack = (PACKAGE*)(*buf).data();

	// 校验包是否有效
	if ( pack->GetMagicNumber() == MagicNumber )
	{
		// 将数据包放入Buffer中
		m_packetBuffer.Put( IP_Package( sock->remote_endpoint().address().to_v4().to_ulong(), *pack ) );
	}

	// 继续读取
	sock->async_read_some( buffer( *buf ), boost::bind( &CNetwork::TCPReadHandler, this, placeholders::error, sock, buf ) );

	std::cout << "==> TCP receives from " << sock->remote_endpoint().address().to_string() << std::endl;
}

void Network::CNetwork::StartUDP()
{
	boost::shared_ptr<ip::udp::endpoint> ep( new ip::udp::endpoint );
	boost::shared_ptr< std::vector<char> > buf( new std::vector<char>( BUFFER_SIZE, 0 ) );

	m_receive_sock->async_receive_from(
		boost::asio::buffer( *buf ), *ep,
		boost::bind( &CNetwork::UDPReadhandler, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred,
		ep,
		buf ) );
}

void Network::CNetwork::UDPReadhandler( const boost::system::error_code& error, std::size_t /*bytes_transferred*/, boost::shared_ptr<boost::asio::ip::udp::endpoint> ep, boost::shared_ptr< std::vector<char> > buf )
{
	if (!error || error == boost::asio::error::message_size)
	{
		PACKAGE* pack = (PACKAGE*)(*buf).data();

		// 校验包是否有效
		if ( pack->GetMagicNumber() == MagicNumber )
		{
			// 将数据包放入Buffer中
			m_packetBuffer.Put( IP_Package( ep->address().to_v4().to_ulong(), *pack ) );
		}

		StartUDP();		// 再次开启UDP监听
	}
}

void Network::CNetwork::TcpSendTo( unsigned long ip, int port, const PACKAGE& p )
{
	using namespace boost::asio;

	// 数据包，复制到堆里，供异步使用
	boost::shared_ptr<PACKAGE> pack( new PACKAGE( p ) );

	// 对方端点
	ip::tcp::endpoint ep( ip::address_v4( ip ), port );

	boost::shared_ptr<ip::tcp::socket> sock;	

	// 查找是否有已连接的tcp
	TCP_IP_Socket_MapType::iterator iter = m_ip_socketMap.find( ip );
	if ( iter == m_ip_socketMap.end() )
	{
		sock = boost::shared_ptr<ip::tcp::socket>( new ip::tcp::socket( m_pool.get_io_service() ) );
		m_ip_socketMap[ ip ] = sock;

		try
		{
			// 连接
			sock->connect( ep );
		}
		catch ( std::exception& e )
		{
			std::cout << e.what() << std::endl;
		}
	}

	sock = m_ip_socketMap[ ip ];

	sock->async_write_some( 
		buffer( (char*)&*pack, pack->GetLength() )
		, boost::bind( &CNetwork::tcp_write_handler, this, placeholders::error, sock, pack ) );


	
	/*try
	{
	sock = boost::shared_ptr<ip::tcp::socket>( new ip::tcp::socket( m_pool.get_io_service() ) );
	sock->connect( ep );
	sock->write_some( buffer( (char*)&p, p.GetLength() ) );
	}
	catch ( std::exception& e )
	{
	std::cout << e.what() << std::endl;
	}*/
}

void Network::CNetwork::tcp_write_handler( const boost::system::error_code& ec,
	boost::shared_ptr<boost::asio::ip::tcp::socket> sock, boost::shared_ptr<PACKAGE> pack )
{
	if ( ec && ec == boost::asio::error::eof )
	{
		// 出错，重发
		unsigned long ip = sock->remote_endpoint().address().to_v4().to_ulong();
		unsigned short port = sock->remote_endpoint().port();

		TCP_IP_Socket_MapType::iterator iter = m_ip_socketMap.find( ip );
		if ( iter != m_ip_socketMap.end() )
		{
			m_ip_socketMap.erase( iter );	// 将原来的sock移除
		}

		TcpSendTo( ip, port, *pack );

		std::cout << "Network::CNetwork::connect_handler error\n";
		return;
	}
}

void Network::CNetwork::AddPackageToBuffer( const PACKAGE& p )
{
	m_packetBuffer.Put( IP_Package( 0, p ) );

}

