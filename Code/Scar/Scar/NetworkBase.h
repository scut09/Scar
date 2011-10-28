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
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include "NetworkPacket.h"
#include "INetwork.h"

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using namespace boost::asio::ip;

	// �յ���Ϣʱ�Ĵ�����������
	typedef std::function< void( unsigned long, const PACKAGE& ) >	MessageHandlerType;

	class NetworkBase
	{
	public:
		virtual ~NetworkBase() {}

		// �յ���Ϣʱ����Ӧ����
		virtual void OnReceive( unsigned long ip, const PACKAGE& p )
		{
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
		virtual void Start( int listen_port, int target_port )
		{
			// ��������
			m_network = std::shared_ptr<Network::CNetwork>( new Network::CNetwork( listen_port, target_port ) );
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

	};
}

#endif // NetworkBase_h__