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
#include "GameBag.h"

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

		virtual void Close();

		// ��Ϣ������
		void OnBroadcastRoom( unsigned long ip, const PACKAGE& p );
		void OnAllowJoinRoom( unsigned long ip, const PACKAGE& p );
		void OnHeroMove( unsigned long ip, const PACKAGE& p );
		void OnHeroRotate( unsigned long ip, const PACKAGE& p );
		void OnNewPlayerJoin( unsigned long ip, const PACKAGE& p );
		void OnBulletCreate( unsigned long ip, const PACKAGE& p );
		// ������Ϣ����
		virtual void OtherMessageHandler( unsigned long ip, const PACKAGE& p );

		// �򿪿ͻ���
		virtual void Start( int listen_port, int target_port );

		
		void QueryRoom();											// �㲥��ѯ����		
		void EnterRoom( const std::string& ip );					// ���뷿��		
		void SendHeroMove( int index, float x, float y, float z );	// ��������ƶ�		
		void SendHeroRot( int index, float x, float y , float z );	// ��������������ת
		void SendBullet( int index, int bullet_type, 
			const irr::core::vector3df& start, const irr::core::vector3df& end, u32 life );


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
	};


}


#endif // Boost_Client_h__
