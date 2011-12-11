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
#include "PlayerManager.h"
#include "GeneralCallBack.h"
#include "PlayerHelper.h"
#include "HumanPlayer.h"
#include "MultiplayerScene.h"

// 测试用
extern IShip* cf1;
IGUIEditBox* box = 0;


using namespace Network;

Network::BoostClient::BoostClient( boost::shared_ptr<PlayerManager>	playerManager ) 
	: m_playerManager( playerManager ), m_server_IP( 0 ), m_index( -11 ), m_IsServer( false )
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
	RegisterMessageHandler( MESSAGE_BROADCAST,
		[this]( unsigned long ip, const PACKAGE& p ){ OnMessage( ip, p ); });
	RegisterMessageHandler( MESSAGE_TO,
		[this]( unsigned long ip, const PACKAGE& p ){ OnMessage( ip, p ); });
	RegisterMessageHandler( SCORE_ARRIVAL,
		[this]( unsigned long ip, const PACKAGE& p ){ OnScoreArrival( ip, p ); });
	RegisterMessageHandler( PLAYER_LOCK,
		[this]( unsigned long ip, const PACKAGE& p ){ OnPlayerLock( ip, p ); });
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
	bullet.owner_index = index;
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
	p.SetData( (char*)&bag, sizeof( BulletHittedBag ) );

	TcpSendTo( m_server_IP, m_target_port, p );
}


