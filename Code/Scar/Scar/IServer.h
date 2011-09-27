/********************************************************************
创建时间: 2011-9-27   15:00
文件名:   IServer.h
作者:     华亮 Cedric Porter [ Stupid ET ]	
说明:     服务器接口。服务器端应该继承IServer并实现IServer的接口，
		系统其他部分针对IServer接口编程

*********************************************************************/

#ifndef _ISERVER_H
#define _ISERVER_H

#include <string>

namespace Network
{

	/*
	** 名字：IServer
	** 说明：服务器接口
	**
	*/
	class IServer
	{
	public:
		virtual ~IServer() {}

		//************************************
		// 函数名:  Network::IServer::CreateGameRoom
		// 返回值:  int
		// 参数:    int maxPlayerNumber					最大玩家数量
		// 参数:    const std::string & gameRoomName		游戏房间的名字
		// 函数修饰:
		// 描述：   创建游戏房间
		//************************************
		virtual int CreateGameRoom( 
			int maxPlayerNumber, 
			const std::string& gameRoomName 
			) = 0;

		//************************************
		// 函数名:  Network::IServer::Start
		// 返回值:  int
		// 函数修饰:
		// 描述：   启动游戏房间，开始接受客户端连接
		//************************************
		virtual int Start() = 0;

		//************************************
		// 函数名:  Network::IServer::Stop
		// 返回值:  int
		// 函数修饰:
		// 描述：   停止游戏房间
		//************************************
		virtual int Stop() = 0;

	};


}



#endif