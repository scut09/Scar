/********************************************************************
    创建时间: 2011-10-25   20:25
    文件名:   Server.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     服务端

*********************************************************************/

#ifndef Boost_Server_h__
#define Boost_Server_h__

#include "CNetwork.h"
#include "NetworkBase.h"
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

namespace Network
{
	// 服务器
	class BoostServer : public NetworkBase
	{
	public:
		BoostServer();

		// 消息处理函数
		virtual void OtherMessageHandler( unsigned long ip, const PACKAGE& p );
		void QueryRoomHandler( unsigned long ip, const PACKAGE& p );
		void RequestEnterRoomHandler( unsigned long ip, const PACKAGE& p );

	private:
		std::list<PlayerInfo>					m_playerList;	// 玩家列表
		std::set<std::string>					m_localIP;		// 本地IP
	};


}

#endif // Boost_Server_h__
