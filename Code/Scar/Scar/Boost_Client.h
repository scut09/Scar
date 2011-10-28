/********************************************************************
    ����ʱ��: 2011-10-25   20:25
    �ļ���:   Client.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     �ͻ���

*********************************************************************/

#ifndef Boost_Client_h__
#define Boost_Client_h__


#include "CNetwork.h"
#include "IShip.h"
#include "NetworkBase.h"
#include "NetworkPacket.h"
#include <irrlicht.h>
#include <map>
#include <set>
#include <vector>

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using namespace boost::asio::ip;

	struct BroadcastRoomBag;

	class BoostClient : public NetworkBase
	{
	public:
		BoostClient();

		~BoostClient()
		{
			Close();
		}

		virtual void Close()
		{
			m_io_thread->interrupt();
			NetworkBase::Close();
		}

		// ��Ϣ������
		void BroadcastRoomHandler( unsigned long ip, const PACKAGE& p );
		void AllowJoinRoomHandler( unsigned long ip, const PACKAGE& p );
		void HeroMoveHandler( unsigned long ip, const PACKAGE& p );
		void HeroRotateHandler( unsigned long ip, const PACKAGE& p );
		void NewPlayerJoinHandler( unsigned long ip, const PACKAGE& p );
		// ������Ϣ����
		virtual void OtherMessageHandler( unsigned long ip, const PACKAGE& p );

		// ʹ��TCP�첽����
		void TcpSendTo( int ip, const PACKAGE& p );

		// �򿪿ͻ���
		virtual void Start( int listen_port, int target_port );

		// �㲥��ѯ����
		void QueryRoom();
		// ���뷿��
		void EnterRoom( const std::string& ip );
		// ��������ƶ�
		void SendHeroMove( int index, float x, float y, float z );
		// ��������������ת
		void SendHeroRot( int index, float x, float y , float z );
		// ��ȡ�����б�
		const std::map<std::string, BroadcastRoomBag>& GetRooms() const;
		// ��ȡ����IP
		const std::set<std::string>& GetLocalIP() const;

	private:
		void SaveLocalIPAddress();

	private:
		// �������������Ϣ����ʱ��Ҫ�ֵ�����������������Ϊ�˷�����ʱ������
		std::hash_map<int, irr::scene::ISceneNode*>			m_players;

	public:
		int										m_index;

	private:
		int										m_target_port;
		std::map<std::string, BroadcastRoomBag>	m_roomMap;
		std::set<std::string>					m_localIP;
		unsigned long							m_server_IP;
		io_service								io;
		std::shared_ptr<boost::thread>			m_io_thread;
	};


}


#endif // Boost_Client_h__
