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

	class INetwork
	{
	public:
		virtual ~INetwork() {}

		// ��ʼ����������Ϣ
		virtual void Start( INetworkCallbackType func ) = 0;

		// �ر�����
		virtual void Close() = 0;

		// ���ͣ������ַ�����ʽ��ip
		virtual void Send( const std::string& ip, const PACKAGE& pack ) = 0;

		// ���ͣ�����������ʽ��ip		
		virtual void Send( unsigned long ip, const PACKAGE& pack ) = 0;

		// ֧�ֶ������Ĺ㲥
		virtual void Broadcast( const PACKAGE& pack ) = 0;		

	};
}


#endif // INetwork_h__