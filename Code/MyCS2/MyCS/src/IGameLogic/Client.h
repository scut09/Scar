///////////////////////////////////////////////////////
//  copyright:	Tian's 2009-2010
//  by author:	Tian
//create date:	2009/11/15 0:11
//description:	�ͻ���ʵ��
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
		//desc:����һ����Ϸ
		//parm [in] serverIP:����һ����Ϸ		
		//return:true:����ɹ� false:����ʧ��
		///////////////////////////////////////
		bool JionHost(unsigned long serverIP, const char* name);

		//////////////////////////////
		///	@brief ��ѯ��ǰ��������
		///	@return void
		//////////////////////////////
		void QueryHost();

		//////////////////////////////
		///	@brief �˳�����		
		///	@param [in] sendMsg:�Ƿ�֪ͨ����		
		///	@return void
		//////////////////////////////
		void ExitHost();

		//////////////////////////////
		///	@brief �˳���Ϸ
		///	@return void
		//////////////////////////////
		void ExitGame();

		void BeExit();

		//////////////////////////////
		///	@brief ����		
		///	@return void
		//////////////////////////////
		void ReSet();

		///////////////////////////////
		//desc:�������Ϸ�е�����
		//return:�Լ�����Ϸ�е�����
		///////////////////////////////
		int	GetIndex();

		///////////////////////////////////////
		//desc:�ж��Ƿ��Ѿ�����һ������
		//return:void
		///////////////////////////////////////
		bool IsJionHost();

		///////////////////////////////////////
		//desc:������ұ�� ����������
		//parm [in] index:��ұ��
		//return:ָ�����ֵ�ָ��
		///////////////////////////////////////
		const char* GetName(int index);

		///////////////////////////////////////
		//desc:���������������
		//parm [in] msg:Ҫ���͵����ݰ�
		//return:void
		///////////////////////////////////////
		void SendMsg(PACKAGE& msg);

		///////////////////////////////////////
		//desc:������Ϣ�õ�ʱ�Ļص�����
		//parm [in] OnMsgCome:�ص�����		
		//return:void
		///////////////////////////////////////
		void SetMsgComeEvent(OnMsgComeEvent OnMsgCome);

		//////////////////////////////
		///	@brief ��ѯĳ������λ���Ƿ������
		///	@param [in] index:������		
		///	@return void
		//////////////////////////////
		bool IsSet(int index);

		///////////////////////////////////////
		//desc:��õ�ͼ����		
		//return:void
		///////////////////////////////////////
		const char* GetMapName();

		
	private:
		INetWork*			m_network;
		int					m_myIndex;		//�Լ���������
		char				m_mapName[30];	//��ͼ����
		unsigned long		m_HostIP;		//����IP
		OnMsgComeEvent		m_OnMsgCome;
		char				m_playerName[4][MyNameLength];
		bool				m_isNull[4];		//������λ���Ƿ�����

		static	CClient*	g_Client;
		static	int			m_isJionOK;	//��Ǽ�����Ϸ�Ƿ�ɹ�
		PACKAGE				m_package;	
	};

}
#endif