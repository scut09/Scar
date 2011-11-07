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
		// 空闲状态
	case Idle:			
		if ( IShip* ship = SearchTarget( 500 ) )
		{
			State = Fire;		// 进入开火状态

			setTarget( ship->getPosition() );

			SendRotate( getRotation() );
		}
		// 攻击状态
	case Fire:
		if ( IShip* ship = SearchTarget( 500 ) )
		{
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
	}
}
