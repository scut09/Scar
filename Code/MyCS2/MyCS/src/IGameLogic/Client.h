///////////////////////////////////////////////////////
//  copyright:	Tian's 2009-2010
//  by author:	Tian
//create date:	2009/11/15 0:11
//description:	客户端实现
///////////////////////////////////////////////////////

#ifndef CClient_h
#define CClient_h
#pragma once
#include "../../include/IGameLogic.h"

namespace GameLogic
{
	void OnCMsgCome(unsigned long SenderIP, PACKAGE& msg);

	class CClient:public IClient
	{
	public:
		CClient(void);
		~CClient(void);
		friend IGAMELOGIC_API IClient* CreateLanClient(OnMsgComeEvent OnMsgCome);
		friend void OnCMsgCome(unsigned long SenderIP, PACKAGE& msg);

	public:
		///////////////////////////////////////
		//desc:加入一个游戏
		//parm [in] serverIP:加入一个游戏		
		//return:true:加入成功 false:加入失败
		///////////////////////////////////////
		bool JionHost(unsigned long serverIP, const char* name);

		//////////////////////////////
		///	@brief 查询当前多少主机
		///	@return void
		//////////////////////////////
		void QueryHost();

		//////////////////////////////
		///	@brief 退出主机		
		///	@param [in] sendMsg:是否通知主机		
		///	@return void
		//////////////////////////////
		void ExitHost();

		//////////////////////////////
		///	@brief 退出游戏
		///	@return void
		//////////////////////////////
		void ExitGame();

		void BeExit();

		//////////////////////////////
		///	@brief 重置		
		///	@return void
		//////////////////////////////
		void ReSet();

		///////////////////////////////
		//desc:获得在游戏中的索引
		//return:自己在游戏中的索引
		///////////////////////////////
		int	GetIndex();

		///////////////////////////////////////
		//desc:判断是否已经加入一个主机
		//return:void
		///////////////////////////////////////
		bool IsJionHost();

		///////////////////////////////////////
		//desc:根据玩家编号 获得玩家名字
		//parm [in] index:玩家编号
		//return:指向名字的指针
		///////////////////////////////////////
		const char* GetName(int index);

		///////////////////////////////////////
		//desc:向服务器发送数据
		//parm [in] msg:要发送的数据包
		//return:void
		///////////////////////////////////////
		void SendMsg(PACKAGE& msg);

		///////////////////////////////////////
		//desc:设置消息得到时的回调函数
		//parm [in] OnMsgCome:回调函数		
		//return:void
		///////////////////////////////////////
		void SetMsgComeEvent(OnMsgComeEvent OnMsgCome);

		//////////////////////////////
		///	@brief 查询某个索引位置是否有玩家
		///	@param [in] index:索引号		
		///	@return void
		//////////////////////////////
		bool IsSet(int index);

		///////////////////////////////////////
		//desc:获得地图名称		
		//return:void
		///////////////////////////////////////
		const char* GetMapName();

		
	private:
		INetWork*			m_network;
		int					m_myIndex;		//自己的索引号
		char				m_mapName[30];	//地图名称
		unsigned long		m_HostIP;		//主机IP
		OnMsgComeEvent		m_OnMsgCome;
		char				m_playerName[4][MyNameLength];
		bool				m_isNull[4];		//标记这个位置是否有人

		static	CClient*	g_Client;
		static	int			m_isJionOK;	//标记加入游戏是否成功
		PACKAGE				m_package;	
	};

}
#endif