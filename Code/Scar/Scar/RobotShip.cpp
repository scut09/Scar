#include "RobotShip.h"
#include "MyIrrlichtEngine.h"
#include "ExplosionMyself.h"

using namespace Network;

ShipAgentPlayer::ShipAgentPlayer( IShip* ship, PlayerManager* mgr, boost::shared_ptr<NetworkBase> server )
	: IAgentPlayer( ship, mgr, server ), State( Idle ), fireOnce( true ), ArmThreshold(0.f)
{
	lastArm = PlayerShip->GetArmor();
}

void ShipAgentPlayer::Update()
{

	if ( PlayerShip->GetArmor() <= 0.0)
	{
		// 放置到原点
		ExplosionMyself e(PlayerShip, PlayerShip->getAbsolutePosition());

		e.Explode();
		PlayerShip->setPosition( vector3df( 0.f, 0.f, 0.f ) );
		PlayerShip->SetShield(1000.f);
		PlayerShip->SetArmor(1000.f);
		e.EndExplode();

		return;
	}

	if (PlayerShip->GetArmor() < 1000.f)
	{
		if (PlayerShip->GetArmor() == lastArm)
		{
			ArmThreshold++;
		}
		if (ArmThreshold >= 50)
		{
			PlayerShip->SetArmor( PlayerShip->GetArmor() + 10 );
			lastArm = PlayerShip->GetArmor();
			ArmThreshold = 0.f;
		}
	}

	lastArm = PlayerShip->GetArmor();

	//SendMove( PlayerShip->getPosition() );

	u32 time = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
	//this->OnAnimate( time );

	PACKAGE p;
	boost::shared_ptr<IPlayer>	player;


	switch ( State )
	{
		
	case Idle:		// 空闲状态	
		if ( SearchTarget( player, 5000 ) )
		{
			State = Track;		// 进入追踪状态
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

	case Track:		// 追踪状态
		if ( SearchTarget( player, 2500 ) )
		{
			IShip* ship = player->GetShip();
			if ( ( ship->getPosition() - PlayerShip->getPosition() ).getLength() < 2500 )
			{
				State = Attack;		// 进入开火状态
				DoUnpress( KEY_KEY_W );
			}

			DoPress( KEY_KEY_W );
		}
		else
		{
			State = Idle;		// 回到空闲状态
			DoUnpress( KEY_KEY_W );
		}
		break;
		
	case Attack:	// 攻击状态
		if ( SearchTarget( player, 2500 ) )
		{
			IShip* ship = player->GetShip();

			if ( ( ship->getPosition() - PlayerShip->getPosition() ).getLength() < 200 )
			{
				DoUnpress( KEY_KEY_W );
				DoPress( KEY_KEY_S );	// 按下减速
			}
			else
			{
				DoUnpress( KEY_KEY_S );	// 松开减速
			}

			if ( fireOnce )
			{
				fireOnce = false;

				DoLeftButtonDown();	// 按下开火按键
			}
		}
		else
		{
			State = Idle;		// 回到空闲状态
			fireOnce = true;

			DoLeftButtonUp();		// 松开开火按键
		}
		break;
	}

	SendMove( PlayerShip->getPosition() );
	SendRotate( PlayerShip->getRotation() );
}
