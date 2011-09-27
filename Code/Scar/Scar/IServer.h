/********************************************************************
����ʱ��: 2011-9-27   15:00
�ļ���:   IServer.h
����:     ���� Cedric Porter [ Stupid ET ]	
˵��:     �������ӿڡ���������Ӧ�ü̳�IServer��ʵ��IServer�Ľӿڣ�
		ϵͳ�����������IServer�ӿڱ��

*********************************************************************/

#ifndef _ISERVER_H
#define _ISERVER_H

#include <string>

namespace Network
{

	/*
	** ���֣�IServer
	** ˵�����������ӿ�
	**
	*/
	class IServer
	{
	public:
		virtual ~IServer() {}

		//************************************
		// ������:  Network::IServer::CreateGameRoom
		// ����ֵ:  int
		// ����:    int maxPlayerNumber					����������
		// ����:    const std::string & gameRoomName		��Ϸ���������
		// ��������:
		// ������   ������Ϸ����
		//************************************
		virtual int CreateGameRoom( 
			int maxPlayerNumber, 
			const std::string& gameRoomName 
			) = 0;

		//************************************
		// ������:  Network::IServer::Start
		// ����ֵ:  int
		// ��������:
		// ������   ������Ϸ���䣬��ʼ���ܿͻ�������
		//************************************
		virtual int Start() = 0;

		//************************************
		// ������:  Network::IServer::Stop
		// ����ֵ:  int
		// ��������:
		// ������   ֹͣ��Ϸ����
		//************************************
		virtual int Stop() = 0;

	};


}



#endif