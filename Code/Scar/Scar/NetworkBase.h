/********************************************************************
	创建时间: 2011-10-28   2:15
	文件名:   NetworkBase.h
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     Server Client的基类

*********************************************************************/

#ifndef NetworkBase_h__
#define NetworkBase_h__

#include <functional>
#include <hash_map>
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include "NetworkPacket.h"
#include "INetwork.h"

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using namespace boost::asio::ip;

	// 收到消息时的处理函数的类型
	typedef std::function< void( unsigned long, const PACKAGE& ) >	MessageHandlerType;

	class NetworkBase
	{
	public:
		virtual ~NetworkBase() {}

		// 收到消息时的响应函数
		virtual void OnReceive( unsigned long ip, const PACKAGE& p )
		{
			auto funcIter = m_handlerMap.find( p.GetCMD() );
			if ( funcIter != m_handlerMap.end() )
			{
				funcIter->second( ip, p );
				return;
			}

			OtherMessageHandler( ip, p );
		}

		//************************************
		// 返回值:  void
		// 参数:    int listen_port		// 监听的端口号
		// 参数:    int target_port		// 发送时的目标端口号
		// 描述：   打开服务器
		//************************************
		virtual void Start( int listen_port, int target_port )
		{
			// 创建网络
			m_network = std::shared_ptr<Network::CNetwork>( new Network::CNetwork( listen_port, target_port ) );
			// 注册接受回调函数
			m_network->Start( [this]( unsigned long ip, const PACKAGE& p )
			{
				OnReceive( ip, p );
			} );
		}

		// 关闭
		virtual void Close()
		{
			m_network.reset();
		}

		virtual void OtherMessageHandler( unsigned long ip, const PACKAGE& p )	{}
		 
		//************************************
		// 返回值:  void
		// 参数:    int cmd						消息类型，默认的消息类型取值大于0
		// 参数:    MessageHandlerType func		处理函数
		// 描述：   注册消息处理函数
		//************************************
		virtual void RegisterMessageHandler( int cmd, MessageHandlerType func )
		{
			m_handlerMap[ cmd ] = func;
		}

	protected:
		std::shared_ptr<INetwork>				m_network;		// 底层网络支持
		std::hash_map<int, MessageHandlerType>	m_handlerMap;	// 消息处理函数映射

	};
}

#endif // NetworkBase_h__