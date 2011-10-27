/********************************************************************
    创建时间: 2011-10-25   20:26
    文件名:   Client.cpp
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     客户端

*********************************************************************/

#include "Boost_Client.h"
#include "GameBag.h"
#include "MyIrrlichtEngine.h"
#include "Frigate.h"


void Network::BoostClient::OnReceive( unsigned long ip, const PACKAGE& p )
{
	int cmd = p.GetCMD();

	//std::cout << "BoostClient cmd = " << cmd << std::endl;

	// 收到房间广播，保存到房间列表中
	if ( cmd == BROADCAST_ROOM )		
	{
		BroadcastRoomBag bag = *(BroadcastRoomBag*)p.GetData();
		m_roomMap[ boost::asio::ip::address_v4( ip ).to_string() ] = bag;

		std::cout << "Server broadcast room: ip= " 
			<< boost::asio::ip::address_v4( ip ).to_string() 
			<< " room name= ";
		std::wcout << ((BroadcastRoomBag*)p.GetData())->room_name
			<< std::endl;

		std::cout << "<current rooms>\n";
		for ( auto iter = m_roomMap.begin(); iter != m_roomMap.end(); ++iter )
		{
			std::cout << "ip " << iter->first << std::endl;
		}
		std::cout << "</current rooms>\n";
	}
	// 收到允许加入房间的消息，开始游戏
	else if ( cmd == ALLOW_JOIN_ROOM )	
	{
		std::cout << boost::asio::ip::address_v4( ip ).to_string() << " ==>BoostClient receives ALLOW_JOIN_ROOM\n";

		m_server_IP = ip;

		PlayerInfo player;
		player = *(PlayerInfo*)p.GetData();

		m_index = player.index;


	}
	// 收到玩家移动
	else if ( cmd == HERO_MOVE )
	{
		HeroMove move;
		move = *(HeroMove*)p.GetData();
		if ( move.index != m_index )
		{
			//std::cout << "=> HERO_MOVE " << move.index << ' ' << move.x << ' ' << move.y << ' ' << move.z << std::endl;
			m_players[ move.index ]->setPosition( irr::core::vector3df( move.x, move.y, move.z ) );
		}
	}
	// 收到新玩家加入
	else if ( cmd == NEW_PLAYER_JOIN )
	{
		OnePlayerInfoBag oneplayer;
		oneplayer = *(OnePlayerInfoBag*)p.GetData();

		auto smgr = MyIrrlichtEngine::GetEngine()->GetSceneManager();

		auto modelMan = MyIrrlichtEngine::GetEngine()->GetModelManager();

		// 创建飞船
		IShip* cf1 = new CFrigate( smgr->getMesh("../module/1234.obj"), 0, smgr, -1 );
		//m_pCamera->addChild( cf1 );
		cf1->setPosition( irr::core::vector3df( 0, 0, 50 ) );

		m_players[ oneplayer.player_index ] = cf1;

		std::cout << "NEW_PLAYER_JOIN " << oneplayer.player_index << std::endl;
	}
}

void Network::BoostClient::Send( std::string ip )
{
	PACKAGE p;
	p.SetCMD( ALLOW_JOIN_ROOM );
	//m_network->Send( ip, p );
}

void Network::BoostClient::Start( int listen_port, int target_port )
{
	// 创建网络
	m_network = std::shared_ptr<Network::CNetwork>( new Network::CNetwork( listen_port, target_port ) );
	// 注册接受回调函数
	m_network->Start( [this]( unsigned long ip, const PACKAGE& p )
	{
		OnReceive( ip, p );
	} );
}

void Network::BoostClient::QueryRoom()
{
	PACKAGE p;
	p.SetCMD( QUERY_ROOM );
	m_network->Broadcast( p );
}

void Network::BoostClient::EnterRoom( const std::string& ip )
{
	PACKAGE pack;
	pack.SetCMD( REQUEST_ENTER_ROOM );
	m_network->Send( ip, pack );
}

void Network::BoostClient::SendHeroMove( int index, float x, float y, float z )
{
	PACKAGE pack;
	pack.SetCMD( HERO_MOVE );

	HeroMove move( index, x, y, z );

	pack.SetData( (char*)&move, sizeof( HeroMove ) );

	m_network->Send( m_server_IP, pack );
}
