///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/11 11:56
//Describe: ������ģʽ �ͻ��� �ӿ�
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
		//desc:����һ����Ϸ
		//parm [in] serverIP:����һ����Ϸ		
		//return:true:����ɹ� false:����ʧ��
		///////////////////////////////////////
		virtual bool JionGame(unsigned long serverIP) = 0;

		///////////////////////////////////////
		//desc:���������������
		//parm [in] msg:Ҫ���͵����ݰ�
		//return:void
		///////////////////////////////////////
		virtual void SendMsg(PACKAGE& msg) = 0;		

	};
}

#endif