/********************************************************************
    ����ʱ��: 2011-10-25   20:25
    �ļ���:   Client.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     �ͻ���

*********************************************************************/

#ifndef Boost_Client_h__
#define Boost_Client_h__


//#include "PlayerHelper.h"
#include "CNetwork.h"
#include "GameBag.h"
#include "IClient.h"
#include "IShip.h"
#include "NetworkBase.h"
#include "NetworkPacket.h"
#include <irrlicht.h>
#include <map>
#include <set>
#include <vector>

class PlayerManager;
class PlayerHelper;

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using namespace boost::asio::ip;

	struct BroadcastRoomBag;

	class BoostClient : public NetworkBase, public IClient
	{
	public:
		BoostClient( boost::shared_ptr<PlayerManager>	playerManager );

		~BoostClient()
		{
			Close();
		}

		void SetPlayerHelp( boost::shared_ptr<PlayerHelper> playerHelp )
		{
			m_PlayerHelper = playerHelp;
		}

		virtual void Close();

		/************************************************************************/
		/* ��Ϣ������                                                          */
		/************************************************************************/
		void OnBroadcastRoom( unsigned long ip, const PACKAGE& p );		// �յ��㲥����
		void OnAllowJoinRoom( unsigned long ip, const PACKAGE& p );		// �յ�������뷿��
		void OnHeroMove( unsigned long ip, const PACKAGE& p );			// �յ�����ƶ�
		void OnHeroRotate( unsigned long ip, const PACKAGE& p );		// �յ�����ӽ���ת
		void OnNewPlayerJoin( unsigned long ip, const PACKAGE& p );		// �յ�����Ҽ���
		void OnBulletCreate( unsigned long ip, const PACKAGE& p );		// �յ��ڵ�����
		void OnBulletHit( unsigned long ip, const PACKAGE& p );			// �յ��ڵ�����
		void OnScoreArrival( unsigned long ip, const PACKAGE& p );		// �յ�����
		void OnMessage( unsigned long ip, const PACKAGE& p );			// �յ���Ϣ
		void OnPlayerLock( unsigned long ip, const PACKAGE& p );		// �յ�������Ϣ
		// ������Ϣ����
		virtual void OtherMessageHandler( unsigned long ip, const PACKAGE& p );

		// �򿪿ͻ���
		virtual void Start( int listen_port, int target_port );

		/************************************************************************/
		/* �����˷������ݵĽӿ�                                                 */
		/************************************************************************/
		void QueryRoom();											// �㲥��ѯ����		
		void EnterRoom( const std::string& ip );					// ���뷿��		

		void SendHeroMove( int index, float x, float y, float z );	// ��������ƶ�		
		void SendHeroRot( int index, float x, float y , float z );	// ��������������ת

		void SendMessageTo( int index, int target_index, const wchar_t* msg );	// ������Ϣ��һ����		
		void BroadcastMessage( int index, const wchar_t* msg );					// Ⱥ��������Ϣ

		// �����ڵ�������Ϣ�����е��ڵ����ж����ɷ������жϣ����оͷ��͸������
		void SendBulletHit( int owner_index, int target_index, int bullet_type, IShip* ship = 0 );	
		// ���ͷ����ڵ�����Ϣ
		void SendBullet( int index, int bullet_type,				
			const irr::core::vector3df& start, 
			const irr::core::vector3df& end, u32 life );

		// ����������Ϣ
		void SendLock( int index, int target_index );

		void SetID( int id )
		{
			m_index = id;
		}

		int GetID() const
		{
			return m_index;
		}

		void SetIsServer( bool bServer ) 
		{
			m_IsServer = bServer;
		}

		bool GetIsServer() const
		{
			return m_IsServer;
		}

		// ��ȡ�����б�
		const std::map<std::string, BroadcastRoomBag>& GetRooms() const;
		// ��ȡ����IP
		const std::set<std::string>& GetLocalIP() const;

	private:
		void SaveLocalIPAddress();

	//private:
	public:
		// �������������Ϣ����ʱ��Ҫ�ֵ�����������������Ϊ�˷�����ʱ������
		std::hash_map<int, irr::scene::ISceneNode*>			m_players;

	public:
		int										m_index;

	private:
		bool									m_IsServer;		// �Լ��Ƿ�Ϊ����
		int										m_target_port;
		std::map<std::string, BroadcastRoomBag>	m_roomMap;
		std::set<std::string>					m_localIP;
		unsigned long							m_server_IP;
		boost::shared_ptr<PlayerHelper>			m_PlayerHelper;
		boost::shared_ptr<PlayerManager>		m_playerManager;
	};


}


#endif // Boost_Client_h__