void Network::BoostClient::SaveLocalIPAddress()
{
	try
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
	catch ( std::exception& e )
	{
		std::cerr << e.what() << std::endl;
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

	// 自己的包或者当自己是服务器是忽略机器人的包
	if ( bag->owner_index == m_index || m_IsServer && bag->owner_index > 70 )	return;
	
	MyIrrlichtEngine::GetEngine()->AddToCloneQueue( p );

}


void Network::BoostClient::OnNewPlayerJoin( unsigned long ip, const PACKAGE& p )
{
	OnePlayerInfoBag oneplayer;
	oneplayer = *(OnePlayerInfoBag*)p.GetData();

	if ( oneplayer.player_index != m_index )
	{
		auto smgr = MyIrrlichtEngine::GetEngine()->GetSceneManager();

		// 加载飞船，需要根据玩家飞船信息组装飞船
		//auto ship = new CFrigate( smgr->getMesh("../model/ship/cf1.obj"), 0, smgr, -1 );
		auto ship = MyIrrlichtEngine::GetEngine()->GetMySceneManager()->addFrigateSceneNode( L"../model/ship/cf1.obj" );
		//GeneralCallBack* cb = new GeneralCallBack( ship );
		//SceneNodeShader shader;
		//shader.ApplyShaderToSceneNode( ship, cb, "Shader/cf_1V.vert", "Shader/cf_1F.frag" );
		//cb->drop();
		//ship->setMaterialFlag( EMF_BACK_FACE_CULLING, false );

		// 设置船的id
		ship->setID( oneplayer.player_index );
		// 保存玩家信息
		m_players[ oneplayer.player_index ] = ship;
		ship->grab();	///!!!!!!!!!!一定要去drop,还没

		ship->setPosition( core::vector3df( 123141, 12312, 1000000 ) );

//		m_playerManager->AddPlayer( ship->getID(), ship );
		boost::shared_ptr<HumanPlayer> player = boost::shared_ptr<HumanPlayer>( new HumanPlayer( ship ) );
		player->SetID( oneplayer.player_index );
		player->SetName( oneplayer.player_name );
		dynamic_cast<MultiplayerScene*>(
			MyIrrlichtEngine::GetEngine()->GetGameSceneManager()->GetCurrentGameScene()
			)->m_playerManager->AddPlayer( player );

		std::cout << "NEW_PLAYER_JOIN " << oneplayer.player_index << std::endl;
	}
	else
	{
		// 设置自己的id		
	//	m_playerManager->m_playerHelper.PlayerShip->setID( m_index );
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

	if ( bag->target_index == m_index )
	{
		auto pEngine = MyIrrlichtEngine::GetEngine();
		if ( pEngine->GetCurrentPlayer()->GetShip()->GetShield() <= 0
			&& pEngine->GetCurrentPlayer()->GetShip()->GetArmor() <= 0 )
		{
			// 自己挂了
			pEngine->GetCurrentPlayer()->SetState( IPlayer::PS_Dead );

			// 通知别人自己挂了
			ScoreArrivalBag score;
			score.ip = 0;
			score.KillCount = pEngine->GetCurrentPlayer()->GetKill();
			score.DeathCount = pEngine->GetCurrentPlayer()->GetDeath();

			PACKAGE pack;
			pack.SetCMD( SCORE_ARRIVAL );			
			pack.SetData( (char*)&score, sizeof( BulletCreateBag ) );			

			TcpSendTo( m_server_IP, m_target_port, pack );
			//m_network->SendTo( m_server_IP, pack );
		}
	}

	// 判断击中目标是否有效
	if ( 0 <= bag->target_index && bag->target_index < 100 )
	{
		ISceneManager* smgr = MyIrrlichtEngine::GetEngine()->GetSceneManager();

		smgr->getSceneNodeFromId( bag->owner_index );

		// 获取命中的节点
		ISceneNode* target_node = smgr->getSceneNodeFromId( bag->target_index );

		int damage = 10;

		IShip *ship = dynamic_cast<IShip *>( target_node );
		if (NULL != ship)
		{
			if (ship->GetShield() > 0.0 )
			{
				// 计算护盾
				ship->SetShield( ship->GetShield() - damage );
				std::cout << "ship SetShield\n";
			}
			else if(ship->GetArmor() > 0.0 )
			{
				// 计算护甲
				ship->SetArmor( ship->GetArmor() - damage );
				std::cout << "ship SetArmor\n";
			}

			if ( ship->GetShield() < 0.0 )
			{
				ship->SetShield(0.0f);
			}

			if ( ship->GetArmor() < 0.0 )
			{
				ship->SetArmor(0.0f);
			}

		}
	}



}

void Network::BoostClient::OnMessage( unsigned long ip, const PACKAGE& p )
{
	BroadcastMessageBag* bag;
	bag = (BroadcastMessageBag*)p.GetData();

	bag->GetMsg();
	bag->index;

	if ( box == 0 )
	{
		box = MyIrrlichtEngine::GetEngine()->GetDevice()->getGUIEnvironment()->addEditBox( _T(""), core::recti( 0, 100, 100, 130 ) );
	}
	box->setVisible( true );
	box->setText( bag->GetMsg() );

	// 两秒后隐藏
	boost::thread t( []()
	{
		boost::thread::sleep( boost::get_system_time() + boost::posix_time::seconds( 2 ) );
		box->setVisible( false );
	} );
}


void Network::BoostClient::SendMessageTo( int index, int target_index, const wchar_t* msg )
{
	BroadcastMessageBag bag;
	bag.index = index;
	bag.target_index = target_index;
	bag.SetMsg( msg );

	PACKAGE p;
	p.SetCMD( MESSAGE_BROADCAST );
	p.SetData( (char*)&bag, bag.GetLength() );
	TcpSendTo( m_server_IP, m_target_port, p );
}

void Network::BoostClient::BroadcastMessage( int index, const wchar_t* msg )
{
	BroadcastMessageBag bag;
	bag.index = index;
	bag.target_index = -1;
	bag.SetMsg( msg );

	PACKAGE p;
	p.SetCMD( MESSAGE_TO );
	p.SetData( (char*)&bag, bag.GetLength() );
	TcpSendTo( m_server_IP, m_target_port, p );
}

void Network::BoostClient::OnScoreArrival( unsigned long ip, const PACKAGE& p )
{
	ScoreArrivalBag bag = *(ScoreArrivalBag*)p.GetData();

	ScoreNode score;
	score.ip = ip;
	score.KillCount = bag.KillCount;
	score.DeathCount = bag.DeathCount;
	m_PlayerHelper->SetPlayerScore( ip, score );
}

void Network::BoostClient::SendLock( int index, int target_index )
{
	PACKAGE p;
	p.SetCMD( PLAYER_LOCK );
	PlayerLockBag bag;
	bag.owner_index = index;
	bag.target_index = target_index;
	p.SetData( (char*)&bag, sizeof(PlayerLockBag) );
	TcpSendTo( m_server_IP, m_target_port, p );
}

void Network::BoostClient::OnPlayerLock( unsigned long ip, const PACKAGE& p )
{
	PlayerLockBag lockBag;
	lockBag = *(PlayerLockBag*)p.GetData();
	if ( lockBag.target_index == m_index )
	{
		
	}
}
