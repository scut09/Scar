/********************************************************************
创建时间: 2011-11-7   14:09
文件名:   RobotShip.h
作者:     华亮 Cedric Porter [ Stupid ET ]	
说明:     飞船机器人

*********************************************************************/

#ifndef RobotShip_h__
#define RobotShip_h__

#include "IRobot.h"



class RobotShip : public IRobot
{
public:
	enum RobotState
	{
		Fire,
		Idle
	};

public:
	RobotShip( IShip* ship, PlayerManager* mgr, std::shared_ptr<NetworkBase> server )
		: IRobot( ship, mgr, server )
	{
		State = Idle;
	}

	virtual void Update()
	{
		SendMove( getPosition() );

		u32 time = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
		this->OnAnimate( time );

		PACKAGE p;

		static bool fireOnce = true;

		switch ( State )
		{
			// 空闲状态
		case Idle:			
			if ( IShip* ship = SearchTarget() )
			{
				State = Fire;

				setTarget( ship->getPosition() );

				SendRotate( getRotation() );
			}
			// 攻击状态
		case Fire:
			if ( IShip* ship = SearchTarget() )
			{
				if ( fireOnce )
				{
					fireOnce = false;

					DoLeftButtonDown();	// 按下开火按键
				}
			}
			else
			{
				State = Idle;
				fireOnce = true;

				DoLeftButtonUp();		// 松开开火按键
			}
		}
	}

private:
	RobotState		State;

};
#endif // RobotShip_h__