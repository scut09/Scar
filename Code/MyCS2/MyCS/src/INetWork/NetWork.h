///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/10 17:25
//Describe: 网络层 实现
///////////////////////////////////////////////////////////////////////

#ifndef  NetWork_CNetWork_h
#define  NetWork_CNetWork_h
#pragma once

#include <WinSock2.h>
#include "..\..\include\INetWork.h"

#pragma comment( lib, "ws2_32.lib" )

namespace Net
{
	DWORD WINAPI ThreadProc(LPVOID lpParameter);
	
	

	struct ThreadParam
	{
		SOCKET m_s;
		OnMsgComeEvent m_fun;
	};

	class CNetWork:INetWork
	{
	public:
		static in_addr		g_Localaddr;				//本机地址
		static in_addr		g_Broadcastaddr;			//广播地址
		static SOCKET		g_SendSocket;				//发送数据的Socket

	public:	
		CNetWork(void);
		~CNetWork(void);

		///////////////////////////////////////
		//desc:开始运行网络模块
		//parm [in] OnMsgCome:有消息到达时的回调函数
		//parm [in] port:要监听的端口
		//return:void
		///////////////////////////////////////
		void Run(OnMsgComeEvent OnMsgCome, int port = 3250);

		//////////////////////////////
		///	@brief 	关闭网络
		///	@return void
		//////////////////////////////
		void Close();

		static	bool InitWinSokcet();

	private:
		//////////////////////////////
		///	@brief 初始化套接字
		///	@return void
		//////////////////////////////
		bool	InitSocket(int port);

		

		
	private:
		HANDLE	m_hThread;			//接收数据的线程
		SOCKET	m_ListenSocket;		//接收数据的套接字
		int		m_port;				//监听的端口
		OnMsgComeEvent m_callBack;	//回调
	};

}

#endif