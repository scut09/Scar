///////////////////////////////////////////////////////
//  copyright:	Tian's 2009-2010
//  by author:	Tian
//create date:	2009/11/14 3:08
//description:	...
///////////////////////////////////////////////////////

#ifndef CServer_h
#define CServer_h


#pragma once
#include "../../include/IGameLogic.h"

namespace  GameLogic
{	
	void OnMsgCome(unsigned long SenderIP, PACKAGE& msg);

	class CServer : public IServer
	{
	public:
		CServer(void);
		~CServer(void);
		static CServer* g_Server;
	public:
		virtual void	CreateHost(const char * name, const char* mapName);

		virtual void	CancelHost();

		virtual bool	BeignGame();

		virtual int		GetHostState();

		friend void		OnMsgCome(unsigned long SenderIP, PACKAGE& msg);


	private:
		//////////////////////////////
		///	@brief ����Ϣ�����͸��������е����г�Ա
		///	@param [in] msg:
		///	@return void
		//////////////////////////////
		void SendToMember(PACKAGE& msg);
	private:
		char	m_player[4][30];		//�������
		unsigned long m_playerIP[4];	//���IP��ַ
		INetWork* m_network;

		bool	m_gameing;				//�Ƿ�����Ϸ��
		int		m_playCount;			//��ǰ��Ϸ�������

		CreateHostStruct m_hostInfo;

		//char	m_hostName[20];
		//char	m_mapName[30];			//��ͼ����
	};
}

#endif