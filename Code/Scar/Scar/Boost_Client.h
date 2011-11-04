/********************************************************************
    创建时间: 2011-10-25   20:25
    文件名:   Client.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     客户端

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

class PlayerManager;

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using namespace boost::asio::ip;

	struct BroadcastRoomBag;

	class BoostClient : public NetworkBase
	{
	public:
		BoostClient( PlayerManager*	playerManager );

		~BoostClient()
		{
			Close();
		}

		virtual void Close();

		/************************************************************************/
		/* 消息处理函数                                                          */
		/************************************************************************/
		void OnBroadcastRoom( unsigned long ip, const PACKAGE& p );		// 收到广播房间
		void OnAllowJoinRoom( unsigned long ip, const PACKAGE& p );		// 收到允许加入房间
		void OnHeroMove( unsigned long ip, const PACKAGE& p );			// 收到玩家移动
		void OnHeroRotate( unsigned long ip, const PACKAGE& p );		// 收到玩家视角旋转
		void OnNewPlayerJoin( unsigned long ip, const PACKAGE& p );		// 收到新玩家加入
		void OnBulletCreate( unsigned long ip, const PACKAGE& p );		// 收到炮弹创建
		void OnBulletHit( unsigned long ip, const PACKAGE& p );			// 收到炮弹命中
		void OnMessage( unsigned long ip, const PACKAGE& p );			// 收到信息
		// 其他消息处理
		virtual void OtherMessageHandler( unsigned long ip, const PACKAGE& p );

		// 打开客户端
		virtual void Start( int listen_port, int target_port );

		/************************************************************************/
		/* 向服务端发送数据的接口                                                 */
		/************************************************************************/
		void QueryRoom();											// 广播查询房间		
		void EnterRoom( const std::string& ip );					// 加入房间		

		void SendHeroMove( int index, float x, float y, float z );	// 发送玩家移动		
		void SendHeroRot( int index, float x, float y , float z );	// 发送玩家摄像机旋转

		void SendMessageTo( int index, int target_index, const wchar_t* msg );	// 发送消息给一个人		
		void BroadcastMessage( int index, const wchar_t* msg );					// 群发发送消息

		// 发送炮弹命中消息，所有的炮弹命中都是由发射人判断，命中就发送给服务端
		void SendBulletHit( int owner_index, int target_index, int bullet_type );	
		// 发送发射炮弹的消息
		void SendBullet( int index, int bullet_type,				
			const irr::core::vector3df& start, 
			const irr::core::vector3df& end, u32 life );
		





		// 获取房间列表
		const std::map<std::string, BroadcastRoomBag>& GetRooms() const;
		// 获取本地IP
		const std::set<std::string>& GetLocalIP() const;

	private:
		void SaveLocalIPAddress();

	private:
		// 管理其他玩家信息，到时需要分到其他类来处理，现在为了方便暂时放这里
		std::hash_map<int, irr::scene::ISceneNode*>			m_players;

	public:
		int										m_index;

	private:
		int										m_target_port;
		std::map<std::string, BroadcastRoomBag>	m_roomMap;
		std::set<std::string>					m_localIP;
		unsigned long							m_server_IP;

		PlayerManager*							m_playerManager;
	};


}


#endif // Boost_Client_h__
