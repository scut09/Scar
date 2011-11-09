#include "RobotShip.h"
#include "MyIrrlichtEngine.h"

using namespace Network;

ShipAgentPlayer::ShipAgentPlayer( IShip* ship, PlayerManager* mgr, boost::shared_ptr<NetworkBase> server )
	: IAgentPlayer( ship, mgr, server ), State( Idle ), fireOnce( true )
{
}

void ShipAgentPlayer::Update()
{
	if ( PlayerShip->GetShield() < 1 )	return;	// ¹ÒÁË

	SendMove( PlayerShip->getPosition() );

	u32 time = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
	//this->OnAnimate( time );

	PACKAGE p;
	boost::shared_ptr<IPlayer>	player;


	switch ( State )
	{
		
	case Idle:		// ¿ÕÏÐ×´Ì¬	
		if ( SearchTarget( player, 5000 ) )
		{
			State = Track;		// ½øÈë×·×Ù×´Ì¬
		}
		//{
		//	DoPress( KEY_KEY_W );
		//	if ( getPosition().Z > 5000 || getPosition().Z < -5000 )
		//	{
		//		auto t = getTarget();
		//		t.Z = -t.Z;
		//		setTarget( t );
		//		SendRotate( getRotation() );
		//	}
		//}
		break;

	case Track:		// ×·×Ù×´Ì¬
		if ( SearchTarget( player, 2500 ) )
		{
			IShip* ship = player->GetShip();
			if ( ( ship->getPosition() - PlayerShip->getPosition() ).getLength() < 2500 )
			{
				State = Attack;		// ½øÈë¿ª»ð×´Ì¬
				DoUnpress( KEY_KEY_W );
			}

			DoPress( KEY_KEY_W );
		}
		else
		{
			State = Idle;		// »Øµ½¿ÕÏÐ×´Ì¬
			DoUnpress( KEY_KEY_W );
		}
		break;
		
	case Attack:	// ¹¥»÷×´Ì¬
		if ( SearchTarget( player, 2500 ) )
		{
			IShip* ship = player->GetShip();

			if ( ( ship->getPosition() - PlayerShip->getPosition() ).getLength() < 200 )
			{
				DoUnpress( KEY_KEY_W );
				DoPress( KEY_KEY_S );	// °´ÏÂ¼õËÙ
			}
			else
			{
				DoUnpress( KEY_KEY_S );	// ËÉ¿ª¼õËÙ
			}

			if ( fireOnce )
			{
				fireOnce = false;

				DoLeftButtonDown();	// °´ÏÂ¿ª»ð°´¼ü
			}
		}
		else
		{
			State = Idle;		// »Øµ½¿ÕÏÐ×´Ì¬
			fireOnce = true;

			DoLeftButtonUp();		// ËÉ¿ª¿ª»ð°´¼ü
		}
		break;
	}
}
