#include "IRobot.h"
#include "MyIrrlichtEngine.h"

IRobot::IRobot( IShip* ship, PlayerManager* mgr, std::shared_ptr<NetworkBase> server ) : CCameraSceneNode( 0, 0, -1 )
	, RobotShip( ship )
	, Manager( mgr )
	, Server( server )
{
	State = Idle;
}

void IRobot::Update()
{
	SendMove( getPosition() );

	u32 time = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
	this->OnAnimate( time );

	PACKAGE p;

	static bool fireOnce = true;

	switch ( State )
	{
	case Idle:			
		if ( SearchTarget() )
			State = Fire;

	case Fire:
		if ( SearchTarget() )
		{
			if ( fireOnce )
			{
				fireOnce = false;

				DoLeftButtonDown();
			}

		}
		else
		{
			State = Idle;
			fireOnce = true;

			DoLeftButtonUp();
		}
	}

	//Server->OnReceive( 0, p );
}

IShip* IRobot::SearchTarget()
{
	auto players = Manager->GetPlayers();
	for ( auto player = players.begin(); player != players.end(); ++player )
	{
		if ( *player == RobotShip )	continue;

		core::vector3df dir = (*player)->getPosition() - RobotShip->getPosition();
		if ( dir.getLength() < 3500 )
		{
			core::vector3df pos = (*player)->getPosition();
			this->setTarget( (*player)->getPosition() );

			SendRotate( pos );

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
