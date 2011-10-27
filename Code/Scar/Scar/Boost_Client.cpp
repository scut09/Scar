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
			auto iter = m_players.find( move.index );
			if ( iter != m_players.end() )
			{
				//std::cout << "=> HERO_MOVE " << move.index << ' ' << move.x << ' ' << move.y << ' ' << move.z << std::endl;
				iter->second->setPosition( irr::core::vector3df( move.x, move.y, move.z ) );
			}
		}
	}
	// 玩家照相机旋转
	else if ( cmd == HERO_ROTATE )
	{
		HeroRotate rot;
		rot = *(HeroRotate*)p.GetData();
		if ( rot.index != m_index )
		{
			auto iter = m_players.find( rot.index );
			if ( iter != m_players.end() )
			{
				//std::cout << "=> HERO_MOVE " << move.index << ' ' << move.x << ' ' << move.y << ' ' << move.z << std::endl;
				iter->second->setPosition( irr::core::vector3df( rot.x, rot.y ) );
			}
		}
	}
	// 收到新玩家加入
	else if ( cmd == NEW_PLAYER_JOIN )
	{
		OnePlayerInfoBag oneplayer;
		oneplayer = *(OnePlayerInfoBag*)p.GetData();

		if ( oneplayer.player_index != m_index )
		{
			auto smgr = MyIrrlichtEngine::GetEngine()->GetSceneManager();

			auto modelMan = MyIrrlichtEngine::GetEngine()->GetModelManager();

			auto bottleNode = modelMan->AddSceneNodeFromMesh( _T("1") );

			// 创建飞船
			//IShip* cf1 = new CFrigate( smgr->getMesh("../module/1234.obj"), 0, smgr, -1 );
			//m_pCamera->addChild( cf1 );
			//cf1->setPosition( irr::core::vector3df( 0, 0, 50 ) );

			m_players[ oneplayer.player_index ] = bottleNode;

			std::cout << "NEW_PLAYER_JOIN " << oneplayer.player_index << std::endl;
		}

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


void Network::BoostClient::SendHeroRot( int index, float x, float y )
{
	PACKAGE pack;
	pack.SetCMD( HERO_ROTATE );

	HeroRotate rot( index, x, y );

	pack.SetData( (char*)&rot, sizeof( HeroRotate ) );

	m_network->Send( m_server_IP, pack );
}


void Network::BoostClient::SaveLocalIPAddress()
{
	using namespace boost::asio::ip;
	boost::asio::io_service io;

	tcp::resolver resolver( io ); 
	tcp::resolver::query query( boost::asio::ip::host_name(), "" ); 
	tcp::resolver::iterator iter = resolver.resolve( query ); 
	tcp::resolver::iterator end; 

	while ( iter != end ) 
	{   
		tcp::endpoint ep = *iter++;    
		if ( ep.address().is_v4() )
		{
			m_localIP.insert( ep.address().to_string() );
			std::cout << ep.address().to_string() << std::endl;
		}
	}
}
