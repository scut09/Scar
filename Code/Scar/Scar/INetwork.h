/********************************************************************
    ����ʱ��: 2011-10-26   1:32
    �ļ���:   INetwork.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     ��������ӿڡ��ṩע����Ϣ���������յ�udp��Ϣ�����ô˻ص�����

*********************************************************************/


#ifndef INetwork_h__
#define INetwork_h__

#include <functional>
#include <string>
#include "NetworkPacket.h"

namespace Network
{
	typedef std::function< void( unsigned long, const PACKAGE& ) >	INetworkCallbackType;

	struct PACKAGE;

	class INetwork
	{
	public:
		virtual ~INetwork() {}

		virtual void AddPackageToBuffer( const PACKAGE& p ) = 0;

		// ��ʼ����������Ϣ
		virtual void Start( INetworkCallbackType func ) = 0;

		// �ر�����
		virtual void Close() = 0;

		// ���ͣ������ַ�����ʽ��ip
		virtual void SendTo( const std::string& ip, const PACKAGE& pack ) = 0;

		// ���ͣ�����������ʽ��ip		
		virtual void SendTo( unsigned long ip, const PACKAGE& pack ) = 0;

		virtual void TcpSendTo( unsigned long ip, int port, const PACKAGE& p ) = 0;

		// ֧�ֶ������Ĺ㲥
		virtual void Broadcast( const PACKAGE& pack ) = 0;		

	};
}


#endif // INetwork_h__