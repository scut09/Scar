/********************************************************************
    创建时间: 2011-10-25   20:26
    文件名:   Client.cpp
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     客户端

*********************************************************************/

#include "Boost_Client.h"
#include "MyIrrlichtEngine.h"
#include "Frigate.h"
#include "BulletNode.h"
#include "CSceneNodeAnimatorSelfDelFlyStraight.h"
#include "GameBag.h"
#include <irrlicht.h>

// 测试用
extern IShip* cf1;

using namespace Network;

Network::BoostClient::BoostClient() : m_server_IP( 0 )
{
	SaveLocalIPAddress();

	// 注册消息处理函数
	RegisterMessageHandler( BROADCAST_ROOM, 
		[this]( unsigned long ip, const PACKAGE& p ){ OnBroadcastRoom( ip, p ); });
	RegisterMessageHandler( ALLOW_JOIN_ROOM, 
		[this]( unsigned long ip, const PACKAGE& p ){ OnAllowJoinRoom( ip, p ); });
	RegisterMessageHandler( HERO_MOVE, 
		[this]( unsigned long ip, const PACKAGE& p ){ OnHeroMove( ip, p ); });
	RegisterMessageHandler( HERO_ROTATE, 
		[this]( unsigned long ip, const PACKAGE& p ){ OnHeroRotate( ip, p ); });
	RegisterMessageHandler( NEW_PLAYER_JOIN, 
		[this]( unsigned long ip, const PACKAGE& p ){ OnNewPlayerJoin( ip, p ); });
	RegisterMessageHandler( BULLET_CREATE, 
		[this]( unsigned long ip, const PACKAGE& p ){ OnBulletCreate( ip, p ); });
	RegisterMessageHandler( BULLET_HIT,
		[this]( unsigned long ip, const PACKAGE& p ){ OnBulletHit( ip, p ); });
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

void Network::BoostClient::SendBullet( int index, int bullet_type, 
	const irr::core::vector3df& start, const irr::core::vector3df& end, u32 life )
{
	BulletCreateBag bullet;
	bullet.owner_index = m_index;
	bullet.start_point = start;
	bullet.end_point = end;
	bullet.life = life;

	PACKAGE pack;
	pack.SetCMD( BULLET_CREATE );
	pack.SetData( (char*)&bullet, sizeof( BulletCreateBag ) );

	m_network->SendTo( m_server_IP, pack );
}


void Network::BoostClient::SendBulletHit( int owner_index, int target_index, int bullet_type )
{
	BulletHittedBag bag;
	bag.owner_index = owner_index;
	bag.target_index = target_index;
	bag.bullet_type = bullet_type;

	PACKAGE p;
	p.SetCMD( BULLET_HIT );
	p.SetData( (char*)&bag, sizeof( PACKAGE ) );

	TcpSendTo( m_server_IP, m_target_port, p );
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

void Network::BoostClient::OnBroadcastRoom( unsigned long ip, const PACKAGE& p )
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

void Network::BoostClient::OnAllowJoinRoom( unsigned long ip, const PACKAGE& p )
{
	std::cout << boost::asio::ip::address_v4( ip ).to_string() << " ==>BoostClient receives ALLOW_JOIN_ROOM\n";

	m_server_IP = ip;

	PlayerInfo player;
	player = *(PlayerInfo*)p.GetData();

	m_index = player.index;
}

void Network::BoostClient::OnHeroMove( unsigned long ip, const PACKAGE& p )
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

void Network::BoostClient::OnHeroRotate( unsigned long ip, const PACKAGE& p )
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


void Network::BoostClient::OnBulletCreate( unsigned long ip, const PACKAGE& p )
{
	BulletCreateBag* bag;
	bag = (BulletCreateBag*)p.GetData();

	if ( bag->owner_index == m_index )	return;
	
	auto bullet = new BulletNode( MyIrrlichtEngine::GetEngine()->GetSceneManager() );
	bullet->setVisible( true );
	bullet->setMaterialTexture( 0, MyIrrlichtEngine::GetEngine()->GetVideoDriver()->getTexture( "../media/Weapon/bullet.png" ) );
	bullet->SetVelocity( 1000 );
	bullet->SetInterval( 100 );

	// 直飞和自删除动画
	auto ani = new CSceneNodeAnimatorSelfDelFlyStraight( 
		bag->start_point, bag->end_point, bag->life, MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime() );
	auto del = MyIrrlichtEngine::GetEngine()->GetSceneManager()->createDeleteAnimator( bag->life );

	// 帮子弹附上动画并发射出去
	bullet->addAnimator( ani );
	bullet->addAnimator( del );
	del->drop();
	ani->drop();

	bullet->setMaterialType( EMT_TRANSPARENT_ALPHA_CHANNEL );
	bullet->setMaterialFlag( EMF_LIGHTING, false );
}


void Network::BoostClient::OnNewPlayerJoin( unsigned long ip, const PACKAGE& p )
{
	OnePlayerInfoBag oneplayer;
	oneplayer = *(OnePlayerInfoBag*)p.GetData();

	if ( oneplayer.player_index != m_index )
	{
		auto smgr = MyIrrlichtEngine::GetEngine()->GetSceneManager();

		// 加载飞船，需要根据玩家飞船信息组装飞船
		auto ship = new CFrigate( smgr->getMesh("../module/1234.obj"), 0, smgr, -1 );

		// 设置船的id
		ship->setID( oneplayer.player_index );
		// 保存玩家信息
		m_players[ oneplayer.player_index ] = ship;

		std::cout << "NEW_PLAYER_JOIN " << oneplayer.player_index << std::endl;
	}
	else
	{
		// 设置自己的id
		cf1->setID( m_index );
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

const std::map<std::string, Network::BroadcastRoomBag>& Network::BoostClient::GetRooms() const
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

void Network::BoostClient::OnBulletHit( unsigned long ip, const PACKAGE& p )
{
	std::cout << "OnBulletHit\n";
	// 获取炮弹类型
	BulletHittedBag* bag = (BulletHittedBag*)p.GetData();

	ISceneManager* smgr = MyIrrlichtEngine::GetEngine()->GetSceneManager();

	smgr->getSceneNodeFromId( bag->owner_index );

	ISceneNode* target_node = smgr->getSceneNodeFromId( bag->target_index );

	int damage = 100;

	IShip *ship = dynamic_cast<IShip *>( target_node );
	if (NULL != ship)
	{
		//ship->SetCurrentLife( ship->GetCurrentLife() - damage );
		ship->SetShield( ship->GetShield() - damage );
		std::cout << "ship\n";

	}

}
