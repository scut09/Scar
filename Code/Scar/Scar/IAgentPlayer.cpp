#include "IAgentPlayer.h"
#include "MyIrrlichtEngine.h"
#include "GameBag.h"
#include "FireAnimator.h"
#include "Robot_Client.h"
#include "SceneNodeAnimatorAircraftFPS.h"

using namespace Network;


IAgentPlayer::IAgentPlayer( IShip* playerShip, PlayerManager* mgr, boost::shared_ptr<Network::NetworkBase> server )
	: IPlayer( playerShip ), Manager( mgr ), Server( server )
{
	// 创建机器人客户端
	boost::shared_ptr<RobotClient> robotClient = boost::shared_ptr<RobotClient>( new RobotClient( server ) );
	robotClient->SetID( GetID() );



	// 添加飞行行为
	auto fpsAni = new CSceneNodeAnimatorAircraftFPS( NULL );
	PlayerShip->addAnimator( fpsAni );
	fpsAni->drop();

	// 添加攻击行为
	auto fireAni2 = new ShipFireAnimator( robotClient );
	PlayerShip->addAnimator( fireAni2 );
	fireAni2->drop();
}


bool IAgentPlayer::SearchTarget( boost::shared_ptr<IPlayer>& outPlayer, int range )
{
	auto players = Manager->GetPlayers();
	for ( auto player = players.begin(); player != players.end(); ++player )
	{
		IShip* targetShip = (*player)->GetShip();
		if ( targetShip == PlayerShip || (*player)->GetID() > 50 )	continue;

		core::vector3df dir = targetShip->getPosition() - PlayerShip->getPosition();
		if ( dir.getLength() < range )
		{
			PlayerShip->setTarget( targetShip->getPosition() );
			SendRotate( PlayerShip->getRotation() );
			outPlayer = (*player);
			return true;
		}
	}
	return false;
}

void IAgentPlayer::SendMove( const vector3df& pos )
{
	//RobotShip_->setPosition( getPosition() );

	PACKAGE pack;
	pack.SetCMD( HERO_MOVE );
	HeroMove move( GetID(), pos.X, pos.Y, pos.Z );
	pack.SetData( (char*)&move, sizeof( HeroMove ) );

	Server->OnReceive( 0, pack );
}

void IAgentPlayer::SendRotate( const core::vector3df& rot )
{
	//RobotShip_->setRotation( getRotation() );

	PACKAGE pack;
	pack.SetCMD( HERO_ROTATE );
	HeroRotate rotate( GetID(), rot.X, rot.Y, rot.Z );
	pack.SetData( (char*)&rotate, sizeof( HeroRotate ) );

	Server->OnReceive( 0, pack );
}

void IAgentPlayer::DoLeftButtonUp()
{
	SEvent ev;

	ev.EventType = EET_MOUSE_INPUT_EVENT;
	ev.MouseInput.Event = EMIE_LMOUSE_LEFT_UP;

	OnEvent( ev );
}

void IAgentPlayer::DoLeftButtonDown()
{
	SEvent ev;

	ev.EventType = EET_MOUSE_INPUT_EVENT;
	ev.MouseInput.Event = EMIE_LMOUSE_PRESSED_DOWN;	

	OnEvent( ev );
}
