/********************************************************************
    创建时间: 2011-10-26   2:42
    文件名:   CNetwork.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     网络接口的实现，提供一个接收消息的框架，可以自定义消息处理回调函数。
			另外也可以通过其发送，基于udp实现

*********************************************************************/


#ifndef CNetwork_h__
#define CNetwork_h__

#include "INetwork.h"
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <vector>

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using boost::asio::ip::udp;

	class CNetwork : public INetwork
	{
	public:
		CNetwork( int port = 12345, int target_port = 0 );

		// 开始接受网络信息
		virtual void Start( INetworkCallbackType func );

		// 关闭网络
		virtual void Close();

		// 发送，输入字符串形式的ip
		virtual void Send( const std::string& ip, int port, const PACKAGE& pack );

		// 发送，输入数字形式的ip		
		virtual void Send( unsigned long ip, int port, const PACKAGE& pack );

	private:
			
		// 在新线程中运行，负责接受消息并调用回调函数处理消息
		void Run();


	private:
		INetworkCallbackType			m_func;			// 消息处理函数
		std::shared_ptr<boost::thread>	m_thread;		// 接受消息的线程的指针
		std::shared_ptr<ip::udp::socket>m_send_sock;	// 发送的socket
		ip::udp::endpoint				m_broadcast_ep;	// 广播的地址
		io_service						io;				// 前摄器模式
		int								m_listen_port;	// 监听的端口
		int								m_target_port;	// 目标的端口
	};
}


#endif // CNetwork_h__