#include "IRobot.h"
#include "MyIrrlichtEngine.h"

IRobot::IRobot( IShip* ship, PlayerManager* mgr, Network::NetworkBase* server ) : CCameraSceneNode( 0, 0, -1 )
	, RobotShip( ship )
	, Manager( mgr )
	, Server( server )
{
	State = Idle;
}

void IRobot::Update()
{
	RobotShip->setPosition( getPosition() );
	RobotShip->setRotation( getRotation() );

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

				SEvent ev;

				ev.EventType = EET_MOUSE_INPUT_EVENT;
				ev.MouseInput.Event = EMIE_LMOUSE_PRESSED_DOWN;	

				OnEvent( ev );
			}

		}
		else
		{
			State = Idle;
			fireOnce = true;

			SEvent ev;

			ev.EventType = EET_MOUSE_INPUT_EVENT;
			ev.MouseInput.Event = EMIE_LMOUSE_LEFT_UP;

			OnEvent( ev );

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

			PACKAGE pack;
			pack.SetCMD( HERO_ROTATE );
			HeroRotate rot( RobotShip->getID(), pos.X, pos.Y, pos.Z );
			pack.SetData( (char*)&rot, sizeof( HeroRotate ) );
			Server->OnReceive( 0, pack );

			return *player;
		}
	}
	return NULL;
}
