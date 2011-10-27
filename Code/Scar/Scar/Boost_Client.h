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
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <hash_map>
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

		// ��Ϣ������
		void BroadcastRoomHandler( unsigned long ip, const PACKAGE& p );
		void AllowJoinRoomHandler( unsigned long ip, const PACKAGE& p );
		void HeroMoveHandler( unsigned long ip, const PACKAGE& p );
		void HeroRotateHandler( unsigned long ip, const PACKAGE& p );
		void NewPlayerJoinHandler( unsigned long ip, const PACKAGE& p );

		virtual void OtherMessageHandler( unsigned long ip, const PACKAGE& p );

		void QueryRoom();

		void EnterRoom( const std::string& ip );

		void SendHeroMove( int index, float x, float y, float z );

		void SendHeroRot( int index, float x, float y , float z );

		const std::map<std::string, BroadcastRoomBag>& GetRooms() const
		{
			return m_roomMap;
		}

		const std::set<std::string>& GetLocalIP() const
		{
			return m_localIP;
		}

	private:
		void SaveLocalIPAddress();


	private:
		// �������������Ϣ����ʱ��Ҫ�ֵ�����������������Ϊ�˷�����ʱ������
		std::hash_map<int, irr::scene::ISceneNode*>			m_players;

	public:
		int										m_index;

	private:
		int										m_port;
		std::map<std::string, BroadcastRoomBag>	m_roomMap;
		std::set<std::string>					m_localIP;
		unsigned long							m_server_IP;
	};


}


#endif // Boost_Client_h__
