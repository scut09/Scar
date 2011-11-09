//#include "IRobot.h"
//#include "MyIrrlichtEngine.h"
//#include "Robot_Client.h"
//#include "FireAnimator.h"
//#include "SceneNodeAnimatorAircraftFPS.h"
//#include "MyIrrlichtEngine.h"
//
//IRobot::IRobot( IShip* ship, PlayerManager* mgr, boost::shared_ptr<NetworkBase> server ) : CCameraSceneNode( 0, 0, -1 )
//	, RobotShip_( ship )
//	, Manager( mgr )
//	, Server( server )
//{
//	// 创建机器人客户端
//	boost::shared_ptr<RobotClient> robotClient = boost::shared_ptr<RobotClient>( new RobotClient( server ) );
//	robotClient->SetID( RobotShip_->getID() );
//
//	//// 添加飞行行为
//	//auto fpsAni = new CSceneNodeAnimatorAircraftFPS( MyIrrlichtEngine::GetEngine()->GetDevice()->getCursorControl(), RobotShip_ );
//	//addAnimator( fpsAni );
//	//fpsAni->drop();
//
//	// 添加攻击行为
//	auto fireAni2 = new ShipFireAnimator( robotClient );
//	RobotShip_->addAnimator( fireAni2 );
//	fireAni2->drop();
//
//	// 添加飞船到玩家管理类
////	mgr->AddPlayer( RobotShip_->getID(), RobotShip_ );
//}
//
//
//
//IShip* IRobot::SearchTarget( int range )
//{
//	//auto players = Manager->GetPlayers();
//	//for ( auto player = players.begin(); player != players.end(); ++player )
//	//{
//	//	if ( *player == RobotShip_ || (*player)->getID() > 50 )	continue;
//
//	//	core::vector3df dir = (*player)->getPosition() - RobotShip_->getPosition();
//	//	if ( dir.getLength() < range )
//	//	{
//	//		setTarget( (*player)->getPosition() );
//	//		SendRotate( getRotation() );
//	//		return *player;
//	//	}
//	//}
//	return NULL;
//}
//
//void IRobot::SendMove( const vector3df& pos )
//{
//	RobotShip_->setPosition( getPosition() );
//
//	PACKAGE pack;
//	pack.SetCMD( HERO_MOVE );
//	HeroMove move( RobotShip_->getID(), pos.X, pos.Y, pos.Z );
//	pack.SetData( (char*)&move, sizeof( HeroMove ) );
//
//	Server->OnReceive( 0, pack );
//}
//
//void IRobot::SendRotate( const core::vector3df& rot )
//{
//	RobotShip_->setRotation( getRotation() );
//
//	PACKAGE pack;
//	pack.SetCMD( HERO_ROTATE );
//	HeroRotate rotate( RobotShip_->getID(), rot.X, rot.Y, rot.Z );
//	pack.SetData( (char*)&rotate, sizeof( HeroRotate ) );
//
//	Server->OnReceive( 0, pack );
//}
//
//void IRobot::DoLeftButtonUp()
//{
//	SEvent ev;
//
//	ev.EventType = EET_MOUSE_INPUT_EVENT;
//	ev.MouseInput.Event = EMIE_LMOUSE_LEFT_UP;
//
//	OnEvent( ev );
//}
//
//void IRobot::DoLeftButtonDown()
//{
//	SEvent ev;
//
//	ev.EventType = EET_MOUSE_INPUT_EVENT;
//	ev.MouseInput.Event = EMIE_LMOUSE_PRESSED_DOWN;	
//
//	OnEvent( ev );
//}
