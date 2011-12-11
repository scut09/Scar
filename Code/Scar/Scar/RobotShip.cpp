#include "RobotShip.h"
#include "MyIrrlichtEngine.h"
#include "ExplosionMyself.h"
#include "MultiplayerScene.h"
using namespace Network;

ShipAgentPlayer::ShipAgentPlayer( IShip* ship, PlayerManager* mgr, boost::shared_ptr<NetworkBase> server )
	: IAgentPlayer( ship, mgr, server ), State( Idle ), fireOnce( true ), TimePoint(0)
{
	TimePoint = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
}

void ShipAgentPlayer::Update()
{
	f32 PassedTime;
	if ( PlayerShip->GetArmor() <= 0.0)
	{
		// ���õ�ԭ��
		ExplosionMyself e(PlayerShip, PlayerShip->getAbsolutePosition());
		vector3df Pos;
		auto playerlist = static_cast<MultiplayerScene*>(MyIrrlichtEngine::GetEngine()->GetGameSceneManager()->GetCurrentGameScene())->m_playerManager->GetPlayers();
		bool canBreak = false;
		while (1)
		{
			for (auto it = playerlist.begin(); it != playerlist.end(); it++)
			{
				if (Pos.getDistanceFrom((*it)->GetShip()->getPosition()) < 200)
				{
					Pos.Z += 200;
					canBreak = false;
				}
			}
			if (canBreak)
			{
				break;
			}
			canBreak = true;
		}

		e.Explode();
		PlayerShip->setPosition( Pos );
		PlayerShip->SetShield(1000.f);
		PlayerShip->SetArmor(1000.f);
		e.EndExplode();

		return;
	}

	PassedTime = (f32)(MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime() - TimePoint);

	if (PassedTime >= 2000)
	{
		TimePoint =  MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
		if (PlayerShip->GetShield() < 1000.f)
		{
			PlayerShip->SetShield( PlayerShip->GetShield() + 10 );
		}

		if (PlayerShip->GetShield() > 1000.f)
		{
			PlayerShip->SetShield( 1000.f );
		}

	}


	//SendMove( PlayerShip->getPosition() );

	u32 time = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
	//this->OnAnimate( time );

	PACKAGE p;
	boost::shared_ptr<IPlayer>	player;


	switch ( State )
	{
		
	case Idle:		// ����״̬	
		if ( SearchTarget( player, 5000 ) )
		{
			State = Track;		// ����׷��״̬
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

	case Track:		// ׷��״̬
		if ( SearchTarget( player, 2500 ) )
		{
			IShip* ship = player->GetShip();
			if ( ( ship->getPosition() - PlayerShip->getPosition() ).getLength() < 2500 )
			{
				State = Attack;		// ���뿪��״̬
				DoUnpress( KEY_KEY_W );
			}

			DoPress( KEY_KEY_W );
		}
		else
		{
			State = Idle;		// �ص�����״̬
			DoUnpress( KEY_KEY_W );
		}
		break;
		
	case Attack:	// ����״̬
		if ( SearchTarget( player, 2500 ) )
		{
			IShip* ship = player->GetShip();

			if ( ( ship->getPosition() - PlayerShip->getPosition() ).getLength() < 200 )
			{
				DoUnpress( KEY_KEY_W );
				DoPress( KEY_KEY_S );	// ���¼���
			}
			else
			{
				DoUnpress( KEY_KEY_S );	// �ɿ�����
			}

			if ( fireOnce )
			{
				fireOnce = false;

				DoLeftButtonDown();	// ���¿��𰴼�
			}
		}
		else
		{
			State = Idle;		// �ص�����״̬
			fireOnce = true;

			DoLeftButtonUp();		// �ɿ����𰴼�
		}
		break;
	}

	SendMove( PlayerShip->getPosition() );
	SendRotate( PlayerShip->getRotation() );
}
