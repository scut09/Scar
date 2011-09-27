/********************************************************************
����ʱ��: 2011:9:27   14:53
�ļ���:   IClient.h
����:     ���� Cedric Porter [ Stupid ET ]	
˵��:     �ͻ��˽ӿڡ��ͻ��˶�Ӧ�ü̳�IClient��ʵ��IClient�Ľӿڣ�
		ϵͳ�����������IClient�ӿڱ��  

*********************************************************************/

#ifndef _ICLIENT_H_
#define _ICLIENT_H_

#include <functional>
#include <string>
#include <list>

namespace Network
{
	/*
	** ���֣�ServerInfo
	** ˵������IClient���صĵ�ǰ����������������Ϣ
	**
	*/
	struct ServerInfo
	{
		std::string ip;
		std::string roomName;
		int			maxPlayerNumber;
		int			currentPlayerNumber;
	};

	typedef std::function< void*( void* ) > IClientOnMsgCallbackFuncType;
	typedef std::list< ServerInfo > ServerInfoList;

	/*
	** ���֣�IClient
	** ˵��������ͻ��˽ӿ�
	**
	*/
	class IClient
	{
	public:
		virtual ~IClient() {}

		//************************************
		// ������:  IClient::SearchGameRoom
		// ����ֵ:  ServerInfoList
		// ��������:
		// ������   ���ҵ�ǰ�������ķ��������������ݶ��˿ں�Ϊ 54321
		//************************************
		virtual ServerInfoList SearchGameRoom() = 0;

		//************************************
		// ������:  IClient::EnterGameRoom
		// ����ֵ:  int
		// ����:    const std::string & ip
		// ��������:
		// ������   ���������
		//************************************
		virtual int EnterGameRoom( const std::string& ip ) = 0;

		//************************************
		// ������:  IClient::SetOnMsgCallbackFunc
		// ����ֵ:  void
		// ����:    IClientOnMsgCallbackFuncType func
		// ��������:
		// ������   ������Ϣ����ʱ�Ļص���������ÿ���ڿͻ�����Ϣ����ʱ���ͻ��˶�Ӧ����
		//			�˺������õĻص�������������Ϣ��
		//************************************
		virtual void SetOnMsgCallbackFunc( IClientOnMsgCallbackFuncType func ) = 0;
	};

}


#endif