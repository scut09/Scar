///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/10 17:25
//Describe: ����� ʵ��
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
		static in_addr		g_Localaddr;				//������ַ
		static in_addr		g_Broadcastaddr;			//�㲥��ַ
		static SOCKET		g_SendSocket;				//�������ݵ�Socket

	public:	
		CNetWork(void);
		~CNetWork(void);

		///////////////////////////////////////
		//desc:��ʼ��������ģ��
		//parm [in] OnMsgCome:����Ϣ����ʱ�Ļص�����
		//parm [in] port:Ҫ�����Ķ˿�
		//return:void
		///////////////////////////////////////
		void Run(OnMsgComeEvent OnMsgCome, int port = 3250);

		//////////////////////////////
		///	@brief 	�ر�����
		///	@return void
		//////////////////////////////
		void Close();

		static	bool InitWinSokcet();

	private:
		//////////////////////////////
		///	@brief ��ʼ���׽���
		///	@return void
		//////////////////////////////
		bool	InitSocket(int port);

		

		
	private:
		HANDLE	m_hThread;			//�������ݵ��߳�
		SOCKET	m_ListenSocket;		//�������ݵ��׽���
		int		m_port;				//�����Ķ˿�
		OnMsgComeEvent m_callBack;	//�ص�
	};

}

#endif