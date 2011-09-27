/********************************************************************
	����ʱ��: 2011:9:27   14:53
	�ļ���:   IClient.h
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     

*********************************************************************/

#ifndef _ICLIENT_H_
#define _ICLIENT_H_

#include <functional>
#include <string>
#include <list>


struct ServerInfo
{
	std::string ip;
	std::string serverName;
	int			maxPlayerNumber;
	int			currentPlayerNumber;
};

typedef std::function< void*( void* ) > IClientOnMsgCallbackFuncType;
typedef std::list< ServerInfo > IPList;

/*
** ���֣�IClient
** ˵��������ͻ��˽ӿ�
**
*/
class IClient
{
public:
	//************************************
	// ������:  IClient::SearchGameRoom
	// ����ֵ:  IPList
	// ��������:
	// ������   ���ҵ�ǰ�������ķ��������������ݶ��˿ں�Ϊ 54321
	//************************************
	virtual IPList SearchGameRoom() = 0;

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
	// ������   ������Ϣ����ʱ�Ļص���������ÿ���ڿͻ�����Ϣ����ʱ���ͻ��˶�Ӧ���ô˺���
	//			��������Ϣ��
	//************************************
	virtual void SetOnMsgCallbackFunc( IClientOnMsgCallbackFuncType func ) = 0;
};

#endif