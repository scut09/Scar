///////////////////////////////////////////////////////
//  copyright:	Tian's 2009-2010
//  by author:	Tian
//create date:	2009/11/14 3:08
//description:	...
///////////////////////////////////////////////////////

#ifndef CServer_h
#define CServer_h


#pragma once
#include "../../include/IGameLogic.h"

namespace  GameLogic
{	
	void OnMsgCome(unsigned long SenderIP, PACKAGE& msg);

	class CServer : public IServer
	{
	public:
		CServer(void);
		~CServer(void);
		static CServer* g_Server;
	public:
		virtual void	CreateHost(const char * name, const char* mapName);

		virtual void	CancelHost();

		virtual bool	BeignGame();

		virtual int		GetHostState();

		friend void		OnMsgCome(unsigned long SenderIP, PACKAGE& msg);


	private:
		//////////////////////////////
		///	@brief 将消息包发送个服务器中的所有成员
		///	@param [in] msg:
		///	@return void
		//////////////////////////////
		void SendToMember(PACKAGE& msg);
	private:
		char	m_player[4][30];		//玩家名字
		unsigned long m_playerIP[4];	//玩家IP地址
		INetWork* m_network;

		bool	m_gameing;				//是否处于游戏中
		int		m_playCount;			//当前游戏玩家数量

		CreateHostStruct m_hostInfo;

		//char	m_hostName[20];
		//char	m_mapName[30];			//地图名字
	};
}

#endif