/********************************************************************
    创建时间: 2011-10-26   2:42
    文件名:   CNetwork.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     网络接口的实现，提供一个接收消息的框架，可以自定义消息处理回调函数。
			另外也可以通过其发送，基于udp实现

*********************************************************************/


#ifndef CNetwork_h__
#define CNetwork_h__

#include "Buffer.h"
#include "INetwork.h"
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <set>
#include <string>
#include <list>
#include <vector>
#include <hash_map>
#include "network_header.h"
#include "io_service_pool.h"

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using boost::asio::ip::udp;

	const int BUFFER_SIZE = 1472;

	struct PACKAGE;

	struct PlayerInfo
	{
		int				index;
		unsigned long	ip;

		PlayerInfo( int i, unsigned long IP ) : ip( IP ), index( i ) {}
		PlayerInfo() {}
	};

	struct IP_Package
	{
		unsigned long ip;
		PACKAGE pack;

		IP_Package() {}
		IP_Package( unsigned long IP, const PACKAGE& p )
			: ip( IP ), pack( p ) 
		{}
	};

	typedef std::shared_ptr<boost::asio::ip::tcp::socket> TCPSocketPointerType;
	typedef std::hash_map< unsigned long, std::shared_ptr<boost::asio::ip::tcp::socket> > TCP_IP_Socket_MapType;

	/*
	** 名字：CNetwork
	** 说明：提供基本网络功能
	**
	*/
	class CNetwork : public INetwork
	{
	public:
		CNetwork( int listen_port, int target_port, int pool_size = 2 );

		~CNetwork();

		// 开始接受网络信息
		virtual void Start( INetworkCallbackType func );

		// 关闭网络
		virtual void Close();

		// udp发送，输入字符串形式的ip
		virtual void SendTo( const std::string& ip, const PACKAGE& pack );

		// udp发送，输入数字形式的ip		
		virtual void SendTo( unsigned long ip, const PACKAGE& pack );

		// 支持多网卡的广播
		virtual void Broadcast( const PACKAGE& pack );

		// 同步tcp发送
		virtual void TcpSendTo( unsigned long ip, int port, const PACKAGE& p );

		void tcp_write_handler( const boost::system::error_code& ec,
			std::shared_ptr<ip::tcp::socket> sock, std::shared_ptr<PACKAGE> pack );

	private:
		// 在新线程中处理消息队列中的数据
		void Message_Handler();

		// TCP监听
		void StartTCP();
		// 有新tcp连接上时保存这个socket
		void TCPAcceptHandler( const boost::system::error_code& ec, TCPSocketPointerType sock );
		// TCP收到消息
		void TCPReadHandler( const boost::system::error_code& ec, TCPSocketPointerType sock, std::shared_ptr< std::vector<char> > buf );
		
		// UDP监听
		void StartUDP();
		// UDP处理函数
		void UDPReadhandler(const boost::system::error_code& error,
			std::size_t /*bytes_transferred*/, std::shared_ptr<ip::udp::endpoint> ep, 
			std::shared_ptr< std::vector<char> > buf );


	private:
		// 创建每个网卡的自己的IP,以便于多网卡广播
		void CreateBroadcastIPAddress();


	private:
		Buffer<IP_Package>					m_packetBuffer;			// 收到的数据包缓冲
		INetworkCallbackType				m_func;					// 消息处理函数
		int									m_listen_port;			// 监听的端口
		int									m_target_port;			// 目标的端口
		ip::udp::endpoint					m_broadcast_ep;			// 广播的地址
		std::set<unsigned long>				m_broadcast_ip;			// 广播IP
		std::shared_ptr<boost::thread>		m_handle_thread;		// 处理消息的线程的指针
		std::shared_ptr<boost::thread>		m_io_thread;			// io的线程的指针
		ip::udp::socket*	m_receive_sock;			// 接受udp的socket
		ip::udp::socket*	m_send_sock;			// 发送的socket
		ip::tcp::acceptor*	m_acceptor;				// tcp的acceptor
		io_service_pool						m_pool;					// io_service pool
		TCP_IP_Socket_MapType				m_ip_socketMap;			// ip和tcp socket的映射

	};
}


#endif // CNetwork_h__