#include "Boost_Server.h"
#include "GameBag.h"
#include "MyIrrlichtEngine.h"
#include "BulletNode.h"
#include "IShip.h"
#include "RobotShip.h"
#include "GeneralCallBack.h"
#include "MultiplayerScene.h"
#include "SpriteFlame.h"

#pragma warning(push)              // 仅禁用此头文件
#pragma warning(disable:4996)


Network::BoostServer::BoostServer() : m_robotID( 99 )
{
	RegisterMessageHandler( QUERY_ROOM, 
		[this]( unsigned long ip, const PACKAGE& p ){ OnQueryRoom( ip, p ); });
	RegisterMessageHandler( REQUEST_ENTER_ROOM, 
		[this]( unsigned long ip, const PACKAGE& p ){ OnRequestEnterRoom( ip, p ); });
}

void Network::BoostServer::OnQueryRoom( unsigned long ip, const PACKAGE& p )
{
	PACKAGE pack;

	pack.SetCMD( BROADCAST_ROOM );

	BroadcastRoomBag room;
	wchar_t* room_name = L"TWX";
	wcscpy( room.room_name, room_name );

	pack.SetData( (const char*)&room, sizeof( BroadcastRoomBag ) );

	m_network->Broadcast( pack );

	std::cout << ip::address_v4( ip ).to_string() << " BoostServer receives REQUEST_ROOM\n";
}

void Network::BoostServer::OnRequestEnterRoom( unsigned long ip, const PACKAGE& p )
{
	if ( m_playerList.size() > 10 )	
	{
		// 失败
	}

	RequestEnterRoomBag enterRoomBag;
	enterRoomBag = *(RequestEnterRoomBag*)p.GetData();

	// 为新玩家分配id
	int index = m_playerList.size();

	std::cout << ip::address_v4( ip ).to_string() << " ";
	std::cout << "==> BoostServer receives REQUEST_ENTER_ROOM\n"
		<< "allocate index " << index << std::endl;

	PACKAGE pack;

	// 发送允许加入消息
	pack.SetCMD( ALLOW_JOIN_ROOM );
	AllowJoinRoomBag allowBag( index, 0, 0, 0 );
	pack.SetData( (char*)&allowBag, sizeof( AllowJoinRoomBag ) );

	//m_network->SendTo( ip, pack );
	TcpSendTo( ip, m_target_port, pack );

	// 保存这个玩家信息
	PlayerInfo player( index, ip, enterRoomBag.shipname );
	m_playerList.push_back( player );

	//Sleep( 2000 );

	// 发送已有玩家信息给新玩家，这个需要改进
	for ( auto iter = m_playerList.begin(); iter != m_playerList.end(); ++iter )
	{
		OnePlayerInfoBag oneplayer;
		oneplayer.player_index = iter->index;
		wcscpy( oneplayer.ship_name, iter->ship_name.c_str() );
		wcscpy( oneplayer.gun_name, iter->gun_name.c_str() );
		wcscpy( oneplayer.missle_name, iter->missle_name.c_str() );

		pack.SetCMD( NEW_PLAYER_JOIN );
		pack.SetData( (char*)&oneplayer, sizeof( OnePlayerInfoBag ) );

		//m_network->SendTo( ip, pack );
		TcpSendTo( ip, m_target_port, pack );
	}

	//Sleep( 2000 );

	OnePlayerInfoBag oneplayer;
	oneplayer.player_index = index;
	wcscpy( oneplayer.ship_name, enterRoomBag.shipname );

	pack.SetCMD( NEW_PLAYER_JOIN );
	pack.SetData( (char*)&oneplayer, sizeof( OnePlayerInfoBag ) );

	//m_network->Broadcast( pack );
	TcpSendToPlayers( pack );
}

void Network::BoostServer::OtherMessageHandler( unsigned long ip, const PACKAGE& p )
{
	// 其他，发送给玩家
	UdpSendToPlayers( p );
}

void Network::BoostServer::TcpSendToPlayers( const PACKAGE& p )
{
	for ( auto iter = m_playerList.begin(); iter != m_playerList.end(); ++iter )
	{
		TcpSendTo( iter->ip, m_target_port, p );
	}
}

void Network::BoostServer::UdpSendToPlayers( const PACKAGE& p )
{
	for ( auto iter = m_playerList.begin(); iter != m_playerList.end(); ++iter )
	{
		m_network->SendTo( iter->ip, p );
	}
}

void Network::BoostServer::Start( int listen_port, int target_port, int pool_size )
{
	m_target_port = target_port;

	NetworkBase::Start( listen_port, target_port, pool_size );
}

void Network::BoostServer::AddRobotPlayer( int type /*= 0 */ )
{
	auto pEngine = MyIrrlichtEngine::GetEngine();
	auto smgr = pEngine->GetSceneManager();
	MultiplayerScene* scene = dynamic_cast<MultiplayerScene*>( pEngine->GetGameSceneManager()->GetCurrentGameScene() );
	auto m_sceneSelector = scene->m_sceneSelector;

	SceneNodeShader shader;

	SpriteFlame spf;

	// 分配id
	int id = m_robotID--;

	// 添加robot
	IShip* npc;
	boost::shared_ptr<ShipAgentPlayer> robot;
	// robot 
	// 加载模型
	npc = pEngine->GetMySceneManager()->addFrigateSceneNode( L"../model/ship/gf1.obj", id );
	npc->SetMaxSpeed( 2 );
	npc->setPosition( vector3df( (f32)(rand() % 100), (f32)(rand() % 100), (f32)(1000 + rand() % 1000) ) );
	spf.SetOffset( vector3df( -6, 0, -22 ) );
	spf.AddFlameToShip( npc, smgr );
	spf.SetOffset( vector3df( 6, 0, -22 ) );
	spf.AddFlameToShip( npc, smgr );
	// 装载武器
	auto bullet = new BulletNode( smgr, smgr->getRootSceneNode() );
	bullet->setMaterialTexture( 0, MyIrrlichtEngine::GetEngine()->GetVideoDriver()->getTexture( "../media/Weapon/bullet.png" ) );
	bullet->setID( 4003 );
	bullet->SetVelocity( 1000 );
	bullet->SetInterval( 100 );
	npc->AddGun( bullet );
	bullet->drop();	
	// 添加玩家，加载模型到玩家中
	robot = boost::shared_ptr<ShipAgentPlayer>( new ShipAgentPlayer( npc, &*scene->m_playerManager, scene->server ) );
	robot->SetID( id );
	scene->m_playerManager->AddPlayer( robot );
	// 使用渲染
	GeneralCallBack* cb = new GeneralCallBack( npc );
	shader.ApplyShaderToSceneNode( npc, cb, "Shader/cf_1V.vert", "Shader/cf_1F.frag" );
	cb->drop();
	npc->setMaterialFlag( EMF_BACK_FACE_CULLING, false );
	auto triSelector = smgr->createOctreeTriangleSelector( static_cast<IMeshSceneNode*>(npc)->getMesh(), npc );
	// 创建三角形选择器以支持碰撞
	npc->setTriangleSelector( triSelector );
	m_sceneSelector->addTriangleSelector( triSelector );
	triSelector->drop();

	// 添加玩家
	PlayerInfo info( robot->GetID(), 0, L"gf1" );
	m_playerList.push_back( info );
}


#pragma warning(pop)              // 恢复最初的警告级别
