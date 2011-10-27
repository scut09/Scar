/********************************************************************
    ����ʱ��: 2011-10-26   2:42
    �ļ���:   CNetwork.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     ����ӿڵ�ʵ�֣��ṩһ��������Ϣ�Ŀ�ܣ������Զ�����Ϣ����ص�������
			����Ҳ����ͨ���䷢�ͣ�����udpʵ��

*********************************************************************/


#ifndef CNetwork_h__
#define CNetwork_h__

#include "Buffer.h"
#include "INetwork.h"
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <set>
#include <string>
#include <vector>

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using boost::asio::ip::udp;

	struct PACKAGE;

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
		CNetwork( int listen_port, int target_port );

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

		// �����߳��д�����Ϣ�����е�����
		void Handle();


	private:
		// ����ÿ���������Լ���IP,�Ա��ڶ������㲥
		void CreateBroadcastIPAddress();


		struct IP_Package
		{
			unsigned long ip;
			PACKAGE pack;

			IP_Package() {}
			IP_Package( unsigned long IP, const PACKAGE& p )
				: ip( IP ), pack( p ) 
			{}
		};


	private:
		Buffer<IP_Package>					m_packetBuffer;	// ������
		INetworkCallbackType				m_func;			// ��Ϣ������
		int									m_listen_port;	// �����Ķ˿�
		int									m_target_port;	// Ŀ��Ķ˿�
		io_service							io;				// ǰ����ģʽ
		ip::udp::endpoint					m_broadcast_ep;	// �㲥�ĵ�ַ
		std::set<unsigned long>				m_broadcast_ip;	// �㲥IP
		std::shared_ptr<boost::thread>		m_handle_thread;// ������Ϣ���̵߳�ָ��
		std::shared_ptr<boost::thread>		m_socket_thread;// ������Ϣ���̵߳�ָ��
		std::shared_ptr<ip::udp::socket>	m_receive_sock; // ����udp��socket
		std::shared_ptr<ip::udp::socket>	m_send_sock;	// ���͵�socket


	};
}


#endif // CNetwork_h__