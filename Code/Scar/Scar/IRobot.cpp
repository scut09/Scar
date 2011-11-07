#include "IRobot.h"
#include "MyIrrlichtEngine.h"
#include "Robot_Client.h"
#include "FireAnimator.h"

IRobot::IRobot( IShip* ship, PlayerManager* mgr, std::shared_ptr<NetworkBase> server ) : CCameraSceneNode( 0, 0, -1 )
	, RobotShip( ship )
	, Manager( mgr )
	, Server( server )
{

	std::shared_ptr<RobotClient> robotClient = std::shared_ptr<RobotClient>( new RobotClient( server ) );
	robotClient->SetID( ship->getID() );
	auto fireAni2 = new FireAnimator( ship, robotClient );
	addAnimator( fireAni2 );
	fireAni2->drop();

}



IShip* IRobot::SearchTarget( int range )
{
	auto players = Manager->GetPlayers();
	for ( auto player = players.begin(); player != players.end(); ++player )
	{
		if ( *player == RobotShip )	continue;

		core::vector3df dir = (*player)->getPosition() - RobotShip->getPosition();
		if ( dir.getLength() < range )
		{
			return *player;
		}
	}
	return NULL;
}

void IRobot::SendMove( const vector3df& pos )
{
	RobotShip->setPosition( getPosition() );

	PACKAGE pack;
	pack.SetCMD( HERO_MOVE );
	HeroMove move( RobotShip->getID(), pos.X, pos.Y, pos.Z );
	pack.SetData( (char*)&move, sizeof( HeroMove ) );

	Server->OnReceive( 0, pack );
}

void IRobot::SendRotate( const core::vector3df& rot )
{
	RobotShip->setRotation( getRotation() );

	PACKAGE pack;
	pack.SetCMD( HERO_ROTATE );
	HeroRotate rotate( RobotShip->getID(), rot.X, rot.Y, rot.Z );
	pack.SetData( (char*)&rotate, sizeof( HeroRotate ) );

	Server->OnReceive( 0, pack );
}

void IRobot::DoLeftButtonUp()
{
	SEvent ev;

	ev.EventType = EET_MOUSE_INPUT_EVENT;
	ev.MouseInput.Event = EMIE_LMOUSE_LEFT_UP;

	OnEvent( ev );
}

void IRobot::DoLeftButtonDown()
{
	SEvent ev;

	ev.EventType = EET_MOUSE_INPUT_EVENT;
	ev.MouseInput.Event = EMIE_LMOUSE_PRESSED_DOWN;	

	OnEvent( ev );
}
