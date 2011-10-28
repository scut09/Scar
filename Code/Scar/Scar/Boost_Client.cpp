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

using namespace Network;

Network::BoostClient::BoostClient() : m_server_IP( 0 )
{
	SaveLocalIPAddress();

	RegisterMessageHandler( BROADCAST_ROOM, 
		[this]( unsigned long ip, const PACKAGE& p ){ BroadcastRoomHandler( ip, p ); });
	RegisterMessageHandler( ALLOW_JOIN_ROOM, 
		[this]( unsigned long ip, const PACKAGE& p ){ AllowJoinRoomHandler( ip, p ); });
	RegisterMessageHandler( HERO_MOVE, 
		[this]( unsigned long ip, const PACKAGE& p ){ HeroMoveHandler( ip, p ); });
	RegisterMessageHandler( HERO_ROTATE, 
		[this]( unsigned long ip, const PACKAGE& p ){ HeroRotateHandler( ip, p ); });
	RegisterMessageHandler( NEW_PLAYER_JOIN, 
		[this]( unsigned long ip, const PACKAGE& p ){ NewPlayerJoinHandler( ip, p ); });
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
	//m_network->SendTo( ip, pack );
	TcpSendTo( boost::asio::ip::address().from_string( ip ).to_v4().to_ulong(), m_target_port, pack );
}

void Network::BoostClient::SendHeroMove( int index, float x, float y, float z )
{
	PACKAGE pack;
	pack.SetCMD( HERO_MOVE );

	HeroMove move( index, x, y, z );

	pack.SetData( (char*)&move, sizeof( HeroMove ) );

	m_network->SendTo( m_server_IP, pack );
}


void Network::BoostClient::SendHeroRot( int index, float x, float y, float z )
{
	PACKAGE pack;
	pack.SetCMD( HERO_ROTATE );

	HeroRotate rot( index, x, y, z );

	pack.SetData( (char*)&rot, sizeof( HeroRotate ) );

	m_network->SendTo( m_server_IP, pack );
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

void Network::BoostClient::BroadcastRoomHandler( unsigned long ip, const PACKAGE& p )
{
	BroadcastRoomBag bag = *(BroadcastRoomBag*)p.GetData();
	m_roomMap[ boost::asio::ip::address_v4( ip ).to_string() ] = bag;

	//std::cout << "Server broadcast room: ip= " 
	//	<< boost::asio::ip::address_v4( ip ).to_string() 
	//	<< " room name= ";
	//std::wcout << ((BroadcastRoomBag*)p.GetData())->room_name
	//	<< std::endl;

	//std::cout << "<current rooms>\n";
	//for ( auto iter = m_roomMap.begin(); iter != m_roomMap.end(); ++iter )
	//{
	//	std::cout << "ip " << iter->first << std::endl;
	//}
	//std::cout << "</current rooms>\n";
}

void Network::BoostClient::AllowJoinRoomHandler( unsigned long ip, const PACKAGE& p )
{
	std::cout << boost::asio::ip::address_v4( ip ).to_string() << " ==>BoostClient receives ALLOW_JOIN_ROOM\n";

	m_server_IP = ip;

	PlayerInfo player;
	player = *(PlayerInfo*)p.GetData();

	m_index = player.index;
}

void Network::BoostClient::HeroMoveHandler( unsigned long ip, const PACKAGE& p )
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

void Network::BoostClient::HeroRotateHandler( unsigned long ip, const PACKAGE& p )
{
	HeroRotate rot;
	rot = *(HeroRotate*)p.GetData();
	if ( rot.index != m_index )
	{
		auto iter = m_players.find( rot.index );
		if ( iter != m_players.end() )
		{
			//std::cout << "=> HERO_MOVE " << move.index << ' ' << move.x << ' ' << move.y << ' ' << move.z << std::endl;
			iter->second->setRotation( irr::core::vector3df( rot.x, rot.y, rot.z ) );
		}
	}
}

void Network::BoostClient::NewPlayerJoinHandler( unsigned long ip, const PACKAGE& p )
{
	OnePlayerInfoBag oneplayer;
	oneplayer = *(OnePlayerInfoBag*)p.GetData();

	if ( oneplayer.player_index != m_index )
	{
		auto smgr = MyIrrlichtEngine::GetEngine()->GetSceneManager();

		auto modelMan = MyIrrlichtEngine::GetEngine()->GetModelManager();

		auto bottleNode = modelMan->AddSceneNodeFromMesh( _T("1") );

		//IShip* cf1 = new CFrigate( smgr->getMesh("../module/1234.obj"), 0, smgr, -1 );
		//m_pCamera->addChild( cf1 );
		//cf1->setPosition( irr::core::vector3df( 0, 0, 50 ) );

		m_players[ oneplayer.player_index ] = bottleNode;

		std::cout << "NEW_PLAYER_JOIN " << oneplayer.player_index << std::endl;
	}
}

void Network::BoostClient::OtherMessageHandler( unsigned long ip, const PACKAGE& p )
{

}

void Network::BoostClient::Start( int listen_port, int target_port )
{
	m_target_port = target_port;

	NetworkBase::Start( listen_port, target_port );
}

const std::map<std::string, BroadcastRoomBag>& Network::BoostClient::GetRooms() const
{
	return m_roomMap;
}

const std::set<std::string>& Network::BoostClient::GetLocalIP() const
{
	return m_localIP;
}

void Network::BoostClient::Close()
{
	//m_io_thread->interrupt();
	NetworkBase::Close();
}
