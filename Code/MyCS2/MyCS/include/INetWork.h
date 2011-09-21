///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/10 16:44
//Describe: 网络模块
///////////////////////////////////////////////////////////////////////

#ifndef  NetWork_INetWork_h
#define  NetWork_INetWork_h

#ifdef	INETWORK_EXPORTS
	#define INETWORK_API __declspec(dllexport)
#else
	#define INETWORK_API __declspec(dllimport)
#endif

#include "NWDefine.h"

namespace Net
{
	typedef void(* OnMsgComeEvent)(unsigned long SenderIP, PACKAGE& msg);

	class INetWork
	{
	public:
		///////////////////////////////////////
		//desc:开始运行网络模块
		//parm [in] OnMsgCome:有消息到达时的回调函数
		//parm [in] port:要监听的端口
		//return:void
		///////////////////////////////////////
		virtual void Run(OnMsgComeEvent OnMsgCome, int port = 3250) = 0;

		//////////////////////////////
		///	@brief 	关闭网络
		///	@return void
		//////////////////////////////
		virtual void Close() = 0;

		virtual ~INetWork(){}
		
	};
	
	///////////////////////////////////////
	//desc:发送数据包
	//parm [in] msg:数据包
	//parm [in] port:端口
	//parm [in] RecverIP:接收者IP地址，如果为NULL则广播此包	
	//return:成功：true 否则:false
	///////////////////////////////////////
	extern "C" INETWORK_API bool SendMessage_char(PACKAGE& msg, int port = 3250, const char* RecverIP = NULL);

	///////////////////////////////////////
	//desc:发送数据包
	//parm [in] msg:数据包
	//parm [in] port:端口
	//parm [in] RecverIP:接收者IP地址，如果为0则广播此包
	//return:成功：true 否则:false
	///////////////////////////////////////
	extern "C" INETWORK_API bool SendMessage(PACKAGE& msg, int port = 3250, unsigned long RecverIP = 0);
	
	///////////////////////////////////////
	//desc:获得本机IP
	//return:
	///////////////////////////////////////
	extern "C" INETWORK_API unsigned long GetIP_long();

	///////////////////////////////////////
	//desc:获得本机IP	
	//return:
	///////////////////////////////////////
	extern "C" INETWORK_API in_addr GetIP_Addr();

	extern "C" INETWORK_API INetWork* CreateNetWork();
}

#endif