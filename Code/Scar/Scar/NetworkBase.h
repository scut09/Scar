/********************************************************************
	����ʱ��: 2011-10-28   2:15
	�ļ���:   NetworkBase.h
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     Server Client�Ļ���

*********************************************************************/

#ifndef NetworkBase_h__
#define NetworkBase_h__

#include <functional>
#include <hash_map>
#include "network_header.h"
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include "NetworkPacket.h"
#include "INetwork.h"
#include "CNetwork.h"

namespace Network
{

	// �յ���Ϣʱ�Ĵ�����������
	typedef std::function< void( unsigned long, const PACKAGE& ) >	MessageHandlerType;


	class NetworkBase
	{
	public:
		virtual ~NetworkBase() {}

		// �յ���Ϣʱ����Ӧ����
		virtual void OnReceive( unsigned long ip, const PACKAGE& p )
		{
			boost::mutex::scoped_lock lock( m_handlerMutex );

			auto funcIter = m_handlerMap.find( p.GetCMD() );
			if ( funcIter != m_handlerMap.end() )
			{
				funcIter->second( ip, p );
				return;
			}

			OtherMessageHandler( ip, p );
		}

		//************************************
		// ����ֵ:  void
		// ����:    int listen_port		// �����Ķ˿ں�
		// ����:    int target_port		// ����ʱ��Ŀ��˿ں�
		// ������   �򿪷�����
		//************************************
		virtual void Start( int listen_port, int target_port, int pool_size = 2 )
		{
			// ��������
			m_network = std::shared_ptr<Network::CNetwork>( new Network::CNetwork( listen_port, target_port, pool_size ) );
			// ע����ܻص�����
			m_network->Start( [this]( unsigned long ip, const PACKAGE& p )
			{
				OnReceive( ip, p );
			} );
		}

		// �ر�
		virtual void Close()
		{
			m_network.reset();
		}

		virtual void OtherMessageHandler( unsigned long ip, const PACKAGE& p )	{}

		// ͬ��tcp����
		virtual void TcpSendTo( unsigned long ip, int port, const PACKAGE& p )
		{
			m_network->TcpSendTo( ip, port, p );
		}
		 
		//************************************
		// ����ֵ:  void
		// ����:    int cmd						��Ϣ���ͣ�Ĭ�ϵ���Ϣ����ȡֵ����0
		// ����:    MessageHandlerType func		������
		// ������   ע����Ϣ������
		//************************************
		virtual void RegisterMessageHandler( int cmd, MessageHandlerType func )
		{
			m_handlerMap[ cmd ] = func;
		}

	protected:
		std::shared_ptr<INetwork>				m_network;		// �ײ�����֧��
		std::hash_map<int, MessageHandlerType>	m_handlerMap;	// ��Ϣ������ӳ��
		boost::mutex							m_handlerMutex;
	};
}

#endif // NetworkBase_h__