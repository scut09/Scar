///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/11 11:47
//Describe: ��Ϸ�߼�����
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
		//desc:����һ������
		//parm [in] serverIP:����һ������
		//parm [in] name:�Լ�������	
		//return:true:����ɹ� false:����ʧ��
		///////////////////////////////////////
		virtual bool JionHost(unsigned long serverIP, const char* name) = 0;

		//////////////////////////////
		///	@brief ��ѯ��ǰ��������
		///	@return void
		//////////////////////////////
		virtual void QueryHost() = 0;

		//////////////////////////////
		///	@brief �˳�����		
		///	@return void
		//////////////////////////////
		virtual void ExitHost() = 0;

		//////////////////////////////
		///	@brief �˳���Ϸ		
		///	@return void
		//////////////////////////////
		virtual void ExitGame() = 0;

		//////////////////////////////
		///	@brief �˳� �����˳�ʱ����		
		///	@return void
		//////////////////////////////
		virtual void BeExit() = 0;

		//////////////////////////////
		///	@brief ��������
		///	@return void
		//////////////////////////////
		virtual void ReSet() = 0;

		///////////////////////////////////////
		//desc:�ж��Ƿ��Ѿ�����һ������
		//return:void
		///////////////////////////////////////
		virtual bool IsJionHost() = 0;

		///////////////////////////////////////
		//desc:������ұ�� ����������
		//parm [in] index:��ұ��
		//return:ָ�����ֵ�ָ��
		///////////////////////////////////////
		virtual const char* GetName(int index) = 0;

		///////////////////////////////////////
		//desc:	 �������Ϸ�е�����
		//return:�Լ�����Ϸ�е�����
		///////////////////////////////////////
		virtual int	GetIndex() = 0;

		///////////////////////////////////////
		//desc:���������������
		//parm [in] msg:Ҫ���͵����ݰ�
		//return:void
		///////////////////////////////////////
		virtual void SendMsg(PACKAGE& msg) = 0;

		///////////////////////////////////////
		//desc:������Ϣ�õ�ʱ�Ļص�����	����ΪNULLʱ��ʾ��������Ϣ
		//parm [in] OnMsgCome:�ص�����		
		//return:void
		///////////////////////////////////////
		virtual void SetMsgComeEvent(OnMsgComeEvent OnMsgCome) = 0;

		//////////////////////////////
		///	@brief ��ѯĳ������λ���Ƿ������
		///	@param [in] index:������		
		///	@return void
		//////////////////////////////
		virtual bool IsSet(int index) = 0;

		///////////////////////////////////////
		//desc:��õ�ͼ����		
		//return:void
		///////////////////////////////////////
		virtual const char* GetMapName() = 0;

		virtual ~IClient(){};

	};


	class IServer
	{
	public:
		///////////////////////////////////////
		//desc:����һ��������
		//parm [in] name:�����ߵ�����
		//parm [in] mapName:��ͼ����
		//return:void
		///////////////////////////////////////
		virtual void	CreateHost(const char * name, const char* mapName) = 0;

		///////////////////////////////////////
		//desc:ȡ������������
		//return:void
		///////////////////////////////////////
		virtual void	CancelHost() = 0;

		///////////////////////////////////////
		//desc:��ʼ��Ϸ
		//return:�����Ϸ����Ϊ1ʱ����false
		///////////////////////////////////////
		virtual bool	BeignGame() = 0;

		//////////////////////////////
		///	@brief �����Ϸ��ǰ״̬
		///	@return ��Ϸ��ǰ״̬
		//////////////////////////////
		virtual int		GetHostState() = 0;

		virtual ~IServer(){};

	};


	//////////////////////////////
	///	@brief	����������ģʽ �ͻ���
	///	@parm [in] OnMsgCome:����Ϣ����ʱ�Ļص�����
	///	@return void
	//////////////////////////////
	extern "C" IGAMELOGIC_API IClient* CreateLanClient(OnMsgComeEvent OnMsgCome);

	//////////////////////////////
	///	@brief	����������ģʽ �����
	///	@return void
	//////////////////////////////
	extern "C" IGAMELOGIC_API IServer* CreateLanServer();

	//////////////////////////////
	///	@brief	��������ģʽ
	///	@return void
	//////////////////////////////
	extern "C" IGAMELOGIC_API void* CreateLocalGame();
}
#endif