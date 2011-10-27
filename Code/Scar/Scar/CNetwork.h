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
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <set>
#include <string>
#include <vector>

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using boost::asio::ip::udp;

	struct PACKAGE;

	struct PlayerInfo
	{
		int				index;
		unsigned long	ip;

		PlayerInfo( int i, unsigned long IP ) : ip( IP ), index( i ) {}
		PlayerInfo() {}
	};

	class CNetwork : public INetwork
	{
	public:
		CNetwork( int listen_port, int target_port );

		~CNetwork();

		// 开始接受网络信息
		virtual void Start( INetworkCallbackType func );

		// 关闭网络
		virtual void Close();

		// 发送，输入字符串形式的ip
		virtual void Send( const std::string& ip, const PACKAGE& pack );

		// 发送，输入数字形式的ip		
		virtual void Send( unsigned long ip, const PACKAGE& pack );

		// 支持多网卡的广播
		virtual void Broadcast( const PACKAGE& pack );

	private:
			
		// 在新线程中运行，负责接受消息并调用回调函数处理消息
		void Run();

		// 在新线程中处理消息队列中的数据
		void Handle();


	private:
		// 创建每个网卡的自己的IP,以便于多网卡广播
		void CreateBroadcastIPAddress();


		struct IP_Package
		{
			unsigned long ip;
			PACKAGE pack;

			IP_Package() {}
			IP_Package( unsigned long IP, const PACKAGE& p )
				: ip( IP ), pack( p ) 
			{}
		};


	private:
		Buffer<IP_Package>					m_packetBuffer;	// 包缓冲
		INetworkCallbackType				m_func;			// 消息处理函数
		int									m_listen_port;	// 监听的端口
		int									m_target_port;	// 目标的端口
		io_service							io;				// 前摄器模式
		ip::udp::endpoint					m_broadcast_ep;	// 广播的地址
		std::set<unsigned long>				m_broadcast_ip;	// 广播IP
		std::shared_ptr<boost::thread>		m_handle_thread;// 接受消息的线程的指针
		std::shared_ptr<boost::thread>		m_socket_thread;// 接受消息的线程的指针
		std::shared_ptr<ip::udp::socket>	m_receive_sock; // 接受udp的socket
		std::shared_ptr<ip::udp::socket>	m_send_sock;	// 发送的socket


	};
}


#endif // CNetwork_h__