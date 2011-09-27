/********************************************************************
创建时间: 2011:9:27   14:53
文件名:   IClient.h
作者:     华亮 Cedric Porter [ Stupid ET ]	
说明:     客户端接口。客户端端应该继承IClient并实现IClient的接口，
		系统其他部分针对IClient接口编程  

*********************************************************************/

#ifndef _ICLIENT_H_
#define _ICLIENT_H_

#include <functional>
#include <string>
#include <list>

namespace Network
{
	/*
	** 名字：ServerInfo
	** 说明：由IClient返回的当前局域网服务器的信息
	**
	*/
	struct ServerInfo
	{
		std::string ip;
		std::string roomName;
		int			maxPlayerNumber;
		int			currentPlayerNumber;
	};

	typedef std::function< void*( void* ) > IClientOnMsgCallbackFuncType;
	typedef std::list< ServerInfo > ServerInfoList;

	/*
	** 名字：IClient
	** 说明：网络客户端接口
	**
	*/
	class IClient
	{
	public:
		virtual ~IClient() {}

		//************************************
		// 函数名:  IClient::SearchGameRoom
		// 返回值:  ServerInfoList
		// 函数修饰:
		// 描述：   查找当前局域网的服务器，我们先暂定端口号为 54321
		//************************************
		virtual ServerInfoList SearchGameRoom() = 0;

		//************************************
		// 函数名:  IClient::EnterGameRoom
		// 返回值:  int
		// 参数:    const std::string & ip
		// 函数修饰:
		// 描述：   加入服务器
		//************************************
		virtual int EnterGameRoom( const std::string& ip ) = 0;

		//************************************
		// 函数名:  IClient::SetOnMsgCallbackFunc
		// 返回值:  void
		// 参数:    IClientOnMsgCallbackFuncType func
		// 函数修饰:
		// 描述：   设置消息到达时的回调处理函数，每次在客户端消息到达时，客户端都应调用
		//			此函数设置的回调函数来处理消息。
		//************************************
		virtual void SetOnMsgCallbackFunc( IClientOnMsgCallbackFuncType func ) = 0;
	};

}


#endif