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
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <set>
#include <string>
#include <list>
#include <vector>
#include <hash_map>
#include "network_header.h"
#include "io_service_pool.h"

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using boost::asio::ip::udp;

	const int BUFFER_SIZE = 1472;

	struct PACKAGE;

	struct PlayerInfo
	{
		int				index;
		unsigned long	ip;

		PlayerInfo( int i, unsigned long IP ) : ip( IP ), index( i ) {}
		PlayerInfo() {}
	};

	struct IP_Package
	{
		unsigned long ip;
		PACKAGE pack;

		IP_Package() {}
		IP_Package( unsigned long IP, const PACKAGE& p )
			: ip( IP ), pack( p ) 
		{}
	};

	typedef std::shared_ptr<boost::asio::ip::tcp::socket> TCPSocketPointerType;
	typedef std::hash_map< unsigned long, std::shared_ptr<boost::asio::ip::tcp::socket> > TCP_IP_Socket_MapType;

	/*
	** ���֣�CNetwork
	** ˵�����ṩ�������繦��
	**
	*/
	class CNetwork : public INetwork
	{
	public:
		CNetwork( int listen_port, int target_port, int pool_size = 2 );

		~CNetwork();

		// ��ʼ����������Ϣ
		virtual void Start( INetworkCallbackType func );

		// �ر�����
		virtual void Close();

		// udp���ͣ������ַ�����ʽ��ip
		virtual void SendTo( const std::string& ip, const PACKAGE& pack );

		// udp���ͣ�����������ʽ��ip		
		virtual void SendTo( unsigned long ip, const PACKAGE& pack );

		// ֧�ֶ������Ĺ㲥
		virtual void Broadcast( const PACKAGE& pack );

		// ͬ��tcp����
		virtual void TcpSendTo( unsigned long ip, int port, const PACKAGE& p );

		void tcp_write_handler( const boost::system::error_code& ec,
			std::shared_ptr<ip::tcp::socket> sock, std::shared_ptr<PACKAGE> pack );

	private:
		// �����߳��д�����Ϣ�����е�����
		void Message_Handler();

		// TCP����
		void StartTCP();
		// ����tcp������ʱ�������socket
		void TCPAcceptHandler( const boost::system::error_code& ec, TCPSocketPointerType sock );
		// TCP�յ���Ϣ
		void TCPReadHandler( const boost::system::error_code& ec, TCPSocketPointerType sock, std::shared_ptr< std::vector<char> > buf );
		
		// UDP����
		void StartUDP();
		// UDP������
		void UDPReadhandler(const boost::system::error_code& error,
			std::size_t /*bytes_transferred*/, std::shared_ptr<ip::udp::endpoint> ep, 
			std::shared_ptr< std::vector<char> > buf );


	private:
		// ����ÿ���������Լ���IP,�Ա��ڶ������㲥
		void CreateBroadcastIPAddress();


	private:
		Buffer<IP_Package>					m_packetBuffer;			// �յ������ݰ�����
		INetworkCallbackType				m_func;					// ��Ϣ������
		int									m_listen_port;			// �����Ķ˿�
		int									m_target_port;			// Ŀ��Ķ˿�
		ip::udp::endpoint					m_broadcast_ep;			// �㲥�ĵ�ַ
		std::set<unsigned long>				m_broadcast_ip;			// �㲥IP
		std::shared_ptr<boost::thread>		m_handle_thread;		// ������Ϣ���̵߳�ָ��
		std::shared_ptr<boost::thread>		m_io_thread;			// io���̵߳�ָ��
		ip::udp::socket*	m_receive_sock;			// ����udp��socket
		ip::udp::socket*	m_send_sock;			// ���͵�socket
		ip::tcp::acceptor*	m_acceptor;				// tcp��acceptor
		io_service_pool						m_pool;					// io_service pool
		TCP_IP_Socket_MapType				m_ip_socketMap;			// ip��tcp socket��ӳ��

	};
}


#endif // CNetwork_h__