///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/11 11:47
//Describe: 游戏逻辑处理
///////////////////////////////////////////////////////////////////////

#ifndef  GameLogic_IGameLogic_h
#define  GameLogic_IGameLogic_h


#ifdef	IGAMELOGIC_EXPORTS
#define IGAMELOGIC_API __declspec(dllexport)
#else
#define IGAMELOGIC_API __declspec(dllimport)
#endif

#include "CMDStruct.h"
#include "INetWork.h"
#include "NWDefine.h"
using namespace Net;

namespace GameLogic
{
	class IClient
	{
	public:
		///////////////////////////////////////
		//desc:加入一个主机
		//parm [in] serverIP:加入一个主机
		//parm [in] name:自己的名字	
		//return:true:加入成功 false:加入失败
		///////////////////////////////////////
		virtual bool JionHost(unsigned long serverIP, const char* name) = 0;

		//////////////////////////////
		///	@brief 查询当前多少主机
		///	@return void
		//////////////////////////////
		virtual void QueryHost() = 0;

		//////////////////////////////
		///	@brief 退出主机		
		///	@return void
		//////////////////////////////
		virtual void ExitHost() = 0;

		//////////////////////////////
		///	@brief 退出游戏		
		///	@return void
		//////////////////////////////
		virtual void ExitGame() = 0;

		//////////////////////////////
		///	@brief 退出 被动退出时调用		
		///	@return void
		//////////////////////////////
		virtual void BeExit() = 0;

		//////////////////////////////
		///	@brief 数据重置
		///	@return void
		//////////////////////////////
		virtual void ReSet() = 0;

		///////////////////////////////////////
		//desc:判断是否已经加入一个主机
		//return:void
		///////////////////////////////////////
		virtual bool IsJionHost() = 0;

		///////////////////////////////////////
		//desc:根据玩家编号 获得玩家名字
		//parm [in] index:玩家编号
		//return:指向名字的指针
		///////////////////////////////////////
		virtual const char* GetName(int index) = 0;

		///////////////////////////////////////
		//desc:	 获得在游戏中的索引
		//return:自己在游戏中的索引
		///////////////////////////////////////
		virtual int	GetIndex() = 0;

		///////////////////////////////////////
		//desc:向服务器发送数据
		//parm [in] msg:要发送的数据包
		//return:void
		///////////////////////////////////////
		virtual void SendMsg(PACKAGE& msg) = 0;

		///////////////////////////////////////
		//desc:设置消息得到时的回调函数	设置为NULL时表示不接受消息
		//parm [in] OnMsgCome:回调函数		
		//return:void
		///////////////////////////////////////
		virtual void SetMsgComeEvent(OnMsgComeEvent OnMsgCome) = 0;

		//////////////////////////////
		///	@brief 查询某个索引位置是否有玩家
		///	@param [in] index:索引号		
		///	@return void
		//////////////////////////////
		virtual bool IsSet(int index) = 0;

		///////////////////////////////////////
		//desc:获得地图名称		
		//return:void
		///////////////////////////////////////
		virtual const char* GetMapName() = 0;

		virtual ~IClient(){};

	};


	class IServer
	{
	public:
		///////////////////////////////////////
		//desc:创建一个服务器
		//parm [in] name:创建者的名字
		//parm [in] mapName:地图名字
		//return:void
		///////////////////////////////////////
		virtual void	CreateHost(const char * name, const char* mapName) = 0;

		///////////////////////////////////////
		//desc:取消服务器创建
		//return:void
		///////////////////////////////////////
		virtual void	CancelHost() = 0;

		///////////////////////////////////////
		//desc:开始游戏
		//return:如果游戏人数为1时返回false
		///////////////////////////////////////
		virtual bool	BeignGame() = 0;

		//////////////////////////////
		///	@brief 获得游戏当前状态
		///	@return 游戏当前状态
		//////////////////////////////
		virtual int		GetHostState() = 0;

		virtual ~IServer(){};

	};


	//////////////////////////////
	///	@brief	创建局域网模式 客户端
	///	@parm [in] OnMsgCome:有消息到达时的回调函数
	///	@return void
	//////////////////////////////
	extern "C" IGAMELOGIC_API IClient* CreateLanClient(OnMsgComeEvent OnMsgCome);

	//////////////////////////////
	///	@brief	创建局域网模式 服务端
	///	@return void
	//////////////////////////////
	extern "C" IGAMELOGIC_API IServer* CreateLanServer();

	//////////////////////////////
	///	@brief	创建单机模式
	///	@return void
	//////////////////////////////
	extern "C" IGAMELOGIC_API void* CreateLocalGame();
}
#endif