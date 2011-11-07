#include "RobotShip.h"


RobotShip::RobotShip( IShip* ship, PlayerManager* mgr, std::shared_ptr<NetworkBase> server )
	: IRobot( ship, mgr, server ), State( Idle ), fireOnce( true )
{
}

void RobotShip::Update()
{
	if ( RobotShip_->GetShield() < 1 )	return;	// ����

	SendMove( getPosition() );

	u32 time = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
	this->OnAnimate( time );

	PACKAGE p;

	switch ( State )
	{
		
	case Idle:		// ����״̬	
		if ( IShip* ship = SearchTarget( 5000 ) )
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
		if ( IShip* ship = SearchTarget( 3000 ) )
		{
			if ( ( ship->getPosition() - RobotShip_->getPosition() ).getLength() < 2500 )
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
		if ( IShip* ship = SearchTarget( 2500 ) )
		{
			if ( ( ship->getPosition() - RobotShip_->getPosition() ).getLength() < 200 )
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
