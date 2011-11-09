#include "RobotShip.h"
#include "MyIrrlichtEngine.h"

using namespace Network;

ShipAgentPlayer::ShipAgentPlayer( IShip* ship, PlayerManager* mgr, boost::shared_ptr<NetworkBase> server )
	: IAgentPlayer( ship, mgr, server ), State( Idle ), fireOnce( true )
{
}

void ShipAgentPlayer::Update()
{
	if ( PlayerShip->GetShield() < 1 )	return;	// ����

	SendMove( PlayerShip->getPosition() );

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
}
