///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/11 11:56
//Describe: 局域网模式 客户端 接口
///////////////////////////////////////////////////////////////////////

#ifndef  IClient_h
#define  IClient_h

#include "NWDefine.h"
using namespace Net;

namespace GameLogic
{
	class IClient
	{
		///////////////////////////////////////
		//desc:加入一个游戏
		//parm [in] serverIP:加入一个游戏		
		//return:true:加入成功 false:加入失败
		///////////////////////////////////////
		virtual bool JionGame(unsigned long serverIP) = 0;

		///////////////////////////////////////
		//desc:向服务器发送数据
		//parm [in] msg:要发送的数据包
		//return:void
		///////////////////////////////////////
		virtual void SendMsg(PACKAGE& msg) = 0;		

	};
}

#endif