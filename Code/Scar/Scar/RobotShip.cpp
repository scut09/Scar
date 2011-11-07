#include "RobotShip.h"


RobotShip::RobotShip( IShip* ship, PlayerManager* mgr, std::shared_ptr<NetworkBase> server )
	: IRobot( ship, mgr, server ), State( Idle ), fireOnce( true )
{
}

void RobotShip::Update()
{
	SendMove( getPosition() );

	u32 time = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
	this->OnAnimate( time );

	PACKAGE p;


	switch ( State )
	{
		// ����״̬
	case Idle:			
		if ( IShip* ship = SearchTarget( 500 ) )
		{
			State = Fire;		// ���뿪��״̬

			setTarget( ship->getPosition() );

			SendRotate( getRotation() );
		}
		// ����״̬
	case Fire:
		if ( IShip* ship = SearchTarget( 500 ) )
		{
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
	}
}
