/********************************************************************
    ����ʱ��: 2011-10-26   2:42
    �ļ���:   CNetwork.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     ����ӿڵ�ʵ�֣��ṩһ��������Ϣ�Ŀ�ܣ������Զ�����Ϣ����ص�������
			����Ҳ����ͨ���䷢�ͣ�����udpʵ��

*********************************************************************/


#ifndef CNetwork_h__
#define CNetwork_h__

#include "INetwork.h"
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <vector>
#include <string>
#include <set>

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using boost::asio::ip::udp;

	struct PlayerInfo
	{
		int				index;
		unsigned long	ip;

		PlayerInfo( int i, unsigned long IP ) : ip( IP ), index( i ) {}
		PlayerInfo() {}
	};

	class CNetwork : public INetwork
	{
	public:
		CNetwork( int port, int target_port );

		~CNetwork();

		// ��ʼ����������Ϣ
		virtual void Start( INetworkCallbackType func );

		// �ر�����
		virtual void Close();

		// ���ͣ������ַ�����ʽ��ip
		virtual void Send( const std::string& ip, const PACKAGE& pack );

		// ���ͣ�����������ʽ��ip		
		virtual void Send( unsigned long ip, const PACKAGE& pack );

		// ֧�ֶ������Ĺ㲥
		virtual void Broadcast( const PACKAGE& pack );

	private:
			
		// �����߳������У����������Ϣ�����ûص�����������Ϣ
		void Run();


	private:
		// ����ÿ���������Լ���IP,�Ա��ڶ������㲥
		void SaveBroadcastIPAddress();


	private:
		INetworkCallbackType			m_func;			// ��Ϣ������
		std::shared_ptr<boost::thread>	m_thread;		// ������Ϣ���̵߳�ָ��
		std::shared_ptr<ip::udp::socket>m_send_sock;	// ���͵�socket
		ip::udp::endpoint				m_broadcast_ep;	// �㲥�ĵ�ַ
		io_service						io;				// ǰ����ģʽ
		int								m_listen_port;	// �����Ķ˿�
		int								m_target_port;	// Ŀ��Ķ˿�
		std::set<unsigned long>			m_broadcast_ip;	// �㲥IP

	};
}


#endif // CNetwork_h__