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
#include <boost/thread/mutex.hpp>
#include <vector>
#include <string>
#include <set>
#include <queue>

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using boost::asio::ip::udp;

	// ���������������ߵĻ��壬�����Get��ʱ�򻺳�Ϊ�գ���������ֱ����Ϊ��
	template< typename T >
	class Buffer
	{
		std::queue<T>	m_queue;
		boost::mutex	m_mutex;
		boost::condition_variable_any m_cond_get;

	public:
		void Put( const T& element )
		{
			{
				boost::mutex::scoped_lock lock( m_mutex );
				m_queue.push( element );
			}

			m_cond_get.notify_one();
		}

		T Get()
		{
			T head;

			{
				boost::mutex::scoped_lock lock( m_mutex );

				if ( m_queue.empty() )
				{
					m_cond_get.wait( m_mutex );
				}

				head = m_queue.front();
				m_queue.pop();
			}

			return head;
		}

		bool IsEmpty() const
		{
			boost::mutex::scoped_lock lock( m_mutex );
			
			return m_queue.empty();
		}
	};

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

		void Handle();


	private:
		// ����ÿ���������Լ���IP,�Ա��ڶ������㲥
		void SaveBroadcastIPAddress();


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
		INetworkCallbackType			m_func;			// ��Ϣ������
		std::shared_ptr<boost::thread>	m_socket_thread;		// ������Ϣ���̵߳�ָ��
		std::shared_ptr<boost::thread>	m_handle_thread;// ������Ϣ���̵߳�ָ��

		std::shared_ptr<ip::udp::socket>m_send_sock;	// ���͵�socket
		ip::udp::endpoint				m_broadcast_ep;	// �㲥�ĵ�ַ
		io_service						io;				// ǰ����ģʽ
		int								m_listen_port;	// �����Ķ˿�
		int								m_target_port;	// Ŀ��Ķ˿�
		std::set<unsigned long>			m_broadcast_ip;	// �㲥IP
		Buffer<IP_Package>			m_packetBuffer;	// ������

	};
}


#endif // CNetwork_h__