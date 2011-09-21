///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/10 16:44
//Describe: ����ģ��
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
		//desc:��ʼ��������ģ��
		//parm [in] OnMsgCome:����Ϣ����ʱ�Ļص�����
		//parm [in] port:Ҫ�����Ķ˿�
		//return:void
		///////////////////////////////////////
		virtual void Run(OnMsgComeEvent OnMsgCome, int port = 3250) = 0;

		//////////////////////////////
		///	@brief 	�ر�����
		///	@return void
		//////////////////////////////
		virtual void Close() = 0;

		virtual ~INetWork(){}
		
	};
	
	///////////////////////////////////////
	//desc:�������ݰ�
	//parm [in] msg:���ݰ�
	//parm [in] port:�˿�
	//parm [in] RecverIP:������IP��ַ�����ΪNULL��㲥�˰�	
	//return:�ɹ���true ����:false
	///////////////////////////////////////
	extern "C" INETWORK_API bool SendMessage_char(PACKAGE& msg, int port = 3250, const char* RecverIP = NULL);

	///////////////////////////////////////
	//desc:�������ݰ�
	//parm [in] msg:���ݰ�
	//parm [in] port:�˿�
	//parm [in] RecverIP:������IP��ַ�����Ϊ0��㲥�˰�
	//return:�ɹ���true ����:false
	///////////////////////////////////////
	extern "C" INETWORK_API bool SendMessage(PACKAGE& msg, int port = 3250, unsigned long RecverIP = 0);
	
	///////////////////////////////////////
	//desc:��ñ���IP
	//return:
	///////////////////////////////////////
	extern "C" INETWORK_API unsigned long GetIP_long();

	///////////////////////////////////////
	//desc:��ñ���IP	
	//return:
	///////////////////////////////////////
	extern "C" INETWORK_API in_addr GetIP_Addr();

	extern "C" INETWORK_API INetWork* CreateNetWork();
}

#endif