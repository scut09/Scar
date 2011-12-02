/********************************************************************
    创建时间: 2011-10-26   1:32
    文件名:   INetwork.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     基本网络接口。提供注册消息处理函数，收到udp消息后会调用此回调函数

*********************************************************************/


#ifndef INetwork_h__
#define INetwork_h__

#include <functional>
#include <string>
#include "NetworkPacket.h"

namespace Network
{
	typedef std::function< void( unsigned long, const PACKAGE& ) >	INetworkCallbackType;

	struct PACKAGE;

	class INetwork
	{
	public:
		virtual ~INetwork() {}

		virtual void AddPackageToBuffer( const PACKAGE& p ) = 0;

		// 开始接受网络信息
		virtual void Start( INetworkCallbackType func ) = 0;

		// 关闭网络
		virtual void Close() = 0;

		// 发送，输入字符串形式的ip
		virtual void SendTo( const std::string& ip, const PACKAGE& pack ) = 0;

		// 发送，输入数字形式的ip		
		virtual void SendTo( unsigned long ip, const PACKAGE& pack ) = 0;

		virtual void TcpSendTo( unsigned long ip, int port, const PACKAGE& p ) = 0;

		// 支持多网卡的广播
		virtual void Broadcast( const PACKAGE& pack ) = 0;		

	};
}


#endif // INetwork_h__