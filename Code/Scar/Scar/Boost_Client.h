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

		// 消息处理函数
		void BroadcastRoomHandler( unsigned long ip, const PACKAGE& p );
		void AllowJoinRoomHandler( unsigned long ip, const PACKAGE& p );
		void HeroMoveHandler( unsigned long ip, const PACKAGE& p );
		void HeroRotateHandler( unsigned long ip, const PACKAGE& p );
		void NewPlayerJoinHandler( unsigned long ip, const PACKAGE& p );
		// 其他消息处理
		virtual void OtherMessageHandler( unsigned long ip, const PACKAGE& p );

		// 使用TCP异步发送
		void TcpSendTo( int ip, const PACKAGE& p );

		// 打开客户端
		virtual void Start( int listen_port, int target_port );

		// 广播查询房间
		void QueryRoom();
		// 加入房间
		void EnterRoom( const std::string& ip );
		// 发送玩家移动
		void SendHeroMove( int index, float x, float y, float z );
		// 发送玩家摄像机旋转
		void SendHeroRot( int index, float x, float y , float z );
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
		io_service								io;
		std::shared_ptr<boost::thread>			m_io_thread;
	};


}


#endif // Boost_Client_h__
